#include "Character.h"

//////////////////////////// CONSTRUCTORS ////////////////////////

const short BASE_STAT = 5;

Character::Character() : Actor()
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
	return m_sHealth;
}

short Character::getDamage()
{
	return m_sDamage;
}

short Character::getSpeed()
{
	return m_sSpeed;
}

short Character::getToughness()
{
	return m_sToughness;
}

short Character::getIntelligence()
{
	return m_sIntelligence;
}

short Character::getStrength()
{
	return m_sStrength;
}

short Character::getLevel()
{
	return m_sLevel;
}

bool* Character::getAbilities()
{
	return m_bAbilities;
}


//////////////////////
void Character::showDamage() 
{

}

void Character::showHealth()
{

}
