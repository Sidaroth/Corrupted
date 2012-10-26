/**
*	@file
*	This .cpp file handles the environment, and translating the bitmap
*/

#include "Environment.h"
#include <iostream>

EnvironmentHandler::EnvironmentHandler( )
{
	TILESIZE = 96;
}

bool EnvironmentHandler::loadContent( )
{
	if( !m_bitmap.loadFromFile( "../../Resources/levelOne.png" ) )
	{
		return EXIT_FAILURE;
	}

	m_iHorizontalBitmapSize = m_bitmap.getSize().x;
	m_iVerticalBitmapSize = m_bitmap.getSize().y;

	if(!m_tiles.loadFromFile( "../../Resources/tiles.png" ) )
	{
		return EXIT_FAILURE;
	}

	m_floorArray.reserve( m_iHorizontalBitmapSize * m_iVerticalBitmapSize );
	bitmapToArray( );
	m_sprites.reserve( m_floorArray.size( ) );
	createLevel( );
	checkWalls( );

	if(!m_objectBitmap.loadFromFile( "../../Resources/levelOneObjects.png" ) )
	{
		return EXIT_FAILURE;
	}

	m_objects.reserve( m_floorArray.size( ) );
	findObjects();

	return EXIT_SUCCESS;
}

void EnvironmentHandler::draw( sf::RenderWindow &window )
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
			pixelColor = m_bitmap.getPixel( i,j );
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

	for( int i = 0; i < m_floorArray.size( ); i++ )
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
sf::IntRect EnvironmentHandler::colorChart( RGB rgb )
{
	sf::IntRect subRect;
	subRect.left = 0;
	subRect.top = 0;
	subRect.width = TILESIZE;
	subRect.height = TILESIZE;

	///floorTile1
	if ( rgb.red == 255 && rgb.green == 0 && rgb.blue == 0 )
	{
		subRect.top = 0;
	}
	///floorTile2
	else if ( rgb.red == 0 && rgb.green == 255 && rgb.blue == 0 )
	{
		subRect.top = TILESIZE * 1;
	}
	///floorTile3
	else if ( rgb.red == 0 && rgb.green == 0 && rgb.blue == 255 )
	{
		subRect.top = TILESIZE * 2;
	}
	///floorTile4
	else if ( rgb.red == 255 && rgb.green == 255 && rgb.blue == 0 )
	{
		subRect.top = TILESIZE * 3;
	}
	///floorTile5
	else if ( rgb.red == 255 && rgb.green == 0 && rgb.blue == 255 )
	{
		subRect.top = TILESIZE * 4;
	}
	///floorTile6
	else if ( rgb.red == 0 && rgb.green == 255 && rgb.blue == 255 )
	{
		subRect.top = TILESIZE * 5;
	}
	///floorTile7
	else if ( rgb.red == 153 && rgb.green == 0 && rgb.blue == 0 )
	{
		subRect.top = TILESIZE * 6;
	}
	///wallTile1
	else if ( rgb.red == 0 && rgb.green == 0 && rgb.blue == 0 )
	{
		subRect.top = TILESIZE * 7;
	}
	else
	{
		subRect.width = 0;
		subRect.height = 0;
	}

	return subRect;
}

