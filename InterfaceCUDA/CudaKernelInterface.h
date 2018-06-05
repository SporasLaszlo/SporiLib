#include <cuda_runtime.h>
//#define __CUDACC__

void CUDAINTERFACE_MedianFilter3x3(int width, int height, unsigned char *imgIn, unsigned char *imgOut, dim3 gridSize, dim3 blockSize);
void CUDAINTERFACE_MedianFilter3x3_1D(int width, int height, unsigned char *imgIn, unsigned char *imgOut, int gridSize, int blockSize);
void CUDAINTERFACE_CopyImage(unsigned char *imgIn, unsigned char *imgOut);