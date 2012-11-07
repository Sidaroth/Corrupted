#pragma once

#include "Actor.h"
#include "Vector2f.h"

class Projectile : public Actor
{
private: 
	
	short m_shSpell;
	short m_shDamage;
	Vector2f m_vPosition;
	float m_fAngle;
	std::vector<sf::Texture> m_vTextures;
	enum m_abilities { FIREBALL, FROSTBOLT, LIGHTNINGBOLT };

public:
	Projectile( );
	Projectile( short spell, short damage, Vector2f position, Vector2f mouseCoordinates );
	bool loadContent( );
	void move( );
	void draw( );
};