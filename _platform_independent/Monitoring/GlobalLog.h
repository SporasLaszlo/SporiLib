#ifndef __GLOBAL_LOG__
#define __GLOBAL_LOG__

#include <mutex>
#include <ctime> //std::time_t
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include "..\GlobalCore\TerminalTextColor.h"
#elif __linux__
#include "../GlobalCore/TerminalTextColor.h"
#endif

#pragma once
/**Az osztaly feladata, hogy logoljon mind consolra, vagy fileba (globalisan)
*/
class CGlobalLog
{
public:
	/**Kiiratas milyen csoportba sorolhato*/
	enum EGlobalLogMessageType { LogWithError, LogWithWarning, LogWithoutError };
private:
	/**Globalis logolas adatai*/
	struct SGlobalLogData
	{
		/**Globalis file, amibe a logolas tortenik*/
		std::string m_globalLogFileName {"GlobalLog.txt"};
		/**Logola szintje (fent declaralt enum szinten tortenik a kiiratas, minel magasabb az erteke, az es az annal kisebb ertekuek lesznek kiiratva)*/
		EGlobalLogMessageType m_logLevel { LogWithoutError };
		/**Kolcsonos kizaras*/
		std::mutex m_mutex;
	};
	static SGlobalLogData m_data;

	/**Folyamatos logolasokat vegzo belso fuggveny
	* @param message a kiirando uzenet
	*/
	static void _WriteCounting(std::string message);
public:
	CGlobalLog();
	~CGlobalLog();

	/**Logolas szintjeinek beallitasa*/
	static void EXT_SetLogLevel(EGlobalLogMessageType newLevel);
	/**Az uzenet kiiratasaert felelos fuggveny
	 * @param messageType logolasi uzenet milyen jellegu
	 * @param fileName melyik fileban keletkezett a logolas
	 * @param className objektum neve, ami uzenetet general
	 * @param classFunction az objektum fuggvenye, ahol uzenetet generalt
	 * @param lineNumber a log keletkezesenek soranak a szama
	 * @param message maga a generalt uzenet
	 */
	static void EXT_Log(EGlobalLogMessageType messageType, std::string fileName, std::string className, std::string classFunction, int lineNumber, std::string message);
};

#endif // __GLOBAL_LOG__