#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <stdlib.h>
#include <iostream>
#include "Player.h"
#include "GameState.h"
#include "Player.h"
#include "GameState.h"
#include "KeyboardController.h"


class Game
{
private:

	sf::RenderWindow m_Window;
	std::string m_sTitle;
	short m_shScreenWidth;
	short m_shScreenHeight;
	short m_shScreenBitColor;
	bool m_bRunning;
	KeyboardController keyControl;
	sf::Color* m_BackgroundColor;
	Player* player;

public:
	Game();
	void start();
	void stop();
	void run();
	void update();
	void initialize(const char* title, short width = 1366, short height = 768, short bitPP = 32, bool fullscreen = false);
	void deInitialize();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void render();
	void processEvents();
	void checkKeyboard();
	bool running();
};