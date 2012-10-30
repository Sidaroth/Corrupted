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

	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();
};