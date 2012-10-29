#pragma once

#include "Character.h"
#include "Ui.h"

class Player : public Character
{
private:
	
	short m_shTotalSouls;
	short m_shCurrentSouls;
	short m_shWeaponLevel;
	short m_shArmorLevel; 

	std::string m_sName;
	Ui* ui;



protected:

public:
	
	Player();
	Player(std::string name);
	bool loadContent();
	void update();
	void draw(sf::RenderWindow &window);
};