#ifdef VERBOSE
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/stat.h> 
#include <sys/types.h> 

using namespace std;
#endif


#include "HyperLCA_Transform_Operations.h"


// --- Function Signatures
void read_Integer_Matrix(char* inputFileName, unsigned short *input_img);
void write_binary_file(char* OutputFileName, unsigned short *compressed_stream, unsigned int written_bytes);
void runCompressor(unsigned short *input_img, char* OutputFileName);		


// --- Main
int main(int argc, char* argv[])
{
#ifdef VERBOSE
  mkdir("output", 0777);
#endif

  // Input Img
  unsigned short *input_img;
  input_img = (unsigned short *)malloc(sizeof(unsigned short)*IMAGE_SIZE);
  //unsigned short input_img[IMAGE_SIZE];  
  
  // Read the Img
  read_Integer_Matrix((char*)INPUT_FILE_NAME, input_img);

  // Run the compressor
  runCompressor(input_img, (char*)OUTPUT_FILE_NAME);

  //Write compressed stream
  // It is done for each block
  
  printf("\n -- Finished OK -- \n\n\n");

  free(input_img);
	
  return 0;	
}


void read_Integer_Matrix(char* inputFileName, unsigned short *input_img)
{
  FILE * inputFile = fopen(inputFileName, "r+b");
  
  int numberOfReadElement = 0;
  int bytesPerElement = 2;

  unsigned short readElement;
  
  while ( numberOfReadElement < IMAGE_SIZE) {
    fread(&readElement, bytesPerElement, 1, inputFile);
    input_img[numberOfReadElement] = (unsigned short)readElement;
    numberOfReadElement++;
  }
  fclose (inputFile);
}


// Function for writting one specific binary bitsream to a file
void write_binary_file(char* OutputFileName, unsigned short *compressed_stream, unsigned int nbytes)
{
  FILE * outputFile = fopen(OutputFileName, "a+w+b");
  fwrite (compressed_stream , sizeof(short), nbytes, outputFile);
  fclose (outputFile);
}



// Function for executing the process
void runCompressor(unsigned short *input_img, char* OutputFileName)		
{
  // Initialize and declare the variables
  unsigned int nBlocks = (COLUMNS*LINES) / BLOCK_SIZE;
  unsigned int nInputElementsPerBlock = BLOCK_SIZE*BANDS;
  
  unsigned short input_block[BLOCK_SIZE * BANDS];	
  unsigned short trasformOutputData[BANDS+(BANDS + BLOCK_SIZE)*PMAX];
  
  unsigned int inputIndex = 0;

  
  for(int blockIndex = 0; blockIndex < nBlocks; blockIndex++){
    // Creating the block vector
    for(int elementIndex=0; elementIndex<nInputElementsPerBlock; elementIndex++){
      input_block[ elementIndex ] = input_img[ inputIndex + elementIndex ];
    }
    inputIndex += nInputElementsPerBlock;
		
    HyperLCA_transform(blockIndex, input_block, trasformOutputData);

		
#ifdef VERBOSE
    if (blockIndex == BLOCK_DBG || BLOCK_DBG==-1){
      stringstream filenameG;
      filenameG << "output/b" << blockIndex << ".txt";
      ofstream goldenFile;
      goldenFile.open(filenameG.str());
      for(int it=0; it !=BANDS+((BLOCK_SIZE+BANDS)*PMAX); it++)
	goldenFile << trasformOutputData[it] << endl;
      goldenFile.close();
    }
#endif
		
    // Write the block bitstream to a file
    write_binary_file(OutputFileName, trasformOutputData, (BANDS+(BANDS+BLOCK_SIZE)*PMAX));
  }
}
