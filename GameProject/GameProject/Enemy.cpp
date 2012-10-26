#include "Enemy.h"

/// Pathfinding algorithm (A*)
std::vector<Vector2f*> Enemy::findPath(Vector2f* startPos, Vector2f* goalPos)
{
	std::vector<Vector2f*> finalPath;

	Point* start = new Point(*startPos);
	Point* goal = new Point(*goalPos);
	Point* current;
	Point* child;
	bool endReached = false;

	std::list<Point*> openList;
	std::list<Point*> closedList;
	std::list<Point*>::iterator i;

	/// The number of loops to try before returning a sub-optimal solution.
	unsigned const short NUMBER_OF_LOOPS = 50;
	unsigned short loopsSoFar = 0;

	// Add the start node to the openlist
	openList.push_back(start);
	start -> opened = true;

	while(!endReached && loopsSoFar < NUMBER_OF_LOOPS)
	{

	}

	return finalPath;
}


