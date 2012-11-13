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

	test = 0;

	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_Sprite.setTexture(m_Texture);
	animation();
	return 0;
}

void Skeleton::draw()
{
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}

void Skeleton::update()
{
	// If it has no path, or has walked a certain amount of steps on it's present path. Calculate new path. 
	if(m_Path.size() == 0 || pathLength - m_Path.size() == 5)
	{
		std::cout << "Calculating new path" << std::endl;
		findPath(m_Sprite.getPosition().x, m_Sprite.getPosition().y, 96, 96);
	}

	pathLocation = m_Path.size() - 1;
	//std::cout << "Moving!" << std::endl;
	if(pathLocation >= 1) // If there is a path
	{
		pathStep = m_Path[pathLocation];

		if(pathStep -> y > m_Sprite.getPosition().y)
		{
			move(SOUTH);
		}
		else if(pathStep -> y < m_Sprite.getPosition().y)
		{
			move(NORTH);
		}

		if(pathStep -> x > m_Sprite.getPosition().x)
		{
			move(EAST);
		}
		else if(pathStep -> x < m_Sprite.getPosition().x)
		{
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