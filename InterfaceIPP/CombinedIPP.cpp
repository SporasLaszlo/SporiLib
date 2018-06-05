#include "stdafx.h"
#include "CombinedIPP.h"

CCombinedIPP::CCombinedIPP(void)
{
}
CCombinedIPP::~CCombinedIPP(void)
{
}

void CCombinedIPP::EXT_ResizeImage(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y, IppiInterpolationType interpolationType)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			if(interpolationType == ippLinear)
			{
				_resize_image_8UC1_Linear(input_image, output_image, dst_size_x, dst_size_y);
			}
			else if(interpolationType == ippSuper)
			{
				_resize_image_8UC1_Super(input_image, output_image, dst_size_x, dst_size_y);
			}
			else if(interpolationType == ippLanczos)
			{
				_resize_image_8UC1_Lanczos(input_image, output_image, dst_size_x, dst_size_y);
			}
		}
		else if(input_image->type() == CV_8UC3)
		{
			if(interpolationType == ippLinear)
			{
				_resize_image_8UC3_Linear(input_image, output_image, dst_size_x, dst_size_y);
			}
			else if(interpolationType == ippSuper)
			{
				_resize_image_8UC3_Super(input_image, output_image, dst_size_x, dst_size_y);
			}
			else if(interpolationType == ippLanczos)
			{
				_resize_image_8UC3_Lanczos(input_image, output_image, dst_size_x, dst_size_y);
			}
		}
	}
}
void CCombinedIPP::_resize_image_8UC1_Linear(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width;
	int dstStep = sizeof(Ipp8u)*dstSize.width;

	output_image->create(dstSize.height, dstSize.width, CV_8UC1);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 1;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippLinear, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeLinearInit_8u(srcSize, dstSize, pSpec);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeLinear_8u_C1R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, border, 0, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}
void CCombinedIPP::_resize_image_8UC3_Linear(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width*3;
	int dstStep = sizeof(Ipp8u)*dstSize.width*3;

	output_image->create(dstSize.height, dstSize.width, CV_8UC3);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 3;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippLinear, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeLinearInit_8u(srcSize, dstSize, pSpec);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeLinear_8u_C3R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, border, 0, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}
void CCombinedIPP::_resize_image_8UC1_Super(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width;
	int dstStep = sizeof(Ipp8u)*dstSize.width;

	output_image->create(dstSize.height, dstSize.width, CV_8UC1);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 1;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippSuper, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeSuperInit_8u(srcSize, dstSize, pSpec);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeSuper_8u_C1R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}
void CCombinedIPP::_resize_image_8UC3_Super(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width*3;
	int dstStep = sizeof(Ipp8u)*dstSize.width*3;

	output_image->create(dstSize.height, dstSize.width, CV_8UC3);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 3;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippSuper, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeSuperInit_8u(srcSize, dstSize, pSpec);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeSuper_8u_C3R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}
void CCombinedIPP::_resize_image_8UC1_Lanczos(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width;
	int dstStep = sizeof(Ipp8u)*dstSize.width;

	output_image->create(dstSize.height, dstSize.width, CV_8UC1);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 1;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippLanczos, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeLanczosInit_8u(srcSize, dstSize, 3, pSpec, pInitBuf);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeLanczos_8u_C1R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, border, 0, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}
void CCombinedIPP::_resize_image_8UC3_Lanczos(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y)
{
	IppiSize srcSize = {input_image->cols, input_image->rows};
	IppiSize dstSize = {dst_size_x, dst_size_y};

	int srcStep = sizeof(Ipp8u)*srcSize.width*3;
	int dstStep = sizeof(Ipp8u)*dstSize.width*3;

	output_image->create(dstSize.height, dstSize.width, CV_8UC3);

	IppiResizeSpec_32f* pSpec = 0;
	int specSize = 0, initSize = 0, bufSize = 0;
	Ipp8u* pBuffer = 0;
	Ipp8u* pInitBuf = 0;
	Ipp32u numChannels = 3;
	IppiPoint dstOffset = {0, 0};
	IppiBorderType border = ippBorderRepl;
	/* Spec and init buffer sizes */
	ippiResizeGetSize_8u(srcSize, dstSize, ippLanczos, 0, &specSize, &initSize);
	/* Memory allocation */
	pInitBuf = ippsMalloc_8u(initSize);
	pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
	/* Filter initialization */
	ippiResizeLanczosInit_8u(srcSize, dstSize, 3, pSpec, pInitBuf);
	ippsFree(pInitBuf);
	/* work buffer size */
	ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
	pBuffer = ippsMalloc_8u(bufSize);
	/* Resize processing */
	ippiResizeLanczos_8u_C3R((Ipp8u*)&input_image->data[0], srcStep, (Ipp8u*)&output_image->data[0], dstStep, dstOffset, dstSize, border, 0, pSpec, pBuffer);
	ippsFree(pSpec);
	ippsFree(pBuffer);
}

