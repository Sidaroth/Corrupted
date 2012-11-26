#include "Skeleton.h"
#include "StateHandler.h"

Skeleton::Skeleton(std::vector<sf::Texture>* textures)
{
	onClosedList = 10;
	onOpenList = 1;
	pathLength = UNDETERMINED;

	m_TextureTypes.push_back( &textures -> at(MOVE) );
	m_TextureTypes.push_back( &textures -> at(ATTACK) );
	m_TextureTypes.push_back( &textures -> at(STILL) );
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
	// NOTE - BUG: Because the skeleton moves 3 and 3 pixels, it will spasm madly and potentially crash if the startX or startY is not a multiple of 3. 
	// NOTE - BUG: Pathstep is erased to soon... Fix is relatively easy, but crash is more important. 

	// If it has no path, or has walked a certain amount of steps on it's present path. Calculate new path. 
	float xPos = m_Sprite.getPosition().x;
	float yPos = m_Sprite.getPosition().y;
	bool stepTaken = false;
	
	if(m_Path.size() == 0 || pathLength - m_Path.size() == 5)
	{
		findPath(xPos, yPos, playerPos -> x, playerPos -> y);
	}

	pathLocation = m_Path.size() - 1;

	//std::cout << "pathloc: " << pathLocation << "\npathSize: " << m_Path.size() << "\npathLength: " << pathLength << "\n";

	if(pathLocation >= 0) // If there is a path
	{
		pathStep = m_Path[pathLocation];

		if(pathStep -> y > yPos)
		{
			move(SOUTH);

			if(m_Sprite.getPosition().y  >= pathStep -> y)
			{
				m_Path.erase(m_Path.end() - 1);
				stepTaken = true;
			}
		}
		else if(pathStep -> y < yPos)
		{
			move(NORTH);

			if(m_Sprite.getPosition().y  <= pathStep -> y)
			{
				m_Path.erase(m_Path.end() - 1);
				stepTaken = true;
			}
		}

		if(pathStep -> x > xPos && !stepTaken)
		{
			move(EAST);

			if(m_Sprite.getPosition().x >= pathStep -> x)
			{
				m_Path.erase(m_Path.end() - 1);
			}
		}
		else if(pathStep -> x < xPos && !stepTaken)
		{
			move(WEST);

			if(m_Sprite.getPosition().x  <= pathStep -> x)
			{
				m_Path.erase(m_Path.end() - 1);
			}
		}
	}
}