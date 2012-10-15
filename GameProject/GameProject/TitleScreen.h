#include "GameState.h"

class TitleScreen : public GameState
{
private:
	sf::Text text;
	sf::Font font;

public:
	TitleScreen();
	~TitleScreen();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};