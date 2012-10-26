#include "GameState.h"

class Ui {

private:
	sf::Text text;
	sf::Font font;

public:
	Ui();
	~Ui();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};