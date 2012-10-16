#include "GameState.h"

class Level1 : public GameState
{
private:
	sf::Text text;
	sf::Font font;

public:
	Level1();
	~Level1();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};