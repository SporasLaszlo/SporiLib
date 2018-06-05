#ifndef __COMBINEDOPENCL__
#define __COMBINEDOPENCL__

#define __CL_ENABLE_EXCEPTIONS

#include <opencv2\opencv.hpp>
#include <fstream>
#include <iostream>

#include <c:\OCLPack\include\CL\cl.h>
#include <c:\OCLPack\include\CL\cl.hpp>
//#include <CL\cl.hpp>
#include "..\GlobalCore\RunTime.h"

/**Funkciok, az optimalis gridek, es blokkok megkeresesere szolgalo fuggveny parameter listabajaban konnyebb azonositas
*/
enum EOpenCLFunction{
	OpenCLFunction_MedianFilter3x3,
	//PCState_Release,
	//PCState_Default
};

#pragma once
/**Feladata, hogy az OpenCV es az OpenCL egyuttes kezelesere egy interfacet szolgaltasson
*/
class CCombinedOpenCL
{
private:
	static bool m_openCLInit;
	static std::vector<cl::Platform> m_openCLAllPlatforms;
	static std::vector<cl::Device> m_openCLAllDevices;
	static cl::Context m_openCLContext;
	static cl::Program m_openCLProgram;

	//
	static cl::Program m_openCLProgram2;
	//

	static cl::CommandQueue m_openCLQueue;

	//
	static cl::CommandQueue m_openCLQueue2;
	//

	/**Megkeresi egy adott kepmerethet, a leggyorsabb futast eredmenyezo grid, es blokk meretet
	* @param imgIn egy random kep, aminek a merete a fontos, ezen lesz tesztelve a fuggveny
	* @param gridSize out, optimalis grid meret
	* @param blockSize out, az optimalis blokk meret
	*/
	static void _CalculateMedianFilter3x3GridAndBlockSize(cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize);
public:
	CCombinedOpenCL(void);
	~CCombinedOpenCL(void);

	/**Inicializalja az osztalyt
	 */
	static void EXT_Init();
	/**Megkeresi egy adott funkciohoz, es egy adott kepmerethet, a leggyorsabb futast eredmenyezo grid, es blokk meretet
	* @param function fuggveny, amire a tesztet akarjuk futtatni
	* @param imgIn egy random kep, aminek a merete a fontos, ezen lesz tesztelve a fuggveny
	* @param gridSize out, optimalis grid meret
	* @param blockSize out, az optimalis blokk meret
	*/
	static void EXT_GetOptimalGridAndBlockSize(EOpenCLFunction function, cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize);

	/**MedianFilter futtatasa 3x3 filterrel (csak 8UC1)
	 * @param imgIn bemeneti kep, amin a szurot szeretnenk futtatni
	 * @param imgOut szuro lefutasa utan a kimeneti kep
	 * @param iterationNumber egymas utan hanyszor szeretnenk a szurot lefuttatni
	 * @param gridSize ennyi blokkra lesz majd szukseg
	 * @param blockSize blokk merete, ennyi szal lesz egy blokkban
	 */
	static void EXT_MedianFilter3x3(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, cv::Size gridSize, cv::Size blockSize);
	/**MedianFilter futtatasa 3x3 filterrel 1D vektorral csak (csak 8UC1)
	* @param imgIn bemeneti kep, amin a szurot szeretnenk futtatni
	* @param imgOut szuro lefutasa utan a kimeneti kep
	* @param iterationNumber egymas utan hanyszor szeretnenk a szurot lefuttatni
	*/
	static void EXT_MedianFilter3x3_1D(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, int gridSize, int blockSize);
	/**WarpPerspective megvalositasa (rosszabb IPP nel)
	* @param imgIn bemeneti kep, amit transzformalunk
	* @param imgOut kimeneti kep a transzformalt bemeneti merettel
	* @param imgOutSize kimeneti kep merete
	* @param H transzformacio
	* @param gridSize ennyi blokkra lesz majd szukseg
	* @param blockSize blokk merete, ennyi szal lesz egy blokkban
	*/
	static void EXT_WarpPerspective(cv::Mat &imgIn, cv::Mat &imgOut, cv::Size imgOutSize, cv::Mat H, cv::Size gridSize, cv::Size blockSize);
};

#endif // __COMBINEDOPENCL__