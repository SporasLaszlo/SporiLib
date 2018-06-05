#ifndef __LUT_HOMOGRAPHY_POINT_TO_POINT__
#define __LUT_HOMOGRAPHY_POINT_TO_POINT__

#include <iostream>

#ifdef _WIN32
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "..\GlobalCore\Functions.h"
#include "..\Monitoring\GlobalLog.h"
#elif __linux__
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../GlobalCore/Functions.h"
#include "../Monitoring/GlobalLog.h"
#endif

#pragma once
/**2D kepekhez LUT tabla letrehozasa
*/
class CLUTHomographyPointToPoint
{
private:
	/**Az objektum inicializalva van - e*/
	bool m_init;
	/**Objektum azonosito*/
	int m_ID;
	/**Azonosito, ahonnan kepezzuk*/
	int m_fromViewID;
	/**Azonosito, ahova kepezzuk*/
	int m_toViewID;
	/**Nezet merete, ahonnan kepzunk*/
	cv::Size m_fromSize;
	/**Nezet merete, ahova kepzunk*/
	cv::Size m_toSize;
	/**Transzformacios matrix*/
	cv::Mat m_transformMat;

	/**From tabla pointere, aminek elemei akkor vannak letrehozva, ahol lett hozzaadott pont*/
	cv::Point **m_tableFromTo;
	/**From tabla merete (width * height)*/
	int m_tableSizeFromTo;
	/**To tabla pointere, aminek elemei akkor vannak letrehozva, ahol lett hozzaadott pont*/
	cv::Point **m_tableToFrom;
	/**To tabla merete (width * height)*/
	int m_tableSizeToFrom;
protected:
	/**LUT - ok letrehozasa
	 * @return sikeres volt e a lefoglalas
	 */
	int _createTables();
	/**Letrehozott LUT - ok feltoltese
	 * @param fromBinaryMask azon a kepen egy binaris maszk, amirol kepezni szeretnénk (0 = nem erdekelt resz, 255 = erdekelt resz) (CV_8UC1)
	 * @param toBinaryMask azok a kepen egy binaris maszk, amire képezni szeretnenk (0 = nem erdekelt resz, 255 = erdekelt resz) (CV_8UC1)
	 * @return tablak feltoltese sikeres volt e
	 */
	int _fillTables(const cv::Mat *fromBinaryMask = NULL, const cv::Mat *toBinaryMask = NULL);
public:
	CLUTHomographyPointToPoint(void);
	~CLUTHomographyPointToPoint(void);
	
	/**Objektum inicializalasa
	 * @param ID objektum azonosito
	 * @param fromViewID azonositoja annak a nezetnek, ahonnan kepezzuk
	 * @param toViewID azonositoja annak a nezetnek, ahova kepezzuk
	 * @param fromSize merete annak a nezetnek, ahonnan kepezzuk
	 * @param toSize merete annak a nezetnek, ahova kepezzuk
	 * @param transformMat a transzformacios matrix
	 * @param toBinaryMask azok a kepen egy binaris maszk, amire kepezni szeretnenk (0 = nem erdekelt resz, 255 = erdekelt resz) (CV_8UC1)
	 * @param fromBinaryMask azon a kepen egy binaris maszk, amirol kepezni szeretnenk (0 = nem erdekelt resz, 255 = erdekelt resz) (CV_8UC1)
	 * @return sikeres volt e az inicializalas
	 */
	int EXT_Init(int ID, int fromViewID, int toViewID, cv::Size fromSize, cv::Size toSize, cv::Mat transformMat, const cv::Mat *fromBinaryMask = NULL, const cv::Mat *toBinaryMask = NULL);
	/**Visszater a from koordinata lekepzett to koordinatajaval
	 * @param inFrom a kiindulo nezet koordinataja (bemenet)
	 * @param outTo veg nezet lekeptett koordinataja (kimenet)
	 * @return az adott bemeneti koordinatahoz tartozik e transzformalt koordinata a nezeten
	 */
	int EXT_GetFromTo(cv::Point &inFrom, cv::Point &outTo);
	/**Visszater a from koordinata lekepzett to koordinatajaval
	 * @param inTo a lekepzett pont koordinataja (bemenet)
	 * @param outFrom a kiindulo nezet koordinataja (honnan kepzodott az inTo) (kimenet)
	 * @return az adott kimeneti koordinatahoz tartozik e bemeneti koordinata
	 */
	int EXT_GetToFrom(cv::Point &inTo, cv::Point &outFrom);
	/**Objektum alaphelyzetbe allitasa, lefoglalt memoria felszabaditasa
	 */
	void EXT_Release();
};

#endif // __LUT_HOMOGRAPHY_POINT_TO_POINT__