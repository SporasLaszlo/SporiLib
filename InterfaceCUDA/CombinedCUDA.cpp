#include "stdafx.h"
#include "CombinedCUDA.h"

bool CCombinedCUDA::m_CUDAInit = false;
int CCombinedCUDA::m_CUDAWarpSize = 0;
int CCombinedCUDA::m_CUDAMaxThreadNumberPerMultiProcessor = 0;
int CCombinedCUDA::m_CUDAMaxThreadNumberPerBlock = 0;
int CCombinedCUDA::m_CUDAHalfMaxThreadNumberPerBlock = 0;

CCombinedCUDA::CCombinedCUDA(void)
{
}
CCombinedCUDA::~CCombinedCUDA(void)
{
}

void CCombinedCUDA::EXT_Init()
{
	cudaDeviceProp deviceProp;
	cudaError error = cudaGetDeviceProperties(&deviceProp, 0);

	//std::cout << deviceProp.multiProcessorCount << std::endl;

	if (error == 0)
	{
		m_CUDAWarpSize = deviceProp.warpSize;
		m_CUDAMaxThreadNumberPerMultiProcessor = deviceProp.maxThreadsPerMultiProcessor;
		m_CUDAMaxThreadNumberPerBlock = deviceProp.maxThreadsPerBlock;
		m_CUDAHalfMaxThreadNumberPerBlock = m_CUDAMaxThreadNumberPerBlock / 2;

		m_CUDAInit = true;
	}
	else
	{
		std::cout << "CUDA error in init!" << std::endl;
		m_CUDAInit = false;
	}
}
void CCombinedCUDA::EXT_GetOptimalGridAndBlockSize(ECUDAFunction function, cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize)
{
	if (m_CUDAInit)
	{
		switch (function)
		{
			case CUDAFunction_MedianFilter3x3: _CalculateMedianFilter3x3GridAndBlockSize(imgIn, gridSize, blockSize); break;
			default: std::cout << "Wrong 'function' parameter!" << std::endl;
		}
	}
	else
		std::cout << "CUDA interface without init!" << std::endl;
}
void CCombinedCUDA::_CalculateMedianFilter3x3GridAndBlockSize(cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize)
{
	if (imgIn.type() == CV_8UC1)
	{
		cv::Mat tempIn = imgIn.clone();
		cv::Mat tempOut = cv::Mat::zeros(tempIn.rows, tempIn.cols, tempIn.type());

		int threadNum = m_CUDAWarpSize;
		int threadCount = 256;

		int blockWidth = m_CUDAWarpSize;
		int blockWidthCount = m_CUDAWarpSize;

		int blockHeight = 0;

		float minTime = FLT_MAX;
		float time;
		int minX, minY, minThread;
		int averageIter = 6;

		CRunTime response;

		for (int threadIter = threadNum; threadIter <= m_CUDAMaxThreadNumberPerMultiProcessor / 2; threadIter = threadIter + threadNum)//(threadIter >= 256) ? (threadIter += threadCount) : (threadIter *= 2))
		{
			//std::cout << "Threads (Block Size): ";
			//std::cout << threadIter << std::endl;

			for (int blockWidthIter = blockWidth; blockWidthIter <= threadIter; blockWidthIter += blockWidthCount)
			{
				if (threadIter % blockWidthIter == 0)
				{
					blockHeight = threadIter / blockWidthIter;
					std::cout << "Block size: ";
					std::cout << blockWidthIter;
					std::cout << " -- ";
					std::cout << blockHeight << std::endl;
					time = 0;

					for (int i = 0; i < averageIter; ++i)
					{
						response.EXT_SetStartTimeLocal();
						CCombinedCUDA::EXT_MedianFilter3x3(tempIn, tempOut, 200, { (unsigned)(std::ceilf((float)tempIn.cols / (float)blockWidthIter)), (unsigned)(std::ceilf((float)tempIn.rows / (float)blockHeight)) }, { (unsigned)(blockWidthIter), (unsigned)(blockHeight) });
						time += response.EXT_SetFinishTimeLocal(false, false);
					}

					std::cout << time << std::endl;

					if (minTime > time)
					{
						std::cout << "            ---------  ADD  ---------" << std::endl;
						minTime = time;
						minThread = threadIter;
						minX = blockWidthIter;
						minY = blockHeight;
					}
				}
			}
		}

		gridSize.width = (int)(std::ceilf((float)tempIn.cols / (float)minX));
		gridSize.height = (int)(std::ceilf((float)tempIn.rows / (float)minY));
		blockSize.width = minX;
		blockSize.height = minY;
	}
	else if(imgIn.type() == CV_8UC3)
	{
		cv::Mat tempIn = imgIn.clone();
		cv::Mat tempOut = cv::Mat::zeros(tempIn.rows, tempIn.cols, tempIn.type());

		std::cout << "Get grid and block size CV_8UC3 not ready!" << std::endl;
	}
}
void CCombinedCUDA::EXT_MedianFilter3x3(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, dim3 gridSize, dim3 blockSize)
{
	if (m_CUDAInit)
	{
		if (imgIn.type() == CV_8UC1)
		{
			uchar *deviceIn, *deviceOut, *deviceFirstBuffer, *deviceSecondBuffer;

			int size = sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows;

			cudaMalloc((void **)&deviceIn, size);
			cudaMalloc((void **)&deviceOut, size);
			cudaMalloc((void **)&deviceFirstBuffer, size);
			cudaMalloc((void **)&deviceSecondBuffer, size);

			//dim3 aa = dim3(3, 3);
			//1U;

			cudaMemcpy(deviceIn, &(imgIn.data[0]), size, cudaMemcpyHostToDevice);

			for (int i = 1; i <= iterationNumber; ++i)
			{
				if (iterationNumber > 1)
				{
					if (i != iterationNumber)
					{
						if (i == 1)
						{
							CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceIn, deviceFirstBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffImgIn);
							//kernelMedianFilter.setArg(1, buffFirst);
							//m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
						}
						else if (i % 2 == 0)
						{
							CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceFirstBuffer, deviceSecondBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffFirst);
							//kernelMedianFilter.setArg(1, buffSecond);
						}
						else if (i % 2 == 1)
						{
							CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceSecondBuffer, deviceFirstBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffSecond);
							//kernelMedianFilter.setArg(1, buffFirst);
						}
					}
					else
					{
						if (i % 2 == 0)
						{
							CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceFirstBuffer, deviceOut, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffFirst);
							//kernelMedianFilter.setArg(1, buffImgOut);
						}
						else if (i % 2 == 1)
						{
							CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceSecondBuffer, deviceOut, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffSecond);
							//kernelMedianFilter.setArg(1, buffImgOut);
						}
					}
				}
				else if (iterationNumber == 1)
				{
					CUDAINTERFACE_MedianFilter3x3(imgIn.cols, imgIn.rows, deviceIn, deviceOut, gridSize, blockSize);
					//m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
				}

				//CRunTime::EXT_SetStartTime();
				//m_openCLQueue.enqueueNDRangeKernel(kernelMedianFilter, cl::NullRange, cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));//cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));
				//m_openCLQueue.finish();
				//CRunTime::EXT_SetFinishTime();
			}

			cudaMemcpy(&(imgOut.data[0]), deviceOut, size, cudaMemcpyDeviceToHost);

			cudaFree(deviceIn);
			cudaFree(deviceOut);
			cudaFree(deviceFirstBuffer);
			cudaFree(deviceSecondBuffer);
		}
	}
	else
		std::cout << "CUDA interface without init!" << std::endl;
}
void CCombinedCUDA::EXT_MedianFilter3x3_1D(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, int gridSize, int blockSize)
{
	if (m_CUDAInit)
	{
		if (imgIn.type() == CV_8UC1)
		{
			uchar *deviceIn, *deviceOut, *deviceFirstBuffer, *deviceSecondBuffer;

			int size = sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows;

			cudaMalloc((void **)&deviceIn, size);
			cudaMalloc((void **)&deviceOut, size);
			cudaMalloc((void **)&deviceFirstBuffer, size);
			cudaMalloc((void **)&deviceSecondBuffer, size);

			cudaMemcpy(deviceIn, &(imgIn.data[0]), size, cudaMemcpyHostToDevice);

			for (int i = 1; i <= iterationNumber; ++i)
			{
				if (iterationNumber > 1)
				{
					if (i != iterationNumber)
					{
						if (i == 1)
						{
							CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceIn, deviceFirstBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffImgIn);
							//kernelMedianFilter.setArg(1, buffFirst);
							//m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
						}
						else if (i % 2 == 0)
						{
							CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceFirstBuffer, deviceSecondBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffFirst);
							//kernelMedianFilter.setArg(1, buffSecond);
						}
						else if (i % 2 == 1)
						{
							CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceSecondBuffer, deviceFirstBuffer, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffSecond);
							//kernelMedianFilter.setArg(1, buffFirst);
						}
					}
					else
					{
						if (i % 2 == 0)
						{
							CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceFirstBuffer, deviceOut, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffFirst);
							//kernelMedianFilter.setArg(1, buffImgOut);
						}
						else if (i % 2 == 1)
						{
							CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceSecondBuffer, deviceOut, gridSize, blockSize);
							//kernelMedianFilter.setArg(0, buffSecond);
							//kernelMedianFilter.setArg(1, buffImgOut);
						}
					}
				}
				else if (iterationNumber == 1)
				{
					CUDAINTERFACE_MedianFilter3x3_1D(imgIn.cols, imgIn.rows, deviceIn, deviceOut, gridSize, blockSize);
					//m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
				}

				//CRunTime::EXT_SetStartTime();
				//m_openCLQueue.enqueueNDRangeKernel(kernelMedianFilter, cl::NullRange, cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));//cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));
				//m_openCLQueue.finish();
				//CRunTime::EXT_SetFinishTime();
			}

			cudaMemcpy(&(imgOut.data[0]), deviceOut, size, cudaMemcpyDeviceToHost);

			cudaFree(deviceIn);
			cudaFree(deviceOut);
			cudaFree(deviceFirstBuffer);
			cudaFree(deviceSecondBuffer);
		}
	}
	else
		std::cout << "CUDA interface without init!" << std::endl;
}
void CCombinedCUDA::EXT_CopyImage(cv::Mat &imgIn, cv::Mat &imgOut)
{
	uchar *deviceIn, *deviceOut;

	int size = sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows;

	cudaMalloc((void **)&deviceIn, size);
	cudaMalloc((void **)&deviceOut, size);

	cudaMemcpy(deviceIn, &(imgIn.data[0]), size, cudaMemcpyHostToDevice);

	CUDAINTERFACE_CopyImage(deviceIn, deviceOut);

	imgOut.create(imgIn.rows, imgIn.cols, imgIn.type());
	cudaMemcpy(&(imgOut.data[0]), deviceOut, size, cudaMemcpyDeviceToHost);

	cudaFree(deviceIn);
	cudaFree(deviceOut);
}