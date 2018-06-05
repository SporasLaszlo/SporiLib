//#include "stdafx.h"
#include "LUTHomographyPointToPoint.h"

CLUTHomographyPointToPoint::CLUTHomographyPointToPoint(void)
{
	m_init = false;
	m_ID = -1;
	m_fromViewID = -1;
	m_toViewID = -1;

	m_fromSize.width = 0;
	m_fromSize.height = 0;

	m_toSize.width = 0;
	m_toSize.height = 0;

	m_tableSizeFromTo = 0;
	m_tableFromTo = NULL;
	m_tableSizeToFrom = 0;
	m_tableToFrom = NULL;
}
CLUTHomographyPointToPoint::~CLUTHomographyPointToPoint(void)
{
	EXT_Release();
}

int CLUTHomographyPointToPoint::_createTables()
{
	m_tableSizeFromTo = m_fromSize.width * m_fromSize.height;
	m_tableSizeToFrom = m_toSize.width * m_toSize.height;
	m_tableFromTo = new cv::Point*[m_tableSizeFromTo];
	m_tableToFrom = new cv::Point*[m_tableSizeToFrom];

	for(int i = 0; i < m_tableSizeFromTo; ++i)
		m_tableFromTo[i] = NULL;
	
	for(int i = 0; i < m_tableSizeToFrom; ++i)
		m_tableToFrom[i] = NULL;
	
	return EXIT_SUCCESS;
}
int CLUTHomographyPointToPoint::_fillTables(const cv::Mat *fromBinaryMask, const cv::Mat *toBinaryMask)
{
	cv::Point fromPoint, toPoint;
	
	cv::Mat toMask;
	cv::Mat fromMask;
	if (fromBinaryMask != NULL)
		//CCombinedIPPI::EXT_CopyImage(fromBinaryMask, &fromMask);
		fromMask = (*fromBinaryMask).clone();

	if (toBinaryMask != NULL)
		//CCombinedIPPI::EXT_CopyImage(toBinaryMask, &toMask);
		toMask = (*toBinaryMask).clone();

	for(int y = 0; y < m_fromSize.height; ++y)
	{
		for(int x = 0; x < m_fromSize.width; ++x)
		{
			if(fromBinaryMask == NULL)
			{
				fromPoint.x = x;
				fromPoint.y = y;

				toPoint = NFunctions::NImageProcessing::EXT_GetHomographySingelPointWithReturn(m_transformMat, fromPoint);

				if(toPoint.x > -1 && toPoint.y > -1 && toPoint.x < m_toSize.width && toPoint.y < m_toSize.height)
				{
					if(m_tableFromTo[y * m_fromSize.width + x] == NULL)
						m_tableFromTo[y * m_fromSize.width + x] = new cv::Point(toPoint.x, toPoint.y);

					if(m_tableToFrom[toPoint.y * m_toSize.width + toPoint.x] == NULL)
						m_tableToFrom[toPoint.y * m_toSize.width + toPoint.x] = new cv::Point(x, y);
				}
			}
			else
			{
				if(fromMask.at<uchar>(y, x) == 255)
				{
					fromPoint.x = x;
					fromPoint.y = y;

					toPoint = NFunctions::NImageProcessing::EXT_GetHomographySingelPointWithReturn(m_transformMat, fromPoint);

					if(toPoint.x > -1 && toPoint.y > -1 && toPoint.x < m_toSize.width && toPoint.y < m_toSize.height)
					{
						if(m_tableFromTo[y * m_fromSize.width + x] == NULL)
							m_tableFromTo[y * m_fromSize.width + x] = new cv::Point(toPoint.x, toPoint.y);

						if(m_tableToFrom[toPoint.y * m_toSize.width + toPoint.x] == NULL)
							m_tableToFrom[toPoint.y * m_toSize.width + toPoint.x] = new cv::Point(x, y);
					}
				}
			}
		}
	}

	for (int y = 0; y < m_toSize.height; ++y)
	{
		for (int x = 0; x < m_toSize.width; ++x)
		{
			if (toBinaryMask == NULL)
			{
				toPoint.x = x;
				toPoint.y = y;

				fromPoint = NFunctions::NImageProcessing::EXT_GetHomographyInverseSingelPointWithReturn(m_transformMat, toPoint);

				if (fromPoint.x > -1 && fromPoint.y > -1 && fromPoint.x < m_fromSize.width && fromPoint.y < m_fromSize.height)
				{
					if (m_tableToFrom[y * m_toSize.width + x] == NULL)
						m_tableToFrom[y * m_toSize.width + x] = new cv::Point(fromPoint.x, fromPoint.y);

					if (m_tableFromTo[fromPoint.y * m_fromSize.width + fromPoint.x] == NULL)
						m_tableFromTo[fromPoint.y * m_fromSize.width + fromPoint.x] = new cv::Point(x, y);
				}
			}
			else
			{
				if (toMask.at<uchar>(y, x) == 255)
				{
					toPoint.x = x;
					toPoint.y = y;

					fromPoint = NFunctions::NImageProcessing::EXT_GetHomographyInverseSingelPointWithReturn(m_transformMat, toPoint);

					if (fromPoint.x > -1 && fromPoint.y > -1 && fromPoint.x < m_fromSize.width && fromPoint.y < m_fromSize.height)
					{
						if (m_tableToFrom[y * m_toSize.width + x] == NULL)
							m_tableToFrom[y * m_toSize.width + x] = new cv::Point(fromPoint.x, fromPoint.y);

						if (m_tableFromTo[fromPoint.y * m_fromSize.width + fromPoint.x] == NULL)
							m_tableFromTo[fromPoint.y * m_fromSize.width + fromPoint.x] = new cv::Point(x, y);
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
int CLUTHomographyPointToPoint::EXT_Init(int ID, int fromViewID, int toViewID, cv::Size fromSize, cv::Size toSize, cv::Mat transformMat, const cv::Mat *fromBinaryMask, const cv::Mat *toBinaryMask)
{
	m_ID = ID;
	m_fromViewID = fromViewID;
	m_toViewID = toViewID;
	m_fromSize = fromSize;
	m_toSize = toSize;
	m_transformMat = transformMat;

	bool valid = true;

	if (m_transformMat.cols != 3 && m_transformMat.rows != 3)
	{
		valid = false;
		CGlobalLog::EXT_Log(CGlobalLog::EGlobalLogMessageType::LogWithError, __FILE__, "CLUTPointToPoint", "EXT_Init", __LINE__, "Transformation martix is not valid!");
		//if(m_data != NULL)
		//	m_data->m_log.EXT_Log(MessageType_LogWithException, m_objName, "EXT_Init", "Transformation martix is not valid!", 1);
	}
	if (m_fromSize.width == 0 || m_fromSize.height == 0 || m_fromSize.width == 0 || m_fromSize.height == 0)
	{
		valid = false;
		CGlobalLog::EXT_Log(CGlobalLog::EGlobalLogMessageType::LogWithError, __FILE__, "CLUTPointToPoint", "EXT_Init", __LINE__, "Size of from or size of to is 0!");
		//if(m_data != NULL)
		//	m_data->m_log.EXT_Log(MessageType_LogWithException, m_objName, "EXT_Init", "From or to size is 0!", 1);
	}
	if (fromBinaryMask != NULL)
	{
		if (fromBinaryMask->cols != m_fromSize.width || fromBinaryMask->rows != m_fromSize.height)
		{
			valid = false;
			CGlobalLog::EXT_Log(CGlobalLog::EGlobalLogMessageType::LogWithError, __FILE__, "CLUTPointToPoint", "EXT_Init", __LINE__, "Size of FromBinaryMask and size of input parameter are not equal!");
		}
	}
	if (toBinaryMask != NULL)
	{
		if (toBinaryMask->cols != m_toSize.width || toBinaryMask->rows != m_toSize.height)
		{
			valid = false;
			CGlobalLog::EXT_Log(CGlobalLog::EGlobalLogMessageType::LogWithError, __FILE__, "CLUTPointToPoint", "EXT_Init", __LINE__, "Size of ToBinaryMask and size of input parameter are not equal!");
		}
	}

	if(valid)
	{
		_createTables();
		_fillTables(fromBinaryMask, toBinaryMask);

		m_init = true;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
int CLUTHomographyPointToPoint::EXT_GetFromTo(cv::Point &inFrom, cv::Point &outTo)
{
	if(m_init)
	{
		if(inFrom.x > -1 && inFrom.y > -1 && inFrom.x < m_fromSize.width && inFrom.y < m_fromSize.height)
		{
			int index = inFrom.y * m_fromSize.width + inFrom.x;
			if(m_tableFromTo[index] != NULL)
			{
				outTo = *m_tableFromTo[index];
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}
int CLUTHomographyPointToPoint::EXT_GetToFrom(cv::Point &inTo, cv::Point &outFrom)
{
	if(m_init)
	{
		if(inTo.x > -1 && inTo.y > -1 && inTo.x < m_toSize.width && inTo.y < m_toSize.height)
		{
			int index = inTo.y * m_toSize.width + inTo.x;
			if(m_tableToFrom[index] != NULL)
			{
				outFrom = *m_tableToFrom[index];
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}
void CLUTHomographyPointToPoint::EXT_Release()
{
	if(m_init)
	{
		//std::cout << m_tableSizeFromTo << std::endl;
		//std::cout << m_tableSizeToFrom << std::endl;

		m_init = false;
		m_ID = -1;
		m_fromViewID = -1;
		m_toViewID = -1;

		m_fromSize.width = 0;
		m_fromSize.height = 0;

		m_toSize.width = 0;
		m_toSize.height = 0;

		cv::Point **iPos = m_tableFromTo;
		for(int i = 0; i < m_tableSizeFromTo; ++i)
		{
			if((*iPos) != NULL)
				delete (*iPos);
			iPos++;
		}
		delete m_tableFromTo;

		m_tableSizeFromTo = 0;
		m_tableFromTo = NULL;

		iPos = m_tableToFrom;
		for(int i = 0; i < m_tableSizeToFrom; ++i)
		{
			if((*iPos) != NULL)
				delete (*iPos);
			iPos++;
		}
		delete m_tableToFrom;

		m_tableSizeToFrom = 0;
		m_tableToFrom = NULL;
	}
}