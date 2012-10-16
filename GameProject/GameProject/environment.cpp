/**
*	@file
*	This .cpp file handles the environment, and translating the bitmap
*/

#include "Environment.h"

EnvironmentHandler::EnvironmentHandler()
{
	TILESIZE = 96;
}

bool EnvironmentHandler::loadContent(std::string path)
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
}

void EnvironmentHandler::draw(sf::RenderWindow &window)
{
	for( int i = 0; i <= m_sprites.size( ); i++ )
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
			pixelColor = m_bitmap.getPixel(i+1,j+1);
			RGB* rgb = new RGB;
			rgb->red = pixelColor.r;
			rgb->green = pixelColor.g;
			rgb->blue = pixelColor.b;
			m_floorArray.push_back(rgb);
		}
	}
}

void EnvironmentHandler::createLevel( ) 
{
	sf::Sprite sprite;
	sf::IntRect subRect;
	RGB* rgb = new RGB;
	int spriteX = 0;
	int spriteY = 0;
	for( int i = 0; i <= m_floorArray.size(); i++ )
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
///creates the subrect for the tile, depending on the RGB color on the pixel
sf::IntRect EnvironmentHandler::colorChart(RGB rgb)
{
	sf::IntRect subRect;

	///floorTile1
	if (rgb.red == 255 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.left = TILESIZE*0;
		subRect.top = TILESIZE*0;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile2
	if (rgb.red == 0 && rgb.green == 255 && rgb.blue == 0)
	{
		subRect.left = TILESIZE*1;
		subRect.top = TILESIZE*1;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile3
	if (rgb.red == 0 && rgb.green == 0 && rgb.blue == 255)
	{
		subRect.left = TILESIZE*2;
		subRect.top = TILESIZE*2;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile4
	if (rgb.red == 255 && rgb.green == 255 && rgb.blue == 0)
	{
		subRect.left = TILESIZE*3;
		subRect.top = TILESIZE*3;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile5
	if (rgb.red == 255 && rgb.green == 0 && rgb.blue == 255)
	{
		subRect.left = TILESIZE*4;
		subRect.top = TILESIZE*4;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile6
	if (rgb.red == 0 && rgb.green == 255 && rgb.blue == 255)
	{
		subRect.left = TILESIZE*5;
		subRect.top = TILESIZE*5;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///floorTile7
	if (rgb.red == 153 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.left = TILESIZE*6;
		subRect.top = TILESIZE*6;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
	///wallTile1
	if (rgb.red == 0 && rgb.green == 0 && rgb.blue == 0)
	{
		subRect.left = TILESIZE*7;
		subRect.top = TILESIZE*7;
		subRect.width = TILESIZE;
		subRect.height = TILESIZE;
		return subRect;
	}
}