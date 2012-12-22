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

	m_Sprite.setPosition(m_Position.x, m_Position.y);
}

/// Moves the position of the actor by the amount specified. 
void Actor::movePosition(float xChange, float yChange)
{
	m_Position.x += xChange;
	m_Position.y += yChange;

	m_Sprite.move(xChange, yChange);
}

Vector2f* Actor::getPosition()
{
	m_Position.x = m_Sprite.getPosition().x;
	m_Position.y = m_Sprite.getPosition().y;
	
	return &m_Position;
}

Vector2f* Actor::getSpritePosition(){
	Vector2f* auxVector = new Vector2f();
	sf::FloatRect actorBounds = m_Sprite.getGlobalBounds();
	int actor_width = actorBounds.width;
	int actor_height = actorBounds.height;
	//sf::FloatRect bounds = m_Sprite.getLocalBounds();
	auxVector ->x =m_Sprite.getPosition().x+(actor_width/2);
	auxVector ->y = m_Sprite.getPosition().y+(actor_height/2);
	return  auxVector;
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
	return !EXIT_FAILURE;
}

void Actor::setSpriteSize(short size)
{
	m_shSpriteSize = size;
}
