/**
*	@file
*	This .cpp file handles the environment, and translating the bitmap
*/

#include "Environment.h"


bool EnvironmentHandler::loadContent(std::string path)
{
	if(!m_bitmap.loadFromFile("../../Resources/levelOne.png"))
	{
		return EXIT_FAILURE;
	}
	m_iHorizontalBitmapSize = m_bitmap.getSize().x;
	m_iVerticalBitmapSize = m_bitmap.getSize().y;
}

void EnvironmentHandler::bitmapToArray()
{
	sf::Color pixelColor;
	for(int j=0; j < m_iVerticalBitmapSize; j++)
	{
		for(int i=0; i < m_iHorizontalBitmapSize; i++)
		{
			pixelColor = m_bitmap.getPixel(i,j);
			RGB* rgb = new RGB;
			rgb->red = pixelColor.r;
			rgb->green = pixelColor.g;
			rgb->blue = pixelColor.b;
			m_floorArray.push_back(rgb);
		}
	}
}

void EnvironmentHandler::drawLevel() 
{
	for(int j=0; j < m_iVerticalBitmapSize; j++)
	{
		for(int i=0; i < m_iHorizontalBitmapSize; i++)
		{
			
		}
	}
}

void EnvironmentHandler::colorChart(RGB rgb)
{
	if (rgb.red == 255 && rgb.green == 0 && rgb.blue == 0)
	{
		sf::IntRect subrect;
	}
	
}