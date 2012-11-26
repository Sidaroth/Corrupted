#include "Character.h"
#include <time.h>
//////////////////////////// CONSTRUCTORS ////////////////////////

const short BASE_STAT = 5;

Character::Character() : Actor()
{
	m_shSpeed = BASE_STAT;
	m_shToughness = BASE_STAT;
	m_shIntelligence = BASE_STAT;
	m_shStrength = BASE_STAT;
	m_bDoingAction = false;
	m_shBitmapRow = 0;
	m_shBitmapCol = 0;
	m_shFrameCount = 0;
	m_shMaxHealth = 50;
	
	m_shCurrentHealth = m_shMaxHealth;

	m_bAbilities = new bool[false, false, false];
}

Character::~Character()
{
	for( std::vector<Projectile*>::iterator it = m_vProjectiles.begin(); it != m_vProjectiles.end(); )
	{
		delete * it;
		it = m_vProjectiles.erase(it);	// Erase calls the deconstructor, but because the pointers don't have deconstructors we need to call delete first.
										// Erase returns a new iterator position, without it it would create holes 
	}
}

void Character::attack(short row) ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	setBitmapRow(row);
	
	if(!m_bDoingAction){
		
		//This has to work totally different, if not, when the plaer holds the mouse button it is not working properly!
		m_Sprite.setTexture(*m_TextureTypes[ATTACK]);
		m_shBitmapCol = 0;
		m_bDoingAction=true;
	}
}

bool Character::loadContent()
{
	//create 5 temp projectiles on load for each enemy/player
	Projectile* projectile;
	for( int i = 0; i < 5; i++ )
	{
		projectile = new Projectile( );
		projectile -> loadContent( );
		projectile -> setEnvironmentObjects( m_environmentLevel -> getObjectVector( ), m_environmentLevel -> getHorizontalBitmapSize( ) );
		m_vProjectiles.push_back( projectile );
	}

	return 0;
}

void Character::startAction(){
	m_bDoingAction = true;
}
void Character::endAction(){
	m_bDoingAction = false;
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
}
void Character::changeAnimationToWalk(){
	
	m_Sprite.setTexture(*m_TextureTypes[MOVE]);
}
void Character::changeAnimationToStand(){
	m_shBitmapCol = 0;
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
}
		
bool Character::isDoingAction(){
	return m_bDoingAction;
}

short Character::getMaxHealth()
{
	return m_shMaxHealth;
}

short Character::getCurrentHealth()
{
	return m_shCurrentHealth;
}

short Character::getMeleeDamage()
{
	return m_shMeleeDamage;
}

short Character::getSpellDamage()
{
	return m_shSpellDamage;
}

short Character::getSpeed()
{
	return m_shSpeed;
}

short Character::getToughness()
{
	return m_shToughness;
}

short Character::getIntelligence()
{
	return m_shIntelligence;
}

short Character::getStrength()
{
	return m_shStrength;
}


float Character::getCriticalChance()
{
	return m_fCriticalChance;
}

bool* Character::getAbilities()
{
	return m_bAbilities;
}

void Character::setFrame()	///set subRect 
{
	sf::IntRect subRect;
	subRect.left = m_shBitmapCol * m_shSpriteSize;
	subRect.top = m_shBitmapRow * m_shSpriteSize;
	subRect.width = m_shSpriteSize;
	subRect.height = m_shSpriteSize;
	m_Sprite.setTextureRect(subRect);
}

void Character::setBitmapRow(short row)		///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	m_shBitmapRow = row;
}

void Character::animation()  ///calculate frame for animation
{
	const int ANIMATION_SPEED = 4;  ///Amount of frame per seconds

	m_shFrameCount += 1;

	m_Sprite.getTexture();
	if(m_shFrameCount % ANIMATION_SPEED == 0)
	{
		
		m_shBitmapCol += 1;
		if ( ( m_shBitmapCol * m_shSpriteSize ) >= m_Sprite.getTexture()->getSize().x - ( m_shSpriteSize ) )
		{
			endAction();
			m_shBitmapCol = 0;
		}
	}
	setFrame();

	for( unsigned int i = 0; i < m_vProjectiles.size( ); i++ )
	{
		if( m_vProjectiles[i]->exist( ) )
		{
			m_vProjectiles[i]->animation( );
		}
	}
}

void Character::draw( )
{
	for( unsigned int i = 0; i < m_vProjectiles.size( ); i++ )
	{
		if( m_vProjectiles[i]->exist( ) )
		{
			m_vProjectiles[i]->draw( );
		}
	}
}

void Character::update( )
{
	for( unsigned int i = 0; i < m_vProjectiles.size( ); i++ )
	{
		if( m_vProjectiles[i]->exist( ) )
		{
			m_vProjectiles[i]->move( );
		}
	}
}

void Character::setEnvironmentLevel(EnvironmentHandler* environmentLevel)
{
	m_environmentLevel = environmentLevel;
}

void Character::move(short direction) // 0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	changeAnimationToWalk();
	Vector2f newPosition;
	newPosition.x = m_Sprite.getPosition().x;
	newPosition.y = m_Sprite.getPosition().y;
	switch (direction)
	{	
		case NORTH:
			newPosition.y -= 3;
			setBitmapRow( NORTH );
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0,-3);
			}
		break;

		case NORTH_EAST:
			newPosition.x += 2.1f;
			setBitmapRow( NORTH_EAST );
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(2.1f, 0);
			}
			newPosition.x -= 2.1f; //back to original x position
			newPosition.y -= 2.1f;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0,-2.1f);
			}
		break;

		case EAST:
			newPosition.x += 3;
			setBitmapRow( EAST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(3,0);
			}
		break;

		case SOUTH_EAST:
			newPosition.x += 2.1f;
			setBitmapRow( SOUTH_EAST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(2.1f,0);
			}
			newPosition.x -= 2.1f; //back to original x position
			newPosition.y += 2.1f;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0,2.1f);
			}
		break;

		case SOUTH:
			newPosition.y += 3;
			setBitmapRow( SOUTH );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0, 3);
			}
		break;

		case SOUTH_WEST:
			newPosition.x -= 2.1f;
			setBitmapRow( SOUTH_WEST );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(-2.1f, 0);
			}
			newPosition.x += 2.1f; //back to original x position
			newPosition.y += 2.1f;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0, 2.1f);
			}
		break;

		case WEST:
			newPosition.x -= 3.0f;
			setBitmapRow( WEST );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(-3, 0);
			}
			break;

		case NORTH_WEST:
			newPosition.x -= 2.1f;
			setBitmapRow( NORTH_WEST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(-2.1f, 0);
			}
			newPosition.x += 2.1f; //back to original x position
			newPosition.y -= 2.1f;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				m_Sprite.move(0, -2.1f);
			}
		break;
	}
}


void Character::showHealth()
{

}

void Character::castSpell( Vector2f mouseCoordinates, short spell )
{
	if( m_bAbilities[spell] )
	{
		for( unsigned int i = 0; i < m_vProjectiles.size( ); i++ )
		{
			if( !m_vProjectiles[i]->exist( ) )
			{
				m_vProjectiles[i]->initiate( spell, m_shSpellDamage, m_Position, mouseCoordinates );
				i = m_vProjectiles.size( ) + 1;
			}
			else if ( i == m_vProjectiles.size( ) - 1 )
			{
				Projectile* projectile = new Projectile;
				projectile -> loadContent( );
				projectile -> setEnvironmentObjects( m_environmentLevel -> getObjectVector( ), m_environmentLevel -> getHorizontalBitmapSize( ) );
				m_vProjectiles.push_back( projectile );
			}
		}
	}
}

void Character::takeDamage( short damage )
{

	m_shCurrentHealth -= damage;
}