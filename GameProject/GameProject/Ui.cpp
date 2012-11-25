#include "Ui.h"



Ui::Ui()
{
	m_shFrameCount = 0;
}

bool Ui::loadContent()
{
	sf::Image maskingImage;
	

	if(!m_uiBackground.loadFromFile("../../Resources/GUI.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!maskingImage.loadFromFile("../../Resources/healthDiamond.PNG"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor(sf::Color(0, 0, 0), 0);
	m_healthDiamond.loadFromImage(maskingImage);

	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_view.reset(sf::FloatRect(0, 0, 1366, 768));

	m_uiBackgroundSprite.setTexture(m_uiBackground);
	m_uiBackgroundSprite.setPosition(0, 0);

	m_healthDiamondSprite.setTexture(m_healthDiamond);
	m_healthDiamondSprite.setPosition(125, 650);
	m_healthDiamondSprite.setOrigin(50, 50);


	rightSideText.setPosition(1085, 583);
	rightSideText.setString("Strength: \nIntelligence: \nToughness: \nSpeed: \n\nMelee Damage: \nSpell Damage\nCritical Chance: ");
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

	healthText.setPosition(95, 710);
	healthText.setScale(0.7, 0.7);
	healthText.setFont(font);
	return !EXIT_FAILURE;
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
								numberToString(m_player->getSpeed())+"\n\n\t\t"+
								numberToString(m_player->getMeleeDamage())+"\n\t\t"+
								numberToString(m_player->getSpellDamage())+"\n\t\t"+
								numberToString(m_player->getCriticalChance())+"%");

	rightSideSecondaryStats.setString(numberToString(m_player->getCurrentSouls())+"\n\n"+
										numberToString(m_player->getWeaponLevel())+"\n"+
										numberToString(m_player->getArmorLevel()));

	healthText.setString(numberToString(m_player->getCurrentHealth())+" / " +
							numberToString(m_player->getMaxHealth())); 


	healthRotation = (105 - (m_player->getCurrentHealth()/m_player->getMaxHealth()*100));
	m_shFrameCount += 1;

	if(m_shFrameCount % healthRotation == 0)
	{
		m_healthDiamondSprite.rotate(healthRotation);
	}
	
}

void Ui::draw()
{
	StateHandler::getInstance().m_pWindow->setView(m_view);

	StateHandler::getInstance().m_pWindow->draw(m_uiBackgroundSprite);
	StateHandler::getInstance().m_pWindow->draw(m_healthDiamondSprite);
	StateHandler::getInstance().m_pWindow->draw(rightSideText);
	StateHandler::getInstance().m_pWindow->draw(rightSideStats);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryText);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryStats);
	StateHandler::getInstance().m_pWindow->draw(healthText);
}

template <typename T>
  std::string numberToString ( T Number )
  {
	 std::ostringstream ss;
	 ss << Number;
	 return ss.str();
  }