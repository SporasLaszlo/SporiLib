//#include "stdafx.h"
#include "MutexImage.h"

CMutexImage::CMutexImage()
{
	m_cameraType = ImageType_Undefined;
}
CMutexImage::CMutexImage(cv::Mat *image)
{
	EXT_Lock();

	_copy(image, &m_image);

	EXT_Unlock();
}
CMutexImage::~CMutexImage()
{
}

void CMutexImage::EXT_Lock()
{
	m_mutex.lock();
}
void CMutexImage::EXT_Unlock()
{
	m_mutex.unlock();
}
void CMutexImage::EXT_SetImage(cv::Mat* image)
{
	EXT_Lock();
	
	_copy(image, &m_image);
	
	EXT_Unlock();
}
void CMutexImage::EXT_SetImage(CMutexImage* image)
{
	EXT_Lock();
	image->EXT_Lock();

	_copy(image->EXT_GetImagePointer(), &m_image);

	image->EXT_Unlock();
	EXT_Unlock();
}
cv::Mat* CMutexImage::EXT_GetImagePointer()
{
	return &m_image;
}
void CMutexImage::EXT_CopyImage(cv::Mat *outputImage)
{
	EXT_Lock();
	
	_copy(&m_image, outputImage);

	EXT_Unlock();
}
void CMutexImage::EXT_CopyImage(cv::Mat *inputImage, cv::Mat *outputImage)
{
	_copy(inputImage, outputImage);
}
void CMutexImage::EXT_SetImageType(ImageType type)
{
	m_cameraType = type;
}
ImageType CMutexImage::EXT_GetImageType()
{
	return m_cameraType;
}
void CMutexImage::_copy(cv::Mat *from, cv::Mat *to)
{
	//sima clone
	(*to) = (*from).clone();
	
	//ipp
//	if(!(from->empty()))
//	{
//		if(from->type() == CV_8UC1)
//		{
//			if(!(to->empty()) && to->rows == from->rows && to->cols == from->cols && to->type() == from->type())
//			{
//				int srcStep = from->cols * sizeof(Ipp8u);
//				int dstStep = from->cols * sizeof(Ipp8u);
//				IppiSize roiSize = {from->cols, from->rows};
//
//				ippiCopy_8u_C1R((const Ipp8u*)(&from->data[0]), srcStep, (Ipp8u*)&to->data[0], dstStep, roiSize);
//			}
//			else
//			{
//				to->create(from->rows, from->cols, from->type());
//
//				int srcStep = from->cols * sizeof(Ipp8u);
//				int dstStep = from->cols * sizeof(Ipp8u);
//				IppiSize roiSize = {from->cols, from->rows};
//
//				ippiCopy_8u_C1R((const Ipp8u*)(&from->data[0]), srcStep, (Ipp8u*)&to->data[0], dstStep, roiSize);
//			}
//		}
//		else if(from->type() == CV_8UC3)
//		{
//			if(!(to->empty()) && to->rows == from->rows && to->cols == from->cols && to->type() == from->type())
//			{
//				int srcStep = from->cols * sizeof(Ipp8u) * 3;
//				int dstStep = from->cols * sizeof(Ipp8u) * 3;
//				IppiSize roiSize = {from->cols, from->rows};
//
//				ippiCopy_8u_C3R((const Ipp8u*)(&from->data[0]), srcStep, (Ipp8u*)&to->data[0], dstStep, roiSize);
//			}
//			else
//			{
//				to->create(from->rows, from->cols, from->type());
//
//				int srcStep = from->cols * sizeof(Ipp8u) * 3;
//				int dstStep = from->cols * sizeof(Ipp8u) * 3;
//				IppiSize roiSize = {from->cols, from->rows};
//
//				ippiCopy_8u_C3R((const Ipp8u*)(&from->data[0]), srcStep, (Ipp8u*)&to->data[0], dstStep, roiSize);
//			}
//		}
//	}
}