#pragma once

#include "Character.h"

class Player : public Character
{
private:
	
	short m_shTotalSouls;
	short m_shCurrentSouls;
	short m_shWeaponLevel;
	short m_shArmorLevel; 

	std::string m_sName;

protected:

public:
	bool loadContent();
	Player();
	Player(std::string name);
	void draw(sf::RenderWindow &window);
};