#include "Ui.h"

Ui::Ui()
{
	m_shFrameCount = 0;

	for (int i = 0; i <= 5; i++)
	{
		increasable[i] = false;
	}
	
}

Ui::~Ui()
{
	
}

bool Ui::loadContent()
{
	sf::Image healthDiamondMaskingImage;
	

	if(!m_uiBackground.loadFromFile("../../Resources/GUI.PNG"))				//Load images
	{
		return EXIT_FAILURE;
	}

	if(!healthDiamondMaskingImage.loadFromFile("../../Resources/healthDiamond.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!m_iconFireball.loadFromFile("../../Resources/fireball_icon.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!m_iconSword.loadFromFile("../../Resources/sword_icon.PNG"))
	{
		return EXIT_FAILURE;
	}

	if(!m_iconEmpty.loadFromFile("../../Resources/empty_icon.PNG"))
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

	healthDiamondMaskingImage.createMaskFromColor(sf::Color(0, 0, 0), 0);			//Remove black backgrounds
	m_healthDiamond.loadFromImage(healthDiamondMaskingImage);


	if(!font.loadFromFile("../../Resources/impact.ttf"))				//Load font 
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_view.reset(sf::FloatRect(0, 0, 1366, 768));						//Set view to game window size

	m_uiBackgroundSprite.setTexture(m_uiBackground);					//Set texture and position on all UI sprites
	m_uiBackgroundSprite.setPosition(0, 0);

	m_healthDiamondSprite.setTexture(m_healthDiamond);
	m_healthDiamondSprite.setPosition(125, 650);
	m_healthDiamondSprite.setOrigin(50, 50);

	m_iconFireballSprite.setTexture(m_iconFireball);
	m_iconFireballSprite.setScale(0.55, 0.55);
	m_iconFireballSprite.setPosition(860, 680);

	m_iconSwordSprite.setTexture(m_iconSword);
	m_iconSwordSprite.setScale(0.55, 0.55);
	m_iconSwordSprite.setPosition(779, 680);

	for (int i = 0; i <= 3; i++)
	{
		m_iconEmptySpriteArray[i].setTexture(m_iconEmpty);
		m_iconEmptySpriteArray[i].setScale(0.55, 0.55);
		m_iconEmptySpriteArray[i].setPosition(455 + i*81, 680);
	}

	for (int i = 0; i <= 5; i++)
	{
		increaseButtonSpriteArray[i].setTexture(m_increaseButtonGray);
	}
	increaseButtonSpriteArray[0].setPosition(1201, 586);
	increaseButtonSpriteArray[1].setPosition(1201, 608);
	increaseButtonSpriteArray[2].setPosition(1201, 631);
	increaseButtonSpriteArray[3].setPosition(1201, 652);
	increaseButtonSpriteArray[4].setPosition(1349, 631);
	increaseButtonSpriteArray[5].setPosition(1349, 652);

																		//Set string, position, scale and font to all texts
	rightSideText.setPosition(1085, 583);
	rightSideText.setString("Strength: \nIntelligence: \nToughness: \nSpeed: \n\nMelee Damage: \nSpell Damage\nCritical Chance: ");
	rightSideText.setScale(0.6, 0.6);
	rightSideText.setFont(font);

	rightSideSecondaryText.setPosition(1225, 583);
	rightSideSecondaryText.setString("Souls: \n\nWeapon Level: \nArmor Level: ");
	rightSideSecondaryText.setScale(0.6, 0.6);
	rightSideSecondaryText.setFont(font);

	rightSideStats.setPosition(1183, 583);
	rightSideStats.setScale(0.6, 0.6);
	rightSideStats.setFont(font);

	rightSideSecondaryStats.setPosition(1331, 583);
	rightSideSecondaryStats.setScale(0.6, 0.6);
	rightSideSecondaryStats.setFont(font);

	healthText.setPosition(95, 710);
	healthText.setScale(0.7, 0.7);
	healthText.setFont(font);

	for (int i = 0; i <= 4; i++) 
	{
		iconText[i].setScale(0.4, 0.4);
		iconText[i].setFont(font);
	}

	iconText[0].setString("1");
	iconText[0].setPosition(480, 740);			
	iconText[1].setString("2");
	iconText[1].setPosition(561, 740);
	iconText[2].setString("3");
	iconText[2].setPosition(644, 740);
	iconText[3].setString("4");
	iconText[3].setPosition(725, 740);
	iconText[4].setString("Mouse");
	iconText[4].setPosition(830, 740);
	

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
	rightSideStats.setString(numberToString((*m_shvPlayerStats[0]))+"\n" +
								numberToString((*m_shvPlayerStats[1]))+"\n" +
								numberToString((*m_shvPlayerStats[2]))+"\n" +
								numberToString((*m_shvPlayerStats[3]))+"\n\n\t\t" +
								numberToString((*m_shvPlayerStats[9]))+"\n\t\t" +
								numberToString((*m_shvPlayerStats[10]))+"\n\t\t" +
								numberToString((*m_fCriticalChance))+"%");

	rightSideSecondaryStats.setString(numberToString((*m_shvPlayerStats[6]))+"\n\n" +
										numberToString((*m_shvPlayerStats[4]))+"\n" +
										numberToString((*m_shvPlayerStats[5])));

	for (int i = 0; i <= 5; i++)											
	{
		if ((*m_shvPlayerStats[6]) >= (*m_shvPlayerStats[i]) * 10)				//Checks if player has enough souls to afford upgrade
		{
			increaseButtonSpriteArray[i].setTexture(m_increaseButtonRed);		//Change the upgrade button to be red
			increasable[i] = true;												//Mark the stat as increasable
		}
		else
		{
			increaseButtonSpriteArray[i].setTexture(m_increaseButtonGray);		//Change it back to gray
			increasable[i] = false;												//And mark the stat as unincreasable
		}
	}

	healthText.setString(numberToString((*m_shvPlayerStats[7]))+" / " +			//Display "current health / max health"
							numberToString(((*m_shvPlayerStats[8])))); 

	m_shFrameCount += 1;

	if(m_shFrameCount % 4 == 0)
	{
		healthRotation = ((105.f - ((float(*m_shvPlayerStats[7]) / float(*m_shvPlayerStats[8])) * 100.f)) / 3.f);	//Calculate the angle to rotate the health diamond
		m_healthDiamondSprite.rotate(healthRotation);																// 105 - 'current hp in percent' / 3
	}

	FloatingText* temp;
	for(std::vector<FloatingText*>::iterator it = m_ftFloatingTextEntities.begin(); it != m_ftFloatingTextEntities.end();)
	{
		temp = (*it);
		temp -> update();

		if(temp -> isDead())
		{
			it = m_ftFloatingTextEntities.erase(it);	// Remove if dead
		}
		else											// if not, go to next. 
		{
			++it;
		}
	}
}

void Ui::processEvents(sf::Event event)
{
	for (int i = 0; i <= 5; i++)																	//Loop through upgradable stats
	{		
		if (event.mouseButton.x >= increaseButtonSpriteArray[i].getPosition().x &&					//check any of the increase buttons are pressed
			event.mouseButton.x <= increaseButtonSpriteArray[i].getPosition().x + 15 &&
			event.mouseButton.y >= increaseButtonSpriteArray[i].getPosition().y &&
			event.mouseButton.y <= increaseButtonSpriteArray[i].getPosition().y + 15 &&
			event.type == sf::Event::MouseButtonPressed &&
			increasable[i] == true)																	//and if the player has enough souls
		{
			(*m_shvPlayerStats[i])++;																//Increase stat by one
			(*m_shvPlayerStats[6]) = ((*m_shvPlayerStats[6]) + ((*m_shvPlayerStats[i]) * -10));		//Decrease current souls by cost
		}																							//Cost is current stat value * 10
	}
}

void Ui::draw()
{
	StateHandler::getInstance().m_pWindow->setView(m_view);

	StateHandler::getInstance().m_pWindow->draw(m_uiBackgroundSprite);
	StateHandler::getInstance().m_pWindow->draw(m_healthDiamondSprite);
	StateHandler::getInstance().m_pWindow->draw(m_iconFireballSprite);
	StateHandler::getInstance().m_pWindow->draw(m_iconSwordSprite);
	StateHandler::getInstance().m_pWindow->draw(rightSideText);
	StateHandler::getInstance().m_pWindow->draw(rightSideStats);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryText);
	StateHandler::getInstance().m_pWindow->draw(rightSideSecondaryStats);
	StateHandler::getInstance().m_pWindow->draw(healthText);
	
	for (int i = 0; i <= 3; i++) 
	{
		StateHandler::getInstance().m_pWindow->draw(m_iconEmptySpriteArray[i]);
		StateHandler::getInstance().m_pWindow->draw(iconText[i]);
	}

	for (int i = 0; i <= 4; i++) 
	{
		StateHandler::getInstance().m_pWindow->draw(iconText[i]);
	}

	for (int i = 0; i <= 5; i++) 
	{
		StateHandler::getInstance().m_pWindow->draw(increaseButtonSpriteArray[i]);
	}

	// Loop through and draw each of the floating text objects. 
	for(std::vector<FloatingText*>::iterator it = m_ftFloatingTextEntities.begin(); it != m_ftFloatingTextEntities.end(); ++it)
	{
		(*it) -> draw(); 
	}
}

void Ui::addFloatingText(std::string message, Vector2f position, sf::Color color)
{
	m_ftFloatingTextEntities.push_back(new FloatingText(message, position, &font, color)); 
	
	std::cout << &font << std::endl;
	//m_ftFloatingTextEntities.back() -> setFont(&font);

}

void Ui::fadeOut()
{

}

template <typename T>  std::string Ui::numberToString ( T Number )				//conversion from number to string
{
	 std::ostringstream ss;
	 ss << Number;
	 return ss.str();
}