#include "Point.h"
#include <iostream>


Point::Point()
{
	m_Parent = NULL;

	f_cost = g_cost = h_cost = 0;

	//m_Position.x = 0;
	//m_Position.y = 0;

	xPosition = 0;
	yPosition = 0;
}

Point::Point(int x, int y)
{
	m_Parent = NULL;

	f_cost = g_cost = h_cost = 0;


	
	xPosition = x;
	yPosition = y;

	//std::cout << xPosition << ", " << yPosition << std::endl;


	//m_Position.x = x;
	//m_Position.y = y;
}

/// Calculates the G Cost (distance from the start) 
short Point::findGCost()
{
	if(m_Parent != NULL)
	{
		if(xPosition != m_Parent -> xPosition && yPosition != m_Parent -> yPosition)		// If not on the same row or column - means the move was diagonal. 
		{
			return m_Parent -> g_cost + DIAGONAL_MOVEMENT_COST;
		}
		else
		{
			return m_Parent -> g_cost + ORTHOGONAL_MOVEMENT_COST;
		}
	}
	
	return -1;
}

/// Calculates the H Cost (distance to the goal - Manhattan style) abs is used so it works "both ways"
/// Manhattan style means NO diagonal movement and ignoring walls in between. This may result in the heuristic overestimating 
// (Will look into other heuristics functions later)
short Point::findHCost(Point* goal)
{
	if(goal != NULL)
	{
		short horizontalDistance = abs(goal -> xPosition - xPosition);
		short verticalDistance = abs(goal -> yPosition - yPosition);
		
		return (horizontalDistance + verticalDistance) * ORTHOGONAL_MOVEMENT_COST;
	}

	return -1;
}

/// Calculates the F cost (The cost of moving to this node, in essence the heuristic(H) + path-cost so far(G)
short Point::findFCost(Point* goal)
{
	g_cost = findGCost();
	h_cost = findHCost(goal);
	f_cost = g_cost + h_cost;

	return f_cost;
}


/// Checks if the point(node) has a parent. Used in backtracking / recreating the best path.
bool Point::hasParent()
{
	return m_Parent != NULL;
}

/// Finds the position on the tileset (hence the 96.0f - Tilesize)
Vector2f* Point::findPosition()
{
	return 0; //new Vector2f(m_Position.x * 96.0f, m_Position.y * 96.0f);
}

void Point::setParent(Point* parent)
{
	m_Parent = parent;
}

////////////////// GETTERS ////////////////////
Point* Point::getParent()
{
	return m_Parent;
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