void CCombinedIPP::EXT_RGBToGray(cv::Mat *input_image, cv::Mat *output_image)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC3)
		{
			IppiSize srcSize = {input_image->cols, input_image->rows};
			IppiSize dstSize = {srcSize.width, srcSize.height};
			IppiSize srcRoi = {srcSize.width, srcSize.height};

			int srcStep = sizeof(Ipp8u)*srcSize.width*3;
			int dstStep = sizeof(Ipp8u)*dstSize.width;

			output_image->create(dstSize.height, dstSize.width, CV_8UC1);

			ippiRGBToGray_8u_C3C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, srcRoi);
		}
	}
}
void CCombinedIPP::EXT_Integral(cv::Mat *input_image, cv::Mat *output_image)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			IppiSize srcSize = {input_image->cols, input_image->rows};
			IppiSize dstSize = {srcSize.width+1, srcSize.height+1};
			IppiSize srcRoi = {srcSize.width, srcSize.height};

			int srcStep = sizeof(Ipp8u)*srcSize.width;
			int dstStep = sizeof(Ipp32f)*dstSize.width;

			output_image->create(dstSize.height, dstSize.width, CV_32FC1);

			ippiIntegral_8u32f_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, srcRoi, 0);
		}
	}
}
void CCombinedIPP::EXT_CopyImage(cv::Mat *input_image, cv::Mat *output_image, IppiRect *roi)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(roi == NULL)
		{
			if(input_image->type() == CV_8UC1)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp8u);
				int dstStep = input_image->cols*sizeof(Ipp8u);
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_8UC3)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp8u)*3;
				int dstStep = input_image->cols*sizeof(Ipp8u)*3;
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_8u_C3R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_32FC1)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp32f);
				int dstStep = input_image->cols*sizeof(Ipp32f);
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_32f_C1R((const Ipp32f*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_32FC3)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp32f)*3;
				int dstStep = input_image->cols*sizeof(Ipp32f)*3;
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_32f_C3R((const Ipp32f*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, roiSize);
			}
		}
		else//ez a rész bugzik a roi parameterekkel
		{
			if(input_image->type() == CV_8UC1)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp8u);
				int dstStep = input_image->cols*sizeof(Ipp8u);
				IppiSize roiSize = {input_image->cols, input_image->rows};

				int maskStep = roi->width;
				IppiSize maskSize = {roi->width, roi->height};

				cv::Mat mask;
				mask.create(maskSize.height, maskSize.width, CV_8UC1);

				ippiSet_8u_C1R(1, (Ipp8u*)(&mask.data[0]), maskStep, maskSize);
				ippiSet_8u_C1R(0, (Ipp8u*)(&output_image->data[0]), dstStep, roiSize);

				//std::cout << roiSize.width * roi->y + roi->x << std::endl;
				//std::cout << srcStep << std::endl;
				//std::cout << dstStep << std::endl;
				//std::cout << maskSize.width << std::endl;
				//std::cout << maskSize.height << std::endl;
				//std::cout << maskStep << std::endl;

				//cv::imshow("111", *input_image);
				//cv::imshow("222", *output_image);
				//cv::waitKey(0);

				ippiCopy_8u_C1MR((const Ipp8u*)(&input_image->data[roiSize.width * roi->y + roi->x]), srcStep, (Ipp8u*)&output_image->data[roiSize.width * roi->y + roi->x], dstStep, maskSize, (const Ipp8u*)(&mask.data[0]), maskStep);
				//ippiCopy_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_8UC3)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp8u)*3;
				int dstStep = input_image->cols*sizeof(Ipp8u)*3;
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_8u_C3R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_32FC1)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp32f);
				int dstStep = input_image->cols*sizeof(Ipp32f);
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_32f_C1R((const Ipp32f*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, roiSize);
			}
			else if(input_image->type() == CV_32FC3)
			{
				output_image->create(input_image->rows, input_image->cols, input_image->type());

				int srcStep = input_image->cols*sizeof(Ipp32f)*3;
				int dstStep = input_image->cols*sizeof(Ipp32f)*3;
				IppiSize roiSize = {input_image->cols, input_image->rows};

				ippiCopy_32f_C3R((const Ipp32f*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, roiSize);
			}
		}

		/*else if(input_image->type() == CV_64FC1)
		{
			output_image->create(input_image->rows, input_image->cols, input_image->type());

			int srcStep = input_image->cols*sizeof(Ipp64f);
			int dstStep = input_image->cols*sizeof(Ipp64f);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			ippicopy_64((const Ipp32f*)(&input_image->data[0]), srcStep, (Ipp32f*)&output_image->data[0], dstStep, roiSize);
		}*/
	}
}
void CCombinedIPP::EXT_Erode(cv::Mat *input_image, cv::Mat *output_image)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			int dstStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			if(output_image != NULL)
			{
				//output_image->create(roiSize.height+2, roiSize.width+2, CV_8UC1);
				
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);

				IppiMorphState* pSpec = NULL;
				Ipp8u* pBuffer = NULL;
				//IppiSize srcSize = {5, 5};
				Ipp8u pMask[3*3] = {1, 1, 1,
				1, 1, 1,
				1, 1, 1};
				IppiSize maskSize = {3, 3};
				
				//int srcStep = 5*sizeof(Ipp16u);
				//int dstStep = 5*sizeof(Ipp16u);
				//int dstSize = 5;
				IppStatus status = ippStsNoErr;
				int specSize = 0, bufferSize = 0;
				IppiBorderType borderType= ippBorderRepl;
				Ipp8u borderValue = 0;
				status = ippiMorphologyBorderGetSize_8u_C1R(roiSize, maskSize, &specSize, &bufferSize);

				if (status != ippStsNoErr) std::cout << status << std::endl;

				pSpec = (IppiMorphState*)ippsMalloc_8u(specSize);
				pBuffer = (Ipp8u*)ippsMalloc_8u(bufferSize);
				status = ippiMorphologyBorderInit_8u_C1R(roiSize, pMask, maskSize, pSpec, pBuffer);

				if (status != ippStsNoErr)
				{
					ippsFree(pBuffer);
					ippsFree(pSpec);
				
					std::cout << status << std::endl;
				}
				status = ippiErodeBorder_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize, borderType, borderValue, pSpec, pBuffer);
				ippsFree(pBuffer);
				ippsFree(pSpec);

				//ippiErodeBorder_8u_C1R((const Ipp8u*)(&input_image->data[roiSize.width+3]), 
				//ippiErode3x3_8u_C1R((const Ipp8u*)(&input_image->data[roiSize.width+3]), srcStep, (Ipp8u*)&output_image->data[roiSize.width+3], dstStep, roiSize);
			}
			else
			{
				//output_image->create(roiSize.height+2, roiSize.width+2, CV_8UC1);
				//output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				cv::Mat outImg = cv::Mat(roiSize.height, roiSize.width, CV_8UC1);

				IppiMorphState* pSpec = NULL;
				Ipp8u* pBuffer = NULL;
				//IppiSize srcSize = {5, 5};
				Ipp8u pMask[3*3] = {1, 1, 1,
				1, 1, 1,
				1, 1, 1};
				IppiSize maskSize = {3, 3};
				
				//int srcStep = 5*sizeof(Ipp16u);
				//int dstStep = 5*sizeof(Ipp16u);
				//int dstSize = 5;
				IppStatus status = ippStsNoErr;
				int specSize = 0, bufferSize = 0;
				IppiBorderType borderType= ippBorderRepl;
				Ipp8u borderValue = 0;
				status = ippiMorphologyBorderGetSize_8u_C1R(roiSize, maskSize, &specSize, &bufferSize);

				if (status != ippStsNoErr) std::cout << status << std::endl;

				pSpec = (IppiMorphState*)ippsMalloc_8u(specSize);
				pBuffer = (Ipp8u*)ippsMalloc_8u(bufferSize);
				status = ippiMorphologyBorderInit_8u_C1R(roiSize, pMask, maskSize, pSpec, pBuffer);

				if (status != ippStsNoErr)
				{
					ippsFree(pBuffer);
					ippsFree(pSpec);
				
					std::cout << status << std::endl;
				}
				status = ippiErodeBorder_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&outImg.data[0], dstStep, roiSize, borderType, borderValue, pSpec, pBuffer);
				ippsFree(pBuffer);
				ippsFree(pSpec);

				CCombinedIPP::EXT_CopyImage(&outImg, input_image);
			}
		}
	}
}
void CCombinedIPP::EXT_Dilate(cv::Mat *input_image, cv::Mat *output_image)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			int dstStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			if(output_image != NULL)
			{
				//output_image->create(roiSize.height+2, roiSize.width+2, CV_8UC1);
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);

				IppiMorphState* pSpec = NULL;
				Ipp8u* pBuffer = NULL;
				//IppiSize srcSize = {5, 5};
				Ipp8u pMask[3*3] = {1, 1, 1,
				1, 1, 1,
				1, 1, 1};
				IppiSize maskSize = {3, 3};
				
				//int srcStep = 5*sizeof(Ipp16u);
				//int dstStep = 5*sizeof(Ipp16u);
				//int dstSize = 5;
				IppStatus status = ippStsNoErr;
				int specSize = 0, bufferSize = 0;
				IppiBorderType borderType= ippBorderRepl;
				Ipp8u borderValue = 0;
				status = ippiMorphologyBorderGetSize_8u_C1R(roiSize, maskSize, &specSize, &bufferSize);

				if (status != ippStsNoErr) std::cout << status << std::endl;

				pSpec = (IppiMorphState*)ippsMalloc_8u(specSize);
				pBuffer = (Ipp8u*)ippsMalloc_8u(bufferSize);
				status = ippiMorphologyBorderInit_8u_C1R(roiSize, pMask, maskSize, pSpec, pBuffer);

				if (status != ippStsNoErr)
				{
					ippsFree(pBuffer);
					ippsFree(pSpec);
				
					std::cout << status << std::endl;
				}
				status = ippiDilateBorder_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize, borderType, borderValue, pSpec, pBuffer);
				ippsFree(pBuffer);
				ippsFree(pSpec);

				//ippiDilateBorder_8u_C1R;
				//ippiDilate3x3_8u_C1R((const Ipp8u*)(&input_image->data[roiSize.width+3]), srcStep, (Ipp8u*)&output_image->data[roiSize.width+3], dstStep, roiSize);
			}
			else
			{
				//output_image->create(roiSize.height+2, roiSize.width+2, CV_8UC1);
				//output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				cv::Mat outImg = cv::Mat(roiSize.height, roiSize.width, CV_8UC1);

				IppiMorphState* pSpec = NULL;
				Ipp8u* pBuffer = NULL;
				//IppiSize srcSize = {5, 5};
				Ipp8u pMask[3*3] = {1, 1, 1,
				1, 1, 1,
				1, 1, 1};
				IppiSize maskSize = {3, 3};
				
				//int srcStep = 5*sizeof(Ipp16u);
				//int dstStep = 5*sizeof(Ipp16u);
				//int dstSize = 5;
				IppStatus status = ippStsNoErr;
				int specSize = 0, bufferSize = 0;
				IppiBorderType borderType= ippBorderRepl;
				Ipp8u borderValue = 0;
				status = ippiMorphologyBorderGetSize_8u_C1R(roiSize, maskSize, &specSize, &bufferSize);

				if (status != ippStsNoErr) std::cout << status << std::endl;

				pSpec = (IppiMorphState*)ippsMalloc_8u(specSize);
				pBuffer = (Ipp8u*)ippsMalloc_8u(bufferSize);
				status = ippiMorphologyBorderInit_8u_C1R(roiSize, pMask, maskSize, pSpec, pBuffer);

				if (status != ippStsNoErr)
				{
					ippsFree(pBuffer);
					ippsFree(pSpec);
				
					std::cout << status << std::endl;
				}
				status = ippiDilateBorder_8u_C1R((const Ipp8u*)(&input_image->data[0]), srcStep, (Ipp8u*)&outImg.data[0], dstStep, roiSize, borderType, borderValue, pSpec, pBuffer);
				ippsFree(pBuffer);
				ippsFree(pSpec);

				CCombinedIPP::EXT_CopyImage(&outImg, input_image);
			}
		}
	}
}
void CCombinedIPP::EXT_Threshold_GT(cv::Mat *input_image, Ipp8u thresValue, Ipp8u value)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			ippiThreshold_GTVal_8u_C1IR((Ipp8u*)(&input_image->data[0]), srcStep, roiSize, thresValue, value);
		}
	}
}
void CCombinedIPP::EXT_Threshold_LT(cv::Mat *input_image, Ipp8u thresValue, Ipp8u value)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			ippiThreshold_LTVal_8u_C1IR((Ipp8u*)(&input_image->data[0]), srcStep, roiSize, thresValue, value);
		}
	}
}
void CCombinedIPP::EXT_Threshold(cv::Mat *input_image, Ipp8u thresValue, Ipp8u minValue, Ipp8u maxValue)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			ippiThreshold_LTVal_8u_C1IR((Ipp8u*)(&input_image->data[0]), srcStep, roiSize, thresValue, minValue);

			//std::cout << stat << std::endl;
			ippiThreshold_GTVal_8u_C1IR((Ipp8u*)(&input_image->data[0]), srcStep, roiSize, thresValue-1, maxValue);

			//std::cout << stat << std::endl;
			//ippiThreshold_LTValGTVal_8u_C1IR((Ipp8u*)(&input_image->data[0]), srcStep, roiSize, thresValue, minValue, thresValue, maxValue);
		}
	}
}
void CCombinedIPP::EXT_Add(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image)
{
	if (input_image1 != NULL && !(input_image1->empty()) && input_image2 != NULL && !(input_image2->empty()))
	{
		if (input_image1->type() == CV_8UC1 && input_image2->type() == CV_8UC1 && input_image1->cols == input_image2->cols && input_image1->rows == input_image2->rows)
		{
			int srcStep = input_image1->cols*sizeof(Ipp8u);
			int dstStep = input_image2->cols*sizeof(Ipp8u);
			IppiSize roiSize = { input_image1->cols, input_image1->rows };

			if (output_image != NULL)
			{
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				ippiAdd_8u_C1RSfs((const Ipp8u*)&input_image1->data[0], srcStep, (const Ipp8u*)&input_image2->data[0], dstStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize, 0);
				//ippiAnd_8u_C1R((const Ipp8u*)&input_image1->data[0], srcStep, (const Ipp8u*)&input_image2->data[0], dstStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else
			{
				ippiAdd_8u_C1IRSfs((const Ipp8u*)&input_image1->data[0], srcStep, (Ipp8u*)&input_image2->data[0], dstStep, roiSize, 0);
				//ippiAnd_8u_C1IR((const Ipp8u*)&input_image1->data[0], srcStep, (Ipp8u*)&input_image2->data[0], dstStep, roiSize);
			}
		}
	}
}
void CCombinedIPP::EXT_And(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image)
{
	if(input_image1 != NULL && !(input_image1->empty()) && input_image2 != NULL && !(input_image2->empty()))
	{
		if(input_image1->type() == CV_8UC1 && input_image2->type() == CV_8UC1 && input_image1->cols == input_image2->cols && input_image1->rows == input_image2->rows)
		{
			int srcStep = input_image1->cols*sizeof(Ipp8u);
			int dstStep = input_image2->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image1->cols, input_image1->rows};

			if(output_image != NULL)
			{
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				ippiAnd_8u_C1R((const Ipp8u*)&input_image1->data[0], srcStep, (const Ipp8u*)&input_image2->data[0], dstStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else
			{
				ippiAnd_8u_C1IR((const Ipp8u*)&input_image1->data[0], srcStep, (Ipp8u*)&input_image2->data[0], dstStep, roiSize);
			}
		}
	}
}
void CCombinedIPP::EXT_AndWithROI(cv::Mat &inImg, cv::Mat &inOutImg, IppiRect roi, cv::Mat *outImg)
{
	if(!(inImg.empty()) && !(inOutImg.empty()))
	{
		if(inImg.type() == CV_8UC1 && inOutImg.type() == CV_8UC1 && inImg.cols == inOutImg.cols && inImg.rows == inOutImg.rows)
		{
			int srcStep = inImg.cols*sizeof(Ipp8u);
			int dstStep = inOutImg.cols*sizeof(Ipp8u);
			IppiSize srcSize = {inImg.cols, inImg.rows};
			IppiSize roiSize = {roi.width, roi.height};

			if(outImg != NULL)
			{
				outImg->create(srcSize.height, srcSize.width, CV_8UC1);
				ippiSet_8u_C1R(0, (Ipp8u*)(&outImg->data[0]), dstStep, srcSize);
				ippiAnd_8u_C1R((const Ipp8u*)&inImg.data[srcSize.width * roi.y + roi.x], srcStep, (const Ipp8u*)&inOutImg.data[srcSize.width * roi.y + roi.x], dstStep, (Ipp8u*)&outImg->data[srcSize.width * roi.y + roi.x], dstStep, roiSize);
			}
			else
			{
				ippiAnd_8u_C1IR((const Ipp8u*)&inImg.data[srcSize.width * roi.y + roi.x], srcStep, (Ipp8u*)&inOutImg.data[srcSize.width * roi.y + roi.x], dstStep, roiSize);
			}
		}
	}
}
void CCombinedIPP::EXT_Or(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image)
{
	if(input_image1 != NULL && !(input_image1->empty()) && input_image2 != NULL && !(input_image2->empty()))
	{
		if(input_image1->type() == CV_8UC1 && input_image2->type() == CV_8UC1 && input_image1->cols == input_image2->cols && input_image1->rows == input_image2->rows)
		{
			int srcStep = input_image1->cols*sizeof(Ipp8u);
			int dstStep = input_image2->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image1->cols, input_image1->rows};

			if(output_image != NULL)
			{
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				ippiOr_8u_C1R((const Ipp8u*)&input_image1->data[0], srcStep, (const Ipp8u*)&input_image2->data[0], dstStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else
			{
				ippiOr_8u_C1IR((const Ipp8u*)&input_image1->data[0], srcStep, (Ipp8u*)&input_image2->data[0], dstStep, roiSize);
			}
		}
	}
}
void CCombinedIPP::EXT_Xor(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image)
{
	if(input_image1 != NULL && !(input_image1->empty()) && input_image2 != NULL && !(input_image2->empty()))
	{
		if(input_image1->type() == CV_8UC1 && input_image2->type() == CV_8UC1 && input_image1->cols == input_image2->cols && input_image1->rows == input_image2->rows)
		{
			int srcStep = input_image1->cols*sizeof(Ipp8u);
			int dstStep = input_image2->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image1->cols, input_image1->rows};

			if(output_image != NULL)
			{
				output_image->create(roiSize.height, roiSize.width, CV_8UC1);
				ippiXor_8u_C1R((const Ipp8u*)&input_image1->data[0], srcStep, (const Ipp8u*)&input_image2->data[0], dstStep, (Ipp8u*)&output_image->data[0], dstStep, roiSize);
			}
			else
			{
				ippiXor_8u_C1IR((const Ipp8u*)&input_image1->data[0], srcStep, (Ipp8u*)&input_image2->data[0], dstStep, roiSize);
			}
		}
	}
}
void CCombinedIPP::EXT_FloodFill(cv::Mat *input_image, IppiPoint seed, Ipp8u newVal, IppiConnectedComp *pRegion)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			int pBufSize = 0;

			ippiFloodFillGetSize(roiSize, &pBufSize);
			Ipp8u* pBuffer = ippsMalloc_8u(pBufSize);

			ippiFloodFill_8Con_8u_C1IR((Ipp8u*)&input_image->data[0], srcStep, roiSize, seed, newVal, pRegion, pBuffer);

			if (pBuffer != NULL)
			{
				ippsFree(pBuffer);
			}
		}
	}
}
void CCombinedIPP::EXT_FloodFillRange(cv::Mat *input_image, IppiPoint seed, Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta, IppiConnectedComp *pRegion)
{
	if(input_image != NULL && !(input_image->empty()))
	{
		if(input_image->type() == CV_8UC1)
		{
			int srcStep = input_image->cols*sizeof(Ipp8u);
			IppiSize roiSize = {input_image->cols, input_image->rows};

			int pBufSize = 0;
			//IppiConnectedComp pRegion;

			ippiFloodFillGetSize(roiSize, &pBufSize);
			Ipp8u* pBuffer = ippsMalloc_8u(pBufSize);

			ippiFloodFill_Range8Con_8u_C1IR((Ipp8u*)&input_image->data[0], srcStep, roiSize, seed, newVal, minDelta, maxDelta, pRegion, pBuffer);

			if (pBuffer != NULL)
			{
				ippsFree(pBuffer);
			}
		}
	}
}
bool CCombinedIPP::EXT_GetWarpPerspectiveInf(IppiRect rectRoi, cv::Mat H, int *out_width, int *out_height, int *out_offset_x, int *out_offset_y)
{
	//if(!H.empty())
	//{
		std::vector<IppiPoint> points;
		std::vector<IppiPoint> transform_points;

		IppiPoint new_element = {rectRoi.x, rectRoi.y};
		points.push_back(new_element);
		new_element.x = rectRoi.x + rectRoi.width;
		new_element.y = rectRoi.y;
		points.push_back(new_element);
		new_element.x = rectRoi.x + rectRoi.width;
		new_element.y = rectRoi.y + rectRoi.height;
		points.push_back(new_element);
		new_element.x = rectRoi.x;
		new_element.y = rectRoi.y + rectRoi.height;
		points.push_back(new_element);

		cv::Mat dummy_point = cv::Mat(3, 1, H.type());

		for(unsigned iPos = 0; iPos < points.size(); iPos++)
		{
			dummy_point.at<double>(0,0) = points.at(iPos).x;
			dummy_point.at<double>(1,0) = points.at(iPos).y;
			dummy_point.at<double>(2,0) = 1;

			std::cout << "-------" << std::endl;
			std::cout << "Bemenet" << std::endl;
			std::cout << points.at(iPos).x << std::endl;
			std::cout << points.at(iPos).y << std::endl;

			dummy_point = H * dummy_point;

			std::cout << "(2, 0) pont" << std::endl;
			std::cout << dummy_point.at<double>(2,0) << std::endl;

			new_element.x = (int)(dummy_point.at<double>(0,0)/dummy_point.at<double>(2,0));
			new_element.y = (int)(dummy_point.at<double>(1,0)/dummy_point.at<double>(2,0));

			transform_points.push_back(new_element);

			std::cout << "Kimenet" << std::endl;
			std::cout << transform_points.at(iPos).x << std::endl;
			std::cout << transform_points.at(iPos).y << std::endl;
			std::cout << "-------" << std::endl;
		}

	//	int dest_image_min_x = INT_MAX;
	//	int dest_image_max_x = INT_MIN;
	//	int dest_image_min_y = INT_MAX;
	//	int dest_image_max_y = INT_MIN;

	//	for(int k = 0; k < 4; k++)
	//	{
	//		if(transform_points.at(k).x > dest_image_max_x)
	//		{
	//			dest_image_max_x = transform_points.at(k).x;
	//		}
	//		if(transform_points.at(k).x < dest_image_min_x)
	//		{
	//			dest_image_min_x = transform_points.at(k).x;
	//		}
	//		if(transform_points.at(k).y > dest_image_max_y)
	//		{
	//			dest_image_max_y = transform_points.at(k).y;
	//		}
	//		if(transform_points.at(k).y < dest_image_min_y)
	//		{
	//			dest_image_min_y = transform_points.at(k).y;
	//		}
	//	}

	//	std::cout << "minx: " << std::endl;
	//	std::cout << dest_image_min_x << std::endl;
	//	std::cout << "maxx: " << std::endl;
	//	std::cout << dest_image_max_x << std::endl;

	//	std::cout << std::endl;

	//	std::cout << "miny: " << std::endl;
	//	std::cout << dest_image_min_y << std::endl;
	//	std::cout << "maxy: " << std::endl;
	//	std::cout << dest_image_max_y << std::endl;

	//	*out_offset_x = dest_image_min_x;
	//	*out_offset_y = dest_image_min_y;
	//	*out_width = dest_image_max_x - dest_image_min_x;
	//	*out_height = dest_image_max_y - dest_image_min_y;

	//	/*double corners[4][2];
	//	double bound[2][2];
	//
	//	double double_H[3][3];

	//	for(int y = 0; y < 3; y++)
	//	{
	//		for(int x = 0; x < 3; x++)
	//		{
	//			double_H[y][x] = (double)H.at<double>(y, x);
	//		}
	//	}

	//	IppStatus status = ippiGetPerspectiveQuad(rectRoi, corners, double_H);

	//	std::cout << status << std::endl;

	//	for(int i = 0; i < 4; i++)
	//	{
	//		std::cout << corners[i][0] << std::endl;
	//		std::cout << corners[i][1] << std::endl;
	//	}*/

	//	return true;
	//}
	//else
	//{
	//	std::cout << "EXT_getWarpPerspectiveInf error" << std::endl;
	//	*out_offset_x = 0;
	//	*out_offset_y = 0;
	//	*out_width = 0;
	//	*out_height = 0;
	//	return false;
	//}

	//double corners[4][2];
	double bound[2][2];
	
	double double_H[3][3];

	for(int y = 0; y < 3; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			double_H[y][x] = (double)H.at<double>(y, x);
		}
	}

	IppStatus status = ippiGetPerspectiveBound(rectRoi, bound, double_H);
	//ippiGetPerspectiveQuad(rectRoi, corners, double_H);

	if(status == ippStsNoErr)
	{
		*out_offset_x = (int)bound[0][0];
		*out_offset_y = (int)bound[0][1];
		*out_width = (int)(bound[1][0] - bound[0][0]);
		*out_height = (int)(bound[1][1] - bound[0][1]);

		/*std::cout << "_______" << std::endl;
		std::cout << "_______" << std::endl;
		std::cout << bound[0][0] << std::endl;
		std::cout << bound[0][1] << std::endl;
		std::cout << "-------" << std::endl;
		std::cout << bound[1][0] << std::endl;
		std::cout << bound[1][1] << std::endl;
		std::cout << "-------" << std::endl;
		std::cout << "-------" << std::endl;

		int dest_image_min_x = INT_MAX;
		int dest_image_max_x = INT_MIN;
		int dest_image_min_y = INT_MAX;
		int dest_image_max_y = INT_MIN;

		for(int k = 0; k < 4; k++)
		{
			std::cout << "_______" << std::endl;
			std::cout << corners[k][0] << std::endl;
			std::cout << corners[k][1] << std::endl;
			std::cout << "-------" << std::endl;

			if(corners[k][0] > dest_image_max_x)
			{
				dest_image_max_x = corners[k][0];
			}
			if(corners[k][0] < dest_image_min_x)
			{
				dest_image_min_x = corners[k][0];
			}
			if(corners[k][1] > dest_image_max_y)
			{
				dest_image_max_y = corners[k][1];
			}
			if(corners[k][1] < dest_image_min_y)
			{
				dest_image_min_y = corners[k][1];
			}
		}

		std::cout << "minx: " << std::endl;
		std::cout << dest_image_min_x << std::endl;
		std::cout << "maxx: " << std::endl;
		std::cout << dest_image_max_x << std::endl;

		std::cout << std::endl;

		std::cout << "miny: " << std::endl;
		std::cout << dest_image_min_y << std::endl;
		std::cout << "maxy: " << std::endl;
		std::cout << dest_image_max_y << std::endl;

		*out_offset_x = dest_image_min_x;
		*out_offset_y = dest_image_min_y;
		*out_width = dest_image_max_x - dest_image_min_x;
		*out_height = dest_image_max_y - dest_image_min_y;*/

		return true;
	}
	else
	{
		std::cout << "EXT_getWarpPerspectiveInf error" << std::endl;
		*out_offset_x = 0;
		*out_offset_y = 0;
		*out_width = 0;
		*out_height = 0;
		return false;
	}
}
IppStatus CCombinedIPP::EXT_WarpPerspective(cv::Mat *inputImage, cv::Mat *outputImage, cv::Mat H, IppiRect srcRoi, IppiSize dstSize, IppiRect dstRoi)
{
	if(inputImage != NULL && !(inputImage->empty()) && H.rows == 3 && H.cols == 3)
	{
		if(inputImage->type() == CV_8UC1)
		{
			outputImage->create(dstSize.height, dstSize.width, inputImage->type());

			int srcStep = inputImage->cols*sizeof(Ipp8u);
			int dstStep = outputImage->cols*sizeof(Ipp8u);
			IppiSize srcSize = {inputImage->cols, inputImage->rows};
			//IppiSize dstSize = {dst_width, dst_height};
			//IppiRect srcRoi = {0, 0, input_image->cols, input_image->rows};
			//IppiRect dstRoi = {0, 0, dst_width, dst_height};

			ippiSet_8u_C1R(0, (Ipp8u*)(&outputImage->data[0]), dstStep, dstSize);

			double double_H[3][3];

			for(int y = 0; y < 3; y++)
			{
				for(int x = 0; x < 3; x++)
				{
					double_H[y][x] = (double)H.at<double>(y, x);
				}
			}

			IppiWarpSpec* pSpec = 0;
			int specSize = 0, initSize = 0, bufSize = 0; Ipp8u* pBuffer = 0;
			const Ipp32u numChannels = 1;
			IppiPoint dstOffset = {dstRoi.x, dstRoi.y};
			IppiSize dstRoiSize = {dstRoi.width, dstRoi.height};
			IppStatus status = ippStsNoErr;
			IppiBorderType borderType = ippBorderConst;
			IppiWarpDirection direction = ippWarpForward;
			IppiInterpolationType interpolationType = ippNearest;
			Ipp64f pBorderValue[numChannels];
			for (int i = 0; i < numChannels; ++i) pBorderValue[i] = 255.0;

			/* Spec and init buffer sizes */
			status = ippiWarpPerspectiveGetSize(srcSize, srcRoi, dstSize, ipp8u, double_H, interpolationType, direction, borderType, &specSize, &initSize);
			if (status != ippStsNoErr) return status;
			//std::cout << status << std::endl;
			/* Memory allocation */
			pSpec = (IppiWarpSpec*)ippsMalloc_8u(specSize);
			if (pSpec == NULL)
			{
				return ippStsNoMemErr;
			}
			
			/* Filter initialization */
			//status = ippiWarpAffineLinearInit(srcSize, dstSize, ipp8u, double_H, direction, numChannels, borderType, pBorderValue, 0, pSpec);
			status = ippiWarpPerspectiveNearestInit(srcSize, srcRoi, dstSize, ipp8u, double_H, direction, numChannels, borderType, pBorderValue, 0, pSpec);
			//std::cout << status << std::endl;
			if (status != ippStsNoErr)
			{
				ippsFree(pSpec);
				return status;
			}

			/* work buffer size */
			status = ippiWarpGetBufferSize(pSpec, dstRoiSize, &bufSize);
			if (status != ippStsNoErr)
			{
				ippsFree(pSpec);
				return status;
			}
			pBuffer = ippsMalloc_8u(bufSize);
			if (pBuffer == NULL)
			{
				ippsFree(pSpec);
				return ippStsNoMemErr;
			}
			//std::cout << status << std::endl;
			/* Resize processing */
			//status = ippiWarpAffineLinear_8u_C3R(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);

			//status = ippiWarpPerspectiveNearest_8u_C1R((const Ipp8u*)&inputImage->data[srcRoi.y * srcSize.width + srcRoi.x], srcStep, (Ipp8u*)&outputImage->data[0], dstStep, dstOffset, dstRoiSize, pSpec, pBuffer);
			status = ippiWarpPerspectiveNearest_8u_C1R((const Ipp8u*)&inputImage->data[srcRoi.y * srcSize.width + srcRoi.x], srcStep, (Ipp8u*)&outputImage->data[dstRoi.y * dstSize.width + dstRoi.x], dstStep, dstOffset, dstRoiSize, pSpec, pBuffer);
			
			//std::cout << status << std::endl;

			ippsFree(pSpec);
			ippsFree(pBuffer);
			return status;
			//return ippiWarpPerspective_8u_C1R((const Ipp8u*)&inputImage->data[0], srcSize, srcStep, srcRoi, (Ipp8u*)&outputImage->data[0], dstStep, dstRoi, double_H, IPPI_INTER_NN);
		}
		else if(inputImage->type() == CV_8UC3)
		{
			outputImage->create(dstSize.height, dstSize.width, inputImage->type());

			int srcStep = inputImage->cols*sizeof(Ipp8u)*3;
			int dstStep = outputImage->cols*sizeof(Ipp8u)*3;
			IppiSize srcSize = {inputImage->cols, inputImage->rows};
			//IppiSize dstSize = {dst_width, dst_height};
			//IppiRect srcRoi = {0, 0, input_image->cols, input_image->rows};
			//IppiRect dstRoi = {0, 0, dst_width, dst_height};
			Ipp8u val[3] = {0, 0, 0};
			ippiSet_8u_C3R(val, (Ipp8u*)(&outputImage->data[0]), dstStep, dstSize);

			double double_H[3][3];

			for(int y = 0; y < 3; y++)
			{
				for(int x = 0; x < 3; x++)
				{
					double_H[y][x] = (double)H.at<double>(y, x);
				}
			}

			IppiWarpSpec* pSpec = 0;
			int specSize = 0, initSize = 0, bufSize = 0; Ipp8u* pBuffer = 0;
			const Ipp32u numChannels = 3;
			IppiPoint dstOffset = {dstRoi.x, dstRoi.y};
			IppiSize dstRoiSize = {dstRoi.width, dstRoi.height};
			IppStatus status = ippStsNoErr;
			IppiBorderType borderType = ippBorderConst;
			IppiWarpDirection direction = ippWarpForward;
			IppiInterpolationType interpolationType = ippNearest;
			Ipp64f pBorderValue[numChannels];
			for (int i = 0; i < numChannels; ++i) pBorderValue[i] = 255.0;

			/* Spec and init buffer sizes */
			status = ippiWarpPerspectiveGetSize(srcSize, srcRoi, dstSize, ipp8u, double_H, interpolationType, direction, borderType, &specSize, &initSize);
			if (status != ippStsNoErr) return status;
			//std::cout << status << std::endl;
			/* Memory allocation */
			pSpec = (IppiWarpSpec*)ippsMalloc_8u(specSize);
			if (pSpec == NULL)
			{
				return ippStsNoMemErr;
			}
			
			/* Filter initialization */
			//status = ippiWarpAffineLinearInit(srcSize, dstSize, ipp8u, double_H, direction, numChannels, borderType, pBorderValue, 0, pSpec);
			status = ippiWarpPerspectiveNearestInit(srcSize, srcRoi, dstSize, ipp8u, double_H, direction, numChannels, borderType, pBorderValue, 0, pSpec);
			//std::cout << status << std::endl;
			if (status != ippStsNoErr)
			{
				ippsFree(pSpec);
				return status;
			}

			/* work buffer size */
			status = ippiWarpGetBufferSize(pSpec, dstRoiSize, &bufSize);
			if (status != ippStsNoErr)
			{
				ippsFree(pSpec);
				return status;
			}
			pBuffer = ippsMalloc_8u(bufSize);
			if (pBuffer == NULL)
			{
				ippsFree(pSpec);
				return ippStsNoMemErr;
			}
			//std::cout << status << std::endl;
			/* Resize processing */
			//status = ippiWarpAffineLinear_8u_C3R(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);

			//status = ippiWarpPerspectiveNearest_8u_C1R((const Ipp8u*)&inputImage->data[srcRoi.y * srcSize.width + srcRoi.x], srcStep, (Ipp8u*)&outputImage->data[0], dstStep, dstOffset, dstRoiSize, pSpec, pBuffer);
			status = ippiWarpPerspectiveNearest_8u_C3R((const Ipp8u*)&inputImage->data[srcRoi.y * srcSize.width + srcRoi.x], srcStep, (Ipp8u*)&outputImage->data[dstRoi.y * dstSize.width + dstRoi.x], dstStep, dstOffset, dstRoiSize, pSpec, pBuffer);
			
			//std::cout << status << std::endl;

			ippsFree(pSpec);
			ippsFree(pBuffer);
			return status;

			//outputImage->create(dstSize.height, dstSize.width, inputImage->type());

			//int srcStep = inputImage->cols*sizeof(Ipp8u)*3;
			//int dstStep = outputImage->cols*sizeof(Ipp8u)*3;
			//IppiSize srcSize = {inputImage->cols, inputImage->rows};
			////IppiSize dstSize = {dst_width, dst_height};
			////IppiRect srcRoi = {0, 0, input_image->cols, input_image->rows};
			////IppiRect dstRoi = {0, 0, dst_width, dst_height};

			//Ipp8u zero[] = {0, 0, 0};
			//ippiSet_8u_C3R(zero, (Ipp8u*)(&outputImage->data[0]), dstStep, dstSize);

			//double double_H[3][3];

			//for(int y = 0; y < 3; y++)
			//{
			//	for(int x = 0; x < 3; x++)
			//	{
			//		double_H[y][x] = (double)H.at<double>(y, x);
			//	}
			//}

			//return ippiWarpPerspective_8u_C3R((const Ipp8u*)&inputImage->data[0], srcSize, srcStep, srcRoi, (Ipp8u*)&outputImage->data[0], dstStep, dstRoi, double_H, IPPI_INTER_NN);
			//return ippStsNullPtrErr;
		}
	}
	return ippStsNullPtrErr;
}
void CCombinedIPP::EXT_CountInRange(cv::Mat *inputImage, int *counts, Ipp8u lowerBound, Ipp8u upperBound)
{
	if(inputImage != NULL && !(inputImage->empty()))
	{
		if(inputImage->type() == CV_8UC1)
		{
			int srcStep = inputImage->cols*sizeof(Ipp8u);
			IppiSize roiSize = {inputImage->cols, inputImage->rows};

			ippiCountInRange_8u_C1R((const Ipp8u*)&inputImage->data[0], srcStep, roiSize, counts, lowerBound, upperBound);
		}
	}
}
void CCombinedIPP::EXT_CountInRangeWithROI(cv::Mat *inputImage, int *counts, Ipp8u lowerBound, Ipp8u upperBound, IppiRect roi)
{
	if(inputImage != NULL && !(inputImage->empty()))
	{
		if(inputImage->type() == CV_8UC1)
		{
			int srcStep = inputImage->cols*sizeof(Ipp8u);
			IppiSize srcRoi = {roi.width, roi.height};

			ippiCountInRange_8u_C1R((const Ipp8u*)&inputImage->data[inputImage->cols * roi.y + roi.x], srcStep, srcRoi, counts, lowerBound, upperBound);
		}
	}
}
void CCombinedIPP::EXT_Concatenate(cv::Mat *inputImage1, cv::Mat *inputImage2, cv::Mat *outputImage)
{
	if(inputImage1 != NULL && !(inputImage1->empty()) && inputImage2 != NULL && !(inputImage2->empty()))
	{
		if(inputImage1->type() == CV_8UC1 && inputImage2->type() == CV_8UC1)
		{
			outputImage->create((inputImage1->rows > inputImage2->rows)?inputImage1->rows:inputImage2->rows, inputImage1->cols + inputImage2->cols, inputImage1->type());

			int srcStep = inputImage1->cols*sizeof(Ipp8u);
			int dstStep = outputImage->cols*sizeof(Ipp8u);
			IppiSize roiSize = {inputImage1->cols, inputImage1->rows};

			ippiCopy_8u_C1R((const Ipp8u*)(&inputImage1->data[0]), srcStep, (Ipp8u*)&outputImage->data[0], dstStep, roiSize);

			srcStep = inputImage2->cols*sizeof(Ipp8u);
			roiSize.height = inputImage2->rows;
			roiSize.width = inputImage2->cols;

			ippiCopy_8u_C1R((const Ipp8u*)(&inputImage2->data[0]), srcStep, (Ipp8u*)&outputImage->data[inputImage1->cols*sizeof(Ipp8u)], dstStep, roiSize);
		}
		else if(inputImage1->type() == CV_8UC3 && inputImage2->type() == CV_8UC3)
		{
			outputImage->create((inputImage1->rows > inputImage2->rows)?inputImage1->rows:inputImage2->rows, inputImage1->cols + inputImage2->cols, inputImage1->type());

			int srcStep = inputImage1->cols*sizeof(Ipp8u)*3;
			int dstStep = outputImage->cols*sizeof(Ipp8u)*3;
			IppiSize roiSize = {inputImage1->cols, inputImage1->rows};

			ippiCopy_8u_C3R((const Ipp8u*)(&inputImage1->data[0]), srcStep, (Ipp8u*)&outputImage->data[0], dstStep, roiSize);

			srcStep = inputImage2->cols*sizeof(Ipp8u)*3;
			roiSize.height = inputImage2->rows;
			roiSize.width = inputImage2->cols;

			ippiCopy_8u_C3R((const Ipp8u*)(&inputImage2->data[0]), srcStep, (Ipp8u*)&outputImage->data[inputImage1->cols*sizeof(Ipp8u)*3], dstStep, roiSize);
		}
	}
}
void CCombinedIPP::EXT_Convert8u16u(cv::Mat *inputImage, cv::Mat *outputImage)
{
	if(inputImage != NULL && !(inputImage->empty()))
	{
		if(inputImage->type() == CV_8UC1)
		{
			outputImage->create(inputImage->rows, inputImage->cols, CV_16UC1);

			int srcStep = inputImage->cols*sizeof(Ipp8u);
			int dstStep = outputImage->cols*sizeof(Ipp16u);
			IppiSize roiSize = {inputImage->cols, inputImage->rows};

			ippiConvert_8u16u_C1R((const Ipp8u*)(&inputImage->data[0]), srcStep, (Ipp16u*)&outputImage->data[0], dstStep, roiSize);
		}
	}
}
void CCombinedIPP::EXT_MaxIndex(cv::Mat *inputImage, int &outMaxVal, int &outIndexX, int &outindexY)
{
	if(inputImage != NULL && !(inputImage->empty()))
	{
		if(inputImage->type() == CV_8UC1)
		{
			int srcStep = inputImage->cols*sizeof(Ipp8u);
			IppiSize roiSize = {inputImage->cols, inputImage->rows};

			Ipp8u max;

			ippiMaxIndx_8u_C1R((const Ipp8u*)(&inputImage->data[0]), srcStep, roiSize, &max, &outIndexX, &outindexY);

			outMaxVal = (int)max;
		}
	}
}
void CCombinedIPP::EXT_SetImage(cv::Mat &inputImage, cv::Scalar scalar)
{
	if(!inputImage.empty())
	{
		if(inputImage.type() == CV_8UC1)
		{
			int srcStep = inputImage.cols * sizeof(Ipp8u);
			IppiSize srcSize = {inputImage.cols, inputImage.rows};
			ippiSet_8u_C1R((Ipp8u)scalar.val[0], (Ipp8u*)(&inputImage.data[0]), srcStep, srcSize);
		}
		if(inputImage.type() == CV_8UC3)
		{
			int srcStep = inputImage.cols * sizeof(Ipp8u) * 3;
			IppiSize srcSize = {inputImage.cols, inputImage.rows};
			Ipp8u val[3];
			val[0] = (Ipp8u)scalar.val[0];
			val[1] = (Ipp8u)scalar.val[1];
			val[2] = (Ipp8u)scalar.val[2];
			ippiSet_8u_C3R(val, (Ipp8u*)(&inputImage.data[0]), srcStep, srcSize);
		}
	}
}
void CCombinedIPP::EXT_Remap(cv::Mat &inputImage, cv::Mat &outputImage, IppiRect srcRoi, IppiSize dstSize, cv::Mat &xMap, cv::Mat &yMap)
{
	if(!inputImage.empty())
	{
		if(inputImage.type() == CV_8UC1)
		{
			outputImage.create(dstSize.height, dstSize.width, inputImage.type());

			int srcStep = inputImage.cols * sizeof(Ipp8u);
			int xMapStep = xMap.cols * sizeof(Ipp32f);
			int yMapStep = yMap.cols * sizeof(Ipp32f);
			int dstStep = dstSize.width * sizeof(Ipp8u);
			IppiSize srcSize = {inputImage.cols, inputImage.rows};

			ippiSet_8u_C1R(0, (Ipp8u*)(&outputImage.data[0]), dstStep, dstSize);

			//cv::namedWindow("0", CV_WINDOW_FREERATIO|CV_WINDOW_NORMAL);
			//cv::imshow("0", outputImage);
			//cv::waitKey(0);

			//std::cout << "a" << std::endl;
			IppStatus s = ippiRemap_8u_C1R((const Ipp8u*)(&inputImage.data[0]), srcSize, srcStep, srcRoi, (const Ipp32f*)(&xMap.data[0]), xMapStep, (const Ipp32f*)(&yMap.data[0]), yMapStep, (Ipp8u*)(&outputImage.data[0]), dstStep, dstSize, IPPI_INTER_LINEAR);
		
			//std::cout << "aaa" << std::endl;

			//std::cout << s << std::endl;
		}
	}
}
void CCombinedIPP::EXT_MedianFilter(cv::Mat &inputImage, cv::Mat &outputImage)
{
	if (!inputImage.empty())
	{
		if (inputImage.type() == CV_8UC1)
		{
			outputImage.create(inputImage.rows, inputImage.cols, inputImage.type());

			int srcStep = inputImage.cols * sizeof(Ipp8u);
			int dstStep = outputImage.cols * sizeof(Ipp8u);
			IppiSize srcSize = { inputImage.cols, inputImage.rows };
			IppiSize maskSize = { 3, 3 };
			IppiBorderType borderType = ippBorderRepl;
			Ipp8u* pBuffer = 0;
			int bufferSize;

			ippiSet_8u_C1R(0, (Ipp8u*)(&outputImage.data[0]), dstStep, srcSize);

			ippiFilterMedianBorderGetBufferSize(srcSize, maskSize, ipp8u, inputImage.channels(), &bufferSize);
			
			pBuffer = ippsMalloc_8u(bufferSize);

			ippiFilterMedianBorder_8u_C1R((const Ipp8u*)(&inputImage.data[0]), srcStep, (Ipp8u*)(&outputImage.data[0]), dstStep, srcSize, maskSize, borderType, 0, pBuffer);

			ippsFree(pBuffer);
		}
	}
}