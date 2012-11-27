#pragma once

#include "Enemy.h"
#include "Skeleton.h"

/// Factory handling the creation and deletion of all enemies. 
class EnemyFactory
{
protected:

	enum TextureType
	{
		MOVE,
		ATTACK,
		STILL,
		DIE
	};

public:

	EnemyFactory();
	bool loadContent();

	std::vector<sf::Texture> m_SkellieTextures;

	enum Enemies
	{
		Skellie
		// More soon (tm)..
	};

	Enemy* createEnemy(Enemies enemyType);
};