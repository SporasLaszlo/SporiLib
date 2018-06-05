#include "RunTime.h"

//platformfuggetlen
std::chrono::steady_clock::time_point CRunTime::m_startRunTime;
std::chrono::steady_clock::time_point CRunTime::m_finishRunTime;

CRunTime::CRunTime()
{
}
CRunTime::~CRunTime()
{
}

void CRunTime::EXT_SetStartTime(bool showStart)
{
	m_startRunTime = std::chrono::steady_clock::now();

	if (showStart)
	{
		std::cout << "Start time (msec): ";
		std::cout << std::chrono::time_point_cast<std::chrono::milliseconds>(m_startRunTime).time_since_epoch().count() << std::endl;
	}
}
float CRunTime::EXT_SetFinishTime(int showTimeType, bool showFinish, bool showRunTime)
{
	m_finishRunTime = std::chrono::steady_clock::now();

	if (showFinish)
	{
		std::cout << "Finish time (msec): ";
		std::cout << std::chrono::time_point_cast<std::chrono::milliseconds>(m_finishRunTime).time_since_epoch().count() << std::endl;
	}

	float diff = 0;

	if (showRunTime)
	{
		if (showTimeType == 3 || showTimeType == -1)
		{
			std::chrono::duration<float, std::nano> durationDiff = m_finishRunTime - m_startRunTime;
			diff = durationDiff.count();
			std::cout << "Run time (nsec): ";
			std::cout << diff << std::endl;
		}

		if (showTimeType == 2 || showTimeType == -1)
		{
			std::chrono::duration<float, std::micro> durationDiff = m_finishRunTime - m_startRunTime;
			diff = durationDiff.count();
			std::cout << "Run time (usec): ";
			std::cout << diff << std::endl;
		}

		if (showTimeType == 1 || showTimeType == -1)
		{
			std::chrono::duration<float, std::milli> durationDiff = m_finishRunTime - m_startRunTime;
			diff = durationDiff.count();
			std::cout << "Run time (msec): ";
			std::cout << diff << std::endl;
		}

		if (showTimeType == 0 || showTimeType == -1)
		{
			std::chrono::duration<float> durationDiff = m_finishRunTime - m_startRunTime;
			diff = durationDiff.count();
			std::cout << "Run time (sec): ";
			std::cout << diff << std::endl;
		}
	}

	return diff;
}