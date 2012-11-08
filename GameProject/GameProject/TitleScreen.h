#pragma once

#include "GameState.h"
#include "StateHandler.h"

class TitleScreen : public GameState
{
private:

	bool menuArray[2];
	short currentButton;

	sf::Texture m_menuBackground;
	sf::Sprite m_menuBackgroundSprite;

	sf::Texture m_startButton;
	sf::Texture m_startButtonMouseOver;
	sf::Sprite m_startButtonSprite;

	sf::Texture m_exitButton;
	sf::Texture m_exitButtonMouseOver;
	sf::Sprite m_exitButtonSprite;

public:
	TitleScreen();
	~TitleScreen();

	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();
};