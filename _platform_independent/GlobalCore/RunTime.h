#ifndef __RUNTIME__
#define __RUNTIME__

#include <chrono>
#include <iostream>
#include <string>

#pragma once
/**Futasi ido vizsgalatara szolgalo osztaly
*/
class CRunTime
{
private:
	//platformfuggetlen
	static std::chrono::steady_clock::time_point m_startRunTime, m_finishRunTime;
public:
	CRunTime();
	~CRunTime();

	/**Kezdesi ido beallitasa
	* @param showStart mutassa e a kezdeti idopontot
	*/
	static void EXT_SetStartTime(bool showStart = false);
	/**Befejezesi ido beallitasa
	* @param showTimeType milyen tipusu legyen a kiirt ido (alapertelmezetten az osszes; 0 = sec, 1 = msec, 2 = usec, 3 = nsec)
	* @param showFinish mutassa e a befejezesi idopontot
	* @param showRunTime mutassa e a futasi idot
	* @return visszater az eltelt idovel (showTimeType tol fugg, hogy mi a kimenet mertekegysege, -1 eseten sec)
	*/
	static float EXT_SetFinishTime(int showTimeType = -1, bool showFinish = false, bool showRunTime = true);
};

#endif // __RUNTIME__