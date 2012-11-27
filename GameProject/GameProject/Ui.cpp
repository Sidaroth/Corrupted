#include "Ui.h"



Ui::Ui()
{
	m_shFrameCount = 0;
	for (int i = 0; i <= 5; i++) {
		increasable[i] = false;
	}
	
}

Ui::~Ui()
{
	delete m_player;
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

	if(!m_increaseButtonGray.loadFromFile("../../Resources/increaseButtonGray.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!m_increaseButtonRed.loadFromFile("../../Resources/increaseButtonRed.PNG"))
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

	for (int i = 0; i <= 5; i++) {
		increaseButtonSpriteArray[i].setTexture(m_increaseButtonGray);
	}
	increaseButtonSpriteArray[0].setPosition(1200, 586);
	increaseButtonSpriteArray[1].setPosition(1200, 608);
	increaseButtonSpriteArray[2].setPosition(1200, 631);
	increaseButtonSpriteArray[3].setPosition(1200, 652);
	increaseButtonSpriteArray[4].setPosition(1345, 631);
	increaseButtonSpriteArray[5].setPosition(1345, 652);


	rightSideText.setPosition(1085, 583);
	rightSideText.setString("Strength: \nIntelligence: \nToughness: \nSpeed: \n\nMelee Damage: \nSpell Damage\nCritical Chance: ");
	rightSideText.setScale(0.6, 0.6);
	rightSideText.setFont(font);

	rightSideSecondaryText.setPosition(1225, 583);
	rightSideSecondaryText.setString("Souls: \n\nWeapon Level: \nArmor Level: ");
	rightSideSecondaryText.setScale(0.6, 0.6);
	rightSideSecondaryText.setFont(font);

	rightSideStats.setPosition(1185, 583);
	rightSideStats.setScale(0.6, 0.6);
	rightSideStats.setFont(font);

	rightSideSecondaryStats.setPosition(1333, 583);
	rightSideSecondaryStats.setScale(0.6, 0.6);
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

	for (int i = 0; i <= 5; i++)
	{
		if (m_player->getCurrentSouls() >= m_player->getStatArray(i)*10) 
		{
			increaseButtonSpriteArray[i].setTexture(m_increaseButtonRed);
			increasable[i] = true;
		}
		else
		{
			increaseButtonSpriteArray[i].setTexture(m_increaseButtonGray);
			increasable[i] = false;
		}
	}

	sf::Event event;
	while (StateHandler::getInstance().m_pWindow->pollEvent(event)) 
	{
		for (int i = 0; i <= 5; i++) 
		{
			if (event.mouseButton.x >= increaseButtonSpriteArray[i].getPosition().x &&
				event.mouseButton.x <= increaseButtonSpriteArray[i].getPosition().x + 15 &&
				event.mouseButton.y >= increaseButtonSpriteArray[i].getPosition().y &&
				event.mouseButton.y <= increaseButtonSpriteArray[i].getPosition().y + 15 &&
				increasable[i] == true) 
			{
				m_player->increaseStat(i);
				m_player->modifySouls(m_player->getStatArray(i)*-10);
			}	
		}
	}

	healthText.setString(numberToString(m_player->getCurrentHealth())+" / " +
							numberToString(m_player->getMaxHealth())); 


	healthRotation = ((105 - (m_player->getCurrentHealth()/m_player->getMaxHealth()*100))/5);
	m_shFrameCount += 1;

	if(m_shFrameCount % 4 == 0)
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
	for (int i = 0; i <= 5; i++) {
		StateHandler::getInstance().m_pWindow->draw(increaseButtonSpriteArray[i]);
	}
}

template <typename T>
  std::string numberToString ( T Number )
  {
	 std::ostringstream ss;
	 ss << Number;
	 return ss.str();
  }