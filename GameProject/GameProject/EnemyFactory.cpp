#include "EnemyFactory.h"


EnemyFactory::EnemyFactory()
{

}

bool EnemyFactory::loadContent()
{
	sf::Texture tempTexture;
	sf::Image maskingImage;

	if(!maskingImage.loadFromFile("../../Resources/SkeletonWalk.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor( bgColor, 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	if( !maskingImage.loadFromFile("../../Resources/SkeletonAttack.png"))
	{
		return EXIT_FAILURE;
	}
	
	maskingImage.createMaskFromColor( bgColor, 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	if( !maskingImage.loadFromFile("../../Resources/SkeletonStand.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor( bgColor, 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	if( !maskingImage.loadFromFile("../../Resources/SkeletonDie.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor( bgColor, 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	return EXIT_SUCCESS;
}

Enemy* EnemyFactory::createEnemy(Enemies enemyType, short level)
{
	switch(enemyType)
	{
	case Skellie:
		return new Skeleton(&m_SkellieTextures, level);
	}

	return NULL;
}