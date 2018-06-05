#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#ifdef _WIN32
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#elif __linux__
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdarg.h>
#include <chrono>
#include <sys/stat.h>

//#include <Windows.h>

#pragma once
/**Feladata, hogy segedfunkciokat lasson el
*/
namespace NFunctions
{
	/**Konverzios fuggvenyek gyujtemenye
	*/
	namespace NConversion
	{
		/**Wchar alakitasa std::string - e
		* @param in bemeneti wchar
		* @return std::string tipusu kimenet
		*/
		std::string EXT_WcharToStdString(wchar_t *in);
		/**Std::string - et alakit int - e (tizes szamrendszerben) (C++11)
		* @param in bemeneti string
		* @return int tipusu kimenet
		*/
		int EXT_StdStringToInt(std::string in);
		/**Std::string - et alakit double - e (C++11)
		* @param in bemeneti string
		* @return double tipusu kimenet
		*/
		double EXT_StdStringToDouble(std::string in);
		/**Std::string - et alakit float - e (C++11)
		* @param in bemeneti string
		* @return float tipusu kimenet
		*/
		float EXT_StdStringToFloat(std::string in);
		/**Std::string - et alakit PCSTR - e (C++11)
		* @param in bemeneti string
		* @return PCSTR tipusu kimenet
		*/
		//PCSTR EXT_StdStringToPCSTR(std::string in);
		/**Atalakitja a parametert egy string - e
		* @param T Atalakitando ertek (template)
		* @return allProcTime teljes feldolgozasi ido
		*/
		template<typename T>
		std::string EXT_ConvertToString(T thing)
		{
			std::stringstream s;
			s << thing;
			return s.str();
		}
	}

//	/**Matematikai fuggvenyek gyujtemenye
//	*/
//	namespace NMath
//	{
//		/**Float ok kerekitese, pont utan mekkora pontossagu legyen
//		* @param number kerekitendo szam
//		* @param precision pont utan mennyi szamjegyig kerekitsen
//		* return kerekitett ertek
//		*/
//		float EXT_Round(float number, int precision);
//		/**Letrehoz egy txt - t a Precision/Recall ra, amit Excel el ki lehet rajzoltatni
//		* @param fileName kiirando file neve
//		* @param measures 4 elemu tomb, amiknek az elemei sorra (TruePositive, TrueNegative, FalsePositive, FalseNegative)
//		*/
//		void EXT_CreatePrecisionRecall(std::string fileName, float measure[4]);
//		/**2 pont kozti tavolsagot szamolja ki
//		* @param p1 elso pont
//		* @param p2 masodik pont
//		*/
//		float EXT_GetDistance(cv::Point p1, cv::Point p2);
//		/**2 pont kozti tavolsagot szamolja ki
//		* @param p1 elso pont
//		* @param p2 masodik pont
//		*/
//		float EXT_GetDistance(cv::Point2f p1, cv::Point2f p2);
//		/**Visszaadja ket egyenese metszespontjat
//		* @param line11 elso egyenes egyik pontja
//		* @param line12 elso egyenes masik pontja
//		* @param line21 masodik egyenes egyik pontja
//		* @param line22 masodik egyenes masik pontja
//		* @return az egyenesek metszespontja
//		*/
//		cv::Point2f EXT_GetIntersectionFromTwoLine(cv::Point2f line11, cv::Point2f line12, cv::Point2f line21, cv::Point2f line22);
//		/**Visszaadja az input szamot, ha valamelyik korlaton tullug, akkor a korlatot
//		* @param minLimit minimum korlat
//		* @param maxLimit maximum korlat
//		* @param bemeneti ertek
//		* @return szam, vagy a korlatok valamelyike
//		*/
//		double EXT_GetBetweenNumber(double minLimit, double maxLimit, double number);
//		/**Tavolsag szamolasa egy egyenes es pont kozott
//		* @param lineP1 egyenes egyik pontja
//		* @param lineP2 egyenes masik pontja
//		* @param point a pont
//		*/
//		float EXT_GetDistanceFromLine(cv::Point lineP1, cv::Point lineP2, cv::Point point);
//	}
//
//	/**Kepfeldolgozo fuggvenyek gyujtemenye
//	*/
	namespace NImageProcessing
	{
		/**A kepet egy megjelenitheto formara konvertalja (max ertek 255 lesz)
		* @param img a bemeno kep, amit normalizalni szeretnenk (ha az outImg NULL, akkor a kimenet az img, maskulonben az OutImg)
		* @param outImg kimeneti kep (ha NULL, akkor a kimeneti kep az img)
		*/
		void EXT_NormalizeImage(cv::Mat &img, cv::Mat *outImg = NULL);
//		/**Kepeket egymason elhelyezi (csak akkor mukodik, ha az osszes bemeno kep merete es tipusaik megegyeznek)
//		* @param inOutImg az elso bemeno kep, amire az osszes tobbi is rakerul
//		* @param n_args bemeno parameterek szama (hany plusz kep lesz)
//		*/
//		void EXT_MergeImages(cv::Mat &inOutImg, int n_args, ...);
//		/**Kepeket egymason elhelyezi (a kimeneti kep a vektor elso bemeneti kepeben lesz)
//		* @param inputImages vektorban levo kepek (minden kepnek azonos meretunek kell lennie a vectorban, kulonben nem lesz muvelet vegrehajtva)
//		* @param outputImage ha nem null, akkor ebbe fogja összegetni a kepeket
//		*/
//		void EXT_MergeImagesInVector(std::vector<cv::Mat> &inputImages, cv::Mat *outputImage = NULL);
		/**Lekepez egy pontot egy masik sikba
		* @param H transzformacios matrix
		* @param point transzformalando pont
		* @return transzformalt pont
		*/
		cv::Point EXT_GetHomographySingelPointWithReturn(cv::Mat H, cv::Point point);
//		/**Lekepez egy pontot egy masik sikba lekepzett pont float tipusu
//		* @param H transzformacios matrix
//		* @param point transzformalando pont
//		* @return transzformalt pont
//		*/
//		cv::Point2f EXT_GetHomographySingelPointWithReturnFloat(cv::Mat H, cv::Point point);
		/**Egy lekepzett pontrol megmondja, hogy a masik sikbol honnan lett lekepezve (inverz transzformacio)
		* @param H transzformacios matrix (fuggvenyen belul ennek inverze lesz hasznalva)
		* @param transformedPoint a pont, ami a transzformalas utan jott letre
		* @return az eredeti pont, ahonnan transzformalva lett a bemenet
		*/
		cv::Point EXT_GetHomographyInverseSingelPointWithReturn(cv::Mat H, cv::Point transformedPoint);
//		/**Lekepez egy pontot egy masik sikba
//		* @param H transzformacios matrix
//		* @param point bemenetkent transzformalando pont, kimenetkent kimeneti pont fog megjelenni benne
//		*/
//		void EXT_GetHomographySingelPoint(cv::Mat H, cv::Point &ioPoint);
//		/**Lokalis maximumok keresese egy cv_8UC1 tipusu kepen
//		* @param in bemeneti kep
//		* @param out kimeneti kep a lokalis maximumokkal
//		* @param kernelSize kernel merete
//		*/
//		void EXT_FindLocalMaximums(cv::Mat &in, cv::Mat &out, int kernelSize);
		/**Visszater a moszgasmaszkok kereteivel, mereteivel, sulypontjaival (FloodFill belul)
		* @param inImg bemeneti kep (CV_8UC1)
		* @param inMask bemeneti kepen hol szeretnenk blobokat keresni (ha NULL, akkor az egesz kepen keres)
		* @param inMinOutputSizeRate kimeneti blobok minimalis merete
		* @param outAreas kimenet, vektorban tarolt elem parok (ID (egyben az elerasztas erteke is) - elarasztott pontok szama)
		* @param outBlobsCenter kimenet, vektorban tarolt elem parok (ID (egyben az elerasztas erteke is) - elarasztott pontok atlag kozep pontja)
		* @param outBlobsRect kimeneti blob ok keretezo teglalapjai (ha NULL, akkor nem lesz kimenet reteket tartalmazo vektor)
		* @param outMaxArea blobok kozul az az ertek, amelyinel a legtobb pont lett elerasztva
		*/
		void EXT_GetBlobs(cv::Mat &inImg, cv::Rect *inMask, float inMinOutputSizeRate, std::vector<std::pair<int, int>> &outAreas, std::vector<std::pair<int, cv::Point2f>> &outBlobsCenter, std::vector<cv::Rect> &outBlobsRect, int &outMaxArea);
	}

