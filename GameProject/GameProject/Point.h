//#pragma once
//
//#include "Vector2f.h"
//#include "Math.h"		// - abs
//
//
//
///// This class represents a point(node) on the tilemap (bitmap) used in A* pathfinding.
//class Point
//{
//public:
////	Vector2f m_Position;
//	short xPosition;
//	short yPosition;
//	Point* m_Parent;
//
//	short f_cost;
//	short g_cost;
//	short h_cost;
//
//	Point();
//	Point(int x, int y);
//	
//	void  setParent(Point* parent);
//	short findGCost();
//	short findHCost(Point* goal);
//	short findFCost(Point* goal);
//	Vector2f* findPosition();
//	
//	bool inOpenList;
//	bool inClosedList;
//
//	bool hasParent();
//
//	bool operator== (Point* point);
//
//	// GETTERS
//	//Point* getParent();
//	short getFCost();
//	short getGCost();
//	short getHCost();
//
//};