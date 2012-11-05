#include "Projectile.h"

	Projectile::Projectile()
	{

	}

	Projectile::Projectile(short spell, short damage, Vector2f mouseCoordinates)
	{
		m_shSpell = spell;
		m_shDamage = damage;
		m_vGoalPosition = mouseCoordinates;
	}

	bool Projectile::loadContent()
	{
		if(m_shSpell == FIREBALL)
		{
			if(!m_Texture.loadFromFile( "../../Resources/Fireball.png" ) )
			{
				return EXIT_FAILURE;
			}
		}
		else
		{
			std::cout << "\nNO SPELL SPRITE LOADED!\n";
		}

		m_Sprite.setTexture(m_Texture);

		return EXIT_SUCCESS;
	}