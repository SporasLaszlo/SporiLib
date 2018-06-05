#ifndef __COLOR_GENERATOR__
#define __COLOR_GENERATOR__

#include <vector>

#ifdef _WIN32
#include <opencv2\core\core.hpp>
#elif __linux__
#include <opencv2/core/core.hpp>
#endif

#pragma once
/**Szinek visszaadasaert felelos objektum (tulindexelheto a szinpaletta)
 */
class CColorGenerator
{
private:
	struct SColorGeneratorData
	{
		/**Szin vektor inicializalva van e*/
		bool m_init{ false };
		/**Szineket tarolo vector*/
		std::vector<cv::Scalar> m_colors;
	};
	static SColorGeneratorData m_data;

	/**Inicializalja a statikus vectort a szinekkel
	 */
	static void _Init();
public:
	CColorGenerator();
	~CColorGenerator();

	/**Szin lekerese adott index szerint, ha tulindexeles van, akkor is a vektoron beluli elemmel ter vissza
	 * @param ID lekerendo szint index
	 */
	static cv::Scalar EXT_GetColor(int ID);
};

#endif // __COLOR_GENERATOR__