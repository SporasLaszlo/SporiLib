__kernel void medianFilter_3x3_2NDRange_8UC1(__global uchar *imgIn, __global uchar *imgOut, int width, int height)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);

	//const int width = get_global_size(0);
	//const int height = get_global_size(0);

	if ((-1 < x - 1) && (-1 < y - 1) && (x + 1 < width) && (y + 1 < height))
	{
		//uchar arrayBuffer[9];
		uchar r0, r1, r2, r3, r4, r5, r6, r7, r8;

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

		uchar ucharMin = min(r0, r1);
		uchar ucharMax = max(r0, r1);
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

		//// get pixels within aperture
		//r0 = imgIn[iPrev + x - 1];
		//r1 = imgIn[iPrev + x];
		//r2 = imgIn[iPrev + x + 1];

		//r3 = imgIn[iOffset + x - 1];
		//r4 = imgIn[iOffset + x];
		//r5 = imgIn[iOffset + x + 1];

		//r6 = imgIn[iNext + x - 1];
		//r7 = imgIn[iNext + x];
		//r8 = imgIn[iNext + x + 1];

		//uchar tmp;
		////uchar ucharMin;// = min(r0, r1);
		////uchar ucharMax;// = max(r0, r1);
		////r0 = ucharMin;
		////r1 = ucharMax;
		//if (r0 > r1)
		//{
		//	tmp = r0;
		//	r0 = r1;
		//	r1 = tmp;
		//}

		////ucharMin = min(r3, r2);
		////ucharMax = max(r3, r2);
		////r3 = ucharMin;
		////r2 = ucharMax;
		//if (r2 < r3)
		//{
		//	tmp = r2;
		//	r2 = r3;
		//	r3 = tmp;
		//}

		////ucharMin = min(r2, r0);
		////ucharMax = max(r2, r0);
		////r2 = ucharMin;
		////r0 = ucharMax;
		//if (r0 < r2)
		//{
		//	tmp = r0;
		//	r0 = r2;
		//	r2 = tmp;
		//}

		////ucharMin = min(r3, r1);
		////ucharMax = max(r3, r1);
		////r3 = ucharMin;
		////r1 = ucharMax;
		//if (r1 < r3)
		//{
		//	tmp = r1;
		//	r1 = r3;
		//	r3 = tmp;
		//}

		////ucharMin = min(r1, r0);
		////ucharMax = max(r1, r0);
		////r1 = ucharMin;
		////r0 = ucharMax;
		//if (r0 < r1)
		//{
		//	tmp = r0;
		//	r0 = r1;
		//	r1 = tmp;
		//}

		////ucharMin = min(r3, r2);
		////ucharMax = max(r3, r2);
		////r3 = ucharMin;
		////r2 = ucharMax;
		//if (r2 < r3)
		//{
		//	tmp = r2;
		//	r2 = r3;
		//	r3 = tmp;
		//}

		////ucharMin = min(r5, r4);
		////ucharMax = max(r5, r4);
		////r5 = ucharMin;
		////r4 = ucharMax;
		//if (r4 < r5)
		//{
		//	tmp = r4;
		//	r4 = r5;
		//	r5 = tmp;
		//}

		////ucharMin = min(r7, r8);
		////ucharMax = max(r7, r8);
		////r7 = ucharMin;
		////r8 = ucharMax;
		//if (r7 > r8)
		//{
		//	tmp = r7;
		//	r7 = r8;
		//	r8 = tmp;
		//}

		////ucharMin = min(r6, r8);
		////ucharMax = max(r6, r8);
		////r6 = ucharMin;
		////r8 = ucharMax;
		//if (r6 > r8)
		//{
		//	tmp = r6;
		//	r6 = r8;
		//	r8 = tmp;
		//}

		////ucharMin = min(r6, r7);
		////ucharMax = max(r6, r7);
		////r6 = ucharMin;
		////r7 = ucharMax;
		//if (r6 > r7)
		//{
		//	tmp = r6;
		//	r6 = r7;
		//	r7 = tmp;
		//}

		////ucharMin = min(r4, r8);
		////ucharMax = max(r4, r8);
		////r4 = ucharMin;
		////r8 = ucharMax;
		//if (r4 > r8)
		//{
		//	tmp = r4;
		//	r4 = r8;
		//	r8 = tmp;
		//}

		////ucharMin = min(r4, r6);
		////ucharMax = max(r4, r6);
		////r4 = ucharMin;
		////r6 = ucharMax;
		//if (r4 > r6)
		//{
		//	tmp = r4;
		//	r4 = r6;
		//	r6 = tmp;
		//}

		////ucharMin = min(r5, r7);
		////ucharMax = max(r5, r7);
		////r5 = ucharMin;
		////r7 = ucharMax;
		//if (r5 > r7)
		//{
		//	tmp = r5;
		//	r5 = r7;
		//	r7 = tmp;
		//}

		////ucharMin = min(r4, r5);
		////ucharMax = max(r4, r5);
		////r4 = ucharMin;
		////r5 = ucharMax;
		//if (r4 > r5)
		//{
		//	tmp = r4;
		//	r4 = r5;
		//	r5 = tmp;
		//}

		////ucharMin = min(r6, r7);
		////ucharMax = max(r6, r7);
		////r6 = ucharMin;
		////r7 = ucharMax;
		//if (r6 > r7)
		//{
		//	tmp = r6;
		//	r6 = r7;
		//	r7 = tmp;
		//}

		////ucharMin = min(r0, r8);
		////ucharMax = max(r0, r8);
		////r0 = ucharMin;
		////r8 = ucharMax;
		//if (r0 > r8)
		//{
		//	tmp = r0;
		//	r0 = r8;
		//	r8 = tmp;
		//}

		////r4 = max(r0, r4);
		////r5 = max(r1, r5);
		//if (r0 > r4)
		//{
		//	r4 = r0;
		//}
		//if (r1 > r5)
		//{
		//	r5 = r1;
		//}

		////r6 = max(r2, r6);
		////r7 = max(r3, r7);
		//if (r2 > r6)
		//{
		//	r6 = r2;
		//}
		//if (r3 > r7)
		//{
		//	r7 = r3;
		//}

		////r4 = min(r4, r6);
		////r5 = min(r5, r7);
		//if (r4 > r6)
		//{
		//	r4 = r6;
		//}
		//if (r5 > r7)
		//{
		//	r5 = r7;
		//}

		//// store found median into result
		////result |= min(r4, r5);
		//if (r4 < r5)
		//	imgOut[iOffset + x] = r4;
		//else
		//	imgOut[iOffset + x] = r5;


		////Bubble
		////1.
		//uchar ucharMin = min(r0, r1);
		//uchar ucharMax = max(r0, r1);
		//r0 = ucharMin;
		//r1 = ucharMax;

		//ucharMin = min(r1, r2);
		//ucharMax = max(r1, r2);
		//r1 = ucharMin;
		//r2 = ucharMax;

		//ucharMin = min(r2, r3);
		//ucharMax = max(r2, r3);
		//r2 = ucharMin;
		//r3 = ucharMax;

		//ucharMin = min(r3, r4);
		//ucharMax = max(r3, r4);
		//r3 = ucharMin;
		//r4 = ucharMax;

		//ucharMin = min(r4, r5);
		//ucharMax = max(r4, r5);
		//r4 = ucharMin;
		//r5 = ucharMax;

		//ucharMin = min(r5, r6);
		//ucharMax = max(r5, r6);
		//r5 = ucharMin;
		//r6 = ucharMax;

		//ucharMin = min(r6, r7);
		//ucharMax = max(r6, r7);
		//r6 = ucharMin;
		//r7 = ucharMax;

		//ucharMin = min(r7, r8);
		//ucharMax = max(r7, r8);
		//r7 = ucharMin;
		//r8 = ucharMax;

		////2.
		//ucharMin = min(r0, r1);
		//ucharMax = max(r0, r1);
		//r0 = ucharMin;
		//r1 = ucharMax;

		//ucharMin = min(r1, r2);
		//ucharMax = max(r1, r2);
		//r1 = ucharMin;
		//r2 = ucharMax;

		//ucharMin = min(r2, r3);
		//ucharMax = max(r2, r3);
		//r2 = ucharMin;
		//r3 = ucharMax;

		//ucharMin = min(r3, r4);
		//ucharMax = max(r3, r4);
		//r3 = ucharMin;
		//r4 = ucharMax;

		//ucharMin = min(r4, r5);
		//ucharMax = max(r4, r5);
		//r4 = ucharMin;
		//r5 = ucharMax;

		//ucharMin = min(r5, r6);
		//ucharMax = max(r5, r6);
		//r5 = ucharMin;
		//r6 = ucharMax;

		//ucharMin = min(r6, r7);
		//ucharMax = max(r6, r7);
		//r6 = ucharMin;
		//r7 = ucharMax;

		//ucharMin = min(r7, r8);
		//ucharMax = max(r7, r8);
		//r7 = ucharMin;
		//r8 = ucharMax;

		////3.
		//ucharMin = min(r0, r1);
		//ucharMax = max(r0, r1);
		//r0 = ucharMin;
		//r1 = ucharMax;

		//ucharMin = min(r1, r2);
		//ucharMax = max(r1, r2);
		//r1 = ucharMin;
		//r2 = ucharMax;

		//ucharMin = min(r2, r3);
		//ucharMax = max(r2, r3);
		//r2 = ucharMin;
		//r3 = ucharMax;

		//ucharMin = min(r3, r4);
		//ucharMax = max(r3, r4);
		//r3 = ucharMin;
		//r4 = ucharMax;

		//ucharMin = min(r4, r5);
		//ucharMax = max(r4, r5);
		//r4 = ucharMin;
		//r5 = ucharMax;

		//ucharMin = min(r5, r6);
		//ucharMax = max(r5, r6);
		//r5 = ucharMin;
		//r6 = ucharMax;

		//ucharMin = min(r6, r7);
		//ucharMax = max(r6, r7);
		//r6 = ucharMin;
		//r7 = ucharMax;

		//ucharMin = min(r7, r8);
		//ucharMax = max(r7, r8);
		//r7 = ucharMin;
		//r8 = ucharMax;

		////4.
		//ucharMin = min(r0, r1);
		//ucharMax = max(r0, r1);
		//r0 = ucharMin;
		//r1 = ucharMax;

		//ucharMin = min(r1, r2);
		//ucharMax = max(r1, r2);
		//r1 = ucharMin;
		//r2 = ucharMax;

		//ucharMin = min(r2, r3);
		//ucharMax = max(r2, r3);
		//r2 = ucharMin;
		//r3 = ucharMax;

		//ucharMin = min(r3, r4);
		//ucharMax = max(r3, r4);
		//r3 = ucharMin;
		//r4 = ucharMax;

		//ucharMin = min(r4, r5);
		//ucharMax = max(r4, r5);
		//r4 = ucharMin;
		//r5 = ucharMax;

		//ucharMin = min(r5, r6);
		//ucharMax = max(r5, r6);
		//r5 = ucharMin;
		//r6 = ucharMax;

		//ucharMin = min(r6, r7);
		//ucharMax = max(r6, r7);
		//r6 = ucharMin;
		//r7 = ucharMax;

		//ucharMin = min(r7, r8);
		//ucharMax = max(r7, r8);
		//r7 = ucharMin;
		//r8 = ucharMax;

		////5.
		//ucharMin = min(r0, r1);
		//ucharMax = max(r0, r1);
		//r0 = ucharMin;
		//r1 = ucharMax;

		//ucharMin = min(r1, r2);
		//ucharMax = max(r1, r2);
		//r1 = ucharMin;
		//r2 = ucharMax;

		//ucharMin = min(r2, r3);
		//ucharMax = max(r2, r3);
		//r2 = ucharMin;
		//r3 = ucharMax;

		//ucharMin = min(r3, r4);
		//ucharMax = max(r3, r4);
		//r3 = ucharMin;
		//r4 = ucharMax;

		//ucharMin = min(r4, r5);
		//ucharMax = max(r4, r5);
		//r4 = ucharMin;
		//r5 = ucharMax;

		//ucharMin = min(r5, r6);
		//ucharMax = max(r5, r6);
		//r5 = ucharMin;
		//r6 = ucharMax;

		//ucharMin = min(r6, r7);
		//ucharMax = max(r6, r7);
		//r6 = ucharMin;
		//r7 = ucharMax;

		//ucharMin = min(r7, r8);
		//ucharMax = max(r7, r8);
		//r7 = ucharMin;
		//r8 = ucharMax;

		//imgOut[iOffset + x] = r4;
	}
	else if (-1 < x && x < width && -1 < y && y < height)
	{
		int centerPos = width * y + x;
		imgOut[centerPos] = imgIn[centerPos];
	}
}
//__kernel void medianFilter_2NDRange_8UC1(__constant int *imgWidth, __constant int *imgHeight, __global uchar *imgIn, __global uchar *imgOut, __constant int *filterKernelRange, __constant int *filterKernelSize, __constant int *filterKernelFullSize)//, __local uchar *arrayBuffer)
//{
//	int x = get_global_id(0);
//	int y = get_global_id(1);
//
//	int imgW = imgWidth[0];
//	int imgH = imgHeight[0];
//	//
//	int kRange = filterKernelRange[0];
//	int kSize = filterKernelSize[0];
//	int kFullSize = filterKernelFullSize[0];
//
//	//int imgW = 512;
//	//int imgH = 512;
//
//	//int kRange = 1;
//	//int kSize = 3;
//	//int kFullSize = 9;
//
//	//uchar arrayBuffer[9];
//	__private uchar arrayBuffer[KERNELFULLSIZE];
//	uchar temp;
//
//	if ((-1 < x - kRange) && (-1 < y - kRange) && (x + kRange < imgW) && (y + kRange < imgH))
//	{
//		int centerPos = imgW * y + x;;
//		int pos = centerPos - imgW - kRange;
//		int iter = 0;
//
//		for (int i = 0; i < kFullSize / 2 + 1; ++i)
//		{
//			for (int j = 0; j < kFullSize - 1; ++j)
//			{
//				for (int ooo = 0; ooo < 3; ++ooo)
//				{
//					for (int t = 0; t < 3; ++t)
//					{
//						if (imgIn[10] < 170)
//						{
//							arrayBuffer[0] = imgIn[0];
//							arrayBuffer[1] = imgIn[0];
//							arrayBuffer[2] = imgIn[0];
//							arrayBuffer[3] = imgIn[0];
//							arrayBuffer[4] = imgIn[0];
//							arrayBuffer[5] = imgIn[0];
//							arrayBuffer[6] = imgIn[0];
//							arrayBuffer[7] = imgIn[0];
//							arrayBuffer[8] = imgIn[0];
//						}
//					}
//				}
//				//if (arrayBuffer[j] > arrayBuffer[j + 1])
//				//{
//				/*for (int ooo = 0; ooo < kSize; ++ooo)
//				{
//					for (int t = 0; t < kSize; ++t)
//					{
//						arrayBuffer[0] = imgIn[0];
//						arrayBuffer[1] = imgIn[0];
//						arrayBuffer[2] = imgIn[0];
//						arrayBuffer[3] = imgIn[0];
//						arrayBuffer[4] = imgIn[0];
//						arrayBuffer[5] = imgIn[0];
//						arrayBuffer[6] = imgIn[0];
//						arrayBuffer[7] = imgIn[0];
//						arrayBuffer[8] = imgIn[0];
//					}
//				}*/
//				//}
//			}
//		}
//
//		/*int a = 255;
//		int b; 
//		int c;
//
//		int circleIter = imgW;
//
//		for (int i = 0; i < circleIter; ++i)
//		{
//			b = imgIn[pos];
//			b = arrayBuffer[2];
//			for (int j = 0; j < circleIter; ++j)
//			{
//				b++;
//			}
//			a++;
//			c = b;
//
//			a = c;
//		}*/
//
//		for (int j = 0; j < kSize; ++j)
//		{
//			for (int i = 0; i < kSize; ++i)
//			{
//				arrayBuffer[iter] = imgIn[pos];
//				iter++;
//				pos++;
//			}
//			pos += imgW - kSize;
//		}
//		////
//		/*for (int j = 0; j < filterKernelSize; ++j)
//		{
//			pos = imgWidth * (y - filterKernelRange + j) + x - filterKernelRange;
//			for (int i = 0; i < filterKernelSize; ++i)
//			{
//				arrayBuffer[iter] = imgIn[pos];
//				iter++;
//				pos++;
//			}
//		}*/
//
//		//Modified Boubble Sors
//		int bubbleIterOut = (int)(kFullSize / 2 + 1);
//		int bubbleIterIn = (int)(kFullSize - 1);
//		for (int i = 0; i < bubbleIterOut; ++i)
//		{
//			for (int j = 0; j < bubbleIterIn; ++j)
//			{
//				if (arrayBuffer[j] > arrayBuffer[j + 1])
//				{
//					temp = arrayBuffer[j + 1];
//					arrayBuffer[j + 1] = arrayBuffer[j];
//					arrayBuffer[j] = temp;
//				}
//			}
//		}
//
//		imgOut[centerPos] = arrayBuffer[4];
//		//imgOut[centerPos] = kSize * 50;
//	}
//	else
//	{
//		int centerPos = imgW * y + x;
//		imgOut[centerPos] = imgIn[centerPos];
//	}
//}
__kernel void medianFilter_3x3_1NDRange_8UC1(__global uchar *imgIn, __global uchar *imgOut, int width, int height)
{
	const int x = get_global_id(0) % width;
	const int y = get_global_id(0) / width;

	//const int width = get_global_size(0);
	//const int height = get_global_size(0);

	if ((-1 < x - 1) && (-1 < y - 1) && (x + 1 < width) && (y + 1 < height))
	{
		//uchar arrayBuffer[9];
		uchar r0, r1, r2, r3, r4, r5, r6, r7, r8;

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

		uchar ucharMin = min(r0, r1);
		uchar ucharMax = max(r0, r1);
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

		imgOut[iOffset + x] = min(r4, r5);

	}
	else if (-1 < x && x < width && -1 < y && y < height)
	{
		int centerPos = width * y + x;
		imgOut[centerPos] = imgIn[centerPos];
	}
}