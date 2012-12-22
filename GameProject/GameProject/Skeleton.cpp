#include "Skeleton.h"
#include "StateHandler.h"

Skeleton::Skeleton(std::vector<sf::Texture>* textures, short level)
{
	m_shStrength = level;
	m_shIntelligence = level;
	m_shToughness = level;
	m_shSpeed = + level / 5;


	m_shSoulsToDrop = 10;
	onClosedList = 10;
	onOpenList = 1;
	pathLength = UNDETERMINED;

	m_fAttackRange = 48;

	xStepGoalReached = false;
	yStepGoalReached = false;

	m_TextureTypes.push_back( &textures -> at(MOVE) );
	m_TextureTypes.push_back( &textures -> at(ATTACK) );
	m_TextureTypes.push_back( &textures -> at(STILL) );
	m_TextureTypes.push_back( &textures -> at(DIE) );
}

Skeleton::~Skeleton()
{
	for(std::vector<sf::Texture*>::iterator it = m_TextureTypes.begin(); it != m_TextureTypes.end();)
	{
		delete * it;
		it = m_TextureTypes.erase(it);
	}
}

bool Skeleton::loadContent()
{
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
	animation();

	return EXIT_SUCCESS;	// Exit succesfully. 
}

void Skeleton::draw()
{
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}

void Skeleton::update(Vector2f* playerPos)
{
	animation();

	if(!m_bDead)
	{
		float xPos = m_Sprite.getPosition().x;
		float yPos = m_Sprite.getPosition().y;

		pathLocation = m_Path.size() - 1;
		short direction = -1;

		if(pathLocation >= 0) // If there are any pathsteps. 
		{
			pathStep = m_Path[pathLocation];

			if((yPos) < pathStep -> y )
			{
				direction = 4;		// south
			}
			else if((yPos - 48) > pathStep -> y )
			{
				direction = 0;		// north
			}

			if(abs(pathStep -> y - m_Sprite.getPosition().y) < m_fAttackRange)
			{
				yStepGoalReached = true;
			}

			if((xPos + 48) < pathStep -> x )
			{
				if(direction == 4)
				{
					direction--;	// south-east
				}
				else if(direction == 0)
				{
					direction++;	// north-east
				}
				else
				{
					direction = 2;	// east
				}
			}
			else if((xPos - 48) < pathStep -> x)
			{
				if(direction == 4)
				{
					direction++;	// south-west
				}
				else if(direction == 0)
				{
					direction = 7;	// north-west
				}
				else
				{
					direction = 6;	// west
				}
			}

			if(direction != -1)
			{
				move(direction);
			}

			if(abs(pathStep -> x - m_Sprite.getPosition().x < m_fAttackRange))
			{
				xStepGoalReached = true;
			}

			if(xStepGoalReached && yStepGoalReached)
			{
				m_Path.erase(m_Path.end() - 1);
				xStepGoalReached = false;
				yStepGoalReached = false;
			}
		}
		else
		{
			if(abs(playerPos -> x - xPos) < m_fAttackRange &&
			   abs(playerPos -> y - yPos) < m_fAttackRange)
			{
				m_bTryAttack = true;
				m_Sprite.setTexture((*m_TextureTypes[ATTACK]));
			}
			else
			{
				m_bTryAttack = false;
				findPath(xPos, yPos, playerPos -> x, playerPos -> y);
			}
		}
	}
	else
	{

	}
}