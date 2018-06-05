//#include "stdafx.h"
#include "Functions.h"

namespace NFunctions
{
	namespace NConversion
	{
		std::string EXT_WcharToStdString(wchar_t *in)
		{
			std::wstring ws(in);
			std::string str(ws.begin(), ws.end());
			return str;
		}
		int EXT_StdStringToInt(std::string in)
		{
			return std::stoi(in);
		}
		double EXT_StdStringToDouble(std::string in)
		{
			return std::stod(in);
		}
		float EXT_StdStringToFloat(std::string in)
		{
			return std::stof(in);
		}
		//PCSTR EXT_StdStringToPCSTR(std::string in)
		//{
		//	return in.c_str();
		//}
	}
//
////	namespace NMath
////	{
//		float EXT_Round(float number, int precision)
//		{
//			if (precision == 0)
//				return floorf(number + 0.5f);
//			else if (precision < 0)
//				return number;
//
//			return floorf(number * std::pow(float(10), precision) + 0.5f) / std::pow(float(10), precision);
//		}
//		void EXT_CreatePrecisionRecall(std::string fileName, float measure[4])
//		{
//			bool valid = true;
//			float precision, recall, accuracy;
//
//			if ((measure[0] + measure[2]) == 0)
//				valid = false;
//			else
//				precision = measure[0] / (measure[0] + measure[2]);
//
//			if ((measure[0] + measure[3]) == 0)
//				valid = false;
//			else
//				recall = measure[0] / (measure[0] + measure[3]);
//
//			if ((measure[0] + measure[1] + measure[2] + measure[3]) == 0)
//				valid = false;
//			else
//				accuracy = (measure[0] + measure[1]) / (measure[0] + measure[1] + measure[2] + measure[3]);
//
//			if (valid)
//			{
//				std::fstream File(fileName);
//				if (!File.is_open())
//				{
//					std::ofstream create_file(fileName);
//					create_file.close();
//					File.open(fileName);
//				}
//				File.seekp(0, std::ios_base::end);
//
//				precision = EXT_Round(precision, 4);
//				recall = EXT_Round(recall, 4);
//				accuracy = EXT_Round(accuracy, 4);
//
//				std::string line;
//				std::stringstream s;
//
//				s << measure[0];
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << measure[1];
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << measure[2];
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << measure[3];
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << accuracy;
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << precision;
//				line += s.str();
//				line += ";";
//				s.str("");
//
//				s << recall;
//				line += s.str();
//				line += "\n";
//				s.str("");
//
//				File << line;
//
//				File.close();
//			}
//		}
//		float EXT_GetDistance(cv::Point p1, cv::Point p2)
//		{
//			return std::sqrt((float)(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y))));
//		}
//		float EXT_GetDistance(cv::Point2f p1, cv::Point2f p2)
//		{
//			return std::sqrt((float)(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y))));
//		}
//		cv::Point2f EXT_GetIntersectionFromTwoLine(cv::Point2f line11, cv::Point2f line12, cv::Point2f line21, cv::Point2f line22)
//		{
//			float m1, m2;
//			float A1, A2;
//			cv::Point2f tmp;
//
//			if (line11.x > line12.x)
//			{
//				tmp = line11;
//				line11 = line12;
//				line12 = tmp;
//			}
//			if (line21.x > line22.x)
//			{
//				tmp = line21;
//				line21 = line22;
//				line22 = tmp;
//			}
//
//			cv::Point2f intersection;
//
//			m1 = (line11.y - line12.y) / (line11.x - line12.x);
//			A1 = line11.y - m1 * line11.x;
//
//			m2 = (line21.y - line22.y) / (line21.x - line22.x);
//			A2 = line21.y - m2 * line21.x;
//
//			intersection.x = (A2 - A1) / (m1 - m2);
//			intersection.y = m1 * intersection.x + A1;
//
//			return intersection;
//		}
//		double EXT_GetBetweenNumber(double minLimit, double maxLimit, double number)
//		{
//			if (number < minLimit)
//				return minLimit;
//			else if (number > maxLimit)
//				return maxLimit;
//			return number;
//		}
//		float EXT_GetDistanceFromLine(cv::Point lineP1, cv::Point lineP2, cv::Point point)
//		{
//			float val = 0;
//			float fD = (float)((lineP2.x - lineP1.x) * (lineP2.x - lineP1.x) + (lineP2.y - lineP1.y) * (lineP2.y - lineP1.y));
//			if (fD == 0) return 0;
//
//			val = fabs((float)(point.x*(lineP1.y - lineP2.y) + point.y*(lineP2.x - lineP1.x) + lineP1.x*lineP2.y - lineP2.x*lineP1.y)) / std::sqrt(fD);
//			return val;
//		}
//	}
//
	namespace NImageProcessing
	{
		void EXT_NormalizeImage(cv::Mat &img, cv::Mat *outImg)
		{
			if (outImg == NULL)
			{
				if ((!img.empty()))
				{
					cv::Mat normalizeImage;

					double minVal, maxVal;
					cv::minMaxLoc(img, &minVal, &maxVal);

					img.convertTo(normalizeImage, CV_8UC1, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
					img = normalizeImage.clone();
				}
			}
			else
			{
				if ((!img.empty()))
				{
					double minVal, maxVal;
					cv::minMaxLoc(img, &minVal, &maxVal);

					img.convertTo(*outImg, CV_8UC1, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
				}
			}
			////
			//if(outImg == NULL)
			//{
			//	if((!img.empty()) && img.type() == CV_8UC1)
			//	{
			//		int max = -1;

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				if(max < img.at<uchar>(yIndex, xIndex))
			//				{
			//					max = img.at<uchar>(yIndex, xIndex);
			//				}
			//			}
			//		}

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				img.at<uchar>(yIndex, xIndex) = (int)((((float)(img.at<uchar>(yIndex, xIndex)))/(float)max) * (float)255);
			//			}
			//		}
			//	}
			//}
			//else
			//{
			//	if((!img.empty()) && img.type() == CV_8UC1)
			//	{
			//		int max = -1;

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				if(max < img.at<uchar>(yIndex, xIndex))
			//				{
			//					max = img.at<uchar>(yIndex, xIndex);
			//				}
			//			}
			//		}

			//		outImg->create(img.rows, img.cols, CV_8UC1);

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				outImg->at<uchar>(yIndex, xIndex) = (int)((((float)(img.at<uchar>(yIndex, xIndex)))/(float)max) * (float)255);
			//			}
			//		}
			//	}
			//	else if((!img.empty()) && img.type() == CV_16UC1)
			//	{
			//		int max = -1;

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				if(max < img.at<ushort>(yIndex, xIndex))
			//				{
			//					max = img.at<ushort>(yIndex, xIndex);
			//				}
			//			}
			//		}

			//		outImg->create(img.rows, img.cols, CV_8UC1);

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				outImg->at<uchar>(yIndex, xIndex) = (int)((((float)(img.at<ushort>(yIndex, xIndex)))/(float)max) * (float)255);
			//			}
			//		}
			//	}
			//	else if((!img.empty()) && img.type() == CV_32FC1)
			//	{
			//		int max = -1;

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				if(max < (int)img.at<float>(yIndex, xIndex))
			//				{
			//					max = (int)img.at<float>(yIndex, xIndex);
			//				}
			//			}
			//		}

			//		outImg->create(img.rows, img.cols, CV_8UC1);

			//		for(int yIndex = 0; yIndex < img.rows; ++yIndex)
			//		{
			//			for(int xIndex = 0; xIndex < img.cols; ++xIndex)
			//			{
			//				outImg->at<uchar>(yIndex, xIndex) = (int)((((float)(img.at<float>(yIndex, xIndex)))/(float)max) * (float)255);
			//			}
			//		}
			//	}
			//}
		}
//		void EXT_MergeImages(cv::Mat &inOutImg, int n_args, ...)
//		{
//			va_list vl;
//			va_start(vl, n_args);
//			std::vector<cv::Mat> images;
//			images.push_back(inOutImg);
//
//			bool valid = true;
//
//			for (int i = 0; i < n_args; ++i)
//			{
//				images.push_back(va_arg(vl, cv::Mat));
//				if (images.back().cols != inOutImg.cols || images.back().rows != inOutImg.rows || images.back().type() != inOutImg.type())
//					valid = false;
//			}
//
//			if (valid)
//			{
//				int sum = 0;
//				int size = inOutImg.cols * inOutImg.rows;
//
//				if (inOutImg.channels() == 3)
//					size = inOutImg.cols * inOutImg.rows * 3;
//
//				for (int iPos = 0; iPos < size; ++iPos)
//				{
//					sum = 0;
//					for (unsigned i = 0; i < images.size(); ++i)
//					{
//						sum += (int)(images[i].data[iPos]);
//					}
//
//					sum = sum / (int)(images.size());
//					inOutImg.data[iPos] = (uchar)sum;
//				}
//			}
//		}
//		void EXT_MergeImagesInVector(std::vector<cv::Mat> &inputImages, cv::Mat *outputImage)
//		{
//			bool valid = true;
//
//			for (unsigned i = 1; i < inputImages.size(); ++i)
//			{
//				if (inputImages[0].cols != inputImages[i].cols || inputImages[0].rows != inputImages[i].rows || inputImages[0].type() != inputImages[i].type())
//					valid = false;
//			}
//
//			if (inputImages.size() == 0)
//				valid = false;
//
//			if (valid)
//			{
//				if (outputImage == NULL)
//				{
//					int sum = 0;
//					int size = inputImages[0].cols * inputImages[0].rows;
//
//					if (inputImages[0].channels() == 3)
//						size = inputImages[0].cols * inputImages[0].rows * 3;
//
//					for (int iPos = 0; iPos < size; ++iPos)
//					{
//						sum = 0;
//						for (unsigned i = 0; i < inputImages.size(); ++i)
//						{
//							sum += (int)(inputImages[i].data[iPos]);
//						}
//
//						sum = sum / (int)(inputImages.size());
//						inputImages[0].data[iPos] = (uchar)sum;
//					}
//				}
//				else
//				{
//					outputImage->create(inputImages[0].rows, inputImages[0].cols, inputImages[0].type());
//
//					int sum = 0;
//					int size = inputImages[0].cols * inputImages[0].rows;
//
//					if (inputImages[0].channels() == 3)
//						size = inputImages[0].cols * inputImages[0].rows * 3;
//
//					for (int iPos = 0; iPos < size; ++iPos)
//					{
//						sum = 0;
//						for (unsigned i = 0; i < inputImages.size(); ++i)
//						{
//							sum += (int)(inputImages[i].data[iPos]);
//						}
//
//						sum = sum / (int)(inputImages.size());
//						outputImage->data[iPos] = (uchar)sum;
//					}
//				}
//			}
//		}
		cv::Point EXT_GetHomographySingelPointWithReturn(cv::Mat H, cv::Point point)
		{
			if (H.rows == 3 && H.cols == 3 && H.type() == CV_64FC1)
			{
				cv::Mat dummyPoint = cv::Mat(3, 1, CV_64FC1);

				dummyPoint.at<double>(0, 0) = point.x;
				dummyPoint.at<double>(1, 0) = point.y;
				dummyPoint.at<double>(2, 0) = 1;

				dummyPoint = H * dummyPoint;

				return cv::Point((int)(dummyPoint.at<double>(0, 0) / dummyPoint.at<double>(2, 0)), (int)(dummyPoint.at<double>(1, 0) / dummyPoint.at<double>(2, 0)));
			}
			return cv::Point(-1, -1);
		}
//		cv::Point2f EXT_GetHomographySingelPointWithReturnFloat(cv::Mat H, cv::Point point)
//		{
//			if (H.rows == 3 && H.cols == 3 && H.type() == CV_64FC1)
//			{
//				cv::Mat dummyPoint = cv::Mat(3, 1, CV_64FC1);
//
//				dummyPoint.at<double>(0, 0) = point.x;
//				dummyPoint.at<double>(1, 0) = point.y;
//				dummyPoint.at<double>(2, 0) = 1;
//
//				dummyPoint = H * dummyPoint;
//
//				return cv::Point2f((float)(dummyPoint.at<double>(0, 0) / dummyPoint.at<double>(2, 0)), (float)(dummyPoint.at<double>(1, 0) / dummyPoint.at<double>(2, 0)));
//			}
//			return cv::Point2f(-1, -1);
//		}
		cv::Point EXT_GetHomographyInverseSingelPointWithReturn(cv::Mat H, cv::Point transformedPoint)
		{
			if (H.rows == 3 && H.cols == 3 && H.type() == CV_64FC1)
			{
				cv::Mat dummyPoint = cv::Mat(3, 1, CV_64FC1);

				dummyPoint.at<double>(0, 0) = transformedPoint.x;
				dummyPoint.at<double>(1, 0) = transformedPoint.y;
				dummyPoint.at<double>(2, 0) = 1;

				dummyPoint = H.inv() * dummyPoint;

				return cv::Point((int)(dummyPoint.at<double>(0, 0) / dummyPoint.at<double>(2, 0)), (int)(dummyPoint.at<double>(1, 0) / dummyPoint.at<double>(2, 0)));
			}
			return cv::Point(-1, -1);
		}
//		void EXT_GetHomographySingelPoint(cv::Mat H, cv::Point &ioPoint)
//		{
//			if (H.rows == 3 && H.cols == 3 && H.type() == CV_64FC1)
//			{
//				cv::Mat dummyPoint = cv::Mat(3, 1, CV_64FC1);
//
//				dummyPoint.at<double>(0, 0) = ioPoint.x;
//				dummyPoint.at<double>(1, 0) = ioPoint.y;
//				dummyPoint.at<double>(2, 0) = 1;
//
//				dummyPoint = H * dummyPoint;
//
//				ioPoint.x = (int)(dummyPoint.at<double>(0, 0) / dummyPoint.at<double>(2, 0));
//				ioPoint.y = (int)(dummyPoint.at<double>(1, 0) / dummyPoint.at<double>(2, 0));
//			}
//		}
//		void EXT_FindLocalMaximums(cv::Mat &in, cv::Mat &out, int kernelSize)
//		{
//			if (in.type() == CV_8UC1)
//			{
//				out.create(in.rows, in.cols, CV_8UC1);
//				cv::Mat dilatelocalMaximums;
//				cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
//				cv::dilate(in, dilatelocalMaximums, kernel);
//
//				//out = in == dilatelocalMaximums;
//
//				int maxPos = in.rows * out.cols;
//				for (int iPos = 0; iPos < maxPos; ++iPos)
//				{
//					if (in.data[iPos] == dilatelocalMaximums.data[iPos])
//						out.data[iPos] = in.data[iPos];
//					else
//						out.data[iPos] = 0;
//				}
//				//for(unsigned y = 0; y < localMaximums.rows; ++y)
//				//{
//				//	for(unsigned x = 0; x < localMaximums.cols; ++x)
//				//	{
//				//		if(parallelMerge.at<uchar>(y, x) == 0)
//				//			localMaximums.at<uchar>(y, x) = 0;
//				//	}
//				//}
//			}
//		}
		void EXT_GetBlobs(cv::Mat &inImg, cv::Rect *inMask, float inMinOutputSizeRate, std::vector<std::pair<int, int>> &outAreas, std::vector<std::pair<int, cv::Point2f>> &outBlobsCenter, std::vector<cv::Rect> &outBlobsRect, int &outMaxArea)
		{
			int iID = 0;
			int iSX = 0;
			int iSY = 0;
			int iEX = inImg.cols;
			int iEY = inImg.rows;
		
			if (inMask) iSX = inMask->x;
			if (inMask) iSY = inMask->y;
			if (inMask) iEX = iSX + inMask->width;
			if (inMask) iEY = iSY + inMask->height;
			outMaxArea = 0;
		
			unsigned char chVal;
			cv::Rect tmpRect;
			int iArea = 0;
			cv::Point minP;
			cv::Point maxP;
			cv::Point2f average;
				
			if (inImg.type() == CV_8UC1)
			{
				for (int y = iSY; y < iEY; y++)
				{
					for (int x = iSX; x < iEX; x++)
					{
						chVal = inImg.at<unsigned char>(y, x);
					
						if (chVal == 255)
						{
							iID++;
							cv::floodFill(inImg, cv::Point(x, y), iID, &tmpRect, 0, 0, cv::FLOODFILL_FIXED_RANGE + 4);
							iArea = 0;
							minP = cv::Point(INT_MAX, INT_MAX);
							maxP = cv::Point(0, 0);
							average = cv::Point2f(0, 0);
					
							for (int y2 = iSY; y2 < iEY; y2++)
							{
								for (int x2 = iSX; x2 < iEX; x2++)
								{
									unsigned char chVal = inImg.at<unsigned char>(y2, x2);
									if (chVal == iID) 
									{
										average.x += x2;
										average.y += y2;
										iArea++;
										if (y2 < minP.y) minP.y = y2;
										if (y2 > maxP.y) maxP.y = y2;
										if (x2 < minP.x) minP.x = x2;
										if (x2 > maxP.x) maxP.x = x2;
									}
								}
							}

							if (iArea)
							{
								average.x /= iArea;
								average.y /= iArea;
							}

							outAreas.push_back(std::pair<int, int>(iID, iArea));
							outBlobsCenter.push_back(std::pair<int, cv::Point2f>(iID, average));
							outBlobsRect.push_back(cv::Rect(minP.x, minP.y, maxP.x - minP.x + 1, maxP.y - minP.y + 1));
							if (iArea > outMaxArea) outMaxArea = iArea;
						}
					}
				}
			
				int imgSize = inImg.cols *inImg.rows;
				int minSize = (int)((float)imgSize * inMinOutputSizeRate);
				for (int i = 0; i < outAreas.size(); ++i)
				{
					int blobSize = outBlobsRect[i].width * outBlobsRect[i].height;
				
					if (blobSize < minSize)
					{
						outAreas.erase(outAreas.begin() + i);
						outBlobsCenter.erase(outBlobsCenter.begin() + i);
						outBlobsRect.erase(outBlobsRect.begin() + i);
						i--;
					}
				}
			}
			else
				std::cout << "Error: NFunctions::NImageProcessing::EXT_GetBlobs(): inImg type is not CV_8UC1!" << std::endl;
		}
	}

	namespace NDisplay
	{
//		void EXT_ArticulateInformation(int spaceBetweenValues, int n_args, ...)
//		{
//			va_list vl;
//			va_start(vl, n_args);
//			std::vector<std::string> informations;
//
//			for (int i = 0; i < n_args; ++i)
//				informations.push_back(va_arg(vl, std::string));
//
//			for (int i = 0; i < n_args; ++i)
//			{
//				std::cout << std::setw(spaceBetweenValues) << std::left << informations[i];
//			}
//
//			std::cout << std::endl;
//		}
		void EXT_ShowDistortionCoefficient(cv::Mat &distCoeff)
		{
			std::cout.precision(5);
			if (distCoeff.cols < 10 && distCoeff.type() == CV_64FC1)
			{
				for (int i = 0; i < distCoeff.cols; ++i)
				{
					std::cout << std::setw(15) << std::left << distCoeff.at<double>(0, i);
				}
				std::cout << std::endl;
			}
			else if (distCoeff.cols < 10 && distCoeff.type() == CV_32FC1)
			{
				for (int i = 0; i < distCoeff.cols; ++i)
				{
					std::cout << std::setw(15) << std::left << distCoeff.at<float>(0, i);
				}
				std::cout << std::endl;
			}
		}
		void EXT_ShowHTransformation(cv::Mat &H)
		{
			std::cout.precision(10);
			if (H.cols == 3 && H.rows == 3 && H.type() == CV_64FC1)
			{
				for (int j = 0; j < 3; ++j)
				{
					for (int i = 0; i < 3; ++i)
					{
						std::cout << std::setw(20) << std::left << H.at<double>(j, i);
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
			else if (H.cols == 3 && H.rows == 3 && H.type() == CV_32FC1)
			{
				for (int j = 0; j < 3; ++j)
				{
					for (int i = 0; i < 3; ++i)
					{
						std::cout << std::setw(20) << std::left << H.at<float>(j, i);
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}
		std::string EXT_GetHTransformation(cv::Mat &H)
		{
			std::string hString;
			if (H.cols == 3 && H.rows == 3 && H.type() == CV_64FC1)
			{
				for (int j = 0; j < 3; ++j)
				{
					for (int i = 0; i < 3; ++i)
					{
						hString += NFunctions::NConversion::EXT_ConvertToString<double>(H.at<double>(j, i));
						hString += "	";
						//std::cout << std::setw(20) << std::left << H.at<double>(j, i);
					}
					hString += "\n";
					//std::cout << std::endl;
				}
				hString += "\n";
				//std::cout << std::endl;
			}
			return hString;
		}
		void EXT_ShowPointsWithRadius(std::vector<cv::Point> points, float radius, cv::Size size)
		{
			cv::Mat img = cv::Mat::zeros(size, CV_8UC1);

			for (unsigned int i = 0; i < points.size(); ++i)
			{
				img.at<uchar>(points.at(i).y, points.at(i).x) = 255;
				cv::circle(img, points.at(i), (int)radius, 255, 3);
			}

			cv::namedWindow("Circles", CV_WINDOW_NORMAL | CV_WINDOW_FREERATIO);
			cv::imshow("Circles", img);
			cv::waitKey(10);
		}
		void EXT_drawCross(cv::Mat &img, cv::Point center, cv::Scalar color)
		{
			int d = (int)((float)(img.cols) * 0.02);
			int thickness = (img.cols) / 100;
			if (thickness == 0)
				thickness = 1;
			cv::line(img, cv::Point(center.x - d, center.y - d), cv::Point(center.x + d, center.y + d), color, thickness, CV_AA, 0);
			cv::line(img, cv::Point(center.x + d, center.y - d), cv::Point(center.x - d, center.y + d), color, thickness, CV_AA, 0);
		}
	}

	namespace NOthers
	{
		void EXT_Numbering(int number, int sizeOfString, std::string &outString)
		{
			outString.clear();
			//outString = "_";

			std::string numberString;
			std::stringstream s;

			s << number;
			numberString = s.str();
			s.str("");
			int iter = sizeOfString - numberString.length();

			for (int i = 0; i < iter; i++)
				outString.append("0");

			outString.append(numberString);
		}
//		void EXT_CoutTimeOfProcessing(float actualProcTime, float allProcTime)
//		{
//			std::cout << "\r" << "           " << "\r";
//			std::cout.precision(2);
//
//			float percent = actualProcTime / allProcTime * (float)100;
//
//			std::cout << std::fixed << percent;
//			std::cout << " %";
//
//			if (percent == 100)
//				std::cout << std::endl;
//		}
		std::string EXT_DateToString(std::chrono::system_clock::time_point time, bool needHourMinSec, bool needMillisec)
		{
			std::time_t time2 = std::chrono::system_clock::to_time_t(time);
			
			const tm *values = std::localtime(&time2);
			std::string date;
			std::string tmp;
			
			date = NConversion::EXT_ConvertToString<int>(values->tm_year + 1900);
			
			tmp = NConversion::EXT_ConvertToString<int>(values->tm_mon + 1);
			if (tmp.length() == 1)
				tmp = "0" + tmp;
			date += tmp;
			
			tmp = NConversion::EXT_ConvertToString<int>(values->tm_mday);
			if (tmp.length() == 1)
				tmp = "0" + tmp;
			date += tmp;
			
			if (needHourMinSec)
			{
				date += "_";
			
				tmp = NConversion::EXT_ConvertToString<int>(values->tm_hour);
				if (tmp.length() == 1)
					tmp = "0" + tmp;
				date += tmp;
			
				tmp = NConversion::EXT_ConvertToString<int>(values->tm_min);
				if (tmp.length() == 1)
					tmp = "0" + tmp;
				date += tmp;
			
				tmp = NConversion::EXT_ConvertToString<int>(values->tm_sec);
				if (tmp.length() == 1)
					tmp = "0" + tmp;
				date += tmp;
			}
				
			if (needHourMinSec && needMillisec)
			{
				date += "_";
				
				std::chrono::system_clock::time_point timeRounded = std::chrono::system_clock::from_time_t(time2);
				if (timeRounded > time) {
					--time2;
					timeRounded -= std::chrono::seconds(1);
				}
				
				int milliseconds = std::chrono::duration_cast<std::chrono::duration<int, std::milli> >(time - timeRounded).count();
				
				tmp = NConversion::EXT_ConvertToString<int>(milliseconds);
				while (tmp.length() != 3)
					tmp = "0" + tmp;
				
				date += tmp;
			}
			
			return date;
			/*
			const time_t t = time(0);   // get time now
			//tm *now = localtime(&t);
			tm now;
			localtime_s(&now, &t);

			std::string date;

			date = NConversion::EXT_ConvertToString<int>(now.tm_year + 1900);
			date += ".";
			date += NConversion::EXT_ConvertToString<int>(now.tm_mon + 1);
			date += ".";
			date += NConversion::EXT_ConvertToString<int>(now.tm_mday);
			date += "_";
			date += NConversion::EXT_ConvertToString<int>(now.tm_hour);
			date += ".";
			date += NConversion::EXT_ConvertToString<int>(now.tm_min);
			date += ".";
			date += NConversion::EXT_ConvertToString<int>(now.tm_sec);

			return date;
			//*/
		}
		bool EXT_CheckExist(std::string fullPath)
		{
			struct stat buffer;
			return (stat(fullPath.c_str(), &buffer) == 0); 
		}
	}
}