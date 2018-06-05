#include "KeyboardPress.h"

CKeyboardPress::SKeyboardPressData CKeyboardPress::m_data;
std::thread CKeyboardPress::m_threadListening;

CKeyboardPress::CKeyboardPress()
{
}
CKeyboardPress::~CKeyboardPress()
{
}

void CKeyboardPress::_ThreadListening(SKeyboardPressData *data)
{
	char ch;

	while (data->m_isListening)
	{
#ifdef _WIN32
		//Ez var addig, amig nem jon egy char (nem kell neki ENTER)
		ch = _getch();
		
		data->m_mutexChar.lock();
		data->m_lastChar = ch;
		data->m_mutexChar.unlock();

		std::cout << "Pressed key: '" << ch << "'" << std::endl;
#elif __linux__
		//*
		int iter = 0;
		ch = '-';
		
		while (ch != '\n')
		{
			ch = std::getchar();
			if (iter == 0)
			{
				data->m_mutexChar.lock();
				data->m_lastChar = ch;
				data->m_mutexChar.unlock();
				
				std::cout << "Pressed key: ";
				std::cout << ch << std::endl;
			}
			iter++;
		}
		//*/
#endif
	}
}
void CKeyboardPress::EXT_StartListening()
{
	if (m_data.m_isListening == false)
	{
		m_data.m_isListening = true;
		m_threadListening = std::thread(_ThreadListening, &m_data);
	}
	else
	{
		std::cout << "Listening is already active!" << std::endl;
	}
}
char CKeyboardPress::EXT_LastKeyDownChar()
{
	m_data.m_mutexChar.lock();
	char ch = m_data.m_lastChar;
	m_data.m_lastChar = '\n';
	m_data.m_mutexChar.unlock();
	
	return ch;
}
void CKeyboardPress::EXT_ReleaseListening()
{
	if (m_data.m_isListening == true)
	{
#ifdef _WIN32
		std::cout << "Press any key to finish the character listening..." << std::endl;
#elif __linux__
		std::cout << "Press an ENTER to finish the character listening..." << std::endl;
#endif
		m_data.m_isListening = false;
		m_threadListening.join();
	}
}