	/**Megjelenito fuggvenyek gyujtemenye
	*/
	namespace NDisplay
	{
		/**Bemeneti valtozokat tagoltan irja ki (c++11)
		* @param n_args bemeno flusz parameterek szama (tovabbi parameterek csak stringek)
		*/
		//void EXT_ArticulateInformation(int spaceBetweenValues, int n_args, ...);
		/**Konzolra kiirja torzios egyutthato vektort
		* @param torzios egyutthatok
		*/
		void EXT_ShowDistortionCoefficient(cv::Mat &distCoeff);
		/**Konzolra kiirja a H transzformacio elemeit
		* @param H transzformacio
		*/
		void EXT_ShowHTransformation(cv::Mat &H);
		/**H matrixot atalakitja string formatumura
		* @param H transzformacio
		* @return kimeneti string H
		*/
		std::string EXT_GetHTransformation(cv::Mat &H);
		/**Kepre rajzol pontokat a megadott sugarakkal feltuntetve
		* @param points pontok
		* @param radius sugar
		* @param size a kep merete
		*/
		void EXT_ShowPointsWithRadius(std::vector<cv::Point> points, float radius, cv::Size size);
		/**"X" rajzolasa a bemeneti kepre
		* @param img bementi kep
		* @param center az "X" kozeppontja
		* @param color az "X" szine
		*/
		void EXT_drawCross(cv::Mat &img, cv::Point center, cv::Scalar color);
	}

