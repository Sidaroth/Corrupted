#include "Player.h"
#include "StateHandler.h"


Player::~Player()
{
	delete m_EnemyVector;
	for(std::vector<sf::Texture*>::iterator it = m_TextureTypes.begin(); it != m_TextureTypes.end();)
	{
		delete * it;
		it = m_TextureTypes.erase(it);
	}
}

Player::Player() : Character()
{
	m_shTotalSouls = 0;
	m_shCurrentSouls = 0;
	m_shWeaponLevel = 1;
	m_shArmorLevel = 1;

	for (int i = 0; i <= 5; i++)
	{
		m_saStatArray[i] = 0;
	}
}

void Player::setUserInterface(Ui* ui)
{
	userInterface = ui;
}

bool Player::loadContent()
{
	srand(time(NULL));
	//load projectiles in character
	Character::loadContent();

	sf::Image maskingImage;

	//Loading move action
	if (!maskingImage.loadFromFile("../../Resources/player.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(bgColor, 0);
	m_MoveTexture.loadFromImage( maskingImage );

	m_TextureTypes.push_back( &m_MoveTexture );

	//Loading attack action
	if (!maskingImage.loadFromFile("../../Resources/player_attack.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(bgColor, 0);
	m_AttackTexture.loadFromImage( maskingImage );

	m_TextureTypes.push_back( &m_AttackTexture );

	//Loading standing action
	if (!maskingImage.loadFromFile("../../Resources/player_still.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(bgColor, 0);
	m_StillTexture.loadFromImage( maskingImage );

	m_TextureTypes.push_back( &m_StillTexture );

	if(!maskingImage.loadFromFile("../../Resources/player_die.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(bgColor, 0);
	m_DeathTexture.loadFromImage( maskingImage );

	m_TextureTypes.push_back( &m_DeathTexture );


	m_Sprite.setTexture(*m_TextureTypes[STILL]);
	animation();

	userInterface -> initialize(&m_shStrength, &m_shIntelligence, &m_shToughness, &m_shSpeed,
							    &m_shCurrentSouls, &m_shWeaponLevel, &m_shArmorLevel, &m_shCurrentHealth,
								&m_shMaxHealth, &m_shMeleeDamage, &m_shSpellDamage, &m_fCriticalChance);
	return EXIT_SUCCESS;
}

void Player::update() 
{
	Character::update();

	collisionCheck( );
}

void Player::draw()
{
	Character::draw();
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}


void Player::modifySouls(short amount) 
{
	m_shCurrentSouls += amount;

	// Build up the message to be shown. 
	sf::Color color(sf::Color::Blue);
	std::string message = "+ ";
	message += std::to_string((long long) amount);
	message += " Souls";

	// Calculate the position on the UI, not the world coords.
	sf::View tempView = StateHandler::getInstance().m_pWindow -> getView();

	int windowX = tempView.getCenter().x - ( tempView.getSize().x / 2 );
	int windowY = tempView.getCenter().y - ( tempView.getSize().y / 2 );

	Vector2f uiPosition(m_Position.x - windowX, m_Position.y - windowY);
	uiPosition.x /= 1.5;
	uiPosition.y /= 1.5;

	userInterface -> addFloatingText(message, uiPosition, color);

	if (amount > 0)
	{
		m_shTotalSouls += amount;
	}
}

void Player::setEnemyVector(std::vector<Enemy*>* enemyVector)
{
	m_EnemyVector = enemyVector;
}

/// Checks to see if you've hit something when trying to do a melee attack. 
// I changed this to use iterators instead of just standard for loop.  - Chris.
bool Player::checkAttackCollision(short direction)
{
	Vector2f* enemyPosition;
	Vector2f* projectilePosition;

	int player_x = getSpritePosition()->x;
	int player_y = getSpritePosition()->y;

	int attackPoint_x = 0;
	int attackPoint_y = 0;
	int range = 30;

	bool doDamage;

	for(std::vector<Enemy*>::iterator it = m_EnemyVector -> begin(); it != m_EnemyVector -> end(); ++it)
	{
		doDamage = false;
		enemyPosition = (*it) -> getSpritePosition();
		
		if((enemyPosition -> x < player_x + 300) 
			&& (enemyPosition -> x > player_x - 300) 
			&& (enemyPosition -> y < player_y + 300) 
			&& (enemyPosition -> y > player_y - 300))
		{
			sf::FloatRect enemy_bounds = (*it) -> getSprite().getGlobalBounds();
			int enemy_width = enemy_bounds.width;
			int enemy_height = enemy_bounds.height;
			int enemy_x = enemyPosition -> x;
			int enemy_y = enemyPosition -> y;
		
			switch (direction)
			{	
				case NORTH:
					attackPoint_x = player_x;
					attackPoint_y = player_y-range;
				break;

				case NORTH_EAST:
					attackPoint_x = player_x+range;
					attackPoint_y = player_y-range;
				break;

				case EAST:
					attackPoint_x = player_x+range;
					attackPoint_y = player_y;
				break;

				case SOUTH_EAST:
					attackPoint_x = player_x+range;
					attackPoint_y = player_y+range;
				break;

				case SOUTH:
					attackPoint_x = player_x;
					attackPoint_y = player_y+range;
				break;

				case SOUTH_WEST:
					attackPoint_x = player_x-range;
					attackPoint_y = player_y+range;
				break;

				case WEST:
					attackPoint_x = player_x-range;
					attackPoint_y = player_y;
					break;

				case NORTH_WEST:
					attackPoint_x = player_x-range;
					attackPoint_y = player_y-range;
				break;
			}
			
			if ((attackPoint_x > (enemy_x - enemy_width / 2)) && (attackPoint_x < (enemy_x + (enemy_width / 2))))
			{
				if ((attackPoint_y > (enemy_y - enemy_height / 2)) && (attackPoint_y < (enemy_y + (enemy_height / 2))))
				{
					doDamage = true;
				}
			}

			if ((player_x > (enemy_x - enemy_width / 2)) && (player_x < ((enemy_x + enemy_width / 2))))
			{
				if ((player_y > (enemy_y - (enemy_height / 2))) && (player_y < (enemy_y + (enemy_height / 2))))
				{
					doDamage = true;
				}
			}

			if (doDamage)
			{
				short damage;
				if(rand() % 100 < m_fCriticalChance)
				{
					damage = m_shMeleeDamage * 2;
				}
				else
				{
					damage = m_shMeleeDamage;
				}
				if((*it) -> takeDamage( damage ))
				{
					modifySouls((*it) -> kill());		// kill and erase.
					//it = m_EnemyVector -> erase(it);	// If we want to bodies to stay on the ground.. do not erase.
				}
				
				return true;
			}
		}
	}

	return false;
}

bool Player::pointInsideRect(int pX,int pY,sf::FloatRect rectangle)
{
		int rect_width = rectangle.width;
		int rect_height = rectangle.height;
		int rect_x = rectangle.left;
		int rect_y = rectangle.top;
		
		if ((pX > rect_x) && (pX < rect_x + rect_width))
		{
			if((pY > rect_y) && (pY < rect_y + rect_height))
			{
				return true;
			}
		}

	return false;
}

void Player::collisionCheck( )
{
	/////////Player Projectiles vs Enemy/////////////

	const short PROJECTILE_SIZE = 48;
	Vector2f* enemyPosition;
	Vector2f* projectilePosition;
	bool doDamage;
	bool doIncrement;

	for (std::vector<Enemy*>::iterator it = m_EnemyVector -> begin(); it != m_EnemyVector -> end();)
	{
		doIncrement = true;
		enemyPosition =	(*it) -> getPosition( );

		for ( int j = 0; j < m_vProjectiles.size( ); j++ )
		{
			if ( m_vProjectiles[j] -> exist( ) )
			{
				doDamage = false;

				projectilePosition =  m_vProjectiles[j] -> getPosition( );
				if ( ( projectilePosition -> x > enemyPosition -> x ) && ( projectilePosition -> x < enemyPosition -> x + TILESIZE ) )  //if top left corner of projectile is in enemy x and x + TILESIZE
				{
					if ( ( projectilePosition -> y > enemyPosition -> y ) && ( projectilePosition -> y < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x + PROJECTILE_SIZE > enemyPosition -> x ) && ( projectilePosition -> x + PROJECTILE_SIZE < enemyPosition -> x + TILESIZE ) )  //if top right corner of projectile is in enemy x and x + TILESIZE
				{
					if ( ( projectilePosition -> y > enemyPosition -> y ) && ( projectilePosition -> y < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x > enemyPosition -> x ) && ( projectilePosition -> x < enemyPosition -> x + TILESIZE ) )  //if bottom left corner of projectile is in enemy x and x + TILESIZE
				{
					if ( ( projectilePosition -> y + PROJECTILE_SIZE > enemyPosition -> y ) && ( projectilePosition -> y + PROJECTILE_SIZE < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x + PROJECTILE_SIZE > enemyPosition -> x ) && ( projectilePosition -> x + PROJECTILE_SIZE < enemyPosition -> x + TILESIZE ) )  //if bottom right corner of projectile is in enemy x and x + TILESIZE
				{
					if ( ( projectilePosition -> y + PROJECTILE_SIZE > enemyPosition -> y ) && ( projectilePosition -> y + PROJECTILE_SIZE < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						doDamage = true;
					}
				}


				if (doDamage)
				{
					if((*it) -> takeDamage( (m_vProjectiles[j]) -> getDamage()))	//damage to enemy
					{
							modifySouls((*it) -> kill());
							//it = m_EnemyVector -> erase(it);
							//doIncrement = false;
					}

					m_vProjectiles[j] -> setInvisible( );   //put the projectile back to be unused
				}
			}
		}

		if (doIncrement)
		{
			++it;
		}
	}


	/////////Enemy Projectiles vs Player/////////////

	std::vector<Projectile*>* enemyProjectiles;

	for (std::vector<Enemy*>::iterator it = m_EnemyVector -> begin(); it != m_EnemyVector -> end(); ++it)
	{
		enemyProjectiles =	(*it) -> getProjectile( );
		for ( std::vector<Projectile*>::iterator currProjectile = enemyProjectiles -> begin(); currProjectile != enemyProjectiles -> end(); ++currProjectile)
		{
			doDamage = false;

			if ( (*currProjectile) -> exist( ) )
			{
				projectilePosition =  (*currProjectile) -> getPosition( );

				if ( ( projectilePosition -> x > m_Position.x ) && ( projectilePosition -> x < m_Position.x + TILESIZE ) )  //if top left corner of projectile is in player x and x + TILESIZE
				{
					if ( ( projectilePosition -> y > m_Position.y ) && ( projectilePosition -> y < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x + TILESIZE > m_Position.x ) && ( projectilePosition -> x + TILESIZE < m_Position.x + TILESIZE ) )  //if top right corner of projectile is in player x and x + TILESIZE
				{
					if ( ( projectilePosition -> y > m_Position.y ) && ( projectilePosition -> y < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x > m_Position.x ) && ( projectilePosition -> x < m_Position.x + TILESIZE ) )  //if bottom left corner of projectile is in player x and x + TILESIZE
				{
					if ( ( projectilePosition -> y + TILESIZE > m_Position.y ) && ( projectilePosition -> y + TILESIZE < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				else if ( ( projectilePosition -> x + TILESIZE > m_Position.x ) && ( projectilePosition -> x + TILESIZE < m_Position.x + TILESIZE ) )  //if bottom right corner of projectile is in player x and x + TILESIZE
				{
					if ( ( projectilePosition -> y + TILESIZE > m_Position.y ) && ( projectilePosition -> y + TILESIZE < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						doDamage = true;
					}
				}

				if (doDamage)
				{
					if(takeDamage( (*currProjectile)->getDamage() )) // if damage to player is enough to kill. 
					{
						die();
					}

					(*currProjectile) -> setInvisible( );	//put the enemy projectile back to be unused
				}
			}
		}
	}
}

void Player::die()
{
	m_bDead = true;
	m_Sprite.setTexture((*m_TextureTypes[DIE]));
	userInterface -> fadeOut();

	// fade out into highscore screen. 
}