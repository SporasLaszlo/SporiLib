#ifndef __MOTION_DETECTOR__
#define __MOTION_DETECTOR__

#ifdef _WIN32
#include "..\..\BaseObject.h"
#include "..\..\Monitoring\GlobalLog.h"
#include "MutexImage.h"
#elif __linux__
#include "../../BaseObject.h"
#include "../../Monitoring/GlobalLog.h"
#include "MutexImage.h"
#endif

#pragma once
/**Az osztaly feladata, hogy mozgas maszkokat generaljon, taroljon, es atadjon
*/
class CMotionDetector : public CBaseObject
{
public:
	/**A kep, amin a mozgast szeretnenk erzekelni*/
	CMutexImage m_image;
	/**Kimeneti mozgas maszk*/
	CMutexImage m_outImage;
public:
	CMotionDetector();
	virtual ~CMotionDetector();
	
	/**Belso parameterek feltoltese, es inicializalasa
	 * @param imageType milyen tipusu lesz a feldolgozando kep
	 * @papam history hatter mask mennyi frambol kepzodik atlagolva
	 * @param threshold 16 szokott az erteke lenni 4*4
	 * @param shadowDetection arnyek detekcio ki be kapcsolatas (nem sok valtozast tapasztaltam vele)
	 */
	virtual void EXT_Init(ImageType imageType, int history, float threshold, bool shadowDetection) = 0;
	/**Mozgas maszkok keszitese, az eddig eltarolt, es az aktualisan kovetkezo kepek elemzesebol
	 * @param image soron kovetkezo kep pointer
	 */
	virtual void EXT_Detect(CMutexImage *image) = 0;
	/**Bemeneti kep lekerese
	 * @return bemeneti kep
	 */
	CMutexImage* EXT_GetInputImage();
	/**Legyartott eloter maszk lekerese
	 * @return elkesztitett es eltarolt mozgas maszk cime
	 */
	CMutexImage* EXT_GetMovingMask();
};

#endif // __MOTION_DETECTOR__