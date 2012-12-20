#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2f.h"
#include "StateHandler.h"

class FloatingText
{
protected:
	sf::Text m_Message;
	sf::Font* m_Font;
	sf::Color m_Color;
	
	bool m_bDead; 
	short m_shTimeToLive;
	short m_shTimeLived;

public:
	FloatingText();
	FloatingText(std::string message, Vector2f position, sf::Font* font, sf::Color color);
	void update();
	void draw();
	bool isDead();

	void setFont(sf::Font* font);
};