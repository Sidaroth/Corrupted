#include "Character.h"
#include <time.h>
//////////////////////////// CONSTRUCTORS ////////////////////////



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
	
	m_fHealCoolDown = m_iCoolDown.getElapsedTime().asSeconds();
	m_fFireballCoolDown = m_iCoolDown.getElapsedTime().asSeconds();
	m_shCurrentHealth = m_shMaxHealth;

	m_bDead = false;
	stopAnimation = false;

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

bool Character::attack(short row) ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
{
	if(!m_bDoingAction)
	{
		setBitmapRow(row);
		m_Sprite.setTexture(*m_TextureTypes[ATTACK]);
		m_shBitmapCol = 0;
		m_bDoingAction = true;
		return true;
	}

	return false;
}

bool Character::loadContent()
{
	srand(time(NULL));
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

void Character::startAction()
{
	m_bDoingAction = true;
}

void Character::endAction()
{
	m_bDoingAction = false;
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
}

void Character::changeAnimationToWalk()
{
	m_Sprite.setTexture(*m_TextureTypes[MOVE]);
}

void Character::changeAnimationToStand()
{
	m_shBitmapCol = 0;
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
}
		
bool Character::isDoingAction()
{
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

	short speed = BASE_STAT - ( ( ( m_shSpeed - BASE_STAT) * ( BASE_STAT - 1 ) ) / (20 - BASE_STAT));
	if(m_shFrameCount % speed == 0)
	{
		
		m_shBitmapCol += 1;
		if ( ( m_shBitmapCol * m_shSpriteSize ) >= m_Sprite.getTexture()->getSize().x - ( m_shSpriteSize ) )
		{
			endAction();

			if(!m_bDead)
			{
				m_shBitmapCol = 0;
			}
			else
			{
				stopAnimation = true;
			}
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
	m_shMaxHealth     = m_shToughness    * m_shToughness * 2;
	m_shMeleeDamage   = m_shStrength     * m_shStrength;
	m_shSpellDamage   = m_shIntelligence * m_shIntelligence;
	m_fCriticalChance = m_shStrength / 2 + m_shSpeed / 2 + m_shIntelligence / 2;

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

	float diagonalSpeed = (float)(m_shSpeed * (2.f / 3.f ));
	float orthogonalSpeed = (float)(m_shSpeed * (3.f / 4.f ));

	switch (direction)
	{	
		case NORTH:
			newPosition.y -= orthogonalSpeed;
			setBitmapRow( NORTH );
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, -orthogonalSpeed);
				//m_Sprite.move(0,-orthogonalSpeed);
			}
		break;

		case NORTH_EAST:
			newPosition.x += diagonalSpeed;
			setBitmapRow( NORTH_EAST );
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(diagonalSpeed, 0);
			}

			newPosition -= diagonalSpeed;  // x back to original, change y. 
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, -diagonalSpeed);
			}
		break;

		case EAST:
			newPosition.x += orthogonalSpeed;
			setBitmapRow( EAST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(orthogonalSpeed, 0);
			}
		break;

		case SOUTH_EAST:
			newPosition.x += diagonalSpeed;
			setBitmapRow( SOUTH_EAST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(diagonalSpeed, 0);
			}

			newPosition.x -= diagonalSpeed; //back to original x position
			newPosition.y += diagonalSpeed; 
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, diagonalSpeed);
			}
		break;

		case SOUTH:
			newPosition.y += orthogonalSpeed;
			setBitmapRow( SOUTH );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, orthogonalSpeed);
			}
		break;

		case SOUTH_WEST:
			newPosition.x -= diagonalSpeed;
			setBitmapRow( SOUTH_WEST );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(-diagonalSpeed, 0);
			}

			newPosition += diagonalSpeed;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, diagonalSpeed);
			}
		break;

		case WEST:
			newPosition.x -= orthogonalSpeed;
			setBitmapRow( WEST );
		
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(-orthogonalSpeed, 0);
			}
			break;

		case NORTH_WEST:
			newPosition.x -= diagonalSpeed;
			setBitmapRow( NORTH_WEST );

			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(-diagonalSpeed, 0);
			}

			newPosition.x += diagonalSpeed; //back to original x position
			newPosition.y -= diagonalSpeed;
			
			if( m_environmentLevel -> checkCollision( newPosition ) )
			{
				movePosition(0, -diagonalSpeed);
			}
		break;
	}
}

void Character::setUserInterface(Ui* ui)
{
	userInterface = ui;
}


void Character::showHealth()
{

}

void Character::castSpell( Vector2f mouseCoordinates, short spell )
{
	if( m_bAbilities[spell] )
	{
		if(m_iCoolDown.getElapsedTime().asSeconds() >= m_fFireballCoolDown) //Need || on other spells if we get that far
		{
			if(spell == FIREBALL)
			{
				m_fFireballCoolDown = m_iCoolDown.getElapsedTime().asSeconds() + 1.f;
				StateHandler::getInstance().m_AudioManager.playSound("cast_fireball");
			}
			for( unsigned int i = 0; i < m_vProjectiles.size( ); i++ )
			{
				if( !m_vProjectiles[i]->exist( ) )
				{
					short spellDamage;
					if(rand() % 100 < m_fCriticalChance)
					{
						spellDamage = m_shSpellDamage * 2;
					}
					else
					{
						spellDamage = m_shSpellDamage;
					}

					m_vProjectiles[i]->initiate( spell, spellDamage, m_Position, mouseCoordinates );
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
}

/// Can both heal and damage players and enemies, if it kills the target, it returns true.
bool Character::takeDamage( short damage )
{
	m_shCurrentHealth -= (damage);

	// Calculate the position on the UI, not the world coords.
	sf::View tempView = StateHandler::getInstance().m_pWindow -> getView();

	int windowX = tempView.getCenter( ).x - ( tempView.getSize( ).x / 2 );
	int windowY = tempView.getCenter( ).y - ( tempView.getSize( ).y / 2 );

	Vector2f uiPosition(m_Position.x, m_Position.y);
	uiPosition.x -= windowX;
	uiPosition.y -= windowY;
	uiPosition.x /= 1.5;
	uiPosition.y /= 1.5;

	std::string message;
	sf::Color color;

	if(damage > 0)
	{
		message += "- ";
		color = sf::Color::Red;
	}
	else
	{
		message += "+ ";
		damage *= -1;
		color = sf::Color::Green;
	}

	message += std::to_string ((long long) damage) + " Health";

	userInterface -> addFloatingText(message, uiPosition, color);

	if( m_shCurrentHealth <= 0)
	{
		m_shCurrentHealth = 0;
		return true;
	}
	else if (m_shCurrentHealth > m_shMaxHealth)
	{
		m_shCurrentHealth = m_shMaxHealth;
	}

	return false;
}

void Character::heal()
{
	if(m_iCoolDown.getElapsedTime().asSeconds() >= m_fHealCoolDown)
	{
		m_fHealCoolDown = m_iCoolDown.getElapsedTime().asSeconds() + 5.f;
		StateHandler::getInstance().m_AudioManager.playSound("heal");
		takeDamage(-m_shSpellDamage);
	}
}