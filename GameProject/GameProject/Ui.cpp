#include "Ui.h"

Ui::Ui()
{
	// We'll see..
}

bool Ui::loadContent()
{
	if(!m_uiBackground.loadFromFile("../../Resources/GUI.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_view.reset(sf::FloatRect(0, 0, 1366, 768));

	m_uiBackgroundSprite.setTexture(m_uiBackground);
	m_uiBackgroundSprite.setPosition(0, 0);

	titleText.setPosition(100, 50);
	titleText.setString("THIS IS THE CURRENT GUI");
	titleText.setFont(font);
}

void Ui::unloadContent()
{

}

void Ui::update()
{
	
}

void Ui::draw(sf::RenderWindow &window)
{
	window.setView(m_view);

	window.draw(titleText);
	window.draw(m_uiBackgroundSprite);

	window.setView(window.getDefaultView());
}