#include "MotionDetector_OpenCV.h"

CMotionDetector_OpenCV::CMotionDetector_OpenCV()
{
	m_className = "CMotionDetector_OpenCV";
	
	m_image.EXT_SetImageType(ImageType_Undefined);
	m_outImage.EXT_SetImageType(ImageType_Undefined);
	
	m_imgSize.height = 0;
	m_imgSize.width = 0;
}
CMotionDetector_OpenCV::~CMotionDetector_OpenCV()
{
}

void CMotionDetector_OpenCV::EXT_Init(ImageType imageType, int history, float threshold, bool shadowDetection)
{
	m_image.EXT_SetImageType(imageType);
	m_outImage.EXT_SetImageType(imageType);
	
	m_backgroundSubstractor = cv::BackgroundSubtractorMOG2(history, threshold, shadowDetection);
	//m_backgroundSubstractor.setBool("detectShadows", true);
	m_backgroundSubstractor.setInt("nmixtures", 4);
	m_backgroundSubstractor.set("backgroundRatio", 0.4); 
	//m_backgroundSubstractor.set("fVarMin", 5);
}
void CMotionDetector_OpenCV::EXT_Detect(CMutexImage *image)
{
	m_classFunction = "EXT_Detect";
	
	m_image.EXT_SetImage(image);

	if (!((*m_image.EXT_GetImagePointer()).empty()))
	{   
		if (m_imgSize.height == 0)
		{
			m_imgSize.width = m_image.EXT_GetImagePointer()->cols;
			m_imgSize.height = m_image.EXT_GetImagePointer()->rows;
		}
		//if ((*m_fgimg.EXT_GetImagePointer()).empty())
		//{
		//	(m_image).EXT_Lock();
		//	(*m_fgimg.EXT_GetImagePointer()).create((*(m_image.EXT_GetImagePointer())).size(), (*(m_image.EXT_GetImagePointer())).type());
		//	(m_image).EXT_Unlock();
		//}
		//(*m_fgimg.EXT_GetImagePointer()) = cv::Scalar::all(0);

		if (m_imgSize.width == m_image.EXT_GetImagePointer()->cols && m_imgSize.height == m_image.EXT_GetImagePointer()->rows)
		{
			m_image.EXT_Lock();
			m_outImage.EXT_Lock();
		
			m_backgroundSubstractor((*m_image.EXT_GetImagePointer()), (*m_outImage.EXT_GetImagePointer()), true ? -1 : 0);
		
			m_outImage.EXT_Unlock();
			m_image.EXT_Unlock();
		}
		else
			CGlobalLog::EXT_Log(LogWithError, __FILE__, m_className, m_classFunction, __LINE__, "Stored size and input image size are not equal!");
		
		//test
		//cv::Mat a = cv::Mat()
		//cv::Mat bgMask = cv::Mat(image->cols, image->rows, CV_8UC3);
		
		//m_backgroundSubstractor.getBackgroundImage(bgMask);
		//cv::namedWindow("BG mask", CV_WINDOW_FREERATIO | CV_WINDOW_NORMAL);
		//cv::imshow("BG mask", bgMask);
		//cv::waitKey(5);
		
		//(*(m_img).EXT_get_image_pointer()).copyTo((*(m_fgimg).EXT_get_image_pointer()), (*(m_out_img).EXT_get_image_pointer()));

	}
	else
		CGlobalLog::EXT_Log(LogWithError, __FILE__, m_className, m_classFunction, __LINE__, "Input image is empty!");
}

