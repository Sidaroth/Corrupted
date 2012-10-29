#pragma once

#include "GameState.h"

class Ui {

private:
	sf::View m_view;

	sf::Texture m_uiBackground;
	sf::Sprite m_uiBackgroundSprite;
	
	sf::Text text;
	sf::Font font;

public:
	Ui();
	~Ui();

	bool loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};