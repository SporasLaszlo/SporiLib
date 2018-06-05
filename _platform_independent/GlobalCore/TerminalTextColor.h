#ifndef __TERMINALTEXTCOLOR__
#define __TERMINALTEXTCOLOR__

#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <map>
#include <mutex>

/**Konzolra kerulo szovegeknek ad szint
*/
#pragma once
class CTerminalTextColor
{
public:
	enum ETerminalTextColor
	{
		TERMINALTEXTCOLOR_RESET,
		TERMINALTEXTCOLOR_RED,
		TERMINALTEXTCOLOR_GREEN,
		TERMINALTEXTCOLOR_YELLOW,
		TERMINALTEXTCOLOR_BLUE,
		TERMINALTEXTCOLOR_MAGENTA,
		TERMINALTEXTCOLOR_CYAN,
#ifdef __linux__
		TERMINALTEXTCOLOR_BLACK,
		TERMINALTEXTCOLOR_WHITE,
		TERMINALTEXTCOLOR_BOLDBLACK,
		TERMINALTEXTCOLOR_BOLDRED,
		TERMINALTEXTCOLOR_BOLDGREEN,
		TERMINALTEXTCOLOR_BOLDYELLOW,
		TERMINALTEXTCOLOR_BOLDBLUE,
		TERMINALTEXTCOLOR_BOLDMAGENTA,
		TERMINALTEXTCOLOR_BOLDCYAN,
		TERMINALTEXTCOLOR_BOLDWHITE
#endif
	};
private:
	/**A szin vector inicializalva van e*/
	static bool m_init;
	/**Init fazishoz mutex*/
	static std::mutex m_mutex;
	/**Szineket tarolo vector parokba szedve*/
#ifdef _WIN32
	static std::map<ETerminalTextColor, int> m_terminalTextColors;
#elif __linux__
	static std::map<ETerminalTextColor, std::string> m_terminalTextColors;
#endif
	
	/**Inicializalja a statikus vectort a szinekkel
	 */
	static void _Init();
public:
	/**Adott szinnel irja ki a bemeneti szoveget
	 * @param text bemeneti szoveg
	 * @param color milyen szinnel irja ki
	 */
	static void EXT_Cout(std::string text, ETerminalTextColor color);
};

#endif // __TERMINALTEXTCOLOR__