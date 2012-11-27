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

	sf::Texture m_increaseButtonGray;
	sf::Texture m_increaseButtonRed;

	sf::Sprite increaseButtonSpriteArray[6];
	bool increasable[6];

	Player* m_player;
	sf::Font font;

	sf::Text rightSideText;
	sf::Text rightSideStats;

	sf::Text rightSideSecondaryText;
	sf::Text rightSideSecondaryStats;

	sf::Text healthText;

	float healthRotation;
	short m_shFrameCount;

public:
	Ui();
	~Ui();

	void addFloatingText();
	bool loadContent();
	void unloadContent();
	void update(Player* player);
	void draw();	
};

template <typename T> std::string numberToString ( T Number );