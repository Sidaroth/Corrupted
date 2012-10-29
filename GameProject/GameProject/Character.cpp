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
		if (!m_Texture.loadFromFile("player_attack.png"))
		{
		}else{
		m_Sprite.setTexture(m_Texture);
		}
		m_shBitmapCol = 0;
		m_bDoingAction=true;

	}
	
}

void Character::startAction(){
	m_bDoingAction = true;
}
void Character::endAction(){
	m_bDoingAction = false;
	changeAnimationToWalk();
}
//This function is just provisional (only for testing)
void Character::changeAnimationToWalk(){
	if (!m_Texture.loadFromFile("player.png"))
	{
	}else{
	m_Sprite.setTexture(m_Texture);
	}
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
	const int ANIMATION_SPEED = 5;  ///Amount of frame per seconds

	m_shFrameCount += 1;

	if(m_shFrameCount % ANIMATION_SPEED == 0)
	{
		m_shBitmapCol += 1;
		if ( ( m_shBitmapCol * m_shSpriteSize ) >= m_Texture.getSize( ).x - ( m_shSpriteSize ) )
		{
			m_shBitmapCol = 0;
			endAction();
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
	// WE NEED TO CHECK IF THE PLAYER IS HITTING AN OBSTRUCTION HERE... (obstructions not yet implemented as of this writing)
	Vector2f currentPos;
	currentPos.x = m_Sprite.getPosition().x;
	currentPos.y = m_Sprite.getPosition().y;
	switch (direction)
	{	
		case NORTH:
			currentPos.y -= 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( NORTH );
				m_Sprite.move(0,-3);
			}
		break;
		case NORTH_EAST:
			currentPos.x += 3;
			currentPos.y -= 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( NORTH_EAST );
				m_Sprite.move(3,-3);
			}
		break;
		case EAST:
			currentPos.x += 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( EAST );
				m_Sprite.move(3,0);
			}
		break;
		case SOUTH_EAST:
			currentPos.x += 3;
			currentPos.y += 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( SOUTH_EAST );
				m_Sprite.move(3,3);
			}
		break;
		case SOUTH:
			currentPos.y += 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( SOUTH );
				m_Sprite.move(0,3);
			}
		break;
		case SOUTH_WEST:
			currentPos.x -= 3;
			currentPos.y += 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( SOUTH_WEST );
				m_Sprite.move(-3,3);
			}
		break;
		case WEST:
			currentPos.x -= 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( WEST );
				m_Sprite.move(-3,0);
			}
			break;
		case NORTH_WEST:
			currentPos.x -= 3;
			currentPos.y -= 3;
			if( m_environmentLevel -> checkCollision( currentPos ) )
			{
				setBitmapRow( NORTH_WEST );
				m_Sprite.move(-3,-3);
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
