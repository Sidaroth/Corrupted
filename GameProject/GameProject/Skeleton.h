#pragma once

#include "Enemy.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Skeleton : public Enemy
{
protected:

public:
	Skeleton(std::vector<sf::Texture>* textures);
	~Skeleton();
	void draw();
	void update(Vector2f* playerPos);
	bool loadContent();
};