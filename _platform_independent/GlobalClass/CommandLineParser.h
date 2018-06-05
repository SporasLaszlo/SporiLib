#ifndef __COMMANDLINEPARSER__
#define __COMMANDLINEPARSER__

#include <string>

/**Parancssorban futtatott allomanyok kapcsoloihoz tartozo ertekek beolvasasara alkalmas parser
*/
#pragma once
class CCommandLineParser
{
	/*Bemeneti parameterek szama (kapcsolok, est ertekek egyutt)*/
	int m_argc;
	/*Bementei parameterek vektora*/
	char **m_argv;
public:
	/**Bemeneti parameterek szamanak feltoltese, es a konkret parameterek feltoltese
	 * @param _argc parameterek szama
	 * @param _argv parameterek vektora
	 */
	CCommandLineParser(int _argc, char **_argv);
	/**Megvizsgalja, hogy a parameterek között (vagy kapcsolo) az adott string szerepel e (ha igen, akkor igazzal ter vissza)
	 * @param param keresett parameter
	 */
	bool operator[](std::string param);
	/**Egy adott parameterhez (vagy kapcsolohoz) visszater az ertekkel (egyel nagyobb indexu elemmel)
	 * @param param keresett parameter
	 * @param defValue alapertelmezett ertek, ha a keresett parameter nem talalhato
	 * @return keresett parameterhez tartozo ertek
	 */
	std::string operator()(std::string param, std::string defValue = "-1");
};

#endif // __COMMANDLINEPARSER__