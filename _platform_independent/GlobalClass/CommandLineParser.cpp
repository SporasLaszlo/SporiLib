#include "CommandLineParser.h"

CCommandLineParser::CCommandLineParser(int _argc, char **_argv)
	: m_argc(_argc)
	, m_argv(_argv)
{
}
bool CCommandLineParser::operator[](std::string param)
{
	int idx = -1;
	for (int i = 0; i < m_argc && idx == -1; i++)
		if (std::string(m_argv[i]) == param) idx = i;
	return (idx != -1);
}
std::string CCommandLineParser::operator()(std::string param, std::string defValue)
{
	int idx = -1;
	for (int i = 0; i < m_argc && idx == -1; i++)
		if (std::string(m_argv[i]) == param) idx = i;
	if (idx == -1)
		return defValue;
	else 
		return (m_argv[idx + 1]);
}