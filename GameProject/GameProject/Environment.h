/**
*	@file
*	This .h file that handles the environment, and translating the bitmap
*/
#include "SFML/Graphics.hpp"
#include <vector>
#include "Vector2f.h"

#pragma once

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

	Vector2f m_playerPosition;

	sf::Image m_bitmap;
	sf::Texture m_tiles;
	sf::Image m_objectBitmap;

	int m_iHorizontalBitmapSize;
	int m_iVerticalBitmapSize;

	std::vector<RGB*> m_floorArray;
	std::vector<sf::Sprite> m_sprites;
	std::vector<bool> m_objects;

public:
	EnvironmentHandler( );
	bool loadContent( );
	void draw( sf::RenderWindow &window );
	void bitmapToArray( );
	void createLevel( );
	sf::IntRect colorChart( struct RGB );
	void checkWalls( );
	void findObjects( );
	bool checkCollision( Vector2f playerPosition );
	Vector2f getPlayerPosition( );
};