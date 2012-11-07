#pragma once

#include "SFML/Graphics.hpp"
#include "Character.h"
#include <list>
#include "Vector2f.h"
#include "Point.h"

#define TILESIZE 96
#define getParent(m) (m - 1) / 2

/// The generic class for our enemies. All types of enemies will inherit from this class
class Enemy : public Character
{
protected:
	short m_shSoulsToDrop;
	std::vector<bool>* collisionMap;
	short m_HorizontalBitmapSize;
	short m_VerticalBitmapSize;

public:
	virtual void sayHello() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool loadContent() = 0;
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	Vector2f* findPath(int startX, int startY, int goalX, int goalY);
};



//Point* openList[100 * 100];		// I hate arrays and their constant size QQ.
	//Point* closedList[9999];

	//short currentRow = startY / TILESIZE;
	//short currentColumn = startX / TILESIZE;
	//short currentPos = 0;

	//Point* start = new Point(currentColumn, currentRow);
	//Point* goal = new Point(goalX / TILESIZE, goalY / TILESIZE);

	//Point* adjacent;
	//Point* current;
	//Point* swapTemp;

	//bool goalReached = false;
	//bool placeFound = false;
	//bool swapNeeded = false;

	//short heapCurrent = 0;
	//short heapLowChild = 0;

	//short numberOfClosedListItems = 0;
	//short numberOfOpenListItems = 0;
	//short m = 0;
	//short parentPos = 0;
	//short tilesChecked = 0;
	//const short NUMBER_OF_TILES_TO_CHECK = 50;
	//
	//openList[0] = start;
	//numberOfOpenListItems++;
	//current = start;


	//while(!goalReached && tilesChecked < NUMBER_OF_TILES_TO_CHECK)
	//{
	//	/// CHECK ADJACENT TILES
	//	
	//	for(int y = -1; y <= 1; y++)
	//	{
	//		for(int x = -1; x <= 1; x++)
	//		{
	//			if(x == 0 && y == 0)		// IF NOT SELF. 
	//			{
	//				std::cout << "DERP" << std::endl;
	//			}
	//			else
	//			{
	//				currentPos = (currentRow + y) * m_HorizontalBitmapSize + (currentColumn + x);
	//				std::cout << "X, Y: " << x << ", " << y << std::endl;
	//				std::cout << "currPos: " << currentPos << std::endl;
	//				// NEED A FEW MORE CHECKS TO CHECK FOR EDGES OF THE MAP FIRST. 

	//				if( (*collisionMap)[currentPos])		// IF WALKABLE
	//				{
	//					adjacent = new Point(currentColumn + x, currentRow + y);
	//					adjacent -> setParent(current);
	//					adjacent -> findFCost(goal);										//	findFCost calculates the G, H and F cost of the tile. 
	//																	                    //	Add the adjacent, walkable tile to the openList.  

	//					std::cout << "Adjacent Pos (x,y): " << adjacent -> xPosition << ", " << adjacent -> yPosition << std::endl;
	//					m = numberOfOpenListItems;
	//					openList[numberOfOpenListItems++] = adjacent;

	//					while (m > 0)		// While the item hasn't reached the top. 
	//					{
	//						parentPos = getParent(m);
	//						

	//						if(openList[m] -> getFCost() <= openList[parentPos] -> getFCost())		// if the child is lesser than it's parent. Swap places. 
	//						{
	//							swapTemp = openList[parentPos];
	//							openList[parentPos];
	//							openList[m] = swapTemp;

	//							m = parentPos;
	//						}
	//						else
	//						{
	//							m = 0; // Force jump out of while. 
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	
	//	/// Picking lowest F cost / Removing from the heap (openList). 
	//	current = openList[0];
	//	currentColumn = current -> xPosition;
	//	currentRow = current -> yPosition;

	//	closedList[numberOfClosedListItems] = current;

	//	if(closedList[numberOfClosedListItems] == goal)
	//	{
	//		goalReached = true;
	//	}

	//	openList[0] = openList[numberOfOpenListItems - 1];

	//	numberOfClosedListItems++;
	//	numberOfOpenListItems--;

	//	

	//	heapCurrent = heapLowChild = 0;		// set current and child to root of binary heap.

	//	while(!placeFound)		// Until we find the apropriate place in the heap for the item
	//	{						// Moved to position 1. 
	//		if((2 * heapCurrent + 2) < numberOfOpenListItems) // If both children exist.
	//		{
	//			if((openList[heapCurrent] -> getFCost()) >= openList[2 * heapCurrent + 1] -> getFCost())
	//			{
	//				heapLowChild = 2 * heapCurrent + 1;		// 1st Child was lower. 
	//				swapNeeded = true;
	//			}

	//			if((openList[heapLowChild] -> getFCost()) >= openList[2 * heapCurrent + 2] -> getFCost())
	//			{
	//				heapLowChild = 2 * heapCurrent + 2;		// 2nd Child was lower. 
	//				swapNeeded = true;
	//			}
	//		}
	//		else if((2 * heapCurrent + 1) < numberOfOpenListItems)			// If only one child
	//		{
	//			if(openList[heapCurrent] >= openList[2 * heapCurrent + 1])
	//			{
	//				heapLowChild = 2 * heapCurrent + 1;
	//				swapNeeded = true;
	//			}
	//		}



	//		if(swapNeeded)
	//		{
	//			swapTemp = openList[heapCurrent];
	//			openList[heapCurrent] = openList[heapLowChild];
	//			openList[heapLowChild] = swapTemp;
	//			swapNeeded = false;
	//			heapCurrent = heapLowChild;
	//		}
	//		else
	//		{
	//			placeFound = true;
	//		}
	//	}
	//}

	///// rebuild Best path