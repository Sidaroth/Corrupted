/**
*	@file
*	This .h file that handles the environment, and translating the bitmap
*/
#include "SFML/Graphics.hpp"
#include <vector>

class EnvironmentHandler
{
private:
	struct RGB
	{
		int red;
		int green;
		int blue;
	};
	sf::Image m_bitmap;
	int m_iHorizontalBitmapSize;
	int m_iVerticalBitmapSize;
	std::vector<RGB*> m_floorArray;

public:
	bool loadContent(std::string path);
	void bitmapToArray();
	void drawLevel();
	sf::IntRect colorChart(struct RGB);
};