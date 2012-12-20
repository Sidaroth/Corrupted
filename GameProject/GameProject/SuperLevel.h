#pragma once

#include "GameState.h"
#include "StateHandler.h"
#include "Environment.h"
#include "Player.h"
#include "KeyboardController.h"
#include "EnemyHandler.h"
#include "Ui.h"

class SuperLevel : public GameState
{

protected:
	sf::Font font;
	EnvironmentHandler* m_Level;
	sf::View m_Viewport;
	Player* player;
	KeyboardController* keyControl;
	EnemyHandler* m_EnemyHandler;
	Ui* ui;

public:
	SuperLevel();
	~SuperLevel();

	void superLoadContent();
	void unloadContent();	
	void processEvents(sf::Event event);
	void update();
	void superDraw();
};