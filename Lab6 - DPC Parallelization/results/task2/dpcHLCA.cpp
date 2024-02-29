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

  sycl::queue q(sycl::gpu_selector_v);
  sycl::device d = q.get_device();

  std::cout << "Device: " << q.get_device().get_info<sycl::info::device::name>()<< std::endl;
  std::cout << "Version: " << d.get_info<sycl::info::device::version>()<< std::endl;
  std::cout << "Global memory size: " << d.get_info<sycl::info::device::global_mem_size>()<< std::endl;
  std::cout << "Global cache memory size: " << d.get_info<sycl::info::device::global_mem_cache_size>()<< std::endl;
  std::cout << "Max clock frequency: " << d.get_info<sycl::info::device::max_clock_frequency>()<< std::endl;
  
  
  short Img[BLOCK_SIZE * BANDS];	// 14.02 bits 
  int centroid[BANDS];				// 32.00 bits
  int qVector[BANDS];					// 20.12 bits
  int uVector[BANDS];					// 02.30 bits
  int projection[BLOCK_SIZE];				// 02.30 bits

int maxIndex;				// 32.00 bits
long long maxBrightness;  	// 48.16 bits

unsigned int lastOutputElement = 0;
    
// Calculating the centroid pixel
averagePixel(q, ImgRef, centroid);

// --> Sending Average Pixel -->
writingCentroidResult(centroid, trasformOutputData);
lastOutputElement = BANDS;

// Cast ImgRef to int values (16.16), copy it in Img and subtract the centroid pixel
duplicateAndCentralizeImg(ImgRef, Img, centroid);

  // Extracting the representative pixels and their projections
  for(int iter=0; iter<PMAX; iter++){
    // Calculating the brightness of each pixel	
    brighness(Img, maxIndex, maxBrightness);
    
    // Calculating "qVector" and "uVector"
    quVectors(Img, maxIndex, maxBrightness, qVector, uVector);
				
#ifdef VERBOSE
    if (blockIndex == BLOCK_DBG || BLOCK_DBG==-1){
      cout <<  maxIndex << endl;
    }
#endif

    // --> Sending Brightest Pixel -->
    writingPixelResult(maxIndex, ImgRef, trasformOutputData, lastOutputElement);
    lastOutputElement += BANDS;

    // Calculating the projection of "Img" into "uVector"
    projectingImg(Img, projection, uVector);

    // --> Sending Scaled Projection -->
    writingProjectionResult(projection, trasformOutputData, lastOutputElement);
    lastOutputElement += BLOCK_SIZE;

    // Subtracting the information contained in projection from the image
    subtractingInformation(Img, projection, qVector);
  }	
}

// ---------- HyperLCA Operators ---------- // 

// Calculating the average pixel of the frame (centroid pixel)
void averagePixel(sycl::queue &q, unsigned short *ImgRef, int *centroid){
  // Creating buffers for input and output data
  sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
  sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));
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
void duplicateAndCentralizeImg(unsigned short *ImgRef, short *Img, int *centroid)
{
  for(int pixel=0; pixel<BLOCK_SIZE; pixel++){
    for(int band=0; band<BANDS; band++){
      Img[pixel*BANDS + band] = ((short)(ImgRef[pixel*BANDS + band]) - (short)(centroid[band]))<<2;
    }
  } 
}

// Calculating the brightness of each pixel
void brighness(short *Img, int &maxIndex, long long &maxBrightness)
{
  maxBrightness = 0; // 48.16
  maxIndex = 0;

  unsigned long long actualBrightness;
  long long ImgValueLong;

  for(int pixel=0; pixel<BLOCK_SIZE; pixel++){
    // Computing the brightness of one pixel
    actualBrightness = 0;
    for(int band=0; band<BANDS; band++){	
      ImgValueLong = Img[pixel*BANDS + band]; // (62.02)
      actualBrightness += (ImgValueLong * ImgValueLong)<<12; 
      // (62.02) * (62.02) = 60.04 -> 60.04<<12 = 48.16
    }	

    // Comparing with the maximum value obtained
    if(actualBrightness > maxBrightness){
      maxIndex = pixel;
      maxBrightness = actualBrightness;
    }
  }
}	

// Calculating "qVector" and "uVector"
void quVectors(short *Img, int &maxIndex, long long &maxBrightness, int *qVector, int *uVector)
{

  for(int band=0; band<BANDS; band++){	
    // qVector (30.02)
    qVector[band] = Img[maxIndex*BANDS + band];

    // uVector (02.30)
    // Img (14.02) ; (long int)(Img) = (62.02) ; ImgValueLomg (34.30) -> ImgValueLong = ImgValue << 28
    long long ImgValueLong = Img[maxIndex*BANDS + band]; 
    ImgValueLong = ImgValueLong << 28; // -1 Considering the sign	
    uVector[band] = ImgValueLong / (maxBrightness >> 16);
  }
}

// Calculating the projection of "Img" into "uVector"
void projectingImg(short *Img, int *projection, int *uVector)
{
  long long uValueLong;
  long long ImgValueLong;
  long long projectionValueLong;
	
  for(int pixel=0; pixel<BLOCK_SIZE; pixel++){
    projectionValueLong = 0;
    for(int band=0; band<BANDS; band++){
      uValueLong = uVector[band];
      ImgValueLong = Img[pixel*BANDS + band];

      projectionValueLong += uValueLong * ImgValueLong; 
      // (34.30)*(64.00) = (34.30) -> (int)(34.30) = (2.30)
    }
    projection[pixel] = projectionValueLong>>2; // 2.30 (considering the signe)
  }
}

// Subtracting the information contained in projection from the image
void subtractingInformation(short *Img, int *projection, int *qVector)
{
  long long longValueToSubtract; // 20.44 bits
  long long qValueLong;
  long long projectionValueLong;
	
  for(int pixel=0; pixel<BLOCK_SIZE; pixel++) {
    for(int band=0; band<BANDS; band++)	{
      qValueLong = qVector[band];
      projectionValueLong = projection[pixel];

      // (62.02)*(34.30) = (32.32) ->  (32.32) >> 30 = (62.02) -> (short)(62.02) = 14.02
      longValueToSubtract   = qValueLong * projectionValueLong;
      Img[pixel*BANDS + band] -= longValueToSubtract >> 30; // 20.12 bits (considering the signe)
    }
  }
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