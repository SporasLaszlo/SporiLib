//#include "stdafx.h"
#include "MotionDetector_TopView.h"

CMotionDetector_TopView::CMotionDetector_TopView()
{
	m_className = "CMotionDetector_TopView";

	m_image.EXT_SetImageType(ImageType_Undefined);
	m_outImage.EXT_SetImageType(ImageType_Undefined);

	m_imgSize.height = 0;
	m_imgSize.width = 0;

	m_history = NULL;
	m_partsOfImage = NULL;
	m_historySum = NULL;
	m_historyAvg = NULL;

	m_historyPartSize = 0;
	m_historyPartSizeIteration = 0;
	m_historyPartLastPos = 0;
	m_historyPartSum = NULL;
	m_historyPartAvg = NULL;
}
CMotionDetector_TopView::~CMotionDetector_TopView()
{
	if (m_history != NULL)
	{
		for (int i = 0; i < m_historyDataSize; ++i)
		{
			delete[] m_history[i];
		}
		
		delete[] m_history;
	}
	if (m_partsOfImage != NULL)
	{
		for (int i = 0; i < m_partsOfImageSize.width; ++i)
		{
			delete[] m_partsOfImage[i];
			//delete[] m_partOfImageHistory[i];
		}
		
		delete[] m_partsOfImage;
		//delete[] m_partOfImageHistory;
	}
	if (m_historySum != NULL)
		delete[] m_historySum;

	if (m_historyAvg != NULL)
		delete[] m_historyAvg;

	if (m_historyPartSum != NULL)
		delete[] m_historyPartSum;

	if (m_historyPartAvg != NULL)
		delete[] m_historyPartAvg;
}

