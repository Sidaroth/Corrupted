#include "Skeleton.h"

Skeleton::Skeleton()
{
	std::cout << "I'm being created! Yay!" << std::endl;
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
	return 0;
}

void Skeleton::draw(sf::RenderWindow &window)
{
	window.draw(m_Sprite);
}