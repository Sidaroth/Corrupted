#pragma once

#include "StateHandler.h"
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include <sstream>



class Ui {

private:
	sf::View m_view;

	sf::Texture m_uiBackground;
	sf::Sprite m_uiBackgroundSprite;

	sf::Texture m_healthDiamond;
	sf::Sprite m_healthDiamondSprite;
	
	sf::Font font;

	sf::Text rightSideText;
	sf::Text rightSideStats;

	sf::Text rightSideSecondaryText;
	sf::Text rightSideSecondaryStats;

	Player* m_player;
	int healthRotation;
	short m_shFrameCount;

public:
	Ui();
	~Ui();

	bool loadContent();
	void unloadContent();
	void update(Player* player);
	void draw();	
};

template <typename T> std::string numberToString ( T Number );