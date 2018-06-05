//#include "stdafx.h"
#include "MotionDetector.h"

CMotionDetector::CMotionDetector()
{
	m_image.EXT_SetImageType(ImageType_Undefined);
	m_outImage.EXT_SetImageType(ImageType_Undefined);
}
CMotionDetector::~CMotionDetector()
{
}

CMutexImage* CMotionDetector::EXT_GetInputImage()
{
	return &m_image;
}
CMutexImage* CMotionDetector::EXT_GetMovingMask()
{
	return &m_outImage;
}

