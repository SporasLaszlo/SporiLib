#ifndef __BASE_OBJECT__
#define __BASE_OBJECT__

#include <string>
#include <sstream>

#pragma once
/**Az osztaly feladata, hogy az alap adattagokat, es fuggvenyeket letrehozza, es a kesobbi osztalyok ebbol legyenek leszarmazva
*/
class CBaseObject
{
protected:
	/**Az objektum inicializalva van - e*/
	bool m_init;
	/**Object neve; logolashoz*/
	std::string m_className;
	/**Aktualis funkcio, ami fut; logolashoz*/
	std::string m_classFunction;
	/**Leszarmazott osztalyok azonositoja (opcionalis, ha a nev)*/
	int m_ID;
public:
	CBaseObject();
	~CBaseObject();

	/**Beallitja az objektum azonositojat
	 * @param ID az objektum azonositoja
	 */
	void EXT_SetID(int ID);
	/**Visszater az objektum azonositojaval
	 * @return az objektum azonositoja
	 */
	int EXT_GetID();
};

#endif // __BASE_OBJECT__