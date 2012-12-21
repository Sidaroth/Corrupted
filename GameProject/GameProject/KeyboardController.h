#pragma once

#include "Player.h"
#include "AudioManager.h"
#include "StateHandler.h"


class KeyboardController 
{

private:
	
	Player* m_Player;
	sf::RenderWindow* m_Window;
	AudioManager audio_manager;


public:

	KeyboardController(Player* player, sf::RenderWindow* window);
	~KeyboardController();

	void keyboardInput();
	void mouseInput(sf::Event event);
	bool mouseNotInUi(sf::Event event);
};