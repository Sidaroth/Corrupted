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

void Actor::setPosition(Vector2f newPos)
{
	
	m_Position.x = newPos.x;
	m_Position.y = newPos.y;

	m_Sprite.setPosition(newPos.x, newPos.y);
}

Vector2f* Actor::getPosition()
{
	m_Position.x = m_Sprite.getPosition().x;
	m_Position.y = m_Sprite.getPosition().y;
	return &m_Position;
}

float Actor::getXPosition()
{
		return m_Sprite.getPosition().x;
}

float Actor::getYPosition()
{
	return m_Sprite.getPosition().y;
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
