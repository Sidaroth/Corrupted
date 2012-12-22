#include "Skeleton.h"
#include "StateHandler.h"

Skeleton::Skeleton(std::vector<sf::Texture>* textures, short level)
{
	m_shStrength = level;
	m_shIntelligence = level;
	m_shToughness = level;
	m_shSpeed = level;


	m_shSoulsToDrop = 10;
	onClosedList = 10;
	onOpenList = 1;
	pathLength = UNDETERMINED;

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

		if(pathLocation >= 0) // If there are any pathsteps. 
		{
			pathStep = m_Path[pathLocation];

			if(pathStep -> y > yPos)
			{
				move(SOUTH);
			}
			else if(pathStep -> y < yPos)
			{
				move(NORTH);
			}

			if(abs(pathStep -> y - m_Sprite.getPosition().y < 10))
			{
				yStepGoalReached = true;
			}

			if(pathStep -> x > xPos)
			{
				move(EAST);
			}
			else if(pathStep -> x < xPos)
			{
				move(WEST);
			}

			if(abs(pathStep -> x - m_Sprite.getPosition().x < 10))
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
			findPath(xPos, yPos, playerPos -> x, playerPos -> y);
		}
	}
	else
	{

	}
}