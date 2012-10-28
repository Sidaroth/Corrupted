#include "Enemy.h"

/// Sets the collision map for the enemy, and the width and height of the world. Refers to memory address of the map inside the environment. 
void Enemy::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	m_HorizontalBitmapSize = horizontalSize;
	m_VerticalBitmapSize = collisionMap -> size() / horizontalSize;
	this -> collisionMap = collisionMap;
}



/// Pathfinding algorithm (A*) using a Binary Heap representation of the openList. 
	/*!
	 Given a tileset:
	 | 0,0 | 1,0 | 2,0 | 3,0 | 4,0 |
	 | 0,1 | 1,1 | 2,1 | 3,1 | 4,1 |
	 | 0,2 | 1,2 | 2,2 | 3,2 | 4,2 |
	 | 0,3 | 1,3 | 2,3 | 3,3 | 4,3 |
	 | 0,4 | 1,4 | 2,4 | 3,4 | 4,4 |
	 
	 Represented as a 1D array this will look like (Row0 Row1 Row2 Row3 etc.)
	 (0,0), (1,0), (2,0), (3,0), (4,0), (0,1), (1,1), (2,1), (3,1), (4,1), (0,2), (1,2), (2,2), (3,2), (4,2)

	 We can find the coordinate position in the array by doing (row * horizontalSize + column).
	 Example: if the position we want is (2, 1) we can find it in the array by doing 1 * 5 + 2 = 7 (For humans this would be 8, but as programmers we count from 0)
	 Example2: if the position we want is (3,0) we can find it in the array by doing 0 * 5 + 3 = 3 (For humans this would be 4, but as programmers we count from 0)

	*/
std::vector<Vector2f*> Enemy::findPath(int startX, int startY, int goalX, int goalY)
{
	std::vector<Vector2f*> finalPath;
	finalPath.reserve(40);

	Point* openList[32 * 32];		// I hate arrays and their constant size QQ. 

	short currentRow = startY / TILESIZE;
	short currentColumn = startX / TILESIZE;
	short currentPos = 0;

	Point* start = new Point(currentColumn, currentRow);
	Point* goal = new Point(goalX / TILESIZE, goalY / TILESIZE);
	Point* current;

	short squaresChecked = 0;
	short numberOfOpenListItems = 0;

	
	openList[numberOfOpenListItems++] = start;
	squaresChecked += 1;

	
	for(int y = -1; y <= 1; y++)
	{
		for(int x = -1; x <= 1; x++)
		{
			if(x != 0 && y != 0)		// IF NOT SELF. 
			{
				currentPos = (currentRow + y) * m_HorizontalBitmapSize + (currentColumn + x);
				
				std::cout << (*collisionMap)[currentPos] << std::endl;
				if( (*collisionMap)[currentPos])		// IF WALKABKE
				{
					// INSERT
				}
			}
		}
	}

	

	// Find all childs
	// insert all childs

	// Deleting / picking lowest F cost.

	// rebuild fastest path


//	Let n be the number of elements in the heap and i be an arbitrary valid index of the array storing the heap. If the tree root is at index 0, with valid indices 0 through n-1, then each element a[i] has
//children a[2i+1] and a[2i+2]
//parent a[floor((i−1)/2)]


	return finalPath;
}


//
//
//	Point* start = new Point(*startPos);
//	Point* goal = new Point(*goalPos);
//	Point* current;
//	Point* child;
//	bool goalReached = false;
//
//	std::list<Point*> openList;
//	std::list<Point*> closedList;
//	std::list<Point*>::iterator i;
//
//	/// The number of loops to try before returning a sub-optimal solution.
//	unsigned const short NUMBER_OF_LOOPS = 50;
//	unsigned short loopsSoFar = 0;
//
//	// Add the start node to the openlist
//	openList.push_back(start);
//	start -> opened = true;
//
//	while(!goalReached && loopsSoFar < NUMBER_OF_LOOPS)
//	{
//		for(i = openList.begin(); i != openList.end(); i++)
//		{
//			if(i == openList.begin())
//			{
//				current = (*i);
//			}
//				
//		}
//
//		if(current == goal)
//		{
//			goalReached = true;
//		}
//
//		openList.remove(current);
//		current -> opened = false;
//
//		closedList.push_back(current);
//		current -> closed = true;
//
//		// Get all walkable adjacent points X
//		// XXX
//		// XOX
//		// XXX		- O being the center / current
//		for(int y = -1; y <= 1; y++)
//		{
//			for(int x = -1; x <= 1; x++)
//			{
//				if(x == 0 && y == 0)
//				{
//					continue;
//				}
//
//
//
//			}
//		}
//	}
//
//
//	