/**
*	@file
*	This .cpp file handles the environment, and translating the bitmap
*/

#include "Environment.h"
#include <iostream>

EnvironmentHandler::EnvironmentHandler()
{
	TILESIZE = 96;
}

bool EnvironmentHandler::loadContent()
{
	if(!m_bitmap.loadFromFile("../../Resources/levelOne.png"))
	{
		return EXIT_FAILURE;
	}

	m_iHorizontalBitmapSize = m_bitmap.getSize().x;
	m_iVerticalBitmapSize = m_bitmap.getSize().y;

	if(!m_tiles.loadFromFile("../../Resources/tiles.png"))
	{
		return EXIT_FAILURE;
	}

	bitmapToArray();
	createLevel();

	return EXIT_SUCCESS;
}

void EnvironmentHandler::draw(sf::RenderWindow &window)
{
	for( int i = 0; i < m_sprites.size( ); i++ )
	{
		window.draw( m_sprites[i] );
	}
}

void EnvironmentHandler::bitmapToArray()
{
	sf::Color pixelColor;
	for( int j = 0; j < m_iVerticalBitmapSize; j++ )
	{
		for( int i = 0; i < m_iHorizontalBitmapSize; i++ )
		{
		//	std::cout << "i: " << i << " j: " << j << std::endl;
			pixelColor = m_bitmap.getPixel(i,j);
			RGB* rgb = new RGB;
			rgb->red = pixelColor.r;
			rgb->green = pixelColor.g;
			rgb->blue = pixelColor.b;
			m_floorArray.push_back(rgb);
		}
	}
}

/// Creates the level out of the floorArray
void EnvironmentHandler::createLevel( ) 
{
	sf::Sprite sprite;
	sf::IntRect subRect;
	RGB* rgb = new RGB;
	int spriteX = 0;
	int spriteY = 0;
	for( int i = 0; i < m_floorArray.size(); i++ )
	{
		sprite.setTexture( m_tiles );
		rgb = m_floorArray[i];
		subRect = colorChart( *rgb );
		sprite.setTextureRect( subRect );
		spriteX = i % m_iHorizontalBitmapSize;

		if( spriteX == 0 )
		{
			spriteY++;
		}
		sprite.setPosition( spriteX * TILESIZE , ( spriteY - 1 ) * TILESIZE );
		m_sprites.push_back( sprite );
	}
}
/// creates the subrect for the tile, depending on the RGB color on the pixel
sf::IntRect EnvironmentHandler::colorChart(RGB rgb)
{
	sf::IntRect subRect;
	subRect.left = 0;
	subRect.top = 0;
	subRect.width = TILESIZE;
	subRect.height = TILESIZE;

	///floorTile1
	if (rgb.red == 255 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.top = 0;
	}
	///floorTile2
	else if (rgb.red == 0 && rgb.green == 255 && rgb.blue == 0)
	{
		
		subRect.top = TILESIZE * 1;
	}
	///floorTile3
	else if (rgb.red == 0 && rgb.green == 0 && rgb.blue == 255)
	{
		
		subRect.top = TILESIZE*2;
	}
	///floorTile4
	else if (rgb.red == 255 && rgb.green == 255 && rgb.blue == 0)
	{
		subRect.top = TILESIZE*3;
	}
	///floorTile5
	else if (rgb.red == 255 && rgb.green == 0 && rgb.blue == 255)
	{
		subRect.top = TILESIZE*4;
	}
	///floorTile6
	else if (rgb.red == 0 && rgb.green == 255 && rgb.blue == 255)
	{
		subRect.top = TILESIZE*5;
	}
	///floorTile7
	else if (rgb.red == 153 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.top = TILESIZE*6;
	}
	///wallTile1
	else if (rgb.red == 0 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.top = TILESIZE * 6;
	}
	else
	{
		subRect.width = 0;
		subRect.height = 0;
	}

	return subRect;
}