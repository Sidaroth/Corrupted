#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <stdlib.h>
#include <iostream>

#pragma once
 
// Making this as a singleton.. Might not be the best approach. (Static class?)

class Game
{
private:

	static Game* m_gameInstance;
	Game();

	sf::RenderWindow m_Window;
	std::string m_sTitle;
	int m_iScreenWidth;
	int m_iScreenHeight;
	int m_iScreenBitColor;
	bool m_bRunning;

	void stop();
	void run();
	void tick();
	void initialize();
	void deInitialize();
	void render(sf::Text text);
	void processEvents();

public:
	static Game* getInstance();
	void start();
};