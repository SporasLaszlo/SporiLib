#ifndef __COMBINED_IPP__
#define __COMBINED_IPP__

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

#include "ippcore.h"
#include "ippi.h"
#include "ipps.h"
#include "ippcc.h"
#include "ippcv.h"
#include "ippvm.h" //CrossProduct

#pragma once
/**Feladata, hogy az OpenCV es az IPP egyuttes kezelesere egy interfacet szolgaltasson
*/
class CCombinedIPP
{
protected:
	void static _resize_image_8UC1_Linear(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
	void static _resize_image_8UC3_Linear(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
	void static _resize_image_8UC1_Super(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
	void static _resize_image_8UC3_Super(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
	void static _resize_image_8UC1_Lanczos(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
	void static _resize_image_8UC3_Lanczos(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y);
public:
	CCombinedIPP(void);
	~CCombinedIPP(void);

	/**Kepek atmeretezese (IPPIResize)
	 * @param input_image kep, amit atmeretezunk (csak: CV_8UC1, CV_8UC3; OpenCV tipus)
	 * @param output_image kimeneti atmeretezett kep
	 * @param dst_size_x kimeneti kep szelessege (x)
	 * @param dst_size_y kimeneti kep magassaga (y)
	 * @param interpolationType az etmeretezes soran hasznalt interpolacio (Ippi - s tipus) (csak: ippLinear, ippSuper, ippLanczos)
	 */
	void static EXT_ResizeImage(cv::Mat *input_image, cv::Mat *output_image, int dst_size_x, int dst_size_y, IppiInterpolationType interpolationType = ippLinear);
	/**Szines kepet szurkearnyalatossa alakit
	 * @param input_image kep, amit at akarunk konvertalni (csak: CV_8UC3; OpenCV tipus)
	 * @param output_image kimeneti szurkearnyalatos kep
	 */
	void static EXT_RGBToGray(cv::Mat *input_image, cv::Mat *output_image);
	/**Integral kep keszitese
	 * @param input_image szurkearnyalatos bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image kimeneti integral kep
	 */
	void static EXT_Integral(cv::Mat *input_image, cv::Mat *output_image);
	/**Input kep masolasa az output kepbe (A kep meretek meg fognak egyezni)
	 * @param input_image kep, amit masolni akarunk (csak: CV_8UC1, CV_8UC3; OpenCV tipus)
	 * @param output_image kep, ahova masolni szeretnenk
	 * @param roi a bemeneti kep mekkora reszet kell majd masolni
	 */
	void static EXT_CopyImage(cv::Mat *input_image, cv::Mat *output_image, IppiRect *roi = NULL);
	/**Kep erosionalasa (3x3 as matrixal)
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image ahova az erosiot vegre szeretnenk hajtani, NULL eseten a bemeneti kep lesz egyben a kimeneti kep is
	 */
	void static EXT_Erode(cv::Mat *input_image, cv::Mat *output_image = NULL);
	/**Kep hizlalasa (3x3 as matrixal)
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image ahova a hizlalast vegre szeretnenk hajtani, NULL eseten a bemeneti kep lesz egyben a kimeneti kep is
	 */
	void static EXT_Dilate(cv::Mat *input_image, cv::Mat *output_image = NULL);
	/**Bemeneti CV_8UC1 kepen thresholdolas (aminel nagyobbak, azokra uj ertek)
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param thresValue vagasi ertek (ez meg beletartozik az uj max ertekbe)
	 * @param value uj ertek az igaz pixelekre
	 */
	void static EXT_Threshold_GT(cv::Mat *input_image, Ipp8u thresValue, Ipp8u value);
	/**Bemeneti CV_8UC1 kepen thresholdolas (aminel kisebb, azokra uj ertek)
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param thresValue vagasi ertek (ez meg beletartozik az uj min ertekbe)
	 * @param value uj ertek az igaz pixelekre
	 */
	void static EXT_Threshold_LT(cv::Mat *input_image, Ipp8u thresValue, Ipp8u value);
	/**Bemeneti CV_8UC1 kepen thresholdolas (ket terfelre ertekek felvetele)
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param thresValue vagasi ertek (ez meg beletartozik az uj max ertekbe)
	 * @param minValue vagas alatti pixelek uj erteke
	 * @param maxValue vagas feletti pixelek uj erteke
	 */
	void static EXT_Threshold(cv::Mat *input_image, Ipp8u thresValue, Ipp8u minValue, Ipp8u maxValue);
	/**2 kep osszeadasat valositja meg az output_image kepen (0 es 255 os ertekekre tokeletesen mukodik)
	* @param input_image1 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	* @param input_image2 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	* @param output_image kimeneti kep, ha NULL, a kimenet az input_image2 lesz
	*/
	void static EXT_Add(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image = NULL);
	/**2 kep and kapcsolatat valositja meg az output_image kepen (0 es 255 os ertekekre tokeletesen mukodik)
	 * @param input_image1 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param input_image2 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image kimeneti kep, ha NULL, a kimenet az input_image2 lesz
	 */
	void static EXT_And(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image = NULL);
	/**2 kep and kapcsolatat valositja meg egy meghatarozott roi - val
	 * @param inImg bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param inOutImg bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param roi kivagott terulet, amin a muveletet szeretnenk elvegezni (ha az outImg NULL, akkor vigyazni kell, mert a recten kivul eso pixelek nem fognak valtozni)
	 * @param outImg kimeneti kep, ha NULL, a kimenet az inOutImg lesz
	 */
	void static EXT_AndWithROI(cv::Mat &inImg, cv::Mat &inOutImg, IppiRect roi, cv::Mat *outImg = NULL);
	/**2 kep or kapcsolatat valositja meg az output_image kepen (0 es 255 os ertekekre tokeletesen mukodik)
	 * @param input_image1 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param input_image2 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image kimeneti kep, ha NULL, a kimenet az input_image2 lesz
	 */
	void static EXT_Or(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image = NULL);
	/**2 kep xor kapcsolatat valositja meg az output_image kepen (0 es 255 os ertekekre tokeletesen mukodik)
	 * @param input_image1 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param input_image2 bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param output_image kimeneti kep, ha NULL, a kimenet az input_image2 lesz
	 */
	void static EXT_Xor(cv::Mat *input_image1, cv::Mat *input_image2, cv::Mat *output_image = NULL);
	/**Elarasztasos algoritmust valosit meg az input_image kepen, egy kornyezeten belul, ami egyben a kimeneti kep is lesz
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param seed elarasztas kezdopontja
	 * @param newVal elarasztott teruletek uj erteke
	 * @param pRegion informaciokat tarol az elarasztott teruletrol
	 */
	void static EXT_FloodFill(cv::Mat *input_image, IppiPoint seed, Ipp8u newVal, IppiConnectedComp *pRegion);
	/**Elarasztasos algoritmust valosit meg az input_image kepen, egy kornyezeten belul, ami egyben a kimeneti kep is lesz
	 * @param input_image bemeneti kep (csak: CV_8UC1; OpenCV tipus)
	 * @param seed elarasztas kezdopontja
	 * @param newVal elarasztott teruletek uj erteke
	 * @param minDelta a seed pont erteke, es a vizsgalt pont kozti minimalis megengedett elteres ertek
	 * @param maxDelta a seed pont erteke, es a vizsgalt pont kozti maximalis megengedett elteres ertek
	 * @param pRegion informaciokat tarol az elarasztott teruletrol
	 */
	void static EXT_FloodFillRange(cv::Mat *input_image, IppiPoint seed, Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta, IppiConnectedComp *pRegion);
	/**
	 */
	bool static EXT_GetWarpPerspectiveInf(IppiRect rectRoi, cv::Mat H, int *out_width, int *out_height, int *out_offset_x, int *out_offset_y);
	/**Homografiai transzformacio vegrehajtasa
	 * @param inputImage bemeneti kep, amin a muveletet elvegezzuk
	 * @param outputImage kimeneti kep, a muvelet eredmenye
	 * @param H a homografiai transzformacio matrixa (3x3)
	 * @param srcRoi a bemeneti kep melyik teruletere szeretnenk a transzformaciot lefuttatni
	 * @param dstSize maga a kimeneti kep merete
	 * @param dstRoi a kimeneti kepen melyik az a terulet, ami a transzformacio szempontjabol fontos, csak ezen a teruleten lesznek kimeneti eredmenyek
	 */
	IppStatus static EXT_WarpPerspective(cv::Mat *inputImage, cv::Mat *outputImage, cv::Mat H, IppiRect srcRoi, IppiSize dstSize, IppiRect dstRoi);
	/**Megszamolja azokat a pixeleket, amik megfelelnek a Bound felteteleknek (uchar bemenetu kepekre)
	 * @param inputImage a bemeneti kep, amin szamolni kell (egesz kepre nezve)
	 * @param counts a szamlalo (output)
	 * @param lowerBound a legkisebb ertek, ami meg a szamlalt ertekekhez hozzaveheto (0 - 255)
	 * @param upperBound a legnagyobb ertek, ami meg a szamlalt ertekekhez hozzaveheto (0 - 255)
	 */
	void static EXT_CountInRange(cv::Mat *inputImage, int *counts, Ipp8u lowerBound, Ipp8u upperBound);
	/**Megszamolja azokat a pixeleket, amik megfelelnek a Bound es a roi felteteleknek (uchar bemenetu kepekre)
	 * @param inputImage a bemeneti kep, amin szamolni kell (csak a roi teruleten levo pixelekre lesz a meres)
	 * @param counts a szamlalo (output)
	 * @param lowerBound a legkisebb ertek, ami meg a szamlalt ertekekhez hozzaveheto (0 - 255)
	 * @param upperBound a legnagyobb ertek, ami meg a szamlalt ertekekhez hozzaveheto (0 - 255)
	 * @param roi a kepnek azon terulete, amin a szamlalast el szeretnenk vegezni
	 */
	void static EXT_CountInRangeWithROI(cv::Mat *inputImage, int *counts, Ipp8u lowerBound, Ipp8u upperBound, IppiRect roi);	
	/**A bemeneti 2 kepet osszefuzi egy kimeneti kepbe, amin az elso kep van rajta, es kozvetlej jobbra mellette a masodik (1 es 3 csatornas uchar kepre is)
	 * @param inputImage1 elso bemeneti kep
	 * @param inputImage2 masodik bemeneti kep
	 * @param outputImage az osszefuzott kimeneti kep
	 */
	void static EXT_Concatenate(cv::Mat *inputImage1, cv::Mat *inputImage2, cv::Mat *outputImage);
	/**Egy 1 csatornas uchar kepet konvertal at short tipusuva
	 * @param inputImage bemeneti uchar kep
	 * @param outputImage kimeneti short kep
	 */
	void static EXT_Convert8u16u(cv::Mat *inputImage, cv::Mat *outputImage);
	/**Egy 1 csatornas uchar kepen megkeresi a maximum pontot, es visszater az ertekkel, es a koordinataval
	 * @param inputImage bemeneti kep, amin a maximumot keressuk
	 * @param outMaxVal a maximum ertek
	 * @param outIndexX a maximum ertek X koordinataja
	 * @param outindexY a maximum ertek Y koordinataja
	 */
	void static EXT_MaxIndex(cv::Mat *inputImage, int &outMaxVal, int &outIndexX, int &outindexY);
	/**Beallitja a bemeneti kep minden pixelet a parameterul kapott ertekkel (inicializalas)
	 * @param inputImage bemeneti kep
	 * @param scalar a parameter ertek, amivel fel szeretnenk tolteni a bemeneti kepet
	 */
	void static EXT_SetImage(cv::Mat &inputImage, cv::Scalar scalar);
	/**Ket kep kozotti valamilyen transzformacio megvalositasa LUT felhasznalasaval
	 * @param inputImage bemeneti kep
	 * @param outputImage kimeneti kep
	 * @param srcRoi bemeneti kep azon resze, amin a transzformaciot szeretnenk vegrehajtani
	 * @param dstSize kimeneti kep azon resze, amin a transzformácio utan beleesik a kimenetbe
	 * @param xMap kimeneti kep a LUT x koordinatai
	 * @param yMap kimeneti kep a LUT y koordinatai
	 */
	void static EXT_Remap(cv::Mat &inputImage, cv::Mat &outputImage, IppiRect srcRoi, IppiSize dstSize, cv::Mat &xMap, cv::Mat &yMap);
	/**Median szuro elvegzese a bemeneti kepre
	 * @param inputImage bemeneti kep
	 * @param outputImage szures utani kimeneti kep
	 */
	void static EXT_MedianFilter(cv::Mat &inputImage, cv::Mat &outputImage);
};

#endif // __COMBINED_IPP__