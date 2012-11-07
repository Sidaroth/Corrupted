#pragma once

#include "Vector2f.h"
#include "Math.h"		// - abs

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

/// This class represents a point(node) on the tilemap (bitmap) used in A* pathfinding.
class Point
{
public:
//	Vector2f m_Position;
	short xPosition;
	short yPosition;
	Point* m_Parent;

	short f_cost;
	short g_cost;
	short h_cost;

	Point();
	Point(int x, int y);
	
	void  setParent(Point* parent);
	short findGCost();
	short findHCost(Point* goal);
	short findFCost(Point* goal);
	Vector2f* findPosition();
	
	bool inOpenList;
	bool inClosedList;

	bool hasParent();

	//bool operator== (Point* point);

	// GETTERS
	//Point* getParent();
	short getFCost();
	short getGCost();
	short getHCost();

};