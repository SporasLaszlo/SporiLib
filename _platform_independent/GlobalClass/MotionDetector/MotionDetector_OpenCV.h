#ifndef __MOTION_DETECTOR_OPENCV__
#define __MOTION_DETECTOR_OPENCV__

#include "MotionDetector.h"

#pragma once
/**Az osztaly feladata, hogy mozgas maszkokat generaljon, taroljon, es atadjon OpenCV - s osztalyt hasznalva
*/
class CMotionDetector_OpenCV : public CMotionDetector
{
protected:
	/**A mozgas maszkok kesziteseert, es parameterek beallitasaert (torteneti vagy "history", mozgas erzekenyseg) felelos valtozo*/
	cv::BackgroundSubtractorMOG2 m_backgroundSubstractor;
	/**Detektor altal hasznalt kep merete (elso meghivaskor lesz feltoltve)*/
	cv::Size m_imgSize;
	/**Olyan kep, ami a torteneti, "history" parameter altal eltarolt kepekbol vesz egy atlagolt kepet*/
	CMutexImage  m_fgimg;
public:
	CMotionDetector_OpenCV();
	virtual ~CMotionDetector_OpenCV();
	
	/**Belso parameterek feltoltese, es inicializalasa
	 * @param imageType milyen tipusu lesz a feldolgozando kep
	 * @papam history hatter mask mennyi frambol kepzodik atlagolva
	 * @param threshold 16 szokott az erteke lenni 4*4
	 * @param shadowDetection arnyek detekcio ki be kapcsolatas (nem sok valtozast tapasztaltam vele)
	 */
	void EXT_Init(ImageType imageType, int history, float threshold, bool shadowDetection);
	/**Mozgas maszkok keszitese, az eddig eltarolt, es az aktualisan kovetkezo kepek elemzesebol
	 * @param image soron kovetkezo kep pointer
	 */
	void EXT_Detect(CMutexImage *image);
};

#endif // __MOTION_DETECTOR_OPENCV__