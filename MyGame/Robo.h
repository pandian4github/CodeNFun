#ifndef ROBO_H
#define ROBO_H
#include "SFML\Graphics.hpp"
#include "CollRectManager.h"
#include <iostream>
sf::Sprite *robosprite;
sf::Texture robotex;
int frame_count1,frame_count2;
bool finishedStanding = 0;
bool finishedMoving = 0;
bool move1 = 0,move2 = 0,move3=0;
bool robo1Initialized = 0, robo2Initialized = 0;

void Init_Robo1(int x,int y)
{
	 
	if(!robotex.loadFromFile("Assets/robo1.png"))
	{
		std::cout<<"\nError loading robo1";
	}
	robosprite=new sf::Sprite();
	robosprite->setTexture(robotex);
	robosprite->setTextureRect(sf::IntRect(0,0,60,93));
	robosprite->setPosition((float)x,(float)y);

	frame_count1=0;
	robo1Initialized=1;
}

void Init_Robo2(int x,int y)
{
	 
	if(!robotex.loadFromFile("Assets/robo2.png"))
	{
		std::cout<<"\nError loading robo2";
	}
	robosprite=new sf::Sprite();
	robosprite->setTexture(robotex);
	robosprite->setTextureRect(sf::IntRect(0,0,60,93));
	robosprite->setPosition((float)x,(float)y);

	frame_count2 = 0;
	robo2Initialized=1;
}

void animate_robo_move(int level)
{
	if(level == 4)
	{
		frame_count1 = (frame_count1+1)%160;
		if(frame_count1<159)
			robosprite->move(-1,0);
		else
		{
			finishedMoving = 1;
			if(move1 == 0)
				move1 = 1;
			else if(move2 == 0)
				move2 = 1;
			else if(move3 == 0)
				move3 = 1;
		}
	}
	else if(level == 5)
	{
		//animation for level 5;
	}
}

void animate_robo_stand(int level)
{
	if(level == 4)
	{
		frame_count2 = (frame_count2 + 1) % 80;
		if(frame_count2 >= 79)
			finishedStanding = 1;
	}
}

void display_robo( sf::RenderWindow *window)
{
	window->draw(*robosprite);
}

void changeRoboPosition(int level)
{
	if(level==1)
		myManager->changePosition(0,0,0,0,3); //3rd collision rectangle needs to be changed for level 1
	robosprite->setPosition(0,0);
}
#endif