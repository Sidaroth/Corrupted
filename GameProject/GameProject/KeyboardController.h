#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include "Player.h"
#include <vector>
#include <math.h>

#pragma once

class KeyboardController 
{
private:
	
	Player* player;
	std::string moveFowardKey;
	std::string moveBackwardKey;
	std::string moveLeftKey;
	std::string moveRIghtKey;
	std::string spaceKey;

	enum InputType
	{
		KeyboardInput,
		MouseInput,
		JoystickInput 
	};

	struct MyKeys
	{
		InputType myInputType;
		sf::Event::EventType myEventType;
		sf::Keyboard::Key myKeyCode;
		sf::Mouse::Button myMouseButton;
	};

	std::map<std::string,MyKeys> Keys;

public:

	void checkPressed();
	void setKeyToAction (MyKeys,std::string action);
	void setMoveFowardKey(char key);
	void setMoveBackwardKey(char key);
	void setMoveLeftKey(char key);
	void setMoveRightKey(char key);
	void getMoveFowardKey(char key);
	void getMoveBackwardKey(char key);
	void getMoveLeftKey(char key);
	void getMoveRightKey(char key);
	bool loadXML();
	KeyboardController(Player* player);
};