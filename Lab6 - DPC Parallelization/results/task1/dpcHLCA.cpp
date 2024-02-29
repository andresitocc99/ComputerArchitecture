#include "HyperLCA_Transform_Operations.h"
#include <CL/sycl.hpp>


#ifdef VERBOSE
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#endif

void HyperLCA_transform(int blockIndex, unsigned short *ImgRef, unsigned short *trasformOutputData) {

#ifdef VERBOSE
  if (blockIndex == BLOCK_DBG || BLOCK_DBG==-1)
    cout << "BLOCK: " << blockIndex << std::endl;
#endif
  // Img copy of ImgRef in u shorts
  // centroid (Average pixel in u int)
  // qVector ("q" vector in float, nb elements)
  // uVector ("u" vector in float, nb elements)
  // projection ("projection vector obtained as u'*Img, np elements)
  // scaledProjection ("scaled projection in integer, np elements)
  // maxIndex (index of the next most representative pixel)
  // maxBrightness (brightness of the pixel corresponding with maxIndex)

  sycl::queue q(sycl::default_selector_v);

  short Img[BLOCK_SIZE * BANDS];	// 14.02 bits 
  int centroid[BANDS];				// 32.00 bits
  int qVector[BANDS];					// 20.12 bits
  int uVector[BANDS];					// 02.30 bits
  int projection[BLOCK_SIZE];				// 02.30 bits

  sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
  sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));
  sycl::buffer<short, 1> imgBuf(Img, sycl::range<1>(BLOCK_SIZE * BANDS));
  sycl::buffer<long long, 1> brightnessBuf(sycl::range<1>(BLOCK_SIZE));
  sycl::buffer<int, 1> qVectorBuf(qVector, sycl::range<1>(BANDS));
  sycl::buffer<int, 1> uVectorBuf(uVector, sycl::range<1>(BANDS));
  sycl::buffer<int, 1> projectionBuf(projection, sycl::range<1>(BLOCK_SIZE));



int maxIndex;				// 32.00 bits
long long maxBrightness;  	// 48.16 bits

unsigned int lastOutputElement = 0;
    
// Calculating the centroid pixel
averagePixel(q, imgRefBuf, centroidBuf, ImgRef, centroid);

  // --> Sending Average Pixel -->
  writingCentroidResult(centroid, trasformOutputData);
  lastOutputElement = BANDS;

  // Cast ImgRef to int values (16.16), copy it in Img and subtract the centroid pixel
  duplicateAndCentralizeImg(q, imgRefBuf, centroidBuf, imgBuf, ImgRef, Img, centroid);

  // Extracting the representative pixels and their projections
  for(int iter=0; iter<PMAX; iter++){
    // Calculating the brightness of each pixel	
    brightness(q, imgBuf, brightnessBuf,Img, maxIndex, maxBrightness);
    
    // Calculating "qVector" and "uVector"
    quVectors(q, imgBuf, qVectorBuf, uVectorBuf, Img, maxIndex, maxBrightness, qVector, uVector);
				
#ifdef VERBOSE
    if (blockIndex == BLOCK_DBG || BLOCK_DBG==-1){
      cout <<  maxIndex << endl;
    }
#endif

    // --> Sending Brightest Pixel -->
    writingPixelResult(maxIndex, ImgRef, trasformOutputData, lastOutputElement);
    lastOutputElement += BANDS;

    // Calculating the projection of "Img" into "uVector"
    projectingImg(q, imgBuf, uVectorBuf, projectionBuf,Img, projection, uVector);

    // --> Sending Scaled Projection -->
    writingProjectionResult(projection, trasformOutputData, lastOutputElement);
    lastOutputElement += BLOCK_SIZE;

    // Subtracting the information contained in projection from the image
    subtractingInformation(q, imgBuf, qVectorBuf, projectionBuf, Img, projection, qVector);
  }	
}

// ---------- HyperLCA Operators ---------- // 

