#pragma once

#include "Actor.h"
#include "Environment.h"
#include "Projectile.h"
#include "Ui.h"
#include "AudioManager.h"

#define bgColor sf::Color(106, 76, 48)
#define BASE_STAT 5

class Character : public Actor
{
private:
	
	bool* m_bAbilities;

protected:	
	
	short m_shBitmapRow;		/// What frame of the animation from the spritesheet to display
	short m_shBitmapCol;		/// What animation to display from the spritesheet
	short m_shFrameCount;

	bool m_bDoingAction;
	bool stopAnimation;
	short m_shStrength;
	short m_shIntelligence;
	short m_shToughness;
	short m_shSpeed;

	short m_shCurrentHealth;
	short m_shMaxHealth;

	short m_shMeleeDamage;
	short m_shSpellDamage;
	float m_fCriticalChance;	/// Given in percent

	bool m_bDead;

	sf::Clock m_iCoolDown;

	float m_fHealCoolDown;
	float m_fFireballCoolDown;


	Ui* userInterface;

	~Character();
	Character();
	EnvironmentHandler* m_environmentLevel;
	std::vector<Projectile*> m_vProjectiles;

public:
	bool attack(short row); ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
	virtual bool loadContent();
	virtual void setUserInterface(Ui* ui);

	///////GET FUNCTIONS///////
	short getMaxHealth();
	short getCurrentHealth();
	short getMeleeDamage();
	short getSpellDamage();
	short getSpeed();
	short getToughness();
	short getIntelligence();
	short getStrength();
	float getCriticalChance();
	bool* getAbilities();

	////////SET FUNCTIONS//////
	void setFrame();				///set the correct frame in the animation
	void setBitmapRow(short row);		///1=N, 2=NE, 3=E, 4=SE, 5=S, 6=SW, 7=W, 8=NW
	void setEnvironmentLevel(EnvironmentHandler* environmentLevel);

	void animation();				///calculate the correct frame to be set in setFrame
	virtual void draw();
	virtual void update();

	void moveHorizontal(bool horizontalMovement,bool verticalMovement);
	void moveVertical(bool verticalMovement,bool horizontalMovement);
	void move(short direction);
	void changeAnimationToWalk();
	void changeAnimationToStand();
	
	enum abilities { FIREBALL, FROSTBOLT, LIGHTNINGBOLT };
	enum directions { NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST };
	void showDamage();	// wut wut
	void showHealth();	
	void startAction();
	void endAction();
	bool isDoingAction();
	void castSpell( Vector2f mouseCoordinates, short spell );
	void heal();
	virtual bool takeDamage( short damage );
};