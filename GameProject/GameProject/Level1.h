#include "GameState.h"
#include "Environment.h"
#include "Player.h"
#include "KeyboardController.h"

class Level1 : public GameState
{
private:
	sf::Text text;
	sf::Font font;
	EnvironmentHandler* m_Level;
	sf::View m_Viewport;
	Player* player;
	KeyboardController* keyControl;


public:
	Level1();
	~Level1();

	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);
};