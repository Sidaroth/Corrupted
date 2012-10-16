#include "GameState.h"
#include "Environment.h"

class Level1 : public GameState
{
private:
	sf::Text text;
	sf::Font font;
	EnvironmentHandler* m_Level;
	sf::View m_Viewport;

public:
	Level1();
	~Level1();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};