void CMotionDetector_TopView::EXT_Init(ImageType imageType, int history, float threshold, bool shadowDetection)
{
	m_image.EXT_SetImageType(imageType);
	m_outImage.EXT_SetImageType(imageType);

	m_historySize = history;
	m_historyPartSize = history / 10;
	//m_history.resize(m_historySize);
	//m_partOfImageHistoryThreshold = history;
	m_historyActualPos = 0;
	m_threshold = threshold;
}
void CMotionDetector_TopView::EXT_SetParameters(cv::Size processingImageSize, cv::Size processingPartSize)
{
	m_imgSize = processingImageSize;
	m_processingPartSize = processingPartSize;
	//m_partOfImageHistoryThreshold = historyThreshold;

	m_historyDataSize = m_imgSize.width * m_imgSize.height;

	m_history = new uchar*[m_historyDataSize];

	for (int i = 0; i < m_historyDataSize; ++i)
		m_history[i] = new uchar[m_historySize];
	
	for (int j = 0; j < m_historyDataSize; ++j)
		for (int i = 0; i < m_historySize; ++i)
			m_history[j][i] = 0;

	m_historySum = new int[m_historyDataSize];
	m_historyAvg = new int[m_historyDataSize];

	m_historyPartSum = new int[m_historyDataSize];
	m_historyPartAvg = new int[m_historyDataSize];

	for (int i = 0; i < m_historyDataSize; ++i)
	{
		m_historySum[i] = 0;
		m_historyAvg[i] = 0;

		m_historyPartSum[i] = 0;
		m_historyPartAvg[i] = 0;
	}

	//for (int i = 0; i < m_history.size(); ++i)
	//	m_history[i] = cv::Mat::zeros(m_imgSize, CV_8UC1);
	
	int sizeX = (int)(m_imgSize.width / m_processingPartSize.width);
	if (m_imgSize.width % m_processingPartSize.width > 0)
		sizeX++;

	int sizeY = (int)(m_imgSize.height / m_processingPartSize.height);
	if (m_imgSize.height % m_processingPartSize.height > 0)
		sizeY++;

	m_partsOfImageSize.width = sizeX;
	m_partsOfImageSize.height = sizeY;

	//std::cout << sizeX << " " << sizeY << std::endl;

	m_partsOfImage = new SPart*[sizeX];
	//m_partOfImageHistory = new int*[sizeX];
	for (int i = 0; i < sizeX; ++i)
	{
		m_partsOfImage[i] = new SPart[sizeY];
		//m_partOfImageHistory[i] = new int[sizeY];
	}

	//for (int y = 0; y < sizeY; ++y)
	//	for (int x = 0; x < sizeX; ++x)
	//		m_partOfImageHistory[x][y] = 0;

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			m_partsOfImage[x][y].m_thisPartSize = m_processingPartSize;

			if (x == sizeX - 1)
			{
				int tmp = m_imgSize.width % m_processingPartSize.width;

				if (tmp != 0)
					m_partsOfImage[x][y].m_thisPartSize.width = tmp;
			}

			if (y == sizeY - 1)
			{
				int tmp = m_imgSize.height % m_processingPartSize.height;

				if (tmp != 0)
					m_partsOfImage[x][y].m_thisPartSize.height = tmp;
			}

			//Start pointers
			int pos = y * m_processingPartSize.height * m_imgSize.width + x * m_processingPartSize.width;

			for (int i = 0; i < m_partsOfImage[x][y].m_thisPartSize.height; ++i)
			{
				m_partsOfImage[x][y].m_startPointerPositionOfRows.push_back(pos);
				pos += m_imgSize.width;
			}
			
			//std::cout << m_partsOfImage[x][y].m_thisPartSize;
			//std::cout << "    -     Start Point: " << m_partsOfImage[x][y].m_startPointerPositionOfRows[0] << std::endl;

			//Central Point
			int h = m_partsOfImage[x][y].m_thisPartSize.height;
			int w = m_partsOfImage[x][y].m_thisPartSize.width;
			m_partsOfImage[x][y].centralPointPosition = m_partsOfImage[x][y].m_startPointerPositionOfRows[h / 2] + w / 2;

			//std::cout << m_partsOfImage[x][y].m_thisPartSize;
			//std::cout << "    -     Central Point: " << m_partsOfImage[x][y].centralPointPosition << std::endl;
		}
		//std::cout << std::endl;
	}

	//Check
	/*
	cv::Mat testImg = cv::Mat::zeros(m_imgSize, CV_8UC1);
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			testImg.data[m_partsOfImage[x][y].centralPointPosition] = 255;
		}
	}
	cv::namedWindow("test", CV_WINDOW_NORMAL | CV_WINDOW_FREERATIO);
	cv::imshow("test", testImg);
	cv::waitKey(0);
	//*/

	/*bool validX = true;
	bool validY = true;
	int countX = 0;
	int countY = 0;
	int actIndexX = 0;
	int actIndexY = 0;

	while (validY)
	{
		validX = true;
		countX = 0;
		while (validX)
		{
			actIndexX = m_processingPartSize.width * countX;
			actIndexY = m_processingPartSize.height * countY;

			if (actIndexX < m_imgSize.width)
			{

			}
			else
			{
				validX = false;
			}

			if (actIndexX > m_imgSize.width && actIndexY > m_imgSize.height)
				validY = false;
	
			countX++;
		}
		countY++;
	}*/
}
void CMotionDetector_TopView::EXT_Detect(CMutexImage *image)
{
	m_classFunction = "EXT_Detect";
	bool validImg = false;

	if (image->EXT_GetImagePointer()->type() == CV_8UC1)
	{
		m_image.EXT_SetImage(image);
		validImg = true;
	}
	else if (image->EXT_GetImagePointer()->type() == CV_8UC3)
	{
		image->EXT_Lock();
		m_image.EXT_Lock();

		//image->EXT_GetImagePointer()->convertTo(*(m_image.EXT_GetImagePointer()), CV_8UC1);
		cv::cvtColor(*(image->EXT_GetImagePointer()), *(m_image.EXT_GetImagePointer()), CV_BGR2GRAY);

		//image->EXT_GetImagePointer()->convertTo(*(m_image.EXT_GetImagePointer()), CV_8UC1);

		m_image.EXT_Unlock();
		image->EXT_Unlock();

		validImg = true;
	}
	
	if (validImg)
	{
		//Update BackGround
		//CRunTime::EXT_SetStartTime();
		if (m_historyActualPos == m_historySize)
			m_historyActualPos = 0;
		if (m_historyPartLastPos == m_historySize)
			m_historyPartLastPos = 0;

		uchar *inImg = m_image.EXT_GetImagePointer()->data;
		uchar **backImg = m_history;
		int *posHistorySum = m_historySum;
		int *posHistoryAvg = m_historyAvg;
		int *posHistoryPartSum = m_historyPartSum;
		int *posHistoryPartAvg = m_historyPartAvg;

		uchar *tmp;

		for (int i = 0; i < m_historyDataSize; ++i)
		{
			if (m_historyPartSizeIteration < m_historyPartSize)
			{
				(*posHistoryPartSum) += (int)(*inImg);
				//m_historyPartLastPos = 0;
				//if(i == 10000)
				//{
				//	std::cout << "Sum: " << (int)(*posHistoryPartSum) << std::endl;
				//	std::this_thread::sleep_for(std::chrono::seconds(1));
				//}
			}
			else
			{
				//if (i == 10000)
				//{
					//std::cout << "Akt Pos: " << m_historyActualPos << std::endl;
					//std::cout << "Last Pos: " << m_historyPartLastPos << std::endl;
					//std::this_thread::sleep_for(std::chrono::milliseconds(200));
				//}
				tmp = &((*backImg)[m_historyPartLastPos]);
				(*posHistoryPartSum) -= (int)*tmp;
				(*posHistoryPartSum) += (int)(*inImg);
				(*posHistoryPartAvg) = (*posHistoryPartSum) / m_historyPartSize;
			}

			tmp = &((*backImg)[m_historyActualPos]);
			(*posHistorySum) -= (int)*tmp;

			*tmp = *inImg;
			(*posHistorySum) += (int)(*inImg);
			(*posHistoryAvg) = (*posHistorySum) / m_historySize;

			//if (i == 10000)
			//{
			//	std::cout << "Img: " << (int)(*inImg) << std::endl;
			//	std::cout << "All: " << (int)(*posHistoryAvg) << std::endl;
			//	std::cout << "Part: " << (int)(*posHistoryPartAvg) << std::endl;
			//}

			inImg++;
			backImg++;
			posHistorySum++;
			posHistoryAvg++;
			posHistoryPartSum++;
			posHistoryPartAvg++;
		}
		if (m_historyPartSizeIteration < m_historyPartSize)
			m_historyPartSizeIteration++;
		else
			m_historyPartLastPos++;
		//std::cout << "m_historyPartSizeIteration: " << m_historyPartSizeIteration << std::endl;
		m_historyActualPos++;
		
		//CRunTime::EXT_SetFinishTime();
		//Update BackGround End


		//if (m_backGroundMask.empty())
		//{
		//	m_image.EXT_Lock();
		//	m_backGroundMask = m_image.EXT_GetImagePointer()->clone();
		//	m_image.EXT_Unlock();
		//}

		m_outImage.EXT_Lock();
		*(m_outImage.EXT_GetImagePointer()) = cv::Mat::zeros(m_image.EXT_GetImagePointer()->size(), CV_8UC1);
		m_outImage.EXT_Unlock();

		int diff = 0;
		int sum = 0;
		uchar *iPos;

		for (int y = 0; y < m_partsOfImageSize.height; ++y)
			for (int x = 0; x < m_partsOfImageSize.width; ++x)
				m_partsOfImage[x][y].processed = false;

		m_image.EXT_Lock();
		for (int y = 0; y < m_partsOfImageSize.height; ++y)
		{
			for (int x = 0; x < m_partsOfImageSize.width; ++x)
			{
				diff = std::abs(m_image.EXT_GetImagePointer()->data[m_partsOfImage[x][y].centralPointPosition] - m_historyPartAvg[m_partsOfImage[x][y].centralPointPosition]);
				//sum = 0;
				//iPos = &(m_history[m_partsOfImage[x][y].centralPointPosition][0]);
				//for (int i = 0; i < m_historySize; ++i)
				//{
				//	sum += (int)(*iPos);
				//	iPos++;
				//}

				//sum /= m_historySize;
				//diff = std::abs(m_image.EXT_GetImagePointer()->data[m_partsOfImage[x][y].centralPointPosition] - sum);

				//diff = std::abs(m_image.EXT_GetImagePointer()->data[m_partsOfImage[x][y].centralPointPosition] - m_backGroundMask.data[m_partsOfImage[x][y].centralPointPosition]);
				if (diff > m_threshold)
				{
					for (int yy = y - 1; yy < y + 1; ++yy)
					{
						for (int xx = x - 1; xx < x + 1; ++xx)
						{
							if (yy > -1 && xx > -1 && yy < m_partsOfImageSize.height && xx < m_partsOfImageSize.width && m_partsOfImage[xx][yy].processed == false)
							{
								uchar *foreImg;

								for (int startPointerVec = 0; startPointerVec < m_partsOfImage[xx][yy].m_startPointerPositionOfRows.size(); ++startPointerVec)
								{
									inImg = &(m_image.EXT_GetImagePointer()->data[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									posHistoryAvg = &(m_historyAvg[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									posHistoryPartAvg = &(m_historyPartAvg[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									//backImg = &(m_history[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									//backImg = &(m_backGroundMask.data[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									foreImg = &(m_outImage.EXT_GetImagePointer()->data[m_partsOfImage[xx][yy].m_startPointerPositionOfRows[startPointerVec]]);
									for (int iteration = 0; iteration < m_partsOfImage[xx][yy].m_thisPartSize.width; ++iteration)
									{
										diff = std::abs(*inImg - *posHistoryPartAvg);

										//sum = 0;
										//iPos = &((*backImg)[0]);
										//for (int i = 0; i < m_historySize; ++i)
										//{
										//	sum += (int)(*iPos);
										//	iPos++;
										//}
										//sum /= m_historySize;

										//diff = std::abs(*inImg - sum);

										//diff = std::abs(*inImg - *backImg);
										if (diff > m_threshold)
										{
											diff = std::abs(*inImg - *posHistoryAvg);
											if (diff > m_threshold)
												*foreImg = 255;
										}
										
										//if (m_partOfImageHistory[xx][yy] == m_partOfImageHistoryThreshold)
										//	*backImg = *inImg;

										inImg++;
										posHistoryAvg++;
										posHistoryPartAvg++;
										//backImg++;
										foreImg++;
									}
								}

								//if (m_partOfImageHistory[xx][yy] < m_partOfImageHistoryThreshold)
								//	m_partOfImageHistory[xx][yy]++;
								//else
								//	m_partOfImageHistory[xx][yy] = 0;

								m_partsOfImage[xx][yy].processed = true;
							}
						}
					}
					//m_partsOfImage[x][y].processed = true;
				}
			}
		}
		m_image.EXT_Unlock();

		//for (int y = 0; y < m_partsOfImageSize.height; ++y)
		//{
		//	for (int x = 0; x < m_partsOfImageSize.width; ++x)
		//	{
		//		if (m_partsOfImage[x][y].processed = false)
		//		{
		//			if (m_partOfImageHistory[x][y] != 0)
		//				m_partOfImageHistory[x][y]--;
		//		}
		//	}
		//}
	}
}