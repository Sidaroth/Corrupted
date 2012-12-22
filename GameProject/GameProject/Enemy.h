#pragma once

#include "SFML/Graphics.hpp"
#include "Character.h"
#include "Math.h"


// variables used in A* returns. 
#define UNDETERMINED 0
#define FOUND 1
#define NONEXISTANT 2


#define TILESIZE 96
#define OPEN_LIST_ELEMENTS 500
#define getParent(m) (m - 1) / 2

/// The generic class for our enemies. All types of enemies will inherit from this class
class Enemy : public Character
{
protected:
	bool xStepGoalReached;
	bool yStepGoalReached;
	bool m_bTryAttack;
	bool m_bAttacked;

	float m_fAttackRange;

	short m_shSoulsToDrop;
	std::vector<bool>* collisionMap;
	short m_HorizontalBitmapSize;
	short m_VerticalBitmapSize;
	std::vector<Vector2f*> m_Path;
	Vector2f* pathStep;
	Vector2f* m_pPlayerPos;

	short squaresChecked;			// total number of items added to the open list. 
	short tilesChecked;				// total number of items added to the closed list. 
	
	short onClosedList;
	short onOpenList;

	short numberOfOpenListItems;	// Number of items currently in the open list
	short current;
	short currentRow;
	short currentColumn;
	short goalTileY;
	short goalTileX;
	short parentXval;
	short parentYval;


	short pathLocation;
	short pathLength;
	short path;
		
	short openList[OPEN_LIST_ELEMENTS];
	short fCost[OPEN_LIST_ELEMENTS];
	short gCost[OPEN_LIST_ELEMENTS][OPEN_LIST_ELEMENTS];
	short openX[OPEN_LIST_ELEMENTS];
	short openY[OPEN_LIST_ELEMENTS];
	short parentX[OPEN_LIST_ELEMENTS][OPEN_LIST_ELEMENTS];
	short parentY[OPEN_LIST_ELEMENTS][OPEN_LIST_ELEMENTS];
	short whichList[OPEN_LIST_ELEMENTS][OPEN_LIST_ELEMENTS];

public:
	~Enemy();
	virtual void draw() = 0;
	virtual bool loadContent(Vector2f* playerPos) = 0;
	
	void update();
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	
	std::vector<Projectile*>* getProjectile( );
	
	short findPath(int startX, int startY, int goalX, int goalY);
	bool isDead();
	bool hasAttacked();
	void stopAttack();

	void insertIntoOpenList(short column, short row);
	void selectFromOpenList();
	void initializePathFind();

	short kill();
};