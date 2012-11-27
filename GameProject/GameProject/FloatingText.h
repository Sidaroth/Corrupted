#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2f.h"
#include "StateHandler.h"

class FloatingText
{
protected:
	sf::Text m_Message;
	sf::Font* m_Font;

public:
	FloatingText();
	FloatingText(std::string message, Vector2f position, sf::Font* font);
	void update();
	void draw();

	void setFont(sf::Font* font);
};