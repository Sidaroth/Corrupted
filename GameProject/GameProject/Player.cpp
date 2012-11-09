#include "Player.h"
#include "StateHandler.h"

Player::Player() : Character()
{
	m_shTotalSouls = 0;
	m_shCurrentSouls = 0;
	m_shWeaponLevel = 1;
	m_shArmorLevel = 1;

	m_sName = "Ronald McDonald";
}

bool Player::loadContent()
{
	//load projectiles in character
	Character::loadContent();

	sf::Image maskingImage;
		//Loading move action
	if (!maskingImage.loadFromFile("../../Resources/player.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["move"].imgTexture=m_Texture;
	m_TexturesActions["move"].size=m_Texture.getSize().x;
	//Loading attack action
	if (!maskingImage.loadFromFile("../../Resources/player_attack.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["attack"].imgTexture=m_Texture;
	m_TexturesActions["attack"].size=m_Texture.getSize().x;
	//
	//Loading standing action
	if (!maskingImage.loadFromFile("../../Resources/player_still.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage );
	m_TexturesActions["still"].imgTexture=m_Texture;
	m_TexturesActions["still"].size=m_Texture.getSize().x;
	//

	m_Sprite.setTexture(m_TexturesActions["still"].imgTexture);
	animation();

	

	return 0;
}

void Player::update() 
{
	Character::update();
}

void Player::draw()
{
	Character::draw();
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}