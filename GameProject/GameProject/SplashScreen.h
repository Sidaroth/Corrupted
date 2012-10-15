#include "GameState.h"

class SplashScreen : public GameState
{
private:
	sf::String text;
	sf::Font font;

public:
	SplashScreen();
	~SplashScreen();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};