// Calculating the average pixel of the frame (centroid pixel)
void averagePixel(sycl::queue &q, sycl::buffer<unsigned short, 1> &imgRefBuf, sycl::buffer<int, 1> &centroidBuf, unsigned short *ImgRef, int *centroid){
  
  sycl::range<1> workRange(BANDS);
  // Sending task to the queue for it execution in the device
  q.submit([&](sycl::handler& h) {
    // Accessing to the buffers
    auto imgAcc = imgRefBuf.get_access<sycl::access::mode::read>(h);
    auto centroidAcc = centroidBuf.get_access<sycl::access::mode::discard_write>(h);

    h.parallel_for(workRange, [=](sycl::id<1> bandId) {
        int sum = 0;
        for(int pixel = 0; pixel < BLOCK_SIZE; ++pixel) {
            int index = pixel * BANDS + bandId[0];
            sum += imgAcc[index];
        }
        centroidAcc[bandId] = sum / BLOCK_SIZE;
    });

  }); 
  q.wait();

  sycl::host_accessor readCentroid(centroidBuf, sycl::read_only);
  for (int i = 0; i < BANDS; ++i) {
      centroid[i] = readCentroid[i];
  }

}

// Subtracting the centroid pixel and create the Auxiliary Img (16.16)
void duplicateAndCentralizeImg(sycl::queue &q, sycl::buffer<unsigned short, 1> &imgRefBuf, sycl::buffer<int, 1> &centroidBuf, sycl::buffer<short, 1> &imgBuf, unsigned short *ImgRef, short *Img, int *centroid)
{
  // Send the task to the queue for execution in the device
  q.submit([&](sycl::handler& h) {
      // Buffer access
      auto imgRefAcc = imgRefBuf.get_access<sycl::access::mode::read>(h);
      auto imgAcc = imgBuf.get_access<sycl::access::mode::write>(h);
      auto centroidAcc = centroidBuf.get_access<sycl::access::mode::read>(h);

      // Running in parallel
      h.parallel_for(sycl::range<1>(BLOCK_SIZE * BANDS), [=](sycl::id<1> idx) {
          int pixel = idx[0] / BANDS;
          int band = idx[0] % BANDS;
          imgAcc[idx] = (imgRefAcc[pixel * BANDS + band] - centroidAcc[band]) << 2;
      });
  });
  q.wait();
  {
    sycl::host_accessor hostAccImg(imgBuf, sycl::read_only);
    for (size_t i = 0; i < BLOCK_SIZE * BANDS; ++i) {
      Img[i] = hostAccImg[i];
    }
  }

}

// Calculating the brightness of each pixel
void brightness(sycl::queue& q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<long long, 1> &brightnessBuf, short *Img, int& maxIndex, long long& maxBrightness) {

  q.submit([&](sycl::handler& h) {
      auto imgAcc = imgBuf.get_access<sycl::access::mode::read>(h);
      auto brightnessAcc = brightnessBuf.get_access<sycl::access::mode::write>(h);

      h.parallel_for(sycl::range<1>(BLOCK_SIZE), [=](sycl::id<1> id) {
          int pixel = id[0];
          long long sum = 0;
          for(int band = 0; band < BANDS; ++band) {
              long long value = imgAcc[pixel * BANDS + band];
              sum += (value * value) << 12;
          }
          brightnessAcc[pixel] = sum;
      });
  });
  q.wait();

  sycl::host_accessor brightnessHost(brightnessBuf, sycl::read_only);
  maxBrightness = 0;
  for (int i = 0; i < BLOCK_SIZE; ++i) {
      if (brightnessHost[i] > maxBrightness) {
          maxBrightness = brightnessHost[i];
          maxIndex = i;
      }
  }
}

// Calculating "qVector" and "uVector"
void quVectors(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &qVectorBuf, sycl::buffer<int, 1> &uVectorBuf, short *Img, int maxIndex, long long maxBrightness, int *qVector, int *uVector) {
  
  q.submit([&](sycl::handler &h) {
      auto imgAcc = imgBuf.get_access<sycl::access::mode::read>(h);
      auto qAcc = qVectorBuf.get_access<sycl::access::mode::write>(h);
      auto uAcc = uVectorBuf.get_access<sycl::access::mode::write>(h);

      h.parallel_for(sycl::range<1>(BANDS), [=](sycl::id<1> id) {
          int band = id[0];
          int index = maxIndex * BANDS + band;
          short qValue = imgAcc[index];
          qAcc[band] = qValue;

          long long uValueLong = static_cast<long long>(qValue) << 28;
          long long uValue = maxBrightness > 0 ? uValueLong / (maxBrightness >> 16) : 0;
          uAcc[band] = static_cast<int>(uValue);
      });
  }).wait();
  {
      sycl::host_accessor hostAccQ(qVectorBuf, sycl::read_only);
      sycl::host_accessor hostAccU(uVectorBuf, sycl::read_only);
      for (int i = 0; i < BANDS; ++i) {
          qVector[i] = hostAccQ[i];
          uVector[i] = hostAccU[i];
      }
  }
}

