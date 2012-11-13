#include "Projectile.h"
#include "StateHandler.h"

Projectile::Projectile( )
{
	m_shSpell = NULL;
	m_shDamage = 0;
	m_vPosition.x = 0;
	m_vPosition.y = 0;
	m_shTraveled = 0;
	m_bExist = false;
	m_shSpriteSize = 48;
	m_shBitmapRow = 0;
	m_shBitmapCol = 0;
	m_shFrameCount = 0;

	m_fAngle = 0;
}

void Projectile::initiate( short spell, short damage, Vector2f position, Vector2f mouseCoordinates )
{
	m_shSpell = spell;
	m_shDamage = damage;
	m_vPosition = position;
	m_bExist = true;
	m_shTraveled = 0;

	if( m_shSpell == FIREBALL )
	{
		m_Sprite.setTexture( m_vTextures[FIREBALL] );
	}

	float deltaY = mouseCoordinates.y - m_vPosition.y;
	float deltaX = mouseCoordinates.x - m_vPosition.x;

	m_fAngle = atan2( deltaY, deltaX ) * 180 / 3.1415;
}

bool Projectile::loadContent( )
{
	sf::Image maskingImage;

	if (!maskingImage.loadFromFile("../../Resources/Fireball.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (255, 255, 255), 0);
	m_Texture.loadFromImage( maskingImage );

	m_vTextures.push_back( m_Texture );

	return EXIT_SUCCESS;
}

void Projectile::move( )
{
	float newX = m_vPosition.x + 10 * sin( m_fAngle );
	float newY = m_vPosition.y + 10 * cos( m_fAngle );

	m_Sprite.setPosition( newX, newY );

	m_vPosition.x = newX;
	m_vPosition.y = newY;
}

void Projectile::draw( )
{
	StateHandler::getInstance().m_pWindow->draw( m_Sprite );
}

bool Projectile::exist( )
{
	return m_bExist;
}

void Projectile::animation( )
{
	const int ANIMATION_SPEED = 4;

	m_shFrameCount += 1;

	m_Sprite.getTexture();
		
	if(m_shFrameCount % ANIMATION_SPEED == 0)
	{
		m_shBitmapCol += 1;
			
		if ( ( m_shBitmapCol * m_shSpriteSize ) >= m_Sprite.getTexture()->getSize().x - ( m_shSpriteSize ) )
		{
			m_shBitmapCol = 0;
		}
	}
	setFrame();

	checkCollision();
}

void Projectile::setFrame()	///set subRect 
{
	sf::IntRect subRect;
	subRect.left = m_shBitmapCol * m_shSpriteSize;
	subRect.top = m_shBitmapRow * m_shSpriteSize;
	subRect.width = m_shSpriteSize;
	subRect.height = m_shSpriteSize;
	m_Sprite.setTextureRect( subRect );
}

void Projectile::setInvisible()
{
	m_bExist = false;
}

void Projectile::setEnvironmentObjects(std::vector<bool>* objects)
{
	m_objects = objects;
}

void Projectile::checkCollision( )
{
	//const short TILESIZE = 96;
	//int x = ( ( m_Position.x ) / TILESIZE );
	//int y = ( ( m_Position.y ) / TILESIZE );

	////check top left corner
	//if(!m_objects -> at( ( ( y * m_shHorizontalBitmapSize) + x ) ) )
	//{
	//	setInvisible();
	//}

	//x = ( ( m_Position.x - 48 ) / TILESIZE );

	////check top right corner
	//if(!m_objects -> at( ( ( y * m_shHorizontalBitmapSize) + ( x + 1 ) ) ) )
	//{
	//	setInvisible();
	//}		

	//y = ( ( m_Position.y - 48 ) / TILESIZE );

	////check bottom right corner
	//if(!m_objects -> at( ( ( ( y + 1 ) * m_shHorizontalBitmapSize) + ( x + 1 ) ) ) )
	//{
	//	setInvisible();
	//}

	//x = ( ( m_Position.x ) / TILESIZE );

	////check bottom left corner	
	//if(!m_objects -> at( ( ( ( y + 1 ) * m_shHorizontalBitmapSize) + x ) ) )
	//{
	//	setInvisible();
	//}
}