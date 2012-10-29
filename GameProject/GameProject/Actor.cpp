#include "Actor.h"

Actor::Actor()
{
	m_Position.x = 0;
	m_Position.y = 0;
	m_shSpriteSize = 96;
}

void Actor::draw()
{

}

sf::Sprite Actor::getSprite()
{
	return m_Sprite;
}

void Actor::setPosition(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;
}

Vector2f* Actor::getPosition()
{
	return &m_Position;
	
}

Vector2f* Actor::getSpritePosition(){
	Vector2f* auxVector = new Vector2f();
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	auxVector ->x =m_Sprite.getPosition().x+(bounds.width/2);
	auxVector ->y = m_Sprite.getPosition().y+(bounds.height/2);

	return  auxVector;
}

void Actor::setSprite()
{
	
}

bool Actor::loadContent()
{
	if (!m_Texture.loadFromFile("../Resources/player.png"))
	{
		return EXIT_FAILURE;
	}
	
	m_Sprite.setTexture(m_Texture);
	
}

void Actor::setSpriteSize(short size)
{
	m_shSpriteSize = size;
}
