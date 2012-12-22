#include "Skeleton.h"
#include "StateHandler.h"

Skeleton::Skeleton(std::vector<sf::Texture>* textures, short level)
{
	m_shStrength = level;
	m_shIntelligence = level;
	m_shToughness = level;
	m_shSpeed = BASE_STAT + level / 5;

	frameCount = 0;

	m_shSoulsToDrop = 10;
	onClosedList = 10;
	onOpenList = 1;
	pathLength = UNDETERMINED;

	m_fAttackRange = TILESIZE / 2;

	xStepGoalReached = false;
	yStepGoalReached = false;

	m_TextureTypes.push_back( &textures -> at(MOVE) );
	m_TextureTypes.push_back( &textures -> at(ATTACK) );
	m_TextureTypes.push_back( &textures -> at(STILL) );
	m_TextureTypes.push_back( &textures -> at(DIE) );
}

Skeleton::~Skeleton()
{
	for(std::vector<sf::Texture*>::iterator it = m_TextureTypes.begin(); it != m_TextureTypes.end();)
	{
		delete * it;
		it = m_TextureTypes.erase(it);
	}
}

bool Skeleton::loadContent(Vector2f* playerPos)
{
	m_pPlayerPos = playerPos;
	m_Sprite.setTexture(*m_TextureTypes[STILL]);
	animation();

	return EXIT_SUCCESS;	// Exit succesfully. 
}

void Skeleton::draw()
{
	StateHandler::getInstance().m_pWindow->draw(m_Sprite);
}

//void Skeleton::update()
//{
//	Enemy::update();
//}
