#include "Character.h"

//////////////////////////// CONSTRUCTORS ////////////////////////

Character::Character()
{
	m_sDamage = 10;
	m_sSpeed = BASE_STAT;
	m_sToughness = BASE_STAT;
	m_sIntelligence = BASE_STAT;
	m_sStrength = BASE_STAT;

	m_sLevel = 1;
	m_sHealth = 50;

	m_bAbilities = new bool[false, false, false];
}

void Character::attack()
{

}

short Character::getHealth()
{

}

short Character::getDamage()
{


}

short Character::getSpeed()
{

}

short Character::getToughness()
{


}

short Character::getIntelligence()
{

}

short Character::getStrength()
{


}

short Character::getLevel()
{


}

bool* Character::getAbilities()
{

}


//////////////////////
void Character::showDamage() 
{

}

void Character::showHealth()
{

}
