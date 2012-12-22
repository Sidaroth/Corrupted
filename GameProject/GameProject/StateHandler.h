#pragma once

#include <string>
#include <iostream>

#include "GameState.h"
#include "TitleScreen.h"
#include "AudioManager.h"

// Singleton class managing the state of the game (intro, menu, game, etc...)
class StateHandler
{
private:
	StateHandler();
	StateHandler(StateHandler const&); /// Copy constructor
	void operator=(StateHandler const&); /// Assignment operator
	
	GameState *currentState, *newState;
	bool safe;
	bool m_bRunning;
	bool m_bQuitShield;
	bool m_bMenuShield;

	sf::Sprite m_ShieldSprite;
	sf::Sprite m_ShieldYesSprite;
	sf::Sprite m_ShieldNoSprite;

	sf::Texture m_ShieldMenuTexture;
	sf::Texture m_ShieldQuitTexture;
	sf::Texture m_ShieldYesTexture;
	sf::Texture m_ShieldYesPressedTexture;
	sf::Texture m_ShieldNoTexture;
	sf::Texture m_ShieldNoPressedTexture;



public:
	~StateHandler();
	static StateHandler &getInstance();
	sf::RenderWindow* m_pWindow;
	AudioManager m_AudioManager;
	void initalize();
	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();
	void stopRunning();
	bool getRunning();
	void setMenuShield(bool shield);
	void setQuitShield(bool shield);
	bool getMenuShield();
	bool getQuitShield();
	
	
	void setStartState(GameState* state);
	void addScreen(GameState *state);
};