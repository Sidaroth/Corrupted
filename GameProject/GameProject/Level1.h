#pragma once

#include "StateHandler.h"
#include "SuperLevel.h"

class Level1 : public SuperLevel
{
private:
	

public:
	Level1();
	~Level1();

	void loadContent();
	/*
	void unloadContent();	
	void processEvents(sf::Event event);
	void update();
	*/
	void draw();
};