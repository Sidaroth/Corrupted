#include "Point.h"

Point::Point()
{
	parent = NULL;
	closed = false;
	opened = false;

	f_cost = g_cost = h_cost = 0;
	position.x = 0;
	position.y = 0;
}

Point::Point(Vector2f position)
{
	parent = NULL;
	closed = false;
	opened = false;

	f_cost = g_cost = h_cost = 0;
	position.x = 0;
	position.y = 0;

	this -> position.x = position.x;
	this -> position.y = position.y;
}

Point::Point(Vector2f position, bool walkable)
{
	parent = NULL;
	closed = false;
	opened = false;

	f_cost = g_cost = h_cost = 0;
	position.x = 0;
	position.y = 0;

	this -> position.x = position.x;
	this -> position.y = position.y;

	this -> walkable = walkable;
}

/// Calculates the G Cost (distance from the start) 
short Point::findGCost(Point* parent)
{
	if(position.x == parent -> position.x || position.y == parent -> position.y)
	{
		return parent -> g_cost + ORTHOGONAL_MOVEMENT_COST;
	}
	else
	{
		return parent -> g_cost + DIAGONAL_MOVEMENT_COST;
	}
}

/// Calculates the H Cost (distance to the goal - Manhattan style) abs is used so it works "both ways"
/// Manhattan style means NO diagonal movement and ignoring walls in between. This may result in the heuristic overestimating 
// (Will look into other heuristics functions later)
short Point::findHCost(Point* goal)
{
	short horizontalDistance = abs(goal -> position.x - position.x);
	short verticalDistance = abs(goal -> position.y - position.y);
	return horizontalDistance + verticalDistance * ORTHOGONAL_MOVEMENT_COST;
}

/// Calculates the F cost (The cost of moving to this node, in essence the heuristic(H) + path-cost so far(G)
short Point::findFCost(Point* goal)
{
	g_cost = findGCost(parent);
	h_cost = findHCost(goal);
	f_cost = g_cost + h_cost;
	return f_cost;
}


/// Checks if the point(node) has a parent. Used in backtracking / recreating the best path.
bool Point::hasParent()
{
	return parent != NULL;
}

/// Finds the position on the tileset (hence the 96.0f - Tilesize)
Vector2f* Point::findPosition()
{
	return new Vector2f(position.x * 96.0f, position.y * 96.0f);
}

////////////////// GETTERS ////////////////////
Point* Point::getParent()
{
	return parent;
}

short Point::getFCost()
{
	return f_cost;
}

short Point::getGCost()
{
	return g_cost;
}

short Point::getHCost()
{
	return h_cost;
}

