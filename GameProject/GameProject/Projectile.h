#pragma once

#include "Actor.h"
#include "Vector2f.h"

class Projectile : public Actor
{
private: 
	
	short m_shSpell;
	short m_shDamage;
	short m_shBitmapCol;
	short m_shBitmapRow;
	short m_shSpriteSize;
	short m_shFrameCount;
	short m_shTraveled;
	bool m_bExist;
	float m_fAngle;
	std::vector<sf::Texture> m_vTextures;
	enum m_abilities { FIREBALL, FROSTBOLT, LIGHTNINGBOLT };
	std::vector<bool>* m_objects;
	short m_shHorizontalBitmapSize;

	void checkCollision( );

public:
	Projectile( );
	//Projectile( short spell, short damage, Vector2f position, Vector2f mouseCoordinates );
	void initiate ( short spell, short damage, Vector2f position, Vector2f mouseCoordinates );
	bool loadContent( );
	void animation( );
	void move( );
	void draw( );
	bool exist( );
	void setFrame( );
	void setInvisible( );
	void setEnvironmentObjects(std::vector<bool>* objects, short horizontalBitmapSize );
};