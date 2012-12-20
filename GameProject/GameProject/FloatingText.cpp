#include "FloatingText.h"

FloatingText::FloatingText()
{
	
}

FloatingText::FloatingText(std::string message, Vector2f position, sf::Font* font, sf::Color color)
{
	m_Font = font;
	m_Color = color;
	m_Message.setString(message);
	m_Message.setFont((*font));
	m_Message.setCharacterSize(18);
	m_Message.setColor(m_Color);
	m_Message.setPosition(position.x, position.y);
	m_shTimeLived = 0;
	m_shTimeToLive = 120;
	m_bDead = false;
}

bool FloatingText::isDead()
{
	return m_bDead;
}

void FloatingText::update()
{
	m_shTimeLived++;
	
	m_Message.move(0, -1.2);

	if(m_Color.a >= 3)
	{
		m_Color.a -= 3;
	}
	
	m_Message.setColor(m_Color);

	if(m_shTimeLived > m_shTimeToLive)
	{
		m_bDead = true;
	}
}

void FloatingText::draw()
{
	//sf::View tempView = StateHandler::getInstance().m_pWindow -> getView();

	//int windowX = tempView.getCenter().x - ( tempView.getSize().x / 2);
	//int windowY = tempView.getCenter().y - ( tempView.getSize().y / 2);

	StateHandler::getInstance().m_pWindow -> draw(m_Message);
}

void FloatingText::setFont(sf::Font* font)
{
	m_Font = font;
}