#include "GlobalLog.h"

CGlobalLog::SGlobalLogData CGlobalLog::m_data;

CGlobalLog::CGlobalLog()
{
}
CGlobalLog::~CGlobalLog()
{
}

void CGlobalLog::EXT_SetLogLevel(EGlobalLogMessageType newLevel)
{
	m_data.m_logLevel = newLevel;
}
void CGlobalLog::EXT_Log(EGlobalLogMessageType messageType, std::string fileName, std::string className, std::string classFunction, int lineNumber, std::string message)
{
	if (m_data.m_logLevel >= messageType)
	{
#ifdef _WIN32
		time_t now = time(0);
		char TimeBuffer[26] = {};
		ctime_s(TimeBuffer, 26 * sizeof(char), &now);
		std::string date(TimeBuffer);
#elif __linux__
		time_t now = time(0);
		char *dt = ctime(&now);
		std::string date(dt);
#endif

		std::string writeMessage = "";
		if (messageType == LogWithoutError)
			writeMessage += "-----Log-----\n";
		else if (messageType == LogWithError)
			writeMessage += "-----Log Exception-----\n";

		writeMessage += "File name: ";
		writeMessage += fileName;
		writeMessage += "\n";

		writeMessage += "Class name: ";
		writeMessage += className;
		writeMessage += "\n";

		writeMessage += "Function of class: ";
		writeMessage += classFunction;
		writeMessage += "\n";

		writeMessage += "Line of message: ";
		std::stringstream s;
		s << lineNumber;
		writeMessage += s.str();
		writeMessage += "\n";

		writeMessage += "Message: ";
		writeMessage += message;
		writeMessage += "\n";

		writeMessage += "Date: ";
		writeMessage += date;
		writeMessage += "\n";
		writeMessage += "\n";

		if (messageType == LogWithError)
		{
			CTerminalTextColor::EXT_Cout(writeMessage, CTerminalTextColor::TERMINALTEXTCOLOR_RED);
			std::cout << std::endl;
		}
		else if (messageType == LogWithWarning)
		{
			CTerminalTextColor::EXT_Cout(writeMessage, CTerminalTextColor::TERMINALTEXTCOLOR_YELLOW);
			std::cout << std::endl;
		}
		else if (messageType == LogWithoutError)
		{
			CTerminalTextColor::EXT_Cout(writeMessage, CTerminalTextColor::TERMINALTEXTCOLOR_GREEN);
			std::cout << std::endl;
		}
		
		_WriteCounting(writeMessage);
	}
}
void CGlobalLog::_WriteCounting(std::string message)
{
	m_data.m_mutex.lock();

	std::fstream File(m_data.m_globalLogFileName.c_str());
	if (!File.is_open())
	{
		std::ofstream create_file(m_data.m_globalLogFileName.c_str());
		create_file.close();
		File.open(m_data.m_globalLogFileName.c_str());
	}
	File.seekp(0, std::ios_base::end);
	File << message;
	File.close();

	m_data.m_mutex.unlock();
}