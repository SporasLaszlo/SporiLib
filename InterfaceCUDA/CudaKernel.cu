#include "CUDAKernelInterface.h"
#include <stdio.h>
#include <iostream>
//#include <fstream>


__global__ void cudaMedianFilter3x3(int width, int height, unsigned char *imgIn, unsigned char *imgOut)
{
    //int width = gridDim.x * blockDim.x;
    //int height = gridDim.y * blockDim.y;

    //__shared__ unsigned char hhh[44];

    int x = blockIdx.x*blockDim.x+threadIdx.x;
    int y = blockIdx.y*blockDim.y+threadIdx.y;

    if ((-1 < x - 1) && (-1 < y - 1) && (x + 1 < width) && (y + 1 < height))
	{
		//uchar arrayBuffer[9];
		unsigned char r0, r1, r2, r3, r4, r5, r6, r7, r8;

		const int iOffset = y * width;
		const int iPrev = iOffset - width;
		const int iNext = iOffset + width;

		//// get pixels within aperture
		r0 = imgIn[iPrev + x - 1];
		r1 = imgIn[iPrev + x];
		r2 = imgIn[iPrev + x + 1];

		r3 = imgIn[iOffset + x - 1];
		r4 = imgIn[iOffset + x];
		r5 = imgIn[iOffset + x + 1];

		r6 = imgIn[iNext + x - 1];
		r7 = imgIn[iNext + x];
		r8 = imgIn[iNext + x + 1];

		unsigned char ucharMin = min(r0, r1);
		unsigned char ucharMax = max(r0, r1);
		r0 = ucharMin;
		r1 = ucharMax;

		ucharMin = min(r3, r2);
		ucharMax = max(r3, r2);
		r3 = ucharMin;
		r2 = ucharMax;

		ucharMin = min(r2, r0);
		ucharMax = max(r2, r0);
		r2 = ucharMin;
		r0 = ucharMax;

		ucharMin = min(r3, r1);
		ucharMax = max(r3, r1);
		r3 = ucharMin;
		r1 = ucharMax;

		ucharMin = min(r1, r0);
		ucharMax = max(r1, r0);
		r1 = ucharMin;
		r0 = ucharMax;

		ucharMin = min(r3, r2);
		ucharMax = max(r3, r2);
		r3 = ucharMin;
		r2 = ucharMax;

		ucharMin = min(r5, r4);
		ucharMax = max(r5, r4);
		r5 = ucharMin;
		r4 = ucharMax;

		ucharMin = min(r7, r8);
		ucharMax = max(r7, r8);
		r7 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r6, r8);
		ucharMax = max(r6, r8);
		r6 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r6, r7);
		ucharMax = max(r6, r7);
		r6 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r4, r8);
		ucharMax = max(r4, r8);
		r4 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r4, r6);
		ucharMax = max(r4, r6);
		r4 = ucharMin;
		r6 = ucharMax;

		ucharMin = min(r5, r7);
		ucharMax = max(r5, r7);
		r5 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r4, r5);
		ucharMax = max(r4, r5);
		r4 = ucharMin;
		r5 = ucharMax;

		ucharMin = min(r6, r7);
		ucharMax = max(r6, r7);
		r6 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r0, r8);
		ucharMax = max(r0, r8);
		r0 = ucharMin;
		r8 = ucharMax;

		r4 = max(r0, r4);
		r5 = max(r1, r5);

		r6 = max(r2, r6);
		r7 = max(r3, r7);

		r4 = min(r4, r6);
		r5 = min(r5, r7);

		// store found median into result
		//result |= min(r4, r5);

		imgOut[iOffset + x] = min(r4, r5);
    }
    else if (-1 < x && x < width && -1 < y && y < height)
	{
		int centerPos = width * y + x;
		imgOut[centerPos] = imgIn[centerPos];
	}
}
void CUDAINTERFACE_MedianFilter3x3(int width, int height, unsigned char *imgIn, unsigned char *imgOut, dim3 gridSize, dim3 blockSize)
{
    //dim3 grid(4, 256); //ennyi block unk lesz
    //dim3 block(128, 2); //ennyi thread lesz egy block ban (CUDA ban egy blockhoz max 1024 thread lehet, regebbi verziokban 512)

    //int blockS;
    //int minGridS;
    //
    //cudaOccupancyMaxPotentialBlockSize( &minGridS, &blockS, 
    //                                    cudaMedianFilter3x3, 0, 0); 
    //cudaDeviceSynchronize(); 
    //
    //int maxActiveBlocks;
    //cudaOccupancyMaxActiveBlocksPerMultiprocessor( &maxActiveBlocks, 
    //                                               cudaMedianFilter3x3, blockS, 
    //                                               0);
    //int device;
    //cudaDeviceProp props;
    //cudaGetDevice(&device);
    //cudaGetDeviceProperties(&props, device);
    //
    //float occupancy = (maxActiveBlocks * blockS / props.warpSize) / 
    //                (float)(props.maxThreadsPerMultiProcessor / 
    //                        props.warpSize);
    //
    //printf("Launched blocks of size %d. Theoretical occupancy: %f\n", blockS, occupancy);
    //std::cout << "Min Grid Size: ";
    //std::cout << minGridS << std::endl;
    //
    //std::cout << "Max active block Size: ";
    //std::cout << maxActiveBlocks << std::endl;
    //
    //std::cout << "Multi proc Size: ";
    //std::cout << props.maxThreadsPerMultiProcessor << std::endl;
    //
    //std::cout << "Warp Size: ";
    //std::cout << props.warpSize << std::endl;


    cudaMedianFilter3x3<<<gridSize, blockSize>>>(width, height, imgIn, imgOut);
}

