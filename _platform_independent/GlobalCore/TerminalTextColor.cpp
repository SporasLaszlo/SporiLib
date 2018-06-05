#include "TerminalTextColor.h"

bool CTerminalTextColor::m_init = false;
std::mutex CTerminalTextColor::m_mutex;
#ifdef _WIN32
std::map<CTerminalTextColor::ETerminalTextColor, int> CTerminalTextColor::m_terminalTextColors;
#elif __linux__
std::map<CTerminalTextColor::ETerminalTextColor, std::string> CTerminalTextColor::m_terminalTextColors;
#endif


void CTerminalTextColor::CTerminalTextColor::_Init()
{
	m_mutex.lock();
	m_terminalTextColors.clear();
#ifdef _WIN32
	m_terminalTextColors[TERMINALTEXTCOLOR_RESET] = 7;
	m_terminalTextColors[TERMINALTEXTCOLOR_RED] = 12;
	m_terminalTextColors[TERMINALTEXTCOLOR_GREEN] = 10;
	m_terminalTextColors[TERMINALTEXTCOLOR_YELLOW] = 14;
	m_terminalTextColors[TERMINALTEXTCOLOR_BLUE] = 9;
	m_terminalTextColors[TERMINALTEXTCOLOR_MAGENTA] = 13;
	m_terminalTextColors[TERMINALTEXTCOLOR_CYAN] = 11;
#elif __linux__
	m_terminalTextColors[TERMINALTEXTCOLOR_RESET] = "\033[0m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BLACK] = "\033[30m";
	m_terminalTextColors[TERMINALTEXTCOLOR_RED] = "\033[31m";
	m_terminalTextColors[TERMINALTEXTCOLOR_GREEN] = "\033[32m";
	m_terminalTextColors[TERMINALTEXTCOLOR_YELLOW] = "\033[93m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BLUE] = "\033[34m";
	m_terminalTextColors[TERMINALTEXTCOLOR_MAGENTA] = "\033[35m";
	m_terminalTextColors[TERMINALTEXTCOLOR_CYAN] = "\033[36m";
	m_terminalTextColors[TERMINALTEXTCOLOR_WHITE] = "\033[37m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDBLACK] = "\033[1m\033[30m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDRED] = "\033[1m\033[31m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDGREEN] = "\033[1m\033[32m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDYELLOW] = "\033[1m\033[33m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDBLUE] = "\033[1m\033[34m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDMAGENTA] = "\033[1m\033[35m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDCYAN] = "\033[1m\033[36m";
	m_terminalTextColors[TERMINALTEXTCOLOR_BOLDWHITE] = "\033[1m\033[37m";
#endif
	m_init = true;
	m_mutex.unlock();
}

void CTerminalTextColor::EXT_Cout(std::string text, ETerminalTextColor color)
{
	if (m_init == false)
		_Init();

#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	m_mutex.lock();
	int colorText = m_terminalTextColors.find(color)->second;
	SetConsoleTextAttribute(hConsole, colorText);

	std::cout << text;

	colorText = m_terminalTextColors.find(TERMINALTEXTCOLOR_RESET)->second;
	SetConsoleTextAttribute(hConsole, colorText);
	m_mutex.unlock();
#elif __linux__
	m_mutex.lock();
	std::string colorText = m_terminalTextColors.find(color)->second;
	colorText += text;
	colorText += m_terminalTextColors.find(TERMINALTEXTCOLOR_RESET)->second;
	m_mutex.unlock();

	std::cout << colorText;
#endif
}