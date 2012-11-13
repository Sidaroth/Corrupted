#pragma once

#include "Character.h"
#include "Enemy.h"


class Player : public Character
{
private:
	
	short m_shTotalSouls;
	short m_shCurrentSouls;
	short m_shWeaponLevel;
	short m_shArmorLevel; 

	std::string m_sName;

	std::vector<Enemy*>* m_EnemyVector;

	void collisionCheck( );

protected:

public:
	
	Player();
	Player(std::string name);
	bool loadContent();
	void update();
	void draw();

	short getTotalSouls();
	short getCurrentSouls();
	short getWeaponLevel();
	short getArmorLevel();

	void setEnemyVector( std::vector<Enemy*>* enemyVector);
};