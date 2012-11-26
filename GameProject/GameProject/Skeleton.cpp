#include "Skeleton.h"
#include "StateHandler.h"

Skeleton::Skeleton()
{
	onClosedList = 10;
	onOpenList = 1;
	pathLength = UNDETERMINED;
}

void Skeleton::sayHello()
{
	std::cout << "Hello!\n";
}

bool Skeleton::loadContent()
{
	sf::Image maskingImage;
	if (!maskingImage.loadFromFile("../../Resources/skeleton.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_Sprite.setTexture(m_Texture);
	animation();

	return EXIT_SUCCESS;	// Exit succesfully. 
}

void Skeleton::draw()
{
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}

void Skeleton::update(Vector2f* playerPos)
{
	// KNOWN BUG: Because the skeleton moves 3 and 3 pizels, it will spasm madly and potentially crash if the startX or startY is not a multiple of 3. 
	// If it has no path, or has walked a certain amount of steps on it's present path. Calculate new path. 
	
	if(m_Path.size() == 0 || pathLength - m_Path.size() == 5)
	{
		findPath(m_Sprite.getPosition().x, m_Sprite.getPosition().y, playerPos -> x, playerPos -> y);
	}

	pathLocation = m_Path.size() - 1;

	//std::cout << "Moving!" << std::endl;
	if(pathLocation >= 0) // If there is a path
	{
		pathStep = m_Path[pathLocation];

		if(pathStep -> y > m_Sprite.getPosition().y)
		{
			std::cout << "Moving south" << std::endl;
			move(SOUTH);
		}
		else if(pathStep -> y < m_Sprite.getPosition().y)
		{
			std::cout << "Moving north" << std::endl;
			move(NORTH);
		}

		if(pathStep -> x > m_Sprite.getPosition().x)
		{
			std::cout << "Moving east" << std::endl;
			move(EAST);
		}
		else if(pathStep -> x < m_Sprite.getPosition().x)
		{
			std::cout << "Moving west" << std::endl;
			move(WEST);
		}

		if((m_Sprite.getPosition().x - pathStep -> x <= 10 &&
			m_Sprite.getPosition().x - pathStep -> x > -10)		
			&& (m_Sprite.getPosition().y - pathStep -> y <= 0 &&
				m_Sprite.getPosition().y - pathStep -> y > -10))
		{
			m_Path.erase(m_Path.end() - 1);
		}
	}
}