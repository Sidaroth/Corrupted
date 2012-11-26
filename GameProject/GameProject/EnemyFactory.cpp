#include "EnemyFactory.h"

Enemy* EnemyFactory::createEnemy(Enemies enemyType)
{
	switch(enemyType)
	{
	case Skellie:
		return new Skeleton();
	}

	return NULL;
}