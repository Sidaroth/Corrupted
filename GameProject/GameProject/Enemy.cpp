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
Vector2f* Enemy::findPath(int startX, int startY, int goalX, int goalY)
{
	Vector2f* finalPath;
	std::list<Point*> closedList;
	std::list<Point*> openList;
	std::list<Point*>::iterator it;

	Point* openHeapList[400];

	bool goalReached = false;
	bool doNotCheck = false;

	const short NUMBER_OF_TILES_TO_CHECK = 30;
	short tilesChecked = 0;
	
	short currentRow = startY / TILESIZE;
	short currentColumn = startX / TILESIZE;
	short currentPos = 0;						// Current position in collision vector (1D)
	short lowestFCost = 10000;
	short tentativeGScore = 0;

	Point* current = new Point(currentRow, currentColumn);
	Point* goal = new Point(goalX / TILESIZE, goalY / TILESIZE);
	Point* adjacent;

	openList.push_back(current);
	current -> inOpenList = true;
	current -> findGCost();
	current -> findFCost(goal);


	while(!openList.empty() && tilesChecked < NUMBER_OF_TILES_TO_CHECK)
	{
		// Pick lowest FCost
		for(it = openList.begin(); it != openList.end(); ++it)
		{
			short fCost = (*it) -> getFCost();

			if(fCost < lowestFCost)
			{
				lowestFCost = fCost;
				current = (*it);
				std::cout << current -> xPosition << ", " << current -> yPosition << std::endl;
			}
		}

	
		//std::cout << "Tiles: " << tilesChecked << std::endl;
		if(current == goal)
		{
			std::cout << "Does it ever go here?" << std::endl;
			it = closedList.end();
			return new Vector2f( (*it) -> xPosition * TILESIZE, (*it) -> yPosition * TILESIZE );
		}
		
		currentRow = current -> yPosition;
		currentColumn = current -> xPosition;
		
		openList.remove(current);
		closedList.push_front(current);
		current -> inOpenList = false;
		current -> inClosedList = true;

		tilesChecked++;

		// Check all adjacent tiles. 
		for(int y = -1; y <= 1; ++y)
		{
			for(int x = -1; x <= 1; ++x)
			{
				if( !(x == 0 && y == 0) )		// If not self.
				{
					doNotCheck = false;

					// Check map boundaries. 
					if((currentRow == 0 && y == -1) || ( currentRow == m_VerticalBitmapSize && y == 1 ))
					{
						doNotCheck = true;
					}

					if(( currentColumn == 0 && x == -1 ) || ( currentColumn == m_HorizontalBitmapSize && x == 1 ))
					{
						doNotCheck = true;
					}


					if(!doNotCheck)
					{
						currentPos = ((currentRow + y) * m_HorizontalBitmapSize) + (currentColumn + x);

						//std::cout << currentPos << std::endl;
						if( (*collisionMap)[currentPos] )		// If walkable. 
						{
							adjacent = new Point(currentColumn + x, currentRow + y);
							adjacent -> setParent(current);

							if(!adjacent -> inClosedList)	// not in closed List
							{
								tentativeGScore = adjacent -> findGCost();

								if(!adjacent -> inOpenList || tentativeGScore <= adjacent -> getGCost())	// If not in openList
								{
									// Came from?
									adjacent -> g_cost = tentativeGScore;
									adjacent -> findFCost(goal);

									if(!adjacent -> inOpenList)
									{
										openList.push_front(adjacent);
										adjacent -> inOpenList = true;
									}
								}	
							}
						}
					}
				}
			}
		}
	}

	return new Vector2f(0, 0);
}

