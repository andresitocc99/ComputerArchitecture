#ifndef __HYPERLCA_OPERATIONS__
#define __HYPERLCA_OPERATIONS__

#include "Configurations.h"
#include <CL/sycl.hpp>


void HyperLCA_transform(int blockIndex, unsigned short *ImgRef,	unsigned short *trasformOutputData);

void averagePixel(sycl::queue &q, sycl::buffer<unsigned short, 1> &imgRefBuf, sycl::buffer<int, 1> &centroidBuf, unsigned short *ImgRef, int *centroid);

void duplicateAndCentralizeImg(sycl::queue &q, sycl::buffer<unsigned short, 1> &imgRefBuf, sycl::buffer<int, 1> &centroidBuf, sycl::buffer<short, 1> &imgBuf, unsigned short *ImgRef, short *Img, int *centroid);

void brightness(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<long long, 1> &brightnessBuf, short *Img, int &maxIndex, long long &maxBrightness);

void quVectors(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &qVectorBuf, sycl::buffer<int, 1> &uVectorBuf, short *Img, int maxIndex, long long maxBrightness, int *qVector, int *uVector); 

void projectingImg(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &uVectorBuf, sycl::buffer<int, 1> &projectionBuf, short *Img, int *projection, int *uVector);

void subtractingInformation(sycl::queue &q, sycl::buffer<short, 1> &imgBuf, sycl::buffer<int, 1> &qVectorBuf, sycl::buffer<int, 1> &projectionBuf, short *Img, const int *projection, const int *qVector);


void writingCentroidResult(int *centroid, unsigned short *trasformOutputData);

void writingPixelResult(int &maxIndex, unsigned short *ImgRef,
	unsigned short *trasformOutputData, unsigned int lastOutputElement);

void writingProjectionResult(int *projection, unsigned short *trasformOutputData,
			     unsigned int lastOutputElement);


#endif