void EnvironmentHandler::checkWalls( )
{
	sf::IntRect testRect;
	sf::IntRect subRect;
	bool above = false;
	bool below = false;
	bool right = false;
	bool left = false;

	for( int i = 0; i < m_sprites.size(); i++ )
	{
		//std::cout << "\nmod: " << i % m_iHorizontalBitmapSize;
		above = false;
		below = false;
		right = false;
		left = false;
		subRect =  m_sprites[i].getTextureRect( );
		if( subRect.top >= TILESIZE * 7 )
		{
			if( i > 0 )
			{
				if( i % m_iHorizontalBitmapSize != 0 )
				{
					testRect =  m_sprites[i - 1].getTextureRect( );

					if( testRect.top >= TILESIZE * 7 )
					{
						left = true;
					}
				}
			}
			if( i < m_sprites.size( )-1 )
			{
				if( i % m_iHorizontalBitmapSize != ( m_iHorizontalBitmapSize - 1 ) )
				{
					testRect =  m_sprites[i + 1].getTextureRect( );

					if( testRect.top >= TILESIZE * 7 )
					{
						right = true;
					}
				}
			}
			if( i >= m_iHorizontalBitmapSize )
			{
				testRect =  m_sprites[i - m_iHorizontalBitmapSize].getTextureRect( );
			
				if( testRect.top >= TILESIZE * 7 )
				{
					above = true;
				}
			}
			if( i < ( m_sprites.size( ) - ( m_iHorizontalBitmapSize ) ) )
			{
				testRect =  m_sprites[i + m_iHorizontalBitmapSize].getTextureRect( );

				if( testRect.top >= TILESIZE * 7 )
				{
					below = true;
				}
			}
			if( right && below && !above && !left )
			{
				subRect.top = ( TILESIZE * 11 );
				m_sprites[i].setTextureRect( subRect );
			}
			else if( right && !below && above && !left )
			{
				subRect.top = ( TILESIZE * 12 );
				m_sprites[i].setTextureRect( subRect );
			}
			else if( !right && !below && above && left )
			{
				subRect.top = ( TILESIZE * 13 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( !right && below && !above && left )
			{
				subRect.top = (TILESIZE * 14);
				m_sprites[i].setTextureRect(subRect);
			}
			else if( !right && below && above && !left )
			{
				if( i % m_iHorizontalBitmapSize == 0 )
				{
					subRect.top = ( TILESIZE * 9 );
					m_sprites[i].setTextureRect( subRect );
				}
				else if( i % m_iHorizontalBitmapSize == ( m_iHorizontalBitmapSize - 1 ) )
				{
					subRect.top = ( TILESIZE * 10 );
					m_sprites[i].setTextureRect( subRect );
				}
			}
			else if( right && !below && !above && left )
			{
				if( i >= m_iHorizontalBitmapSize )
				{
					subRect.top = ( TILESIZE * 8 );
					m_sprites[i].setTextureRect( subRect );
				}
			}
		}
	}
}
/// Check the bitmap if it is possible to walk there(true) or not(false)
void EnvironmentHandler::findObjects()
{
	sf::Color pixelColor;
	for( int j = 0; j < m_iVerticalBitmapSize; j++ )
	{
		for( int i = 0; i < m_iHorizontalBitmapSize; i++ )
		{
			pixelColor = m_objectBitmap.getPixel( i, j );
			if( pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0 )
			{
				m_objects.push_back( false );
				//std::cout << '\n' << "vectorpos:  " << ( j * m_iHorizontalBitmapSize ) + i;
			}
			else if( pixelColor.r == 255 && pixelColor.g == 255 && pixelColor.b == 255 )
			{
				m_objects.push_back( true );
				//std::cout << '\n' << "vectorpos:  " << ( j * m_iHorizontalBitmapSize ) + i;
			}
			else if( pixelColor.r == 255 && pixelColor.g == 0 && pixelColor.b == 255 )
			{
				m_playerPosition.x = i * TILESIZE;
				m_playerPosition.y = j * TILESIZE;
				m_objects.push_back( true );
				//std::cout << '\n' << "vectorpos:  " << ( j * m_iHorizontalBitmapSize ) + i;
			}
		}
	}
}

bool EnvironmentHandler::checkCollision( Vector2f playerPosition )
{
	int x = playerPosition.x / TILESIZE;
	int y = playerPosition.y / TILESIZE;

	//for(int i = 64*63; i <= 64*64; i++)
	//{
	//	std::cout << "\nObject Bool: " << (bool)m_objects[((y * m_iHorizontalBitmapSize) + x )];
	//}

	if(!m_objects[( ( y * m_iHorizontalBitmapSize) + x )] )
	{
		return false;
	}
	else if(!m_objects[( ( y * m_iHorizontalBitmapSize) + ( x + 1 ) )] )
	{
		return false;
	}
	else if(!m_objects[( ( ( y + 1 ) * m_iHorizontalBitmapSize) + ( x + 1 ) )] )
	{
		return false;
	}
	else if(!m_objects[( ( ( y + 1 ) * m_iHorizontalBitmapSize) + x )] )
	{
		return false;
	}
	else
	{
		return true;
	}
}

Vector2f EnvironmentHandler::getPlayerPosition( )
{
	return m_playerPosition;
}