#include "Enemy.h"

/// Sets the collision map for the enemy, and the width and height of the world. Refers to memory address of the map inside the environment. 
void Enemy::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	m_HorizontalBitmapSize = horizontalSize;
	m_VerticalBitmapSize = collisionMap -> size() / horizontalSize;
	this -> collisionMap = collisionMap;
}

	/*!
	 Pathfinding algorithm (A*) using a Binary Heap representation of the openList. 

	 Given a tileset:
	 | 0,0 | 1,0 | 2,0 | 3,0 | 4,0 |
	 | 0,1 | 1,1 | 2,1 | 3,1 | 4,1 |
	 | 0,2 | 1,2 | 2,2 | 3,2 | 4,2 |
	 | 0,3 | 1,3 | 2,3 | 3,3 | 4,3 |
	 | 0,4 | 1,4 | 2,4 | 3,4 | 4,4 |
	 
	 Represented as a 1D array this will look like (Row0 Row1 Row2 Row3 etc.)
	 (0,0), (1,0), (2,0), (3,0), (4,0), (0,1), (1,1), (2,1), (3,1), (4,1), (0,2), (1,2), (2,2), (3,2), (4,2), (0,3), (1,3), (2,3), (3,3), (4,3), (0,4), (1,4), (2,4), (3,4), (4,4) 

	 We can find the coordinate position in the array by doing (row * horizontalSize + column).
	 Example: if the position we want is (2, 1) we can find it in the array by doing 1 * 5 + 2 = 7 (For humans this would be 8, but as programmers we count from 0)
	 Example2: if the position we want is (3,0) we can find it in the array by doing 0 * 5 + 3 = 3 (For humans this would be 4, but as programmers we count from 0)
	 Example3: if the position we want is (3,4) we can find it in the array by doing 4 * 5 + 3 = 23 (For humans this would be 24, but as programmers we count from 0)


	 Let n be the number of elements in the heap and i be an arbitrary valid index of the array storing the heap. If the tree root is at index 0, with valid indices 0 through n-1, then each element a[i] has
	 children a[2i+1] and a[2i+2]
	 parent   a[floor((i−1)/2)]			- Flooring is just getting the integer value of a number. 

	*/
std::vector<Vector2f*> Enemy::findPath(int startX, int startY, int goalX, int goalY)
{
	std::vector<Vector2f*> finalPath;
	finalPath.reserve(40);

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

	return finalPath;
}
