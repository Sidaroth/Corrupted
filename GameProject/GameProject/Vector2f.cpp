#include "Vector2f.h"

////////////////////// CONSTRUCTORS & DESTRUCTOR ///////////////////////

/// Default constructor that sets X and Y to 0.  PRIVATE??
Vector2f::Vector2f()
{
	x = 0;
	y = 0;
}

/// Constructor that creates a vector with the given (X, Y). Could be coordinate (X, Y) 
Vector2f::Vector2f(float newX, float newY)
{
	x = newX;
	y = newY;
}

Vector2f::Vector2f(Vector2f const& copy_from_me)
{
	x = copy_from_me.x;
	y = copy_from_me.y;
}

Vector2f::~Vector2f()
{
	// Nothing?
}

////////////////////// VECTOR OPERATORS ///////////////////////

/// Returns the sum of the two vectors.
Vector2f Vector2f::operator+ (Vector2f vect)
{
	return Vector2f(x + vect.x, y + vect.y);
}

/// Returns the difference between the two vectors.
Vector2f Vector2f::operator- (Vector2f vect)
{
	return Vector2f(x - vect.x, y - vect.y);
}

/// Returns the component-wise multiplication of the vectors
Vector2f Vector2f::operator* (Vector2f vect)
{
	return Vector2f(x * vect.x, y * vect.y);
}

/// Returns the component-wise division of the vectors
Vector2f Vector2f::operator/ (Vector2f vect)
{
	return Vector2f(x / vect.x, y / vect.y);
}

/// Sets the vector equal to the parameter vector. 
void Vector2f::operator= (Vector2f vect)
{
	x = vect.x;
	y = vect.y;
}

////////////////////// SCALAR OPERATORS ///////////////////////

/// Returns the vector with all components multiplied by the scalar parameter
Vector2f Vector2f::operator* (float scalar)
{
	return Vector2f(x * scalar, y * scalar); 
}

/// Returns the vector with all components divided by the scalar parameter
Vector2f Vector2f::operator/ (float scalar)
{
	return Vector2f(x / scalar, y / scalar);
}

/// Subtracts the scalar from all components. 
void Vector2f::operator-= (float scalar)
{
	x = x - scalar;
	y = y - scalar;
}

/// Adds the scalar to all components.
void Vector2f::operator+= (float scalar)
{
	x = x + scalar;
	y = y + scalar;
}




////////////////////// PRODUCTS ///////////////////////

/// returns the DOT product between the the two vectors
float Vector2f::dot (Vector2f vect)
{
	return (x * vect.x + y * vect.y);
}

/// Returns the CROSS product between the two vectors
float Vector2f::cross (Vector2f vect)
{
	return (x * vect.y + y * vect.x);
}



////////////////////// LENGTHS ///////////////////////

/// returns the length of the vector
float Vector2f::length()
{
	return sqrt(x * x + y * y);
}

/// Returns the square of the length of the vector. Useful when you just want to compare two vectors
/// to see which is longest, as this avoids computing the square roots. 
float Vector2f::squaredLength()
{
	return (x * x + y * y);
}

/// Returns a vector pointing in the same direction, but with unit length (lenght of 1)
Vector2f Vector2f::unit()
{
	float length = sqrt(x * x + y * y);
	return Vector2f(x / length, y / length);
}



////////////////////// ROTATION AND ANGLE ///////////////////////

/// NOTE: turn functions assume y-axis points up, otherwise they switch meaning (left = right, right = left)
/// Returns the vector rotated 90 degrees to the left. Useful for computing normals.
Vector2f Vector2f::turnLeft()
{
	return Vector2f(-y, x);
}

/// Returns the vector rotated 90 degrees to the right. Useful for computing normals. 
Vector2f Vector2f::turnRight()
{
	return Vector2f(y, -x);
}

/// Rotates the vector by the specified angle. This is equvivalent to multiplying by the 2x2 rotation matrix.
Vector2f Vector2f::rotate(float angle)
{
	float newX = x * cos(angle) - y * sin(angle);
	float newY = x * sin(angle) + y * cos(angle);

	return Vector2f(newX, newY);
}

/// Returns the angle that the vector points to.
/// Note: atan2 Computes arc tangent with two parameters
float Vector2f::angle()
{
	return atan2(y, x);
}