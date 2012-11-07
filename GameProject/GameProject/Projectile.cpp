#include "Projectile.h"
#include "StateHandler.h"

	Projectile::Projectile( )
	{

	}

	Projectile::Projectile( short spell, short damage,Vector2f position, Vector2f mouseCoordinates )
	{
		m_shSpell = spell;
		m_shDamage = damage;
		m_vPosition = position;

		float deltaY = mouseCoordinates.y - m_vPosition.y;
		float deltaX = mouseCoordinates.x - m_vPosition.x;

		m_fAngle = atan2( deltaY, deltaX ) * 180 / 3.1415;
	}

	bool Projectile::loadContent( )
	{
		if(!m_Texture.loadFromFile( "../../Resources/Fireball.png" ) )
		{
			return EXIT_FAILURE;
		}
		m_vTextures.push_back( m_Texture );
		

		if( m_shSpell == FIREBALL )
		{
			m_Sprite.setTexture( m_vTextures[FIREBALL] );
		}

		return EXIT_SUCCESS;
	}

	void Projectile::move( )
	{
		float newX = m_vPosition.x + 10 * cos( m_fAngle );
		float newY = m_vPosition.y + 10 * sin( m_fAngle );

		m_Sprite.setPosition( newX, newY );

		m_vPosition.x = newX;
		m_vPosition.y = newY;
	}

	void Projectile::draw( )
	{
		StateHandler::getInstance().m_pWindow->draw( m_Sprite );
	}