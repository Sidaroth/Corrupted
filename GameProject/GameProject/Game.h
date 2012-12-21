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
#include<SFML\Audio.hpp>


class Game
{
private:

	sf::Text frames_per_sec;
	sf::RenderWindow m_Window;

	sf::Sprite m_ShieldSprite;
	sf::Sprite m_ShieldYesSprite;
	sf::Sprite m_ShieldNoSprite;

	sf::Texture m_ShieldTexture;
	sf::Texture m_ShieldYesTexture;
	sf::Texture m_ShieldYesPressedTexture;
	sf::Texture m_ShieldNoTexture;
	sf::Texture m_ShieldNoPressedTexture;

	std::string m_sTitle;
	short m_shScreenWidth;
	short m_shScreenHeight;
	short m_shScreenBitColor;
	bool m_bRunning;
	bool m_bShield;
	sf::Color* m_BackgroundColor;

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