__global__ void cudaCopyImage(unsigned char *imgIn, unsigned char *imgOut)
{
    int width = gridDim.x * blockDim.x;
    //int height = gridDim.y * blockDim.y;

    int x = blockIdx.x*blockDim.x+threadIdx.x;
    int y = blockIdx.y*blockDim.y+threadIdx.y;

    int pos = width * y + x;
	imgOut[pos] = imgIn[pos];
}
void CUDAINTERFACE_CopyImage(unsigned char *imgIn, unsigned char *imgOut)
{
    dim3 grid(4, 256); //ennyi block unk lesz
    dim3 block(128, 2); //ennyi thread lesz egy block ban (CUDA ban egy blockhoz max 1024 thread lehet)
    cudaCopyImage<<<grid, block>>>(imgIn, imgOut);
}

__global__ void cudaMedianFilter3x3_1D(int width, int height, unsigned char *imgIn, unsigned char *imgOut)
{
    //int width = gridDim.x * blockDim.x;
    //int height = gridDim.y * blockDim.y;

    //__shared__ unsigned char hhh[44];

    //int x = blockIdx.x*blockDim.x+threadIdx.x;
    //int y = blockIdx.y*blockDim.y+threadIdx.y;

    int x = (blockIdx.x*blockDim.x + threadIdx.x) % width;
    int y = (blockIdx.x*blockDim.x + threadIdx.x) / width;

    if ((-1 < x - 1) && (-1 < y - 1) && (x + 1 < width) && (y + 1 < height))
	{
		//uchar arrayBuffer[9];
		unsigned char r0, r1, r2, r3, r4, r5, r6, r7, r8;

		const int iOffset = y * width;
		const int iPrev = iOffset - width;
		const int iNext = iOffset + width;

		//// get pixels within aperture
		r0 = imgIn[iPrev + x - 1];
		r1 = imgIn[iPrev + x];
		r2 = imgIn[iPrev + x + 1];

		r3 = imgIn[iOffset + x - 1];
		r4 = imgIn[iOffset + x];
		r5 = imgIn[iOffset + x + 1];

		r6 = imgIn[iNext + x - 1];
		r7 = imgIn[iNext + x];
		r8 = imgIn[iNext + x + 1];

		unsigned char ucharMin = min(r0, r1);
		unsigned char ucharMax = max(r0, r1);
		r0 = ucharMin;
		r1 = ucharMax;

		ucharMin = min(r3, r2);
		ucharMax = max(r3, r2);
		r3 = ucharMin;
		r2 = ucharMax;

		ucharMin = min(r2, r0);
		ucharMax = max(r2, r0);
		r2 = ucharMin;
		r0 = ucharMax;

		ucharMin = min(r3, r1);
		ucharMax = max(r3, r1);
		r3 = ucharMin;
		r1 = ucharMax;

		ucharMin = min(r1, r0);
		ucharMax = max(r1, r0);
		r1 = ucharMin;
		r0 = ucharMax;

		ucharMin = min(r3, r2);
		ucharMax = max(r3, r2);
		r3 = ucharMin;
		r2 = ucharMax;

		ucharMin = min(r5, r4);
		ucharMax = max(r5, r4);
		r5 = ucharMin;
		r4 = ucharMax;

		ucharMin = min(r7, r8);
		ucharMax = max(r7, r8);
		r7 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r6, r8);
		ucharMax = max(r6, r8);
		r6 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r6, r7);
		ucharMax = max(r6, r7);
		r6 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r4, r8);
		ucharMax = max(r4, r8);
		r4 = ucharMin;
		r8 = ucharMax;

		ucharMin = min(r4, r6);
		ucharMax = max(r4, r6);
		r4 = ucharMin;
		r6 = ucharMax;

		ucharMin = min(r5, r7);
		ucharMax = max(r5, r7);
		r5 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r4, r5);
		ucharMax = max(r4, r5);
		r4 = ucharMin;
		r5 = ucharMax;

		ucharMin = min(r6, r7);
		ucharMax = max(r6, r7);
		r6 = ucharMin;
		r7 = ucharMax;

		ucharMin = min(r0, r8);
		ucharMax = max(r0, r8);
		r0 = ucharMin;
		r8 = ucharMax;

		r4 = max(r0, r4);
		r5 = max(r1, r5);

		r6 = max(r2, r6);
		r7 = max(r3, r7);

		r4 = min(r4, r6);
		r5 = min(r5, r7);

		// store found median into result
		//result |= min(r4, r5);

		imgOut[iOffset + x] = min(r4, r5);
    }
    else if (-1 < x && x < width && -1 < y && y < height)
	{
		int centerPos = width * y + x;
		imgOut[centerPos] = imgIn[centerPos];
	}
}
void CUDAINTERFACE_MedianFilter3x3_1D(int width, int height, unsigned char *imgIn, unsigned char *imgOut, int gridSize, int blockSize)
{
    cudaMedianFilter3x3_1D<<<gridSize, blockSize>>>(width, height, imgIn, imgOut);
}