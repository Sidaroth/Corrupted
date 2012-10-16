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
	int TILESIZE;

	sf::Image m_bitmap;
	sf::Texture m_tiles;
	int m_iHorizontalBitmapSize;
	int m_iVerticalBitmapSize;
	std::vector<RGB*> m_floorArray;
	std::vector<sf::Sprite> m_sprites;

public:
	EnvironmentHandler();
	bool loadContent();
	void draw(sf::RenderWindow &window);
	void bitmapToArray();
	void createLevel();
	sf::IntRect colorChart(struct RGB);
};