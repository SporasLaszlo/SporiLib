//#include "stdafx.h"
#include "CsvManipulate.h"

CCsvManipulate::CCsvManipulate(void)
{
	m_vecMonth.push_back("Január");
	m_vecMonth.push_back("Február");
	m_vecMonth.push_back("Március");
	m_vecMonth.push_back("Április");
	m_vecMonth.push_back("Május");
	m_vecMonth.push_back("Június");
	m_vecMonth.push_back("Július");
	m_vecMonth.push_back("Augusztus");
	m_vecMonth.push_back("Szeptember");
	m_vecMonth.push_back("Obtóber");
	m_vecMonth.push_back("November");
	m_vecMonth.push_back("December");
}
CCsvManipulate::~CCsvManipulate(void)
{
}

void EXT_Numbering(int number, int sizeOfNulls, std::string &outString)
{
	outString.clear();
	//outString = "_";

	std::string numberString;
	std::stringstream s;

	s << number;
	numberString = s.str();
	s.str("");
	int iter = sizeOfNulls - numberString.length();

	for (int i = 0; i < iter; i++)
		outString.append("0");

	outString.append(numberString);
}

void CCsvManipulate::EXT_ConvertAllFromAnsiToUTF8()
{
	std::vector<std::string> files;
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
	    /* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			files.push_back(std::string(ent->d_name));
			//printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else
	{
	  /* could not open directory */
		std::cout << "No directory!" << std::endl;
	}
	
	//Mappaban szereplo osszes mappa, files szurese, csak a 'MF69-' kezdetuekre (sablon: MF69-Szam-NameDate.csv)
	std::string subStr = "MF69-";
	
	for (int i = 0; i < files.size(); ++i)
	{
		if (!(files[i][0] == subStr[0] && files[i][1] == subStr[1] && files[i][2] == subStr[2] && files[i][3] == subStr[3] && files[i][4] == subStr[4]))
		//if (!(files[i].find(subStr) != std::string::npos))
		{
			files.erase(files.begin() + i);
			--i;
		}
	}
	
	for (int i = 0; i < files.size(); ++i)
	{
		std::cout << files[i] << std::endl;
	}
	
	//convert
	std::string convert = "./convert.sh";
	
	for (int i = 0; i < files.size(); ++i)
		system((convert + " " + files[i]).c_str());
}
void CCsvManipulate::EXT_GenerateLOGsFromOfficials(CCsv nameIDCSV, char separator)
{
	std::vector<std::string> files;
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
	    /* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			files.push_back(std::string(ent->d_name));
			//printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else
	{
	  /* could not open directory */
		std::cout << "No directory!" << std::endl;
	}
	
	//Mappaban szereplo osszes mappa, files szurese, csak a 'MF69-' kezdetuekre (sablon: MF69-Szam-NameDate.csv)
	std::string subStr = "utf8-MF69-";
	
	for (int i = 0; i < files.size(); ++i)
	{
		if (!(files[i].find(subStr) != std::string::npos))
		{
			files.erase(files.begin() + i);
			--i;
		}
	}
	
	for (int i = 0; i < files.size(); ++i)
	{
		std::cout << files[i] << std::endl;
	}
	
	int minStartSec = 8*60*60;
	int maxStartSec = 10*60*60;
	int minDiffSec = (int)(0.1f*60.0f*60.0f);
	int maxDiffSec = (int)(0.2f*60.0f*60.0f);
	
	for (int x = 0; x < nameIDCSV.EXT_GetRowSize(); ++x)
	{
		for (int i = 0; i < files.size(); ++i)
		{
			CCsv person;
			person.EXT_Read(files[i]);
			
			std::string outFileName = "check_";
			
			//Nev parositas
			if (nameIDCSV.EXT_GetElement(1, x) == person.EXT_GetElement(0, 0))
			{
				std::cout << person.EXT_GetElement(0, 0) << std::endl;
			
				std::string yy = files[i].substr(files[i].size() - 10, 4);
				std::string mm = files[i].substr(files[i].size() - 6, 2);
				std::string dd;
				
				//std::cout << yy << std::endl;
				//std::cout << mm << std::endl;
				
				//UID lekerese
				std::string UID = nameIDCSV.EXT_GetElement(2, x);
				std::replace(UID.begin(), UID.end(), ',', '_');
				outFileName += UID;
				outFileName += ".csv";
				
				std::ofstream outFile(outFileName);
				
				std::string aa = "SZ";
				
				if (aa != "SZ")
					std::cout << "gaz" << std::endl;
			
				for (int personRow = 0; personRow < person.EXT_GetRowSize(); ++personRow)
				{
					
					if (person.EXT_GetElement(3, personRow) != "0" && person.EXT_GetElement(3, personRow) != "SZ" && person.EXT_GetElement(3, personRow) != "K" && person.EXT_GetElement(3, personRow) != "B" && person.EXT_GetElement(3, personRow) != "FN")
					{
						std::string tmp = person.EXT_GetElement(2, personRow);
						EXT_Numbering(std::stoi(tmp), 2, dd);
					
						//std::cout << dd << std::endl;
						//std::cout << person.EXT_GetElement(3, personRow) << std::endl;
						
						//Becheck
						outFile << yy;
						outFile << ".";
						outFile << mm;
						outFile << ".";
						outFile << dd;
						outFile << ";";
						
						int baseSec = std::stoi(person.EXT_GetElement(3, personRow)) * 60 * 60;
						
						int checkTime = std::rand() % (maxStartSec - minStartSec) + minStartSec + 1;
						int addOutTime = std::rand() % (minDiffSec + maxDiffSec) - minDiffSec + baseSec + 1;
						int outTime = checkTime + addOutTime;
						
						int hour = checkTime / 3600;
						std::string timePart;
						EXT_Numbering(hour, 2, timePart);
						outFile << timePart;
						outFile << ":";
						checkTime -= hour * 3600;
						timePart = "";
						int min = checkTime / 60;
						EXT_Numbering(min, 2, timePart);
						outFile << timePart;
						outFile << ":";
						checkTime -= min * 60;
						timePart = "";
						int sec = checkTime;
						EXT_Numbering(sec, 2, timePart);
						outFile << timePart;
						outFile << ";";
						
						outFile << nameIDCSV.EXT_GetElement(2, x);
						outFile << "\n";
						
						//Random check ek 0 - 2 kozott (kimegy enni, vagy hozott magaval), legnagyobb valoszinuseggel 2 lesz
						int lunchTimeSec = 45 * 60;
						int diffLunch = 15 * 60;
						int calculateLunchTimeSec = std::rand() % (diffLunch * 2) - diffLunch + 1;
						calculateLunchTimeSec += lunchTimeSec;
						
						int randStartLunchTime = std::rand() % 3600 + 1;
						randStartLunchTime += 3600 * 12;
						
						int randEndLunchTime = randStartLunchTime + calculateLunchTimeSec;
						
						//100 % kozott kiosztja az eselyeket az egyes allapotokhoz
						int noOut = 10; //1 - 10
						int lunchOnlyOut = 10; //11 - 20
						int lunchOutBack = 80; //21 - 100
						
						int chance = std::rand() % 100 + 1;
						
						if (chance < 11)
						{
							//nem ment ki
							;
						}
						//munkaora tobb, mint 4
						else if (chance < 21 && std::stoi(person.EXT_GetElement(3, std::stoi(dd) - 1)) > 4)
						{
							//kiment, de visszajövet nem huzta le, csak kimenet
							outFile << yy;
							outFile << ".";
							outFile << mm;
							outFile << ".";
							outFile << dd;
							outFile << ";";
							
							int hour = randStartLunchTime / 3600;
							std::string timePart;
							EXT_Numbering(hour, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randStartLunchTime -= hour * 3600;
							timePart = "";
							int min = randStartLunchTime / 60;
							EXT_Numbering(min, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randStartLunchTime -= min * 60;
							timePart = "";
							int sec = randStartLunchTime;
							EXT_Numbering(sec, 2, timePart);
							outFile << timePart;
							outFile << ";";
						
							outFile << nameIDCSV.EXT_GetElement(2, x);
							outFile << "\n";
						}
						//munkaora tobb, mint 4
						else if (std::stoi(person.EXT_GetElement(3, std::stoi(dd) - 1)) > 4)
						{
							//lehuzta ki, es bemenetkor
							outFile << yy;
							outFile << ".";
							outFile << mm;
							outFile << ".";
							outFile << dd;
							outFile << ";";
							
							int hour = randStartLunchTime / 3600;
							std::string timePart;
							EXT_Numbering(hour, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randStartLunchTime -= hour * 3600;
							timePart = "";
							int min = randStartLunchTime / 60;
							EXT_Numbering(min, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randStartLunchTime -= min * 60;
							timePart = "";
							int sec = randStartLunchTime;
							EXT_Numbering(sec, 2, timePart);
							outFile << timePart;
							outFile << ";";
						
							outFile << nameIDCSV.EXT_GetElement(2, x);
							outFile << "\n";
							
							//back
							outFile << yy;
							outFile << ".";
							outFile << mm;
							outFile << ".";
							outFile << dd;
							outFile << ";";
							
							hour = randEndLunchTime / 3600;
							timePart = "";
							EXT_Numbering(hour, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randEndLunchTime -= hour * 3600;
							timePart = "";
							min = randEndLunchTime / 60;
							EXT_Numbering(min, 2, timePart);
							outFile << timePart;
							outFile << ":";
							randEndLunchTime -= min * 60;
							timePart = "";
							sec = randEndLunchTime;
							EXT_Numbering(sec, 2, timePart);
							outFile << timePart;
							outFile << ";";
						
							outFile << nameIDCSV.EXT_GetElement(2, x);
							outFile << "\n";
						}
						
						//Kicheck
						outFile << yy;
						outFile << ".";
						outFile << mm;
						outFile << ".";
						outFile << dd;
						outFile << ";";
						
						hour = outTime / 3600;
						timePart = "";
						EXT_Numbering(hour, 2, timePart);
						outFile << timePart;
						outFile << ":";
						outTime -= hour * 3600;
						timePart = "";
						min = outTime / 60;
						EXT_Numbering(min, 2, timePart);
						outFile << timePart;
						outFile << ":";
						outTime -= min * 60;
						timePart = "";
						sec = outTime;
						EXT_Numbering(sec, 2, timePart);
						outFile << timePart;
						outFile << ";";
						
						outFile << nameIDCSV.EXT_GetElement(2, x);
						outFile << "\n";
					}
				}
				
				outFile.close();
			}
		}
	}
	//for (int i = 0; i < nameIDCSV.EXT_GetRowSize(); ++i)
	//{
	//	std::cout << nameIDCSV.EXT_GetElement(1, i) << std::endl;
	//}
	
	
	
	
//	bool valid = true;
//	
//	for (int i = 0; i < selectedCols.size(); ++i)
//	{
//		if (selectedCols[i] < 0 || selectedCols[i] > EXT_GetColSize() - 1)
//			valid = false;
//	}
//	
//	if (valid)
//	{
//		std::string actualDate;
//		std::ofstream file;
//		std::string outFile = "check_";
//		
//		for (int row = 0; row < EXT_GetRowSize(); ++row)
//		{
//			if (actualDate != m_table[dateColIndex][row])
//			{
//				if (file.is_open())
//					file.close();
//				
//				actualDate = m_table[dateColIndex][row];
//				std::string date = actualDate;
//				std::replace(date.begin(), date.end(), '.', '_');
//				
//				outFile = "check_";
//				outFile += date;
//				outFile += ".txt";
//				
//				file.open(outFile);
//			}
//			
//			for (int col = 0; col < selectedCols.size(); ++col)
//			{
//				file << m_table[selectedCols[col]][row];
//				if (col != selectedCols.size() - 1)
//					file << separator;
//			}
//			file << "\n";
//		}
//		
//		if (file.is_open())
//			file.close();
//		
//		
//		
//		
//		
////		for (int row = 0; row < EXT_GetRowSize(); ++row)
////		{
////			for (int col = 0; col < selectedCols.size(); ++col)
////			{
////				file << m_table[selectedCols[col]][row];
////				if (col != selectedCols.size() - 1)
////					file << separator;
////			}
////			file << "\n";
////		}
////		file.close();
//	}
//	else
//		std::cout << "Wrong seletced col!" << std::endl;
}
void CCsvManipulate::EXT_GenerateSumFilesFromLOGs(CCsv nameIDCSV, char separator)
{
	std::vector<std::string> files;
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
	    /* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			files.push_back(std::string(ent->d_name));
			//printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else
	{
	  /* could not open directory */
		std::cout << "No directory!" << std::endl;
	}
	
	//Mappaban szereplo osszes mappa, files szurese, csak a 'MF69-' kezdetuekre (sablon: MF69-Szam-NameDate.csv)
	std::string subStr = "check_";
	
	for (int i = 0; i < files.size(); ++i)
	{
		if (!(files[i][0] == subStr[0] && files[i][1] == subStr[1] && files[i][2] == subStr[2] && files[i][3] == subStr[3] && files[i][4] == subStr[4] && files[i][5] == subStr[5]))
		//if (!(files[i].find(subStr) != std::string::npos))
		{
			files.erase(files.begin() + i);
			--i;
		}
	}
	
	for (int i = 0; i < files.size(); ++i)
	{
		CCsv personLog;
		personLog.EXT_Read(files[i]);
		
		//std::cout << files[i] << std::endl;
		//std::cout << personLog.EXT_GetElement(2, 0) << std::endl;
		
		for (int nameIDIndex = 0; nameIDIndex < nameIDCSV.EXT_GetRowSize(); ++nameIDIndex)
		{
			if (nameIDCSV.EXT_GetElement(2, nameIDIndex) == personLog.EXT_GetElement(2, 0))
			{
				std::string outUTF8FileName = "utf8-check_";
				outUTF8FileName += nameIDCSV.EXT_GetElement(1, nameIDIndex);
				outUTF8FileName += ".csv";
				
				//std::cout << outUTF8File << std::endl;
				//File megnyitas
				std::replace(outUTF8FileName.begin(), outUTF8FileName.end(), ' ', '_');
				std::ofstream outUTF8File(outUTF8FileName);
			
				std::string day = "";
				std::string timeStart = "";
				std::string timeEnd = "";
				
				for (int personLogRowIndex = 0; personLogRowIndex < personLog.EXT_GetRowSize(); ++personLogRowIndex)
				{
					if (day != personLog.EXT_GetElement(0, personLogRowIndex))
					{
						if (timeStart != "")
						{
							//kiiras
							outUTF8File << nameIDCSV.EXT_GetElement(1, nameIDIndex);
							outUTF8File << ";";
							outUTF8File << nameIDCSV.EXT_GetElement(2, nameIDIndex);
							outUTF8File << ";";
							outUTF8File << day;
							outUTF8File << ";";
							outUTF8File << timeStart;
							outUTF8File << ";";
							if (timeStart != timeEnd)
							{
								outUTF8File << timeEnd;
							}
							outUTF8File << ";";
							if (timeStart != timeEnd)
							{
								//eltoltott ido szamolasa
								std::string timePart;
						
								int sumSecStart = 0, sumSecEnd = 0;
								int diffTime;
								timePart = timeStart.substr(0, 2);
								sumSecStart = std::stoi(timePart) * 60 * 60;
								timePart = timeStart.substr(3, 2);
								sumSecStart += std::stoi(timePart) * 60;
								timePart = timeStart.substr(6, 2);
								sumSecStart += std::stoi(timePart);
						
								timePart = timeEnd.substr(0, 2);
								sumSecEnd = std::stoi(timePart) * 60 * 60;
								timePart = timeEnd.substr(3, 2);
								sumSecEnd += std::stoi(timePart) * 60;
								timePart = timeEnd.substr(6, 2);
								sumSecEnd += std::stoi(timePart);
						
								diffTime = sumSecEnd - sumSecStart;
						
								int hour = diffTime / 3600;
								timePart = "";
								EXT_Numbering(hour, 2, timePart);
								outUTF8File << timePart;
								outUTF8File << ":";
								diffTime -= hour * 3600;
								timePart = "";
								int min = diffTime / 60;
								EXT_Numbering(min, 2, timePart);
								outUTF8File << timePart;
								outUTF8File << ":";
								diffTime -= min * 60;
								timePart = "";
								int sec = diffTime;
								EXT_Numbering(sec, 2, timePart);
								outUTF8File << timePart;
							}
							outUTF8File << "\n";
						}
						
						day = personLog.EXT_GetElement(0, personLogRowIndex);
						timeStart = personLog.EXT_GetElement(1, personLogRowIndex);
					}
					
					timeEnd = personLog.EXT_GetElement(1, personLogRowIndex);
				}
				
				//utolso elem kiiratasa
				if (timeStart != "")
				{
					//kiiras
					outUTF8File << nameIDCSV.EXT_GetElement(1, nameIDIndex);
					outUTF8File << ";";
					outUTF8File << nameIDCSV.EXT_GetElement(2, nameIDIndex);
					outUTF8File << ";";
					outUTF8File << day;
					outUTF8File << ";";
					outUTF8File << timeStart;
					outUTF8File << ";";
					if (timeStart != timeEnd)
					{
						outUTF8File << timeEnd;
					}
					outUTF8File << ";";
					if (timeStart != timeEnd)
					{
						//eltoltott ido szamolasa
						std::string timePart;
						
						int sumSecStart = 0, sumSecEnd = 0;
						int diffTime;
						timePart = timeStart.substr(0, 2);
						sumSecStart = std::stoi(timePart) * 60 * 60;
						timePart = timeStart.substr(3, 2);
						sumSecStart += std::stoi(timePart) * 60;
						timePart = timeStart.substr(6, 2);
						sumSecStart += std::stoi(timePart);
						
						timePart = timeEnd.substr(0, 2);
						sumSecEnd = std::stoi(timePart) * 60 * 60;
						timePart = timeEnd.substr(3, 2);
						sumSecEnd += std::stoi(timePart) * 60;
						timePart = timeEnd.substr(6, 2);
						sumSecEnd += std::stoi(timePart);
						
						diffTime = sumSecEnd - sumSecStart;
						
						int hour = diffTime / 3600;
						timePart = "";
						EXT_Numbering(hour, 2, timePart);
						outUTF8File << timePart;
						outUTF8File << ":";
						diffTime -= hour * 3600;
						timePart = "";
						int min = diffTime / 60;
						EXT_Numbering(min, 2, timePart);
						outUTF8File << timePart;
						outUTF8File << ":";
						diffTime -= min * 60;
						timePart = "";
						int sec = diffTime;
						EXT_Numbering(sec, 2, timePart);
						outUTF8File << timePart;
					}
					outUTF8File << "\n";
				}
				
//				for (int dayIndex = 1; dayIndex <= howManyDay; ++dayIndex)
//				{
//					outUTF8File << nameIDCSV.EXT_GetElement(1, nameIDIndex);
//					outUTF8File << ";";
//					outUTF8File << m_vecMonth[month - 1];
//					outUTF8File << ";";
//					std::stringstream ss;
//					ss << dayIndex;
//					outUTF8File << ss.str();
//					ss.str("");
//					outUTF8File << ";";
//					
//					//kereses a log file ban, hogy mikor volt az elso be, es utolso ki check
//					
//					outUTF8File << "0";
//					outUTF8File << "\n";
//				}
				
				outUTF8File.close();
			}
		}
	}
	
	
//	std::vector<std::string> files;
//	
//	DIR *dir;
//	struct dirent *ent;
//	if ((dir = opendir(".")) != NULL)
//	{
//	    /* print all the files and directories within directory */
//		while ((ent = readdir(dir)) != NULL)
//		{
//			files.push_back(std::string(ent->d_name));
//			//printf("%s\n", ent->d_name);
//		}
//		closedir(dir);
//	}
//	else
//	{
//	  /* could not open directory */
//		std::cout << "nincs mappa" << std::endl;
//	}
//	
//	//Mappaban szereplo osszes mappa, files szurese, csak a 'check_' kezdetuekre (sablon: check_yyyy_mm_dd.txt)
//	std::string subStr = "check_";
//	
//	for (int i = 0; i < files.size(); ++i)
//	{
//		if (!(files[i].find(subStr) != std::string::npos))
//		{
//			files.erase(files.begin() + i);
//			--i;
//		}
//	}
//	
//	for (int i = 0; i < files.size(); ++i)
//	{
//		std::cout << files[i] << std::endl;
//	}
//	std::cout << std::endl;
//	
//	std::stringstream ss;
//	//Bubi rendezes a 'check_' nevu filekre
//	for (int j = 1; j < files.size() - 1; ++j)
//	{
//		for (int i = 0; i < files.size() - j; ++i)
//		{
//			std::string item;
//			std::vector<std::string> tokens1;
//			std::vector<std::string> tokens2;
//					
//			ss.clear();
//			ss << files[i];
//			while (std::getline(ss, item, '_'))
//				tokens1.push_back(item);
//			tokens1[tokens1.size() - 1] = tokens1[tokens1.size() - 1].substr(0, tokens1[tokens1.size() - 1].size() - 4);
//			
//			ss.clear();
//			ss << files[i + 1];
//			while (std::getline(ss, item, '_'))
//				tokens2.push_back(item);
//			tokens2[tokens2.size() - 1] = tokens2[tokens2.size() - 1].substr(0, tokens2[tokens2.size() - 1].size() - 4);
//			
//			//azert egy, hogy a 'check' reszt ne vizsgaljuk
//			for (int index = 1; index < tokens1.size(); ++index)
//			{
//				//std::cout << tokens1[index] << "  -  " << tokens2[index] << std::endl;
//						
//				if (std::stoi(tokens1[index]) > std::stoi(tokens2[index]))
//				{
//					std::string dummy;
//						
//					dummy = files[i];
//					files[i] = files[i + 1];
//					files[i + 1] = dummy;
//					
//					index = tokens1.size();
//				}
//				else if (std::stoi(tokens1[index]) < std::stoi(tokens2[index]))
//				{
//					index = tokens1.size();
//				}
//			}
//		}
//	}
//	
//	//Read names and id
//	std::ifstream in(nameIDCSV);
//	std::vector<std::pair<std::string, std::string>> vecNameIdPair;
//	
//	if (in)
//	{
//		std::string line;
//		while (std::getline(in, line))
//		{
//			std::stringstream ss(line);
//			std::string item;
//			std::vector<std::string> tokens;
//			
//			while (std::getline(ss, item, separator))
//				tokens.push_back(item);
//			
//			vecNameIdPair.push_back(std::pair<std::string, std::string>(tokens[0], tokens[1]));
//		}
//		
//		std::cout << "Read Name - ID pairs:" << std::endl;
//		for (int i = 0; i < vecNameIdPair.size(); ++i)
//		{
//			std::cout << vecNameIdPair[i].first << "   <<<   " << vecNameIdPair[i].second << std::endl;
//		}
//	}
//	else
//		std::cout << "Input file open error (default: Name_UID.csv)!" << std::endl;
//	
//	
//	
//	
//	for (int i = 0; i < files.size(); ++i)
//	{
//		std::cout << files[i] << std::endl;
//	}
}
void CCsvManipulate::EXT_ConvertAllFromUTF8ToAnsi()
{
	std::vector<std::string> files;
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
	    /* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			files.push_back(std::string(ent->d_name));
			//printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else
	{
	  /* could not open directory */
		std::cout << "No directory!" << std::endl;
	}
	
	//Mappaban szereplo osszes mappa, files szurese, csak a 'MF69-' kezdetuekre (sablon: MF69-Szam-NameDate.csv)
	std::string subStr = "utf8-";
	
	for (int i = 0; i < files.size(); ++i)
	{
		if (!(files[i][0] == subStr[0] && files[i][1] == subStr[1] && files[i][2] == subStr[2] && files[i][3] == subStr[3] && files[i][4] == subStr[4]))
		//if (!(files[i].find(subStr) != std::string::npos))
		{
			files.erase(files.begin() + i);
			--i;
		}
	}
	
	for (int i = 0; i < files.size(); ++i)
	{
		std::cout << files[i] << std::endl;
	}
	
	//convert
	std::string convert = "./convert.sh";
	
	for (int i = 0; i < files.size(); ++i)
	{
		//std::string newName = "ansi-";
		//newName += files[i].substr(5, files[i].size() - 5);
		system((convert + " " + files[i]).c_str());
	}
}