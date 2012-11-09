#include "Enemy.h"

/// Sets the collision map for the enemy, and the width and height of the world. Refers to memory address of the map inside the environment. 
void Enemy::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	m_HorizontalBitmapSize = horizontalSize;
	m_VerticalBitmapSize = collisionMap -> size() / horizontalSize;
	this -> collisionMap = collisionMap;
}

/// adds 10 for orthogonal movement, 14 for diagonal. Precalculating this avoids any 
/// decimal and square root calculations during runtime. The pythagorean theroem states that 
/// c^2 = b^2 + a^2, giving c = sqroot(1^2 + 1^2) = sqroot(2) as the answer.
/// The square root of 2 is 1.414, hence 14. 
#define ORTHOGONAL_MOVEMENT_COST 10;	// Orthogonal == horizontal || vertical. 
#define DIAGONAL_MOVEMENT_COST 14;

// C++ only defines null if any standard libraries are included. 
#ifndef NULL
#define NULL 0
#endif

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
Vector2f* Enemy::findPath(int startX, int startY, int goalX, int goalY)
{
	const short OPEN_LIST_ELEMENTS = 500;
	const short NUMBER_OF_TILES_TO_CHECK = 20;

	short openList[OPEN_LIST_ELEMENTS];

	short fCost[OPEN_LIST_ELEMENTS];
	short openX[OPEN_LIST_ELEMENTS];
	short openY[OPEN_LIST_ELEMENTS];

	short squaresChecked = 0;			// total number of items added to the open list. 
	short tilesChecked = 0;				// total number of items added to the closed list. 

	short numberOfOpenListItems = 0;	// Number of items currently in the open list
	short numberOfClosedListItems = 0;	// Number of items currently in the closed list

	short currentRow = startY / TILESIZE;
	short currentColumn = startX / TILESIZE;
	short currentPos = 0;						// Current position in collision vector (1D)

	short m = 0;
	short current = 0;
	short u = 1;	// Temporary bullshit variables... should be renamed to convey what they do. 
	short v = 1;
	short temp = 0;

	bool goalReached = false;
	bool placeInHeapFound = false;

	return new Vector2f(startX, startY);

	while(!goalReached && tilesChecked < NUMBER_OF_TILES_TO_CHECK)
	{
		

		// Deleting & Selecting

			current = openList[1];
			openList[1] = openList[numberOfOpenListItems];
			numberOfOpenListItems--;

			if(openX[current] == goalX / TILESIZE && openY[current] == goalY / TILESIZE)
			{
				goalReached = true;
			}


			placeInHeapFound = false;


			v = 1;
			
			while(!placeInHeapFound)			// Find the place in the heap for the element we moved. 
			{
				u = v;

				if(2 * u + 1 <= numberOfOpenListItems)	// if both children exists. 
				{
					if(fCost[openList[u]] >= fCost[openList[ 2 * u]])		// Check first child.
					{
						v = 2 * u;
					}
					
					if(fCost[openList[v]] >= fCost[openList[2 * u + 1]])	// Check second child.
					{
						v = 2 * u + 1;
					}
				}
				else if(2 * u <= numberOfOpenListItems)	// If only 1 child.
				{
					if(fCost[openList[u]] >= fCost[openList[ 2 * u]])		// Check first child.
					{
						v = 2 * u;
					}
				}


				if(u != v)					// If 'v' was changed, a swap is needed.
				{
					temp = openList[u];
					openList[u] = openList[v];
					openList[v] = temp;
				}
				else
				{
					placeInHeapFound = true;
				}
			}
			






		// insertion.

			squaresChecked++;
			numberOfOpenListItems++;
			openList[numberOfOpenListItems] = squaresChecked;

			m = numberOfOpenListItems;

			while(m > 1)
			{
				// Check if child is <= parent, if so, swap.
				if(fCost[openList[ m ]] <= fCost[openList[ m / 2 ]])
				{
					temp = openList[ m / 2 ];
					openList[ m / 2 ] = openList[ m ];
					openList[m] = temp;
				
					m = m / 2;
				}
				else
				{
					m = 0;
				}
			}

		// insertion end






	}

}











	//std::list<Point*> closedList;
	//std::list<Point*> openList;
	//std::list<Point*>::iterator it;

	//Point* openHeapList[400];

	//bool doNotCheck = false;

	//const short NUMBER_OF_TILES_TO_CHECK = 20;
	//short tilesChecked = 0;
	//
	//short currentRow = startY / TILESIZE;
	//short currentColumn = startX / TILESIZE;
	//short currentPos = 0;						// Current position in collision vector (1D)
	//short lowestFCost = 10000;
	//short tentativeGScore = 0;

	//Point* current = new Point(currentRow, currentColumn);
	//Point* goal = new Point(goalX / TILESIZE, goalY / TILESIZE);
	//Point* adjacent;

	//openList.push_back(current);
	//current -> inOpenList = true;
	//current -> findGCost();
	//current -> findFCost(goal);

	//while(!openList.empty() && tilesChecked < NUMBER_OF_TILES_TO_CHECK)
	//{
	//	lowestFCost = 100000;
	//	// Pick lowest FCost -- SLOOOOOW PART..
	//	for(it = openList.begin(); it != openList.end(); ++it)
	//	{
	//		short fCost = (*it) -> getFCost();

	//		if(fCost < lowestFCost)
	//		{
	//			lowestFCost = fCost;
	//			current = (*it);
	//		}
	//	}
	//	
	//	currentRow = current -> yPosition;
	//	currentColumn = current -> xPosition;

	//	std::cout << "Before: ";
	//	for(it = openList.begin(); it != openList.end(); ++it)
	//	{
	//		std::cout << (*it) -> xPosition << ", " << (*it) -> yPosition << ", " << (*it) -> inOpenList << ", " << (*it) -> inClosedList << " ... ";
	//	}

	//	openList.remove(current);

	//	std::cout << "\nAfter:  ";

	//	for(it = openList.begin(); it != openList.end(); ++it)
	//	{
	//		std::cout << (*it) -> xPosition << ", " << (*it) -> yPosition << ", " << (*it) -> inOpenList  << ", " << (*it) -> inClosedList << " ... ";
	//	}

	//	std::cout << "\n\n";

	//	char a;
	//	std::cin >> a;

	//	closedList.push_front(current);
	//	current -> inOpenList = false;
	//	current -> inClosedList = true;


	//	if(current == goal)
	//	{
	//		std::cout << "Does it ever go here?" << std::endl;
	//		return new Vector2f(current -> xPosition * TILESIZE, current -> yPosition * TILESIZE);
	//	}


	//	// Check all adjacent tiles. 
	//	for(int y = -1; y <= 1; ++y)
	//	{
	//		for(int x = -1; x <= 1; ++x)
	//		{
	//			if( !(x == 0 && y == 0) )		// If not self.
	//			{
	//				doNotCheck = false;

	//				// Check map boundaries. 
	//				if((currentRow == 0 && y == -1) || ( currentRow == m_VerticalBitmapSize && y == 1 ))
	//				{
	//					doNotCheck = true;
	//				}

	//				if(( currentColumn == 0 && x == -1 ) || ( currentColumn == m_HorizontalBitmapSize && x == 1 ))
	//				{
	//					doNotCheck = true;
	//				}


	//				if(!doNotCheck)
	//				{
	//					currentPos = ((currentRow + y) * m_HorizontalBitmapSize) + (currentColumn + x);

	//					//std::cout << currentPos << std::endl;
	//					if( (*collisionMap)[currentPos] )		// If walkable. 
	//					{
	//						adjacent = new Point(currentColumn + x, currentRow + y);
	//						adjacent -> setParent(current);

	//						if(!adjacent -> inClosedList)	// not in closed List
	//						{
	//							tentativeGScore = adjacent -> findGCost();

	//							if(!adjacent -> inOpenList || tentativeGScore <= adjacent -> getGCost())	// If not in openList
	//							{
	//								adjacent -> g_cost = tentativeGScore;
	//								adjacent -> findFCost(goal);

	//								if(!adjacent -> inOpenList)
	//								{
	//									openList.push_front(adjacent);
	//									adjacent -> inOpenList = true;
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}

	//	tilesChecked++;
	//}

	//return new Vector2f(10 * 96, 12 * 96);
