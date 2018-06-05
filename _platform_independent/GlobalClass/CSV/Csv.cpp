//#include "stdafx.h"
#include "Csv.h"

CCsv::CCsv(void)
{
}
CCsv::~CCsv(void)
{
}
void CCsv::_ClearTable()
{
	for (int i = 0; i < m_table.size(); ++i)
		m_table[i].clear();
	m_table.clear();
}

void CCsv::EXT_Read(std::string file, char separator)
{
	//std::setlocale(LC_ALL, "hu.UTF-8");
	std::ifstream in(file);
	//1250 hun
	//in.imbue(std::locale(".1250"));
	//in.imbue(std::locale(in.getloc(), new std::codecvt<>))
	
	if (in)
	{
		_ClearTable();
		
		std::string line;
		while (std::getline(in, line))
		{
			//std::string aaa(line.begin(), line.end());
			std::stringstream ss(line);
			std::string item;
			std::vector<std::string> tokens;
			
			int colSize = std::count(line.begin(), line.end(), separator) + 1;
			
			//std::cout << line << std::endl;
			
			while (std::getline(ss, item, separator))
			{
				//std::cout << item << std::endl;
				tokens.push_back(item);
			}
				
			//feltoltes az utolso ures helyre, vagy a zaro "\n" torlese
			if (tokens.size() != colSize)
				tokens.push_back("");
			else
			{
				//std::string str = tokens.back();
				//str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
				//str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
				
				//std::cout << str << std::endl;
				
				//std::replace(tokens.back().begin(), tokens.back().end(), '\n', '');
				tokens.back().erase(std::remove(tokens.back().begin(), tokens.back().end(), '\n'), tokens.back().end());
				tokens.back().erase(std::remove(tokens.back().begin(), tokens.back().end(), '\r'), tokens.back().end());
				//if (tokens[tokens.size() - 1][tokens[tokens.size() - 1].size() - 1] == '\n')
				//{
				//	std::cout << "dsgffgsdfgds" << std::endl;
					//tokens[tokens.size() - 1] = tokens[tokens.size() - 1].substr(0, tokens[tokens.size() - 1].size() - 1);
					//tokens.back().erase(tokens.back().end() - 1, tokens.back().end());
				//}
			}
			
			if (m_table.size() == 0)
				m_table.resize(tokens.size());
			
			for (int i = 0; i < tokens.size(); ++i)
			{
				m_table[i].push_back(tokens[i]);
				//std::cout << tokens[i] << " <<< ";
			}
			//std::cout << std::endl;
		}
	}
	else
	{
		std::string message = "Input file open error: ";
		message += file;
		message += "\n";
		std::cout << message << std::endl;
	}
}
int CCsv::EXT_GetColSize()
{
	return m_table.size();
}
int CCsv::EXT_GetRowSize()
{
	int rowSize = 0;
	if (m_table.size() > 0)
		rowSize = m_table[0].size();
	
	return rowSize;
}
std::string CCsv::EXT_GetElement(int col, int row)
{
	std::string element = "";
	
	if (col > -1 && col < m_table.size() && row > -1 && row < m_table[0].size())
		element = m_table[col][row];
	else
		std::cout << "Invalid selected index!" << std::endl;
	
	return element;
}
void CCsv::EXT_SortAboutDate(int colPos_yyyymmdd, int colPos_hhmmss)
{
	if (colPos_yyyymmdd > -1 && colPos_yyyymmdd < m_table.size() && colPos_hhmmss > -1 && colPos_hhmmss < m_table.size())
	{
		bool valid = true;
		
		std::regex regDate1("([2]\\d{3}).(1[0-2]|[1-9]).([12]\\d|3[01]|[1-9])");
		std::regex regDate2("(1[0-9]|2[0-3]|[0-9]):([1-5][0-9]|[0-9]):([1-5][0-9]|[0-9])");
		
		if (m_table[colPos_yyyymmdd].size() > 0)
		{
			if (!std::regex_match(m_table[colPos_yyyymmdd][0], regDate1))
				valid = false;
			if (!std::regex_match(m_table[colPos_hhmmss][0], regDate2))
				valid = false;
		}
		
		if (valid)
		{
			std::stringstream ss;
			for (int j = 1; j < m_table[colPos_yyyymmdd].size() - 1; ++j)
			{
				for (int i = 0; i < m_table[colPos_yyyymmdd].size() - j; ++i)
				{
					std::string item;
					std::vector<std::string> tokens1;
					std::vector<std::string> tokens2;
					
					ss.clear();
					ss << m_table[colPos_yyyymmdd][i];
					while (std::getline(ss, item, '.'))
						tokens1.push_back(item);
					
					ss.clear();
					ss << m_table[colPos_hhmmss][i];
					while (std::getline(ss, item, ':'))
						tokens1.push_back(item);
					
					ss.clear();
					ss << m_table[colPos_yyyymmdd][i + 1];
					while (std::getline(ss, item, '.'))
						tokens2.push_back(item);
					
					ss.clear();
					ss << m_table[colPos_hhmmss][i + 1];
					while (std::getline(ss, item, ':'))
						tokens2.push_back(item);
					
					//std::cout << tokens1.size() << " - " << tokens2.size() << std::endl;
					
					for (int index = 0; index < tokens1.size(); ++index)
					{
						//std::cout << tokens1[index] << "  -  " << tokens2[index] << std::endl;
						
						if (std::stoi(tokens1[index]) > std::stoi(tokens2[index]))
						{
							std::string dummy;
						
							for (int colIndex = 0; colIndex < m_table.size(); ++colIndex)
							{
								dummy = m_table[colIndex][i];
								m_table[colIndex][i] = m_table[colIndex][i + 1];
								m_table[colIndex][i + 1] = dummy;
							}
						
							index = tokens1.size();
						}
						else if (std::stoi(tokens1[index]) < std::stoi(tokens2[index]))
						{
							index = tokens1.size();
						}
					}
				}
			}
		}
		else
			std::cout << "Wrong format!" << std::endl;
	}
	else
		std::cout << "Invalid selected index!" << std::endl;
}
void CCsv::EXT_Show()
{
	for (int row = 0; row < EXT_GetRowSize(); ++row)
	{
		for (int col = 0; col < EXT_GetColSize(); ++col)
		{
			std::cout << m_table[col][row] << " <<< ";
		}
		std::cout << std::endl;
	}
}