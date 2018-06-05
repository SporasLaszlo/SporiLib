//#pragma OPENCL EXTENSION cl_khr_fp64 : enable
//#define KERNELFULLSIZE

__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;

__kernel void vectorSum(__global const uchar *a, __global const uchar *b, __global uchar *c)
{
	int id = get_global_id(0);
	c[id] = (a[id] + b[id]) / 2;
}
__kernel void warpPerspective2D_8UC3(__global const float *HInv, __global const int *imgInWidth, __global const int *imgInHeight, __global const uchar *imgIn, __global const int *imgOutWidth, __global const int *imgOutHeight, __global uchar *imgOut)
{
	//int id = get_global_id(0);

	//int xOut = id % imgOutWidth[0];
	//int yOut = id / imgOutWidth[0];

	int xOut = get_global_id(0);
	int yOut = get_global_id(1);

	//double a = (double)xOut;

	float xFrom = (float)xOut * HInv[0] + (float)yOut * HInv[1] + (float)1 * HInv[2];
	float yFrom = (float)xOut * HInv[3] + (float)yOut * HInv[4] + (float)1 * HInv[5];
	float zFrom = (float)xOut * HInv[6] + (float)yOut * HInv[7] + (float)1 * HInv[8];

	xFrom = xFrom / zFrom;
	yFrom = yFrom / zFrom;

	int xIn = (int)xFrom;
	int yIn = (int)yFrom;

	if ((xIn > -1) && (yIn > -1) && (xIn < imgInWidth[0]) && (yIn < imgInHeight[0]))
	{

		int inPos = 3 * imgInWidth[0] * yIn + 3 * xIn;
		int outPos = 3 * imgOutWidth[0] * yOut + 3 * xOut;

		imgOut[outPos] = imgIn[inPos];
		imgOut[outPos + 1] = imgIn[inPos + 1];
		imgOut[outPos + 2] = imgIn[inPos + 2];
	}
	else
	{
		int outPos = 3 * imgOutWidth[0] * yOut + 3 * xOut;

		imgOut[outPos] = 0;
		imgOut[outPos + 1] = 0;
		imgOut[outPos + 2] = 0;
	}
}
__kernel void warpPerspective_8UC3(__global const float *HInv, __global const int *imgInWidth, __global const int *imgInHeight, __global const uchar *imgIn, __global const int *imgOutWidth, __global const int *imgOutHeight, __global uchar *imgOut)
{
	int id = get_global_id(0);

	int xOut = id % imgOutWidth[0];
	int yOut = id / imgOutWidth[0];
	
	//int xOut = get_global_id(0);
	//int yOut = get_global_id(1);

	//double a = (double)xOut;

	float xFrom = (float)xOut * HInv[0] + (float)yOut * HInv[1] + (float)1 * HInv[2];
	float yFrom = (float)xOut * HInv[3] + (float)yOut * HInv[4] + (float)1 * HInv[5];
	float zFrom = (float)xOut * HInv[6] + (float)yOut * HInv[7] + (float)1 * HInv[8];

	xFrom = xFrom / zFrom;
	yFrom = yFrom / zFrom;

	int xIn = (int)xFrom;
	int yIn = (int)yFrom;

	if ((xIn > -1) && (yIn > -1) && (xIn < imgInWidth[0]) && (yIn < imgInHeight[0]))
	{
		
		int inPos = 3 * imgInWidth[0] * yIn + 3 * xIn;
		int outPos = 3 * id;

		imgOut[outPos] = imgIn[inPos];
		imgOut[outPos + 1] = imgIn[inPos + 1];
		imgOut[outPos + 2] = imgIn[inPos + 2];
	}
	else
	{
		//int inPos = 3 * imgInWidth[0] * yIn + 3 * xIn;
		int outPos = 3 * id;

		imgOut[outPos] = 0;
		imgOut[outPos + 1] = 0;
		imgOut[outPos + 2] = 0;
	}
}
__kernel void valami(__global const uchar *a, __global const uchar *b, __global uchar *c)
{
	int id = get_global_id(0);

	int valtozo;

	for (int i = 0; i < 1000; ++i)
	{
		valtozo = a[id] + b[id];
	}

	c[id] = valtozo;

	//c[id] = 127;
	//c[id] = a[id] + b[id];
}
__kernel void copyImage_8UC1(__global const uchar *in, __global uchar *out)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	//out[x] = 127;
	//const int2 pos = { get_global_id(0), get_global_id(1) };

	//uint4 val = read_imageui(src_image, sampler, pos);
	//write_imageui(dst_image, pos, val);
	//dst_image[x][y] = src_image[x][y];

	out[640 * y + x] = 127;
}
__kernel void copyImage2D_8UC1(__read_only image2d_t in, __global uchar *out)
{
	//int x = get_global_id(0);
	//int y = get_global_id(1);

	const int2 pos = { get_global_id(0), get_global_id(1) };

	const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_LINEAR;

	uchar value = read_imageui(in, sampler, pos).x;

	out[640 * pos.y + pos.x] = value;

	//write_imagei(output, pos, value)

	//out[x] = 127;
	//const int2 pos = { get_global_id(0), get_global_id(1) };

	//uint4 val = read_imageui(src_image, sampler, pos);
	//write_imageui(dst_image, pos, val);
	//dst_image[x][y] = src_image[x][y];

	//out[640 * y + x] = 127;
}
__kernel void argumentumTestHomography(__global const float *HInv, const int imgInWidth, const int imgInHeight, __global const uchar *imgIn, const int imgOutWidth, const int imgOutHeight, __global uchar *imgOut)
{
	//
	int xOut = get_global_id(0);
	int yOut = get_global_id(1);

	float xFrom = (float)xOut * HInv[0] + (float)yOut * HInv[1] + (float)1 * HInv[2];
	float yFrom = (float)xOut * HInv[3] + (float)yOut * HInv[4] + (float)1 * HInv[5];
	float zFrom = (float)xOut * HInv[6] + (float)yOut * HInv[7] + (float)1 * HInv[8];

	xFrom = xFrom / zFrom;
	yFrom = yFrom / zFrom;

	int xIn = (int)xFrom;
	int yIn = (int)yFrom;

	////
	if ((xIn > -1) && (yIn > -1) && (xIn < imgInWidth) && (yIn < imgInHeight))
	{

		int inPos = 3 * imgInWidth * yIn + 3 * xIn;
		int outPos = 3 * imgOutWidth * yOut + 3 * xOut;

		imgOut[outPos] = imgIn[inPos];
		imgOut[outPos + 1] = imgIn[inPos + 1];
		imgOut[outPos + 2] = imgIn[inPos + 2];
	}
	else
	{
		int outPos = 3 * imgOutWidth * yOut + 3 * xOut;

		imgOut[outPos] = 0;
		imgOut[outPos + 1] = 0;
		imgOut[outPos + 2] = 0;
	}
}

