#pragma once

#include "GameState.h"
#include "StateHandler.h"

class TitleScreen : public GameState
{
private:
	sf::Text text;
	sf::Font font;

public:
	TitleScreen();
	~TitleScreen();

	void loadContent();
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw(sf::RenderWindow &window);
};