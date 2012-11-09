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

	rightSideText.setPosition(1085, 583);
	rightSideText.setString("Strength: \nIntelligence: \nToughness: \nSpeed: ");
	rightSideText.setScale(0.5, 0.5);
	rightSideText.setFont(font);

	rightSideSecondaryText.setPosition(1225, 583);
	rightSideSecondaryText.setString("Souls: \n\nWeapon Level: \nArmor Level: ");
	rightSideSecondaryText.setScale(0.5, 0.5);
	rightSideSecondaryText.setFont(font);

	rightSideStats.setPosition(1185, 583);
	rightSideStats.setScale(0.5, 0.5);
	rightSideStats.setFont(font);

	rightSideSecondaryStats.setPosition(1325, 583);
	rightSideSecondaryStats.setScale(0.5, 0.5);
	rightSideSecondaryStats.setFont(font);
}

void Ui::unloadContent()
{

}

void Ui::update(Player* player)
{
	m_player = player;

	rightSideStats.setString(numberToString(m_player->getStrength())+"\n"+
								numberToString(m_player->getIntelligence())+"\n"+
								numberToString(m_player->getToughness())+"\n"+
								numberToString(m_player->getSpeed()));

	//rightSideSecondaryStats.setString(numberToString(m_player->getCurrentSouls())+"\n\n"+
	//									numberToString(m_player->getWeaponLevel())+"\n"+
	//									numberToString(m_player->getArmorLevel()));
}

void Ui::draw()
{
	StateHandler::getInstance().m_pWindow->setView(m_view);

	StateHandler::getInstance().m_pWindow->draw(m_uiBackgroundSprite);
	StateHandler::getInstance().m_pWindow->draw(rightSideText);
	StateHandler::getInstance().m_pWindow->draw(rightSideStats);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryText);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryStats);
}

template <typename T>
  std::string numberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }