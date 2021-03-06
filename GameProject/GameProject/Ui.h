#pragma once

#include "StateHandler.h"
#include "FloatingText.h"
#include <sstream>

class Ui {

private:
	sf::View m_view;

	sf::Texture m_uiBackground;
	sf::Sprite m_uiBackgroundSprite;

	sf::Texture m_healthDiamond;
	sf::Sprite m_healthDiamondSprite;

	sf::Texture m_iconFireball;
	sf::Sprite m_iconFireballSprite;

	sf::Texture m_iconSword;
	sf::Sprite m_iconSwordSprite;

	sf::Texture m_iconEmpty;
	sf::Sprite m_iconEmptySpriteArray[3];

	sf::Texture m_iconHeal;
	sf::Sprite m_iconHealSprite;

	sf::Texture m_increaseButtonGray;
	sf::Texture m_increaseButtonRed;

	sf::Sprite increaseButtonSpriteArray[6];
	bool increasable[6];
	bool m_bFading;
	bool m_bHasFaded;
	
	std::vector<FloatingText *> m_ftFloatingTextEntities;
	std::vector<short *> m_shvPlayerStats;
	float* m_fCriticalChance;

	sf::Font font;

	sf::Text rightSideText;
	sf::Text rightSideStats;

	sf::Text rightSideSecondaryText;
	sf::Text rightSideSecondaryStats;

	sf::Text healthText;

	sf::Text iconText[5];

	sf::RectangleShape fadeRect;
	sf::Color color;

	float healthRotation;
	short m_shFrameCount;

public:
	Ui();
	~Ui();

	void addFloatingText(std::string message, Vector2f position, sf::Color color);
	bool loadContent();
	void unloadContent();
	void update();
	void processEvents(sf::Event event);
	void draw();	
	void fadeOut();
	bool hasFaded();

	void initialize(short* strength, short* intellect, short* toughness, short* speed,
				    short* currentSouls, short* weaponLevel, short* armorLevel, short* currHp,
					short* maxHealth, short* meleeDamage, short* spellDamage, float* critChance);

	template <typename T> std::string numberToString ( T Number );
};