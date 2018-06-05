#ifndef __COMBINEDCUDA__
#define __COMBINEDCUDA__

#include "CudaKernelInterface.h"

#include <opencv2\opencv.hpp>
#include <fstream>
#include <iostream>

#include <cuda_runtime.h>

#include "..\GlobalCore\RunTime.h"

/**Funkciok, az optimalis gridek, es blokkok megkeresesere szolgalo fuggveny parameter listabajaban konnyebb azonositas
*/
enum ECUDAFunction{
	CUDAFunction_MedianFilter3x3,
	//PCState_Release,
	//PCState_Default
};

#pragma once
/**Feladata, hogy az OpenCV es a CUDA egyuttes kezelesere egy interfacet szolgaltasson
*/
class CCombinedCUDA
{
private:
	static bool m_CUDAInit;
	static int m_CUDAWarpSize;
	static int m_CUDAMaxThreadNumberPerMultiProcessor;
	static int m_CUDAMaxThreadNumberPerBlock;
	static int m_CUDAHalfMaxThreadNumberPerBlock;

	/**Megkeresi egy adott kepmerethet, a leggyorsabb futast eredmenyezo grid, es blokk meretet
	* @param imgIn egy random kep, aminek a merete a fontos, ezen lesz tesztelve a fuggveny
	* @param gridSize out, optimalis grid meret
	* @param blockSize out, az optimalis blokk meret
	*/
	static void _CalculateMedianFilter3x3GridAndBlockSize(cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize);
public:
	CCombinedCUDA(void);
	~CCombinedCUDA(void);

	/**Inicializalja az osztalyt
	 */
	static void EXT_Init();
	/**Megkeresi egy adott funkciohoz, es egy adott kepmerethet, a leggyorsabb futast eredmenyezo grid, es blokk meretet
	 * @param function fuggveny, amire a tesztet akarjuk futtatni
	 * @param imgIn egy random kep, aminek a merete a fontos, ezen lesz tesztelve a fuggveny
	 * @param gridSize out, optimalis grid meret
	 * @param blockSize out, az optimalis blokk meret
	 */
	static void EXT_GetOptimalGridAndBlockSize(ECUDAFunction function, cv::Mat &imgIn, cv::Size &gridSize, cv::Size &blockSize);

	/**MedianFilter futtatasa 3x3 filterrel (csak 8UC1)
	* @param imgIn bemeneti kep, amin a szurot szeretnenk futtatni
	* @param imgOut szuro lefutasa utan a kimeneti kep
	* @param iterationNumber egymas utan hanyszor szeretnenk a szurot lefuttatni
	* @param gridSize 
	* @param blockSize
	*/
	static void EXT_MedianFilter3x3(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, dim3 gridSize, dim3 blockSize);
	/**MedianFilter futtatasa 3x3 filterrel, kepek 1D - s vektoran (csak 8UC1)
	* @param imgIn bemeneti kep, amin a szurot szeretnenk futtatni
	* @param imgOut szuro lefutasa utan a kimeneti kep
	* @param iterationNumber egymas utan hanyszor szeretnenk a szurot lefuttatni
	* @param gridSize
	* @param blockSize
	*/
	static void EXT_MedianFilter3x3_1D(cv::Mat &imgIn, cv::Mat &imgOut, int iterationNumber, int gridSize, int blockSize);
	/**Kep masolast valosit meg (rosszabb mint az osszes, ez csak teszt miatt vettem fel pluszban)
	 * @param imgIn bemeneti kep
	 * @param imgOut masolt kep
	 */
	static void EXT_CopyImage(cv::Mat &imgIn, cv::Mat &imgOut);
};

#endif // __COMBINEDCUDA__