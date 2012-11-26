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
	// NOTE - BUG: Because the skeleton moves 3 and 3 pixels, it will spasm madly and potentially crash if the startX or startY is not a multiple of 3. 

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