#include "stdafx.h"
#include "CombinedOpenCL.h"

bool CCombinedOpenCL::m_openCLInit = false;
std::vector<cl::Platform> CCombinedOpenCL::m_openCLAllPlatforms;
std::vector<cl::Device> CCombinedOpenCL::m_openCLAllDevices;
cl::Context CCombinedOpenCL::m_openCLContext;
cl::Program CCombinedOpenCL::m_openCLProgram;
cl::Program CCombinedOpenCL::m_openCLProgram2;
cl::CommandQueue CCombinedOpenCL::m_openCLQueue;
cl::CommandQueue CCombinedOpenCL::m_openCLQueue2;

CCombinedOpenCL::CCombinedOpenCL(void)
{
}
CCombinedOpenCL::~CCombinedOpenCL(void)
{
}

void CCombinedOpenCL::EXT_Init()
{
	try
	{
		cl::Platform::get(&m_openCLAllPlatforms);
		m_openCLAllPlatforms[0].getDevices(CL_DEVICE_TYPE_GPU, &m_openCLAllDevices);

		m_openCLContext = cl::Context(m_openCLAllDevices);

		std::ifstream sourceFile("../InterfaceOpenCL/MedianFilter.cl");
		std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
		cl::Program::Sources sources(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));

		m_openCLProgram = cl::Program(m_openCLContext, sources);
		
		std::ifstream sourceFile2("../InterfaceOpenCL/WarpPerspective.cl");
		std::string sourceCode2(std::istreambuf_iterator<char>(sourceFile2), (std::istreambuf_iterator<char>()));
		cl::Program::Sources sources2(1, std::make_pair(sourceCode2.c_str(), sourceCode2.length() + 1));
		
		m_openCLProgram2 = cl::Program(m_openCLContext, sources2);

		if (m_openCLProgram.build({ m_openCLAllDevices[0] }) != CL_SUCCESS)//, "-D KERNELFULLSIZE=9") != CL_SUCCESS)
		{
			std::cout << " Error building: " << m_openCLProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_openCLAllDevices[0]) << "\n";
			std::system("PAUSE");
			exit(1);
		}

		if (m_openCLProgram2.build({ m_openCLAllDevices[0] }) != CL_SUCCESS)//, "-D KERNELFULLSIZE=9") != CL_SUCCESS)
		{
			std::cout << " Error building: " << m_openCLProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_openCLAllDevices[0]) << "\n";
			std::system("PAUSE");
			exit(1);
		}

		std::cout << "s" << std::endl;
		m_openCLQueue = cl::CommandQueue(m_openCLContext, m_openCLAllDevices[0]);
		std::cout << "22s" << std::endl;
		m_openCLQueue2 = cl::CommandQueue(m_openCLContext, m_openCLAllDevices[0]);
		std::cout << "222s" << std::endl;
		m_openCLInit = true;
	}
	catch (cl::Error &e)
	{
		std::cout << "Here: ";
		std::cout << e.what() << std::endl;
		std::cout << "Error code: ";
		std::cout << e.err() << std::endl;
	}
}
void CCombinedOpenCL::EXT_MedianFilter3x3(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, cv::Size gridSize, cv::Size blockSize)
{
	if (m_openCLInit)
	{
		try
		{
			if (imgIn.type() == CV_8UC1)
			{
				cl::Kernel kernelMedianFilter = cl::Kernel(m_openCLProgram, "medianFilter_3x3_2NDRange_8UC1");
				
				//kep bufferek
				cl::Buffer buffImgIn, buffImgOut, buffFirst, buffSecond;
				//constant bufferek
				//cl::Buffer buffImgWidth, buffImgHeight, buffKernelRange, buffKernelSize, bufKernelFullSize;

				//int filterKernelRange = 1;
				//int filterKernelSize = (filterKernelRange * 2 + 1);
				//int filterKernelFullSize = filterKernelSize * filterKernelSize;
			
				//buffImgWidth = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffImgHeight = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffKernelRange = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffKernelSize = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//bufKernelFullSize = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));

				//m_openCLQueue.enqueueWriteBuffer(buffImgWidth, CL_TRUE, 0, sizeof(int), &imgIn.cols);
				//m_openCLQueue.enqueueWriteBuffer(buffImgHeight, CL_TRUE, 0, sizeof(int), &imgIn.rows);
				//m_openCLQueue.enqueueWriteBuffer(buffKernelRange, CL_TRUE, 0, sizeof(int), &filterKernelRange);
				//m_openCLQueue.enqueueWriteBuffer(buffKernelSize, CL_TRUE, 0, sizeof(int), &filterKernelSize);
				//m_openCLQueue.enqueueWriteBuffer(bufKernelFullSize, CL_TRUE, 0, sizeof(int), &filterKernelFullSize);

				buffImgIn = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffImgOut = cl::Buffer(m_openCLContext, CL_MEM_WRITE_ONLY, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffFirst = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffSecond = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);

				//kernelMedianFilter.setArg(0, buffImgWidth);
				//kernelMedianFilter.setArg(1, buffImgHeight);
				kernelMedianFilter.setArg(0, buffImgIn);
				kernelMedianFilter.setArg(1, buffImgOut);
				kernelMedianFilter.setArg(2, imgIn.cols);
				kernelMedianFilter.setArg(3, imgIn.rows);
				//kernelMedianFilter.setArg(4, buffKernelRange);
				//kernelMedianFilter.setArg(5, buffKernelSize);
				//kernelMedianFilter.setArg(6, bufKernelFullSize);

				//kernelMedianFilter.setArg(0, imgIn.cols);
				//kernelMedianFilter.setArg(1, imgIn.rows);
				//kernelMedianFilter.setArg(2, buffImgIn);
				//kernelMedianFilter.setArg(3, buffImgOut);
				//kernelMedianFilter.setArg(4, filterKernelRange);
				//kernelMedianFilter.setArg(5, filterKernelSize);
				//kernelMedianFilter.setArg(6, filterKernelFullSize);

				//std::cout << imgIn.type() << std::endl;
				//std::cout << CV_8UC1 << std::endl;
				//std::cout << imgIn.cols << std::endl;
				//std::cout << imgIn.rows << std::endl;
				//std::cout << imgIn.channels() << std::endl;


				for (int i = 1; i <= iterationNumber; ++i)
				{
					if (iterationNumber > 1)
					{
						if (i != iterationNumber)
						{
							if (i == 1)
							{
								kernelMedianFilter.setArg(0, buffImgIn);
								kernelMedianFilter.setArg(1, buffFirst);
								m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
							}
							else if (i % 2 == 0)
							{
								kernelMedianFilter.setArg(0, buffFirst);
								kernelMedianFilter.setArg(1, buffSecond);
							}
							else if (i % 2 == 1)
							{
								kernelMedianFilter.setArg(0, buffSecond);
								kernelMedianFilter.setArg(1, buffFirst);
							}
						}
						else
						{
							if (i % 2 == 0)
							{
								kernelMedianFilter.setArg(0, buffFirst);
								kernelMedianFilter.setArg(1, buffImgOut);
							}
							else if (i % 2 == 1)
							{
								kernelMedianFilter.setArg(0, buffSecond);
								kernelMedianFilter.setArg(1, buffImgOut);
							}
						}
					}
					else if (iterationNumber == 1)
					{
						m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
					}

					//CRunTime::EXT_SetStartTime();
					m_openCLQueue.enqueueNDRangeKernel(kernelMedianFilter, cl::NullRange, cl::NDRange(gridSize.width * blockSize.width, gridSize.height * blockSize.height), cl::NDRange(blockSize.width, blockSize.height));//cl::NDRange(128, 2));//cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));
					m_openCLQueue.finish();
					//CRunTime::EXT_SetFinishTime();
				}

				m_openCLQueue.enqueueReadBuffer(buffImgOut, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgOut.data[0]);
			}
		}
		catch (cl::Error &e)
		{
			std::cout << "Here: ";
			std::cout << e.what() << std::endl;
			std::cout << "Error code: ";
			std::cout << e.err() << std::endl;
		}
	}
}
void CCombinedOpenCL::EXT_MedianFilter3x3_1D(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, int gridSize, int blockSize)
{
	if (m_openCLInit)
	{
		try
		{
			if (imgIn.type() == CV_8UC1)
			{
				cl::Kernel kernelMedianFilter = cl::Kernel(m_openCLProgram, "medianFilter_3x3_1NDRange_8UC1");
				
				//kep bufferek
				cl::Buffer buffImgIn, buffImgOut, buffFirst, buffSecond;
				//constant bufferek
				//cl::Buffer buffImgWidth, buffImgHeight, buffKernelRange, buffKernelSize, bufKernelFullSize;

				//int filterKernelRange = 1;
				//int filterKernelSize = (filterKernelRange * 2 + 1);
				//int filterKernelFullSize = filterKernelSize * filterKernelSize;
			
				//buffImgWidth = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffImgHeight = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffKernelRange = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//buffKernelSize = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));
				//bufKernelFullSize = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(int));

				//m_openCLQueue.enqueueWriteBuffer(buffImgWidth, CL_TRUE, 0, sizeof(int), &imgIn.cols);
				//m_openCLQueue.enqueueWriteBuffer(buffImgHeight, CL_TRUE, 0, sizeof(int), &imgIn.rows);
				//m_openCLQueue.enqueueWriteBuffer(buffKernelRange, CL_TRUE, 0, sizeof(int), &filterKernelRange);
				//m_openCLQueue.enqueueWriteBuffer(buffKernelSize, CL_TRUE, 0, sizeof(int), &filterKernelSize);
				//m_openCLQueue.enqueueWriteBuffer(bufKernelFullSize, CL_TRUE, 0, sizeof(int), &filterKernelFullSize);

				buffImgIn = cl::Buffer(m_openCLContext, CL_MEM_READ_ONLY, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffImgOut = cl::Buffer(m_openCLContext, CL_MEM_WRITE_ONLY, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffFirst = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				buffSecond = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);

				//kernelMedianFilter.setArg(0, buffImgWidth);
				//kernelMedianFilter.setArg(1, buffImgHeight);
				kernelMedianFilter.setArg(0, buffImgIn);
				kernelMedianFilter.setArg(1, buffImgOut);
				kernelMedianFilter.setArg(2, imgIn.cols);
				kernelMedianFilter.setArg(3, imgIn.rows);
				//kernelMedianFilter.setArg(4, buffKernelRange);
				//kernelMedianFilter.setArg(5, buffKernelSize);
				//kernelMedianFilter.setArg(6, bufKernelFullSize);

				//kernelMedianFilter.setArg(0, imgIn.cols);
				//kernelMedianFilter.setArg(1, imgIn.rows);
				//kernelMedianFilter.setArg(2, buffImgIn);
				//kernelMedianFilter.setArg(3, buffImgOut);
				//kernelMedianFilter.setArg(4, filterKernelRange);
				//kernelMedianFilter.setArg(5, filterKernelSize);
				//kernelMedianFilter.setArg(6, filterKernelFullSize);

				//std::cout << imgIn.type() << std::endl;
				//std::cout << CV_8UC1 << std::endl;
				//std::cout << imgIn.cols << std::endl;
				//std::cout << imgIn.rows << std::endl;
				//std::cout << imgIn.channels() << std::endl;


				for (int i = 1; i <= iterationNumber; ++i)
				{
					if (iterationNumber > 1)
					{
						if (i != iterationNumber)
						{
							if (i == 1)
							{
								kernelMedianFilter.setArg(0, buffImgIn);
								kernelMedianFilter.setArg(1, buffFirst);
								m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
							}
							else if (i % 2 == 0)
							{
								kernelMedianFilter.setArg(0, buffFirst);
								kernelMedianFilter.setArg(1, buffSecond);
							}
							else if (i % 2 == 1)
							{
								kernelMedianFilter.setArg(0, buffSecond);
								kernelMedianFilter.setArg(1, buffFirst);
							}
						}
						else
						{
							if (i % 2 == 0)
							{
								kernelMedianFilter.setArg(0, buffFirst);
								kernelMedianFilter.setArg(1, buffImgOut);
							}
							else if (i % 2 == 1)
							{
								kernelMedianFilter.setArg(0, buffSecond);
								kernelMedianFilter.setArg(1, buffImgOut);
							}
						}
					}
					else if (iterationNumber == 1)
					{
						m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
					}

					//CRunTime::EXT_SetStartTime();
					m_openCLQueue.enqueueNDRangeKernel(kernelMedianFilter, cl::NullRange, cl::NDRange(gridSize * blockSize), cl::NDRange(blockSize));//cl::NDRange(128, 2));//cl::NDRange(imgIn.cols, imgIn.rows), cl::NDRange(128, 2));
					m_openCLQueue.finish();
					//CRunTime::EXT_SetFinishTime();
				}

				m_openCLQueue.enqueueReadBuffer(buffImgOut, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgOut.data[0]);
			}
		}
		catch (cl::Error &e)
		{
			std::cout << "Here: ";
			std::cout << e.what() << std::endl;
			std::cout << "Error code: ";
			std::cout << e.err() << std::endl;
		}
	}
}
void CCombinedOpenCL::EXT_WarpPerspective(cv::Mat &imgIn, cv::Mat &imgOut, cv::Size imgOutSize, cv::Mat H, cv::Size gridSize, cv::Size blockSize)
{
	if (m_openCLInit)
	{
		if (!imgIn.empty())
		{
			try
			{
				imgOut.create(imgOutSize, imgIn.type());

				cv::Mat float_H(3, 3, CV_32FC1);

				cv::Mat tmpH = H.inv();

				for (int y = 0; y < 3; y++)
				{
					for (int x = 0; x < 3; x++)
					{
						float_H.at<float>(y, x) = (float)tmpH.at<double>(y, x);
					}
				}
				
				cl::Kernel kernelWarpPerspective = cl::Kernel(m_openCLProgram2, "warpPerspective_2D_8UC3");
				
				cl::Buffer buffH, buffImgIn, buffImgOut;

				buffH = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(float) * 3 * 3);
				//buffImgInWidth = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));
				//buffImgInHeight = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));
				buffImgIn = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows);
				//buffImgOutWidth = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));
				//buffImgOutHeight = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));
				buffImgOut = cl::Buffer(m_openCLContext, CL_MEM_READ_WRITE, sizeof(uchar) * imgIn.channels() * imgOutSize.width * imgOutSize.height);
				
				kernelWarpPerspective.setArg(0, buffH);
				kernelWarpPerspective.setArg(1, imgIn.cols);
				kernelWarpPerspective.setArg(2, imgIn.rows);
				kernelWarpPerspective.setArg(3, buffImgIn);
				kernelWarpPerspective.setArg(4, imgOutSize.width);
				kernelWarpPerspective.setArg(5, imgOutSize.height);
				kernelWarpPerspective.setArg(6, buffImgOut);

				m_openCLQueue.enqueueWriteBuffer(buffH, CL_TRUE, 0, sizeof(float) * 3 * 3, &float_H.data[0]);
				m_openCLQueue.enqueueWriteBuffer(buffImgIn, CL_TRUE, 0, sizeof(uchar) * imgIn.channels() * imgIn.cols * imgIn.rows, &imgIn.data[0]);
				
				int error = m_openCLQueue.enqueueNDRangeKernel(kernelWarpPerspective, cl::NullRange, cl::NDRange(gridSize.width * blockSize.width, gridSize.height * blockSize.height), cl::NDRange(blockSize.width, blockSize.height));
				m_openCLQueue.finish();
				
				m_openCLQueue.enqueueReadBuffer(buffImgOut, CL_TRUE, 0, sizeof(uchar) * imgOut.channels() * imgOutSize.width * imgOutSize.height, &imgOut.data[0]);

			}
			catch (cl::Error &e)
			{
				std::cout << "Here: ";
				std::cout << e.what() << std::endl;
				std::cout << "Error code: ";
				std::cout << e.err() << std::endl;
			}
		}
	}
}