#pragma once

#include "Enemy.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Skeleton : public Enemy
{
protected:

public:
	Skeleton();
	void sayHello();
	void draw(sf::RenderWindow &window);
	void update();
	bool loadContent();
};