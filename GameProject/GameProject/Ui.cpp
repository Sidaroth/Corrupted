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

void Ui::initialize(short* strength, short* intelligence, short* toughness, short* speed,
				    short* currentSouls, short* weaponLevel, short* armorLevel, short* currHp,
					short* maxHealth, short* meleeDamage, short* spellDamage, float* critChance)
{
	m_shvPlayerStats.reserve(12);

	m_shvPlayerStats.push_back(strength);		// 0
	m_shvPlayerStats.push_back(intelligence);	// 1
	m_shvPlayerStats.push_back(toughness);		// 2
	m_shvPlayerStats.push_back(speed);			// 3
	m_shvPlayerStats.push_back(weaponLevel);	// 4
	m_shvPlayerStats.push_back(armorLevel);		// 5
	m_shvPlayerStats.push_back(currentSouls);	// 6
	m_shvPlayerStats.push_back(currHp);			// 7
	m_shvPlayerStats.push_back(maxHealth);		// 8
	m_shvPlayerStats.push_back(meleeDamage);	// 9
	m_shvPlayerStats.push_back(spellDamage);	// 10

	m_fCriticalChance = critChance;
}

void Ui::update()
{
	rightSideStats.setString(numberToString((*m_shvPlayerStats[0]))+"\n"+
								numberToString((*m_shvPlayerStats[1]))+"\n"+
								numberToString((*m_shvPlayerStats[2]))+"\n"+
								numberToString((*m_shvPlayerStats[3]))+"\n\n\t\t"+
								numberToString((*m_shvPlayerStats[9]))+"\n\t\t"+
								numberToString((*m_shvPlayerStats[10]))+"\n\t\t"+
								numberToString((*m_fCriticalChance))+"%");

	rightSideSecondaryStats.setString(numberToString((*m_shvPlayerStats[6]))+"\n\n"+
										numberToString((*m_shvPlayerStats[4]))+"\n"+
										numberToString((*m_shvPlayerStats[5])));

	for (int i = 0; i <= 5; i++)
	{
		if ((*m_shvPlayerStats[6]) >= (*m_shvPlayerStats[i]) * 10) 
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

	healthText.setString(numberToString((*m_shvPlayerStats[7]))+" / " +
							numberToString(((*m_shvPlayerStats[8])))); 

	healthRotation = ((105.f - ((float(*m_shvPlayerStats[7]) / float(*m_shvPlayerStats[8])) * 100.f)) / 3.f);
	m_shFrameCount += 1;

	if(m_shFrameCount % 4 == 0)
	{
		m_healthDiamondSprite.rotate(healthRotation);
	}
	
}

void Ui::processEvents(sf::Event event)
{
	for (int i = 0; i <= 5; i++) 
	{
		if (event.mouseButton.x >= increaseButtonSpriteArray[i].getPosition().x &&
			event.mouseButton.x <= increaseButtonSpriteArray[i].getPosition().x + 15 &&
			event.mouseButton.y >= increaseButtonSpriteArray[i].getPosition().y &&
			event.mouseButton.y <= increaseButtonSpriteArray[i].getPosition().y + 15 &&
			increasable[i] == true) 
		{
			(*m_shvPlayerStats[i])++;
			(*m_shvPlayerStats[6]) = ((*m_shvPlayerStats[6]) + ((*m_shvPlayerStats[i]) * -10));
		}	
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

	for (int i = 0; i <= 5; i++) 
	{
		StateHandler::getInstance().m_pWindow->draw(increaseButtonSpriteArray[i]);
	}
}

void Ui::addFloatingText()
{

}

template <typename T>
  std::string numberToString ( T Number )
  {
	 std::ostringstream ss;
	 ss << Number;
	 return ss.str();
  }