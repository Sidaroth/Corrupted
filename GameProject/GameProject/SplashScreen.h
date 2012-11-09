#pragma once

#include "GameState.h"
#include "StateHandler.h"

class SplashScreen : public GameState
{
private:

	sf::Texture m_splashScreen;
	sf::Sprite m_splashScreenSprite;

public:
	SplashScreen();
	~SplashScreen();

	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();
};