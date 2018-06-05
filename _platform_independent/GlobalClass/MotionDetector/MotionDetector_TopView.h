#ifndef __MOTION_DETECTOR_TOPVIEW__
#define __MOTION_DETECTOR_TOPVIEW__

#ifdef _WIN32
#include "opencv\cv.hpp"
#include "MotionDetector.h"
#include "..\..\GlobalCore\RunTime.h"
#elif __linux__
#include "opencv/cv.hpp"
#include "MotionDetector.h"
#include "../../GlobalCore/RunTime.h"
#endif

struct SPart
{
	cv::Size m_thisPartSize;
	std::vector<int> m_startPointerPositionOfRows;
	int centralPointPosition;
	bool processed {false};
};

#pragma once
/**Az osztaly feladata, hogy mozgasmaszkokat generaljon reszeket nezve, nem az osszes pixelen vegigmenve (CV_8UC1)
*/
class CMotionDetector_TopView : public CMotionDetector
{
public:
	/**Detektor altal hasznalt kep merete (elso meghivaskor lesz feltoltve)*/
	cv::Size m_imgSize;
	/**Mozgasmaszkok egy ilyen tortenet tarolo vektorba kerulnek, melynek ciklikus a feltoltese*/
	uchar **m_history;
	/**Torteneti vektor merete*/
	int m_historySize;
	/**Bemeneti kepek .data() merete (w * h); m_history[m_historyDataSize][m_historySize]*/
	int m_historyDataSize;
	/**Feltoltes vagy csere kozben hol tartunk a vektorban*/
	int m_historyActualPos;
	/**az m_history belso elemeintek osszege (meret m_historyDataSize)*/
	int *m_historySum;
	/**az m_history belso elemeintek atlaga (meret m_historyDataSize)*/
	int *m_historyAvg;

	int m_historyPartSize;
	int m_historyPartSizeIteration;
	int m_historyPartLastPos;
	int *m_historyPartSum;
	int *m_historyPartAvg;
	/**mi az a valtozaskulonbseg az aktualis frame es az atlagolt memoriban levo hattermaszk kozott, amire mar azt mondjuk, hogy mozgas*/
	int m_threshold;

	cv::Size m_processingPartSize;
	cv::Size m_partsOfImageSize;
	SPart **m_partsOfImage;
	//int **m_partOfImageHistory;
	//int m_partOfImageHistoryThreshold;
	//cv::Mat m_backGroundMask;
	//cv::Mat m_foreGroundMask;
	//float m_backGroundChangePercent;
public:
	CMotionDetector_TopView();
	~CMotionDetector_TopView();

	/**Belso parameterek feltoltese, es inicializalasa
	* @param imageType milyen tipusu lesz a feldolgozando kep
	* @papam history hatter mask mennyi frambol kepzodik atlagolva
	* @param threshold mi az a valtozaskulonbseg az aktualis frame es az atlagolt memoriban levo hattermaszk kozott, amire mar azt mondjuk, hogy mozgas
	* @param shadowDetection arnyek detekcio ki be kapcsolatas (nem sok valtozast tapasztaltam vele)
	*/
	void EXT_Init(ImageType imageType, int history, float threshold, bool shadowDetection);
	/**Beallitja a mozgas detektornak meg szukseges parametereket
	*/
	void EXT_SetParameters(cv::Size processingImageSize, cv::Size processingPartSize);
	/**Mozgas maszkok keszitese, az eddig eltarolt, es az aktualisan kovetkezo kepek elemzesebol
	* @param image soron kovetkezo kep pointer
	*/
	void EXT_Detect(CMutexImage *image);
};

#endif // __MOTION_DETECTOR_TOPVIEW__