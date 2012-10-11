#include "Actor.h"

#pragma once

class Character : public Actor
{
private: 
	enum abilities { FIREBALL, FROSTBOLT, LIGHTNINGBOLT };
	abilities m_eAbilities;
	short m_shHealth;
	short m_shDamage;
	short m_shSpeed;
	short m_shToughness;
	short m_shIntelligence;
	short m_shStrength;
	short m_shLevel;
	bool* m_bAbilities;

protected:
	Character();
	Character(int variablesHere); // TEMPORARY. 

public:
	void attack();
	short getHealth();
	short getDamage();
	short getSpeed();
	short getToughness();
	short getIntelligence();
	short getStrength();
	short getLevel();
	bool* getAbilities();
	
	void moveHorizontal(bool horizontalMovement);
	void moveVertical(bool verticalMovement);

	void showDamage();	// wut wut
	void showHealth();	
};