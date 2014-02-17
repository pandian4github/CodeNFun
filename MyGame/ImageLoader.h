#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include "SFML\Graphics.hpp"
//#include "CollRectManager.h"
#include <iostream>
sf::Sprite *imagesprite;
sf::Texture imagetex;
void Init_Image()
{
	imagesprite=new sf::Sprite();
}

void set_Image(int xpos, int ypos, int width, int height, std::string imageLocation)
{
	if(!imagetex.loadFromFile(imageLocation))
	{
		std::cout<<"\nError loading image at " << imageLocation << std::endl;
	}
	imagesprite->setTexture(imagetex);
	imagesprite->setTextureRect(sf::IntRect(0,0,width,height));
	imagesprite->setPosition((float)xpos,(float)ypos);

}	
void display_image( sf::RenderWindow *window)
{
	window->draw(*imagesprite);
}

#endif