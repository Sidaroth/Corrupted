#pragma once

#include "Enemy.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Skeleton : public Enemy
{
protected:

public:
	Skeleton(std::vector<sf::Texture>* textures, short level);
	~Skeleton();
	void draw();
	bool loadContent(Vector2f* playerPos);

	//void update();
};