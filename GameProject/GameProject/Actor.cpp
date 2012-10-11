#include "Actor.h"

Actor::Actor()
{
	m_Position.x = 0;
	m_Position.y = 0;
}

void Actor::draw()
{

}

bool Actor::loadContent()
{
	return 1;
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

void Actor::setSprite()
{
	
}
