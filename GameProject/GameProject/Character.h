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
	short m_shBitmapRow;		//What frame of the animation from the spritesheet to display
	short m_shBitmapCol;		//What animation to display from the spritesheet
	float m_fCriticalChance;	//Chance to crit, 1 = 0%, 1.01 = 1% etc.
	bool* m_bAbilities;

protected:
	Character();
	Character(int variablesHere); // TEMPORARY. 

public:
	void attack();

	///////GET FUNCTIONS///////
	short getHealth();
	short getDamage();
	short getSpeed();
	short getToughness();
	short getIntelligence();
	short getStrength();
	short getLevel();
	bool* getAbilities();

	////////SET FUNCTIONS//////
	void setAnimation();
	
	void moveHorizontal(bool horizontalMovement);
	void moveVertical(bool verticalMovement);

	void showDamage();	// wut wut
	void showHealth();	
};