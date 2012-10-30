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
	std::vector<Vector2f*> path = findPath(m_Sprite.getPosition().x, m_Sprite.getPosition().y, 800, 800);

	//for(unsigned int i = 0; i < path.size(); i++)
	//{
	//	std::cout << "path " << i << ": " << path[i] << std::endl;
	//}
}