#include "Player.h"
#include "StateHandler.h"

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

	m_sName = "Ronald McDonald";
}

bool Player::loadContent()
{
	//load projectiles in character
	Character::loadContent();

	sf::Image maskingImage;
		//Loading move action
	if (!maskingImage.loadFromFile("../../Resources/player.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["move"].imgTexture=m_Texture;
	m_TexturesActions["move"].size=m_Texture.getSize().x;
	//Loading attack action
	if (!maskingImage.loadFromFile("../../Resources/player_attack.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["attack"].imgTexture=m_Texture;
	m_TexturesActions["attack"].size=m_Texture.getSize().x;
	//
	//Loading standing action
	if (!maskingImage.loadFromFile("../../Resources/player_still.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["still"].imgTexture=m_Texture;
	m_TexturesActions["still"].size=m_Texture.getSize().x;
	//

	m_Sprite.setTexture(m_TexturesActions["still"].imgTexture);
	animation();

	return 0;
}

void Player::update() 
{
	Character::update();

	m_shMaxHealth = m_shToughness*m_shToughness*2;
	m_shMeleeDamage = m_shStrength*m_shStrength;
	m_shSpellDamage = m_shIntelligence*m_shIntelligence;
	m_fCriticalChance = m_shStrength/5 + m_shSpeed/2;

	m_saStatArray[0] = m_shStrength;
	m_saStatArray[1] = m_shIntelligence;
	m_saStatArray[2] = m_shToughness;
	m_saStatArray[3] = m_shSpeed;
	m_saStatArray[4] = m_shWeaponLevel;
	m_saStatArray[5] = m_shArmorLevel;

	collisionCheck( );
}

void Player::draw()
{
	Character::draw();
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}

short Player::getTotalSouls()
{
	return m_shTotalSouls;
}

short Player::getCurrentSouls()
{
	return m_shCurrentSouls;
}

short Player::getWeaponLevel()
{
	return m_shWeaponLevel;
}

short Player::getArmorLevel()
{
	return m_shArmorLevel;
}

int Player::getStatArray(int stat) 
{
	return m_saStatArray[stat];
}

void Player::increaseStat(int stat)
{
	switch (stat) {
	case 0:
		m_shStrength++;
		break;
	case 1:
		m_shIntelligence++;
		break;
	case 2:
		m_shToughness++;
		break;
	case 3:
		m_shSpeed++;
		break;
	case 4:
		m_shWeaponLevel++;
		break;
	case 5:
		m_shArmorLevel++;
		break;
	}
}

void Player::modifySouls(short amount) 
{
	m_shCurrentSouls += amount;

	if (amount > 0)
	{
		m_shTotalSouls += amount;
	}
}

void Player::setEnemyVector(std::vector<Enemy*>* enemyVector)
{
	m_EnemyVector = enemyVector;
}

bool Player::checkAtackCollision(short direction){

	Vector2f* enemyPosition;
	Vector2f* projectilePosition;
	int player_x = getSpritePosition()->x;
	int player_y = getSpritePosition()->y;
	int atackPoint_x=0;
	int atackPoint_y=0;
	int range=30;
	for( int i = 0; i < m_EnemyVector->size( ); i++ )
	{
		enemyPosition =	m_EnemyVector -> at( i ) -> getSpritePosition( );
		sf::FloatRect enemy_bounds = m_EnemyVector -> at( i )->getSprite().getGlobalBounds();
		int enemy_width = enemy_bounds.width;
		int enemy_height = enemy_bounds.height;
		int enemy_x=enemyPosition->x;
		int enemy_y=enemyPosition->x;
		
		std::cout << "ENEMY POSITION: (" << enemy_x << "," << enemy_y << ")"<< "ENEMY WIDTH AND HEIGHT: (" << enemy_width << "," << enemy_height << ")" << std::endl;
		std::cout << "PLAYER POSITION: (" << player_x << "," <<player_y << ")" << std::endl;
		
		
		switch (direction)
		{	
			case NORTH:
				atackPoint_x = player_x;
				atackPoint_y = player_y-range;
			break;

			case NORTH_EAST:
				atackPoint_x = player_x+range;
				atackPoint_y = player_y-range;
			break;

			case EAST:
				atackPoint_x = player_x+range;
				atackPoint_y = player_y;
			break;

			case SOUTH_EAST:
				atackPoint_x = player_x+range;
				atackPoint_y = player_y+range;
				
			break;

			case SOUTH:
				atackPoint_x = player_x;
				atackPoint_y = player_y+range;
				
			break;

			case SOUTH_WEST:
				atackPoint_x = player_x-range;
				atackPoint_y = player_y+range;
				
			break;

			case WEST:
				atackPoint_x = player_x-range;
				atackPoint_y = player_y;
			
				break;

			case NORTH_WEST:
				atackPoint_x = player_x-range;
				atackPoint_y = player_y-range;
				
			break;
		}
		std::cout << "ATACK POSITION: (" << atackPoint_x << "," <<atackPoint_y << ")" << std::endl;
	
		if((atackPoint_x>(enemy_x-enemy_width/2))&&(atackPoint_x<(enemy_x+(enemy_width/2)))){
			if((atackPoint_y>(enemy_y-enemy_height/2))&&(atackPoint_y<(enemy_y+(enemy_height/2)))){
				return true;
			}
		}
		if((player_x>(enemy_x-enemy_width/2))&&(player_x<((enemy_x+enemy_width/2)))){
			if((player_y>(enemy_y-(enemy_height/2)))&&(player_y<(enemy_y+(enemy_height/2)))){
				return true;
			}
		}
		//Create both triangles/rectangles and see if there is collision


	}
	
	
	return false;
}

bool Player::pointInsideRect(int pX,int pY,sf::FloatRect rectangle){
		
		int rect_width = rectangle.width;
		int rect_height = rectangle.height;
		int rect_x=rectangle.left;
		int rect_y=rectangle.top;
		std::cout << "Px: " << pX << " pY: " << pY << " rect_x: " << rect_x << "rect_y: "<< rect_y <<"width: "<< rect_width << std::endl;
				
		if((pX>rect_x)&&(pX<rect_x+rect_width))
		{
			if((pY>rect_y)&&(pY<rect_y+rect_height))
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

	for( int i = 0; i < m_EnemyVector->size( ); i++ )
	{
		enemyPosition =	m_EnemyVector -> at( i ) -> getPosition( );
		for( int j = 0; j < m_vProjectiles.size( ); j++ )
		{
			if( m_vProjectiles[j] -> exist( ) )
			{
				projectilePosition =  m_vProjectiles[j] -> getPosition( );
				if( ( projectilePosition -> x > enemyPosition -> x ) && ( projectilePosition -> x < enemyPosition -> x + TILESIZE ) )  //if top left corner of projectile is in enemy x and x + TILESIZE
				{
					if( ( projectilePosition -> y > enemyPosition -> y ) && ( projectilePosition -> y < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						m_EnemyVector -> at( i ) -> takeDamage( m_shSpellDamage );		//damage to enemy
						m_vProjectiles[j] -> setInvisible( );							//put the projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x + PROJECTILE_SIZE > enemyPosition -> x ) && ( projectilePosition -> x + PROJECTILE_SIZE < enemyPosition -> x + TILESIZE ) )  //if top right corner of projectile is in enemy x and x + TILESIZE
				{
					if( ( projectilePosition -> y > enemyPosition -> y ) && ( projectilePosition -> y < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						m_EnemyVector -> at( i ) -> takeDamage( m_shSpellDamage );		//damage to enemy
						m_vProjectiles[j] -> setInvisible( );							//put the projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x > enemyPosition -> x ) && ( projectilePosition -> x < enemyPosition -> x + TILESIZE ) )  //if bottom left corner of projectile is in enemy x and x + TILESIZE
				{
					if( ( projectilePosition -> y + PROJECTILE_SIZE > enemyPosition -> y ) && ( projectilePosition -> y + PROJECTILE_SIZE < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						m_EnemyVector -> at( i ) -> takeDamage( m_shSpellDamage );		//damage to enemy
						m_vProjectiles[j] -> setInvisible( );							//put the projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x + PROJECTILE_SIZE > enemyPosition -> x ) && ( projectilePosition -> x + PROJECTILE_SIZE < enemyPosition -> x + TILESIZE ) )  //if bottom right corner of projectile is in enemy x and x + TILESIZE
				{
					if( ( projectilePosition -> y + PROJECTILE_SIZE > enemyPosition -> y ) && ( projectilePosition -> y + PROJECTILE_SIZE < enemyPosition -> y + TILESIZE )  ) //and in enemy y and y + TILESIZE
					{
						m_EnemyVector -> at( i ) -> takeDamage( m_shSpellDamage );		//damage to enemy
						m_vProjectiles[j] -> setInvisible( );							//put the projectile back to be unused
					}
				}
			}
		}
	}


	/////////Enemy Projectiles vs Player/////////////

	std::vector<Projectile*>* enemyProjectiles;

	for( int i = 0; i < m_EnemyVector -> size( ); i++ )
	{
		enemyProjectiles =	m_EnemyVector -> at( i ) -> getProjectile( );

		for( int j = 0; j < enemyProjectiles -> size( ); j++ )
		{
			if( enemyProjectiles -> at( j ) -> exist( ) )
			{
				projectilePosition =  enemyProjectiles -> at( j ) -> getPosition( );
				if( ( projectilePosition -> x > m_Position.x ) && ( projectilePosition -> x < m_Position.x + TILESIZE ) )  //if top left corner of projectile is in player x and x + TILESIZE
				{
					if( ( projectilePosition -> y > m_Position.y ) && ( projectilePosition -> y < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						takeDamage( m_shSpellDamage );											//damage to player
						enemyProjectiles -> at( j ) -> setInvisible( );							//put the enemy projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x + TILESIZE > m_Position.x ) && ( projectilePosition -> x + TILESIZE < m_Position.x + TILESIZE ) )  //if top right corner of projectile is in player x and x + TILESIZE
				{
					if( ( projectilePosition -> y > m_Position.y ) && ( projectilePosition -> y < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						takeDamage( m_shSpellDamage );											//damage to player
						enemyProjectiles -> at( j ) -> setInvisible( );							//put the enemy projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x > m_Position.x ) && ( projectilePosition -> x < m_Position.x + TILESIZE ) )  //if bottom left corner of projectile is in player x and x + TILESIZE
				{
					if( ( projectilePosition -> y + TILESIZE > m_Position.y ) && ( projectilePosition -> y + TILESIZE < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						takeDamage( m_shSpellDamage );											//damage to player
						enemyProjectiles -> at( j ) -> setInvisible( );							//put the enemy projectile back to be unused
					}
				}

				else if( ( projectilePosition -> x + TILESIZE > m_Position.x ) && ( projectilePosition -> x + TILESIZE < m_Position.x + TILESIZE ) )  //if bottom right corner of projectile is in player x and x + TILESIZE
				{
					if( ( projectilePosition -> y + TILESIZE > m_Position.y ) && ( projectilePosition -> y + TILESIZE < m_Position.y + TILESIZE )  ) //and in player y and y + TILESIZE
					{
						takeDamage( m_shSpellDamage );											//damage to player
						enemyProjectiles -> at( j ) -> setInvisible( );							//put the enemy projectile back to be unused
					}
				}
			}
		}
	}
}