	/**Nem kategorizalt fuggvenyek gyujtemenye
	*/
	namespace NOthers
	{
		/**Egy szamhoz egy olyan kimenetet genereal, hogy elotte legyen meghatarozott szamu nulla (kiiratasnal file kezelesnel segit)
		* @param number a szam, ami ele szeretnenk nullakat helyezni
		* @param sizeOfString hany plusz nullat szeretnenk a stringbe
		* @param outString a kimeneti string
		*/
		void EXT_Numbering(int number, int sizeOfString, std::string &outString);
//		/**Kiirja konzolra az aktualis feldolgozottsagot szazalekban
//		* @param actualProcTime ahol a feldolgozas tart
//		* @param allProcTime teljes feldolgozasi ido
//		*/
//		void EXT_CoutTimeOfProcessing(float actualProcTime, float allProcTime);
		/**Datumbol keszit egy stringet (yymmdd_hhmmss_mm)
		* @param time az ido, amibol stringet szerentenk csinalni
		* @param needDayMinSec kimeneti stringben benne lesz a nap, perc, masodperc
		* @param needMillisec kimeneti stringben millisec is benne lesz
		* @return string
		*/
		std::string EXT_DateToString(std::chrono::system_clock::time_point time, bool needHourMinSec = true, bool needMillisec = false);
		/**Letezik e az adott konyvtar, vagy file
		* @param fullPath konyvtar, vagy file elerese a teljes eleresi uttal
		*/
		bool EXT_CheckExist(std::string fullPath);
	}
}

#endif // __FUNCTIONS__