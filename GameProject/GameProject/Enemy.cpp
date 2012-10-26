#include "Enemy.h"

/// Pathfinding algorithm (A*)
std::vector<Vector2f*> Enemy::findPath(Vector2f* startPos, Vector2f* goalPos)
{
	std::vector<Vector2f*> finalPath;

	Point* start = new Point(*startPos);
	Point* goal = new Point(*goalPos);
	Point* current;
	Point* child;
	bool goalReached = false;

	std::list<Point*> openList;
	std::list<Point*> closedList;
	std::list<Point*>::iterator i;

	/// The number of loops to try before returning a sub-optimal solution.
	unsigned const short NUMBER_OF_LOOPS = 50;
	unsigned short loopsSoFar = 0;

	// Add the start node to the openlist
	openList.push_back(start);
	start -> opened = true;

	while(!goalReached && loopsSoFar < NUMBER_OF_LOOPS)
	{
		for(i = openList.begin(); i != openList.end(); i++)
		{
			if(i == openList.begin())
			{
				current = (*i);
			}
				
		}

		if(current == goal)
		{
			goalReached = true;
		}

		openList.remove(current);
		current -> opened = false;

		closedList.push_back(current);
		current -> closed = true;

		// Get all walkable adjacent points X
		// XXX
		// XOX
		// XXX		- O being the center / current
		for(int x = -1; x <= 1; x++)
		{
			for(int y = -1; y <= 1; y++)
			{
				if(x == 0 && y == 0)
				{
					continue;
				}
			}
		}
	}


	return finalPath;
}


