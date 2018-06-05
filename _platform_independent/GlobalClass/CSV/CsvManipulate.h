#ifndef __CSV_MANIPULATE__
#define __CSV_MANIPULATE__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "Csv.h"

class CCsvManipulate
{
private:
	/**Honapok tarolva szovegese, indexek 0 tol*/
	std::vector<std::string> m_vecMonth;
	//std::vector<std::pair<int, std::string>> m_vecNumber;
public:
	CCsvManipulate();
	~CCsvManipulate();
	
	/**Az osszes 'MF69-' kezdeto filt atkonvertalja (a bemeneti csv k iso-8859-2, ezeket kozben atkonvertalja majd utf-8 ra)
	 */
	void EXT_ConvertAllFromAnsiToUTF8();
	/**General kimeneteti txt fileket napra leosztva
	 * @param nameIDCSV a nev - kartyaID parost tarolja (Formatum: Sorszam;Nev;UnitID)
	 */
	void EXT_GenerateLOGsFromOfficials(CCsv nameIDCSV, char separator = ';');
	/**Az osszes check_date.csv filbol a mappaban legeneral egy osszesitett excel.csv - t (kell egy nev-id paros csv is)
	 * @param nameIdCsv a nev - kartyaID parost tarolja (Formatum: Sorszam;Nev;UnitID)
	 * @param separator milyen elvalaszto elem kvan a nem id paros kozott
	 */
	void EXT_GenerateSumFilesFromLOGs(CCsv nameIDCSV, char separator = ';');
	/**Az osszes 'utf8-check' kezdeto filt atkonvertalja (a bemeneti csv k utf-8, ezeket kozben atkonvertalja majd iso-8859-2 ra)
	 */
	void EXT_ConvertAllFromUTF8ToAnsi();
};

#endif // __CSV_MANIPULATE__