#ifndef __HYPERLCA_OPERATIONS__
#define __HYPERLCA_OPERATIONS__

#include "Configurations.h"


void HyperLCA_transform(int blockIndex, unsigned short *ImgRef,
			unsigned short *trasformOutputData);



void averagePixel(unsigned short *ImgRef, int *centroid);

void duplicateAndCentralizeImg(unsigned short *ImgRef, short *Img, int *centroid);



void brighness(short *Img, int &maxIndex, long long &maxBrightness);

void quVectors(short *Img, int &maxIndex, long long &maxBrightness, int *qVector, int *uVector);

void projectingImg(short *Img, int *projection, int *uVector);

void subtractingInformation(short *Img, int *projection, int *qVector);



void writingCentroidResult(int *centroid, unsigned short *trasformOutputData);

void writingPixelResult(int &maxIndex, unsigned short *ImgRef,
	unsigned short *trasformOutputData, unsigned int lastOutputElement);

void writingProjectionResult(int *projection, unsigned short *trasformOutputData,
			     unsigned int lastOutputElement);


#endif
