#pragma once

#include "Enemy.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Skeleton : public Enemy
{
protected:

public:
	short test;
	Skeleton();
	void sayHello();
	void draw();
	void update();
	bool loadContent();
};