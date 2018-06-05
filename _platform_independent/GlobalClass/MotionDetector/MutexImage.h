#ifndef __MUTEX_IMAGE__
#define __MUTEX_IMAGE__

#ifdef _WIN32
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cvaux.h>
#elif __linux__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cvaux.h>
#endif
//#include "ippi.h"
//#include "ippcv.h"
//#include "defs.h"

/**Ez az enum tipus azt hatarozza meg, hogy a CMutexImage peldanya milyen tipusu kepet tarol
*/
enum ImageType {
	ImageType_SwissRanger4000Camera,
	ImageType_OpticalAxisCamera,
	ImageType_ThermalAxisCamera,
	ImageType_WebCamera,
	ImageType_Undefined
};

#pragma once
/**Az osztaly feladata, hogy a kepek atadasa, ha nem szukseges, ne masolassal oldodjon meg, hanem referenciaik atadasaval. 
 *Ez esetben figyelnunk kell arra, hogy az objektumokhoz egy idoben tobb szalu alkalmazasoknal tobb szal is hozzaferhet, ezert a kolcsonos kizaras 
 *problemakorevel is foglalkozni kell.
 */
class CMutexImage
{
private:
	/**Az tarolt kep*/
	cv::Mat m_image;
	/**A kephez tartozo, a kolcsonos kizarast megvalosito mutex*/
	cv::Mutex m_mutex;
	/**Milyen tipusu kamerahoz tartozo kepet, mozgas maszkot tarol (nem feltetlenul szukseges megadni a tarolashoz, ez esetben Undefined lesz)*/
	ImageType m_cameraType;
protected:
	/**Masolast vegrehajto fuggveny (from-bol -> to-ba, IppiCopy segitsegevel)
	 * @param from kep amit masolni szeretnenk
	 * @param to ahova masolni szeretnenk
	 */
	void static _copy(cv::Mat *from, cv::Mat *to);
public:
	/**Konstructor*/
	CMutexImage();
	CMutexImage(cv::Mat *image);
	/**Destructor*/
	~CMutexImage();

	/**Ha a keppel szeretnenk dolgozni, ez a fuggveny felel azert, hogy lefoglaljuk
	 */
	void EXT_Lock();
	/**Ha a kepen mar nem akarunk dolgozni, akkor fel kell oldani, hogy masok is lefoglalhassak, es dolgozhassanak vele
	 */
	void EXT_Unlock();
	/**Az objektum altal tarolni kivant kep beallitasa
	 * @param image a kep, amit tarolni akarunk (a referencia altal mutatott kep masolasa, es tarolasa)
	 */
	void EXT_SetImage(cv::Mat* image);
	/**Az objektum altal tarolni kivant kep beallitasa, egy masik hasonlo tipusu objektum altal
	 * @param image kolcsonos kizarast megvalosito objetum kepenek masolasa
	 */
	void EXT_SetImage(CMutexImage* image);
	/**Tarolt kep cimenek lekerese (hasznalatkor a lock es unlock hasznalata szukseges)
	 * @return tarolt kep cime
	 */
	cv::Mat* EXT_GetImagePointer();
	/**Belso cv::Mat kep atmasolasa e kimeneti kepbe (duplikalas)
	 * @param outputImage tarolt kep masolata
	 */
	void EXT_CopyImage(cv::Mat *outputImage);
	/**Input kep masolasa az output kepbe (IppiCopy)
	 * @param inputImage kep, amit masolni akarunk
	 * @param outputImage kep, ahova masolni szeretnenk
	 */
	void static EXT_CopyImage(cv::Mat *inputImage, cv::Mat *outputImage);
	/**Tarolt kep tipusanak beallitasa
	 * @param type beallitando tipus
	 */
	void EXT_SetImageType(ImageType type);
	/**Tarolt kep tipusanak lekerese
	 * @return tarolt elem kamera tipusa
	 */
	ImageType EXT_GetImageType();
};

#endif // __MUTEX_IMAGE__