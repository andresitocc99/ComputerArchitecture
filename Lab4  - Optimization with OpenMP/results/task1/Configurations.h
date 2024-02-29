#ifndef __CFG_HYPERLCA__
#define __CFG_HYPERLCA__


// Input parameters
#define OUTPUT_FILE_NAME "compressedBitstream.bin"
#define INPUT_FILE_NAME "mission.bin"

#define DR_PROJECTIONS 16
#define BLOCK_SIZE 1024

#define COLUMNS 1024
#define LINES 1024
#define BANDS 180
#define PMAX 12


// Variables values obtained from the input parameters
#define NUMBER_OF_PIXELS (COLUMNS*LINES)
#define IMAGE_SIZE (COLUMNS*LINES*BANDS)


// libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#endif
