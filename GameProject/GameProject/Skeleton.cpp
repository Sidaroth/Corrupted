#include "Skeleton.h"
#include "StateHandler.h"
Skeleton::Skeleton()
{

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
	if(test % 200 == 0)
	{
		Vector2f* path = findPath(m_Sprite.getPosition().x, m_Sprite.getPosition().y, 96, 96);

		if(path -> y > m_Sprite.getPosition().y)
		{
			move(SOUTH);
		}
		else
		{
			move(NORTH);
		}

		if(path -> x > m_Sprite.getPosition().x)
		{
			move(EAST);
		}
		else
		{
			move(WEST);
		}
	}
}