// Calculating the projection of "Img" into "uVector"
void projectingImg(sycl::queue& q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &uVectorBuf, sycl::buffer<int, 1> &projectionBuf, short *Img, int *projection, int *uVector) {

  q.submit([&](sycl::handler& h) {
      auto imgAcc = imgBuf.get_access<sycl::access::mode::read>(h);
      auto projAcc = projectionBuf.get_access<sycl::access::mode::write>(h);
      auto uVecAcc = uVectorBuf.get_access<sycl::access::mode::read>(h);

      h.parallel_for(sycl::range<1>(BLOCK_SIZE), [=](sycl::id<1> id) {
          int pixel = id[0];
          long long projectionValueLong = 0;
          for (int band = 0; band < BANDS; ++band) {
              long long uValueLong = uVecAcc[band];
              long long imgValueLong = imgAcc[pixel * BANDS + band];
              projectionValueLong += uValueLong * imgValueLong;
          }
          projAcc[pixel] = static_cast<int>(projectionValueLong >> 2);
      });
  }).wait();

  {
      sycl::host_accessor hostProjAcc(projectionBuf, sycl::read_only);
      for (int i = 0; i < BLOCK_SIZE; ++i) {
          projection[i] = hostProjAcc[i];
      }
  }
}

// Subtracting the information contained in projection from the image
void subtractingInformation(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &qVectorBuf, sycl::buffer<int, 1> &projectionBuf, short *Img, const int *projection, const int *qVector) {

  q.submit([&](sycl::handler& h) {
      auto imgAcc = imgBuf.get_access<sycl::access::mode::read_write>(h);
      auto projAcc = projectionBuf.get_access<sycl::access::mode::read>(h);
      auto qVecAcc = qVectorBuf.get_access<sycl::access::mode::read>(h);

      h.parallel_for(sycl::range<1>(BLOCK_SIZE * BANDS), [=](sycl::id<1> idx) {
          int pixel = idx[0] / BANDS;
          int band = idx[0] % BANDS;
          long long qValueLong = qVecAcc[band];
          long long projValueLong = projAcc[pixel];

          // Performing the subtraction operation
          long long valueToSubtract = qValueLong * projValueLong >> 30; // Adjust shift according to precision
          imgAcc[idx] -= static_cast<short>(valueToSubtract);
      });
  }).wait();

  // No need for host_accessor here since we're modifying Img in-place and assume it's needed back on the host.
}

// --> Sending Average Pixel -->
void writingCentroidResult(int *centroid, unsigned short *trasformOutputData)
{
  for(int band=0; band<BANDS; band++){
    trasformOutputData[band] = (unsigned short) centroid[band];
  }
}

// --> Sending Brightest Pixel -->
void writingPixelResult(int &maxIndex, unsigned short *ImgRef,
	unsigned short *trasformOutputData, unsigned int lastOutputElement)
{
  for(int band=0; band<BANDS; band++){
    trasformOutputData[lastOutputElement+band] = ImgRef[maxIndex*BANDS + band];  
  }
}
	
// --> Sending Scaled Projection -->
void writingProjectionResult(int *projection, unsigned short *trasformOutputData,
			     unsigned int lastOutputElement)
{
  unsigned short projectionScalingFactor = (1<<(DR_PROJECTIONS-1))-1;

  long long projecitonLong;
  long long addition = 1<<30; // (considering the signe)
  long long positiveProjectionLong;
  long long scaledProjection;

  for(int pixel=0; pixel<BLOCK_SIZE; pixel++){
    projecitonLong = projection[pixel];
    positiveProjectionLong = projecitonLong + addition;
    scaledProjection = positiveProjectionLong * projectionScalingFactor;
			
    trasformOutputData[lastOutputElement+pixel] = scaledProjection >> 30; // (considering the signe)
  }
}