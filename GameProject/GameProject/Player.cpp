#include "Player.h"

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
	sf::Image maskingImage;
	if (!maskingImage.loadFromFile("../../Resources/player.png"))
	{
		return EXIT_FAILURE;
	}
	maskingImage.createMaskFromColor(sf::Color (106, 76, 48), 0);
	m_Texture.loadFromImage( maskingImage);
	m_Sprite.setTexture(m_Texture);
	animation();
	return 0;
}