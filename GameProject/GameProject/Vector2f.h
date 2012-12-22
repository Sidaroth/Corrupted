//																	  //
//	Purpose:	Implement a 2D vector in the MATHEMATICAL sense, not  //
//				in the dynamic array sense (as STL vector is)		  //
//	Author:		Christian Holt										  //
//	Created:	06/10/2012											  //
//  Revised:	26/11/2012											  //
//				22/12/2012											  //
//																	  //
////////////////////////////////////////////////////////////////////////


#pragma once		// Makes sure it is only included once per compile.

#include <math.h>

class Vector2f
{
public:		// Hmm private?
	float x;
	float y;

	 
	// Constructors & Destructor
	Vector2f();								// Default constructor that sets X and Y to 0. 
	Vector2f(float x, float y);				// Constructor that creates a vector with the given (X, Y).
	Vector2f(Vector2f const& copy_from_me);	// Copy constructor
	~Vector2f();							// Destructor. 

	// Vector Operators
	Vector2f operator+ (Vector2f vector);	// Returns the sum of the two vectors.
	Vector2f operator- (Vector2f vector);   // Returns the difference between the two vectors.
	Vector2f operator* (Vector2f vector);	// Returns the component-wise multiplication of the vectors
	Vector2f operator/ (Vector2f vector);	// Returns the component-wise division of the vectors
	void operator= (Vector2f vector);		// Sets the vector equal to the parameter vector. 

	// Scalar operators
	Vector2f operator* (float scalar);		// Returns the vector with all components multiplied by the scalar parameter
	Vector2f operator/ (float scalar);		// Returns the vector with all components divided by the scalar parameter
	void operator-= (float scalar);			// Subtracts the scalar from all components. 
	void operator+= (float scalar);			// Adds the scalar to all components.

	// products
	float dot (Vector2f vector);			// returns the DOT product between the the two vectors
	float cross(Vector2f vector);			// Returns the CROSS product between the two vectors

	// Lengths
	float length();							// returns the length of the vector
	Vector2f unit();						// Returns a vector pointing in the same direction, but with unit length (lenght of 1)
	float squaredLength();					// Returns the square of the length of the vector. Useful when you just want to compare two vectors
											// to see which is longest, as this avoids computing the square roots. 

	// Rotation and angle
											// NOTE: turn functions assume y-axis points up, otherwise they switch meaning (left = right, right = left)
	Vector2f turnLeft();					// Returns the vector rotated 90 degrees to the left. Useful for computing normals.
	Vector2f turnRight();					// Returns the vector rotated 90 degrees to the right. Useful for computing normals. 
	Vector2f rotate(float angle);			// Rotates the vector by the specified angle.
	float angle();							// Returns the angle that the vector points to.
};