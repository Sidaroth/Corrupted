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

	maskingImage.createMaskFromColor( sf::Color (106, 76, 48), 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	if( !maskingImage.loadFromFile("../../Resources/SkeletonAttack.png"))
	{
		return EXIT_FAILURE;
	}
	
	maskingImage.createMaskFromColor( sf::Color (106, 76, 48), 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	if( !maskingImage.loadFromFile("../../Resources/SkeletonStand.png"))
	{
		return EXIT_FAILURE;
	}

	maskingImage.createMaskFromColor( sf::Color (106, 76, 48), 0);
	tempTexture.loadFromImage( maskingImage );
	m_SkellieTextures.push_back(tempTexture);

	
	std::cout << "DONE!\n";

	return EXIT_SUCCESS;
}

Enemy* EnemyFactory::createEnemy(Enemies enemyType)
{
	switch(enemyType)
	{
	case Skellie:
		return new Skeleton(&m_SkellieTextures);
	}

	return NULL;
}