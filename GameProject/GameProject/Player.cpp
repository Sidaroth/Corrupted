#include "Player.h"

Player::Player() : Character()
{
	m_shTotalSouls = 0;
	m_shCurrentSouls = 0;
	m_shWeaponLevel = 1;
	m_shArmorLevel = 1;

	m_sName = "DERP";
}

bool Player::loadContent()
{
	std::cout << "DERP" << std::endl;
	if (!m_Texture.loadFromFile("player.png"))
	{
		return EXIT_FAILURE;
	}

	m_Sprite.setTexture(m_Texture);
	return 0;
}