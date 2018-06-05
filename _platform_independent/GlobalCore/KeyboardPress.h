#ifndef __KEYBOARD_PRESS__
#define __KEYBOARD_PRESS__

#include <thread>
#include <mutex>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#elif __linux__
#endif

#pragma once
/**Az osztaly feladata, hogy a gomb leuteseket kezelje, es visszaadja a legutolsolag leutott billentyut (enter szukseges)
*/
class CKeyboardPress
{
private:
	/**Karakter figyeleshez szukseges adatok*/
	struct SKeyboardPressData
	{
		/**Billentyuzet figyeles aktiv e*/
		bool m_isListening {false};
		/**Leutott utolso karakter*/
		char m_lastChar;
		/**Karakterhez mutex*/
		std::mutex m_mutexChar;
	};
	
	/**Adat stuktura a billenytyuzet lenyomashoz*/
	static SKeyboardPressData m_data;
	/**Szal, amiben a billentyuzet figyelve van*/
	static std::thread m_threadListening;
	
	/**Billentyu leutest figyelo szal
	 * @param data adatok a szalnak
	 */
	static void _ThreadListening(SKeyboardPressData *data);
public:
	CKeyboardPress(void);
	~CKeyboardPress(void);

	/**Figyelo szal inditasa
	 */
	static void EXT_StartListening();
	/**Visszater a legkeseobb leutott billentyuvel char formaban (ha nem volt leutes, akkor '\n', ENTER a visszateres) (Egy leutest csak egyszer kezel le, kovetkezo ciklusban szinten ENTER rel ter vissza)
	 * @return leutoljara leutott billentyu
	 */
	static char EXT_LastKeyDownChar();
	/**Felszabaditja a futo szalat, ami a karakter lenyomast figyeli
	 */
	static void EXT_ReleaseListening();
};

#endif // __KEYBOARD_PRESS__