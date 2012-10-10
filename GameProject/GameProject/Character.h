#include "Actor.h"

#pragma once

class Character : public Actor
{
private: 
	enum abilities { FIREBALL, FROSTBOLT, LIGHTNINGBOLT };
	abilities m_eAbilities;
	short m_sHealth;
	short m_sDamage;
	short m_sSpeed;
	short m_sToughness;
	short m_sIntelligence;
	short m_sStrength;
	short m_sLevel;
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

	void showDamage();	// wut wut
	void showHealth();	
};