//__kernel void medianFilter_2NDRange_8UC1(const int imgWidth, const int imgHeight, __global const uchar *imgIn, __global uchar *imgOut, const int filterKernelRange, const int filterKernelSize, const int filterKernelFullSize)//, __local uchar *arrayBuffer)
//{
//	int x = get_global_id(0);
//	int y = get_global_id(1);
//
//	uchar arrayBuffer[KERNELFULLSIZE];
//
//	//uchar a[kernelFullSize];
//
//	if ((-1 < x - filterKernelRange) && (-1 < y - filterKernelRange) && (x + filterKernelRange < imgWidth) && (y + filterKernelRange < imgHeight))
//	{
//		int pos;// = imgHeight * y + x;
//		int iter = 0;
//
//		//barrier(CLK_LOCAL_MEM_FENCE);
//
//		for (int j = 0; j < filterKernelSize; ++j)
//		{
//			pos = imgWidth * (y - filterKernelRange + j) + x - filterKernelRange;
//			for (int i = 0; i < filterKernelSize; ++i)
//			{
//				arrayBuffer[iter] = imgIn[pos];
//				iter++;
//				pos++;
//			}
//		}
//
//		//Modified Boubble Sors
//		for (int i = 0; i < filterKernelFullSize / 2 + 1; ++i)
//		{
//			for (int j = 0; j < filterKernelFullSize - 1; ++j)
//			{
//				if (arrayBuffer[j] > arrayBuffer[j + 1])
//				{
//					uchar temp = arrayBuffer[j + 1];
//					arrayBuffer[j + 1] = arrayBuffer[j];
//					arrayBuffer[j] = temp;
//				}
//			}
//		}
//
//		pos = imgWidth * y + x;
//
//		imgOut[pos] = arrayBuffer[4];
//		//barrier(CLK_LOCAL_MEM_FENCE);
//	}
//	else
//	{
//		int pos = imgWidth * y + x;
//		imgOut[pos] = imgIn[pos];
//	}
//}