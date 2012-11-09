#include "Character.h"
#include <time.h>
//////////////////////////// CONSTRUCTORS ////////////////////////

const short BASE_STAT = 5;

Character::Character() : Actor()
{
	m_shDamage = 10;
	m_shSpeed = BASE_STAT;
	m_shToughness = BASE_STAT;
	m_shIntelligence = BASE_STAT;
	m_shStrength = BASE_STAT;
	m_bDoingAction = false;
	m_shBitmapRow = 0;
	m_shBitmapCol = 0;
	m_shFrameCount = 0;
	
	m_shLevel = 1;
	m_shHealth = 50;

	m_bAbilities = new bool[false, false, false];
}

void Character::attack(short row) ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	setBitmapRow(row);
	
	if(!m_bDoingAction){
		
		//This has to work totally different, if not, when the plaer holds the mouse button it is not working properly!
		m_Sprite.setTexture(m_TexturesActions["attack"].imgTexture);
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
		projectile->loadContent( );
		m_vProjectiles.push_back( projectile );
	}
	return 0;
}

void Character::startAction(){
	m_bDoingAction = true;
}
void Character::endAction(){
	m_bDoingAction = false;
	m_Sprite.setTexture(m_TexturesActions["still"].imgTexture);
}
void Character::changeAnimationToWalk(){
	
	m_Sprite.setTexture(m_TexturesActions["move"].imgTexture);
}
void Character::changeAnimationToStand(){
	m_shBitmapCol = 0;
	m_Sprite.setTexture(m_TexturesActions["still"].imgTexture);
}
		
bool Character::isDoingAction(){
	return m_bDoingAction;
}

short Character::getHealth()
{
	return m_shHealth;
}

short Character::getDamage()
{
	return m_shDamage;
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

short Character::getLevel()
{
	return m_shLevel;
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

	sf::Texture temptex;
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
}

void Character::setEnvironmentLevel(EnvironmentHandler* environmentLevel)
{
	m_environmentLevel = environmentLevel;
}

void Character::move(short direction) // 0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	changeAnimationToWalk();
	// WE NEED TO CHECK IF THE PLAYER IS HITTING AN OBSTRUCTION HERE... (obstructions not yet implemented as of this writing)
	Vector2f newPosition;
	newPosition.x = m_Sprite.getPosition().x;
	newPosition.y = m_Sprite.getPosition().y;
	switch (direction)
	{	
		case NORTH:
			newPosition.y -= 3;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( NORTH );
				m_Sprite.move(0,-3);
			}
		break;
		case NORTH_EAST:
			newPosition.x += 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( NORTH_EAST );
				m_Sprite.move(2.1, 0);
			}
			newPosition.x -= 2.1; //back to original x position
			newPosition.y -= 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( NORTH_EAST );
				m_Sprite.move(0,-2.1);
			}
		break;
		case EAST:
			newPosition.x += 3;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( EAST );
				m_Sprite.move(3,0);
			}
		break;
		case SOUTH_EAST:
			newPosition.x += 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( SOUTH_EAST );
				m_Sprite.move(2.1,0);
			}
			newPosition.x -= 2.1; //back to original x position
			newPosition.y += 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( SOUTH_EAST );
				m_Sprite.move(0,2.1);
			}
		break;
		case SOUTH:
			newPosition.y += 3;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( SOUTH );
				m_Sprite.move(0,3);
			}
		break;
		case SOUTH_WEST:
			newPosition.x -= 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( SOUTH_WEST );
				m_Sprite.move(-2.1,0);
			}
			newPosition.x += 2.1; //back to original x position
			newPosition.y += 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( SOUTH_WEST );
				m_Sprite.move(0,2.1);
			}
		break;
		case WEST:
			newPosition.x -= 3;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( WEST );
				m_Sprite.move(-3,0);
			}
			break;
		case NORTH_WEST:
			newPosition.x -= 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( NORTH_WEST );
				m_Sprite.move(-2.1,0);
			}
			newPosition.x += 2.1; //back to original x position
			newPosition.y -= 2.1;
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				setBitmapRow( NORTH_WEST );
				m_Sprite.move(0,-2.1);
			}
		break;
	}
}

//////////////////////
void Character::showDamage() 
{

}

void Character::showHealth()
{

}
