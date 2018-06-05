#ifndef __CSV__
#define __CSV__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

class CCsv
{
private:
	/**Beolvasott tabla (indexeles: col, row)*/
	std::vector<std::vector<std::string>> m_table;
	
	/**Torli a tablat
	*/
	void _ClearTable();
public:
	CCsv();
	~CCsv();
	
	/**Beolvassa a csv file - t
	 * @param file beolvasando file
	 * @param separator milyen elvalaszto karakter lesz a beolvasando file - ban
	 */
	void EXT_Read(std::string file, char separator = ';');
	/**Lekeri a tablaban levo oszlopok szamat
	 */
	int EXT_GetColSize();
	/**Lekeri a tablaban levo sorok szamat
	 */
	int EXT_GetRowSize();
	/**Lekeri a tabla egy elemet
	 * @param col melyik oszlop
	 * @param row melyik sor
	 */
	std::string EXT_GetElement(int col, int row);
	/**Rendezi a beolvasott tablat datum, es ido szerint
	 * @param colPos_yymmdd pozicioja az ev-ho-nap oszlopnak (formatum: yyyy.mm.dd)
	 * @param colPos_hhmmss pozicioja az ora-perc-mpercnek (formatum: hh:mm:ss) 
	 */
	void EXT_SortAboutDate(int colPos_yyyymmdd, int colPos_hhmmss);
	/**Kiirja a tablat
	 */
	void EXT_Show();
};

#endif // __CSV__