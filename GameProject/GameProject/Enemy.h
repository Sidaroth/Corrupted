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
	short m_shSoulsToDrop;
	std::vector<bool>* collisionMap;
	short m_HorizontalBitmapSize;
	short m_VerticalBitmapSize;
	std::vector<Vector2f*> m_Path;
	Vector2f* pathStep;

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

public:
	virtual void sayHello() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool loadContent() = 0;
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	
	std::vector<Projectile*>* getProjectile( );
	

	short findPath(int startX, int startY, int goalX, int goalY);

	void insertIntoOpenList(short column, short row);
	void selectFromOpenList();
	void initializePathFind();
};