/**
*	@file
*	This .cpp file handles the environment, and translating the bitmap
*/

#include "Environment.h"
#include <iostream>
#include "StateHandler.h"

EnvironmentHandler::EnvironmentHandler( )
{
	std::cout << "Environment created!\n";
	TILESIZE = 96;
}

EnvironmentHandler::~EnvironmentHandler()
{
	for( std::vector<RGB*>::iterator it = m_floorArray.begin(); it != m_floorArray.end();)
	{
		delete * it;
		it = m_floorArray.erase(it);
	}

	m_sprites.erase(m_sprites.begin(), m_sprites.end());	// erases all / calls deconstructor for the objects.
	m_objects.erase(m_objects.begin(), m_objects.end());	// Erases all / calls deconstructor for the objects.
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

void EnvironmentHandler::draw()
{
	sf::View tempView = StateHandler::getInstance().m_pWindow->getView();

	//Top left corner of the View
	int windowX = tempView.getCenter( ).x - ( tempView.getSize( ).x / 2 );
	int windowY = tempView.getCenter( ).y - ( tempView.getSize( ).y / 2 );

	if( windowX < 0 )
	{
		windowX = 0;
	}
	if( windowY < 0 )
	{
		windowY = 0;
	}
	//find the first square that is needed to be drawn
	windowX /= TILESIZE;
	windowY /= TILESIZE;

	int windowXEnd = ( tempView.getSize( ).x / TILESIZE ) + ( windowX + 1 );
	int windowYEnd = ( tempView.getSize( ).y / TILESIZE ) + windowY;

	//std::cout << "\nWindowX: " << windowX << "  WindowY: " << windowY;
	//std::cout << "\nWindowXEnd: " << windowXEnd << "  WindowYEnd: " << windowYEnd << std::endl;
	for( unsigned int j = windowY; j <= windowYEnd; j++ )
	{
		for( unsigned int i = windowX; i <= windowXEnd; i++ )
		{
			if( ( j * m_iHorizontalBitmapSize ) + ( i ) < m_sprites.size() )
			{
				StateHandler::getInstance().m_pWindow->draw( m_sprites[ ( j * m_iHorizontalBitmapSize ) + ( i ) ] );
			}
		}
	}
}

void EnvironmentHandler::bitmapToArray()
{
	sf::Color pixelColor;			
	RGB* rgb;
	for( int j = 0; j < m_iVerticalBitmapSize; j++ )
	{
		for( int i = 0; i < m_iHorizontalBitmapSize; i++ )
		{
		//	std::cout << "i: " << i << " j: " << j << std::endl;
			pixelColor = m_bitmap.getPixel( i,j );
			rgb = new RGB;
			rgb->red = pixelColor.r;
			rgb->green = pixelColor.g;
			rgb->blue = pixelColor.b;
			m_floorArray.push_back(rgb);
		}
	}

	delete rgb;
}

/// Creates the level out of the floorArray
void EnvironmentHandler::createLevel( ) 
{
	sf::Sprite sprite;
	sf::IntRect subRect;
	RGB* rgb = new RGB;
	int spriteX = 0;
	int spriteY = 0;

	for(unsigned int i = 0; i < m_floorArray.size( ); i++ )
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

		sprite.setPosition( float(spriteX * TILESIZE) , float(( spriteY - 1 ) * TILESIZE) );
		m_sprites.push_back( sprite );
	}

	delete rgb;
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

	for(unsigned int i = 0; i < m_sprites.size(); i++ )
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
				subRect.top = ( TILESIZE * 9 );
				m_sprites[i].setTextureRect( subRect );
			}
			else if( right && !below && above && !left )
			{
				subRect.top = ( TILESIZE * 7 );
				m_sprites[i].setTextureRect( subRect );
			}
			else if( !right && !below && above && left )
			{
				subRect.top = ( TILESIZE * 10 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( !right && below && !above && left )
			{
				subRect.top = ( TILESIZE * 8 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( !right && below && above && !left )
			{
				//if( i % m_iHorizontalBitmapSize == 0 )
				{
					subRect.top = ( TILESIZE * 8 );
					m_sprites[i].setTextureRect( subRect );
				}
				//else if( i % m_iHorizontalBitmapSize == ( m_iHorizontalBitmapSize - 1 ) )
				//{
				//	subRect.top = ( TILESIZE * 10 );
				//	m_sprites[i].setTextureRect( subRect );
				//}
			}
			//else if( right && !below && !above && left )
			//{
			//	if( i >= m_iHorizontalBitmapSize )
			//	{
			//		subRect.top = ( TILESIZE * 8 );
			//		m_sprites[i].setTextureRect( subRect );
			//	}
			//}
			else if( right && above && below && !left )
			{
				subRect.top = ( TILESIZE * 11 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( !right && above && below && left )
			{
				subRect.top = ( TILESIZE * 8 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( right && !above && below && left )
			{
				subRect.top = ( TILESIZE * 11 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( right && above && !below && left )
			{
				subRect.top = ( TILESIZE * 7 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( right && above && below && left )
			{
				subRect.top = ( TILESIZE * 11 );
				m_sprites[i].setTextureRect(subRect);
			}
			else if( ( !right && above && !below && !left ) || ( !right && !above && below && !left ) )
			{
				subRect.top = ( TILESIZE * 8 );
				m_sprites[i].setTextureRect(subRect);
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
				m_playerPosition.x = float(i * TILESIZE);
				m_playerPosition.y = float(j * TILESIZE);
				m_objects.push_back( true );
				//std::cout << '\n' << "vectorpos:  " << ( j * m_iHorizontalBitmapSize ) + i;
			}
		}
	}
}

bool EnvironmentHandler::checkCollision( Vector2f playerPosition )
{
	int x = ( ( playerPosition.x + 35 ) / TILESIZE );
	int y = ( ( playerPosition.y + 48 ) / TILESIZE );

	//for(int i = 64*63; i <= 64*64; i++)
	//{
	//	std::cout << "\nObject Bool: " << (bool)m_objects[((y * m_iHorizontalBitmapSize) + x )];
	//}
	
	//check top left corner
	if(!m_objects[( ( y * m_iHorizontalBitmapSize) + x )] )
	{
		return false;
	}
	
	x = ( ( playerPosition.x - 35 ) / TILESIZE );

	//check top right corner
	if(!m_objects[( ( y * m_iHorizontalBitmapSize) + ( x + 1 ) )] )
	{
		return false;
	}		

	y = ( ( playerPosition.y - 15 ) / TILESIZE );

	//check bottom right corner
	if(!m_objects[( ( ( y + 1 ) * m_iHorizontalBitmapSize) + ( x + 1 ) )] )
	{
		return false;
	}

	x = ( ( playerPosition.x + 35 ) / TILESIZE );

	//check bottom left corner	
	if(!m_objects[( ( ( y + 1 ) * m_iHorizontalBitmapSize) + x )] )
	{
		return false;
	}
	
	return true;
}

Vector2f EnvironmentHandler::getPlayerPosition( )
{
	return m_playerPosition;
}

std::vector<bool>* EnvironmentHandler::getObjectVector()
{
	return &m_objects;
}

int EnvironmentHandler::getHorizontalBitmapSize()
{
	return m_iHorizontalBitmapSize;
}