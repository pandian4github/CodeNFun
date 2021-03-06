#ifndef EVA_H
#define EVA_H
#include "SFML\Graphics.hpp"
#include "CollRectManager.h"
#include <iostream>
sf::Sprite *evasprite;
sf::Texture evatex;
int frame_count;
void Init_Eva(int x,int y)
{
	 
	 if(!evatex.loadFromFile("Assets/robo.png"))
	{
		std::cout<<"\nError loading robo";
	}
	evasprite=new sf::Sprite();
	evasprite->setTexture(evatex);
	evasprite->setTextureRect(sf::IntRect(0,0,150,200));
	evasprite->setPosition((float)x,(float)y);

	frame_count=0;
}

void animate_eva()
{
	
	frame_count=(frame_count+1)%10;
	if(frame_count<5)
		evasprite->move(0,-1);
	else
		evasprite->move(0,+1);
}
void display_eva( sf::RenderWindow *window)
{
	window->draw(*evasprite);
}

void changeEvaPosition(int level)
{
	if(level == 1)
	{
		myManager->changePosition(0,0,0,0,3); //3rd collision rectangle needs to be changed for level 1
		evasprite->setPosition(0,0);
	}
	if(level == 5)
	{
		myManager->changePosition(0,0,0,0,2);
		evasprite->setPosition(169,100);
	}
}
#endif