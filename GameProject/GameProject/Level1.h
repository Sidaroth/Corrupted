#pragma once

#include "GameState.h"
#include "Environment.h"
#include "Player.h"
#include "KeyboardController.h"
#include "EnemyHandler.h"

class Level1 : public GameState
{
private:
	sf::Text text;
	sf::Font font;
	EnvironmentHandler* m_Level;
	sf::View m_Viewport;
	Player* player;
	KeyboardController* keyControl;
	EnemyHandler* m_EnemyHandler;

public:
	Level1();
	~Level1();

	void loadContent();
	void unloadContent();	void update();
	void draw(sf::RenderWindow &window);
};