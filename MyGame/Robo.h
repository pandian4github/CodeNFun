#ifndef ROBO_H
#define ROBO_H

#include "SFML\Graphics.hpp"
#include "CollRectManager.h"
#include "ImageLoader.h"
#include <iostream>

sf::Sprite *robosprite;
sf::Sprite *cratesprite[7];
sf::Texture robotex;

int frame_count1,frame_count2;
int frame_cnt[7];
int crateMove[7];

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

void Init_Robo3(int x,int y)
{
	 
	if(!robotex.loadFromFile("Assets/robo3.png"))
	{
		std::cout<<"\nError loading robo3";
	}
	robosprite=new sf::Sprite();
	robosprite->setTexture(robotex);
	robosprite->setTextureRect(sf::IntRect(0,0,60,93));
	robosprite->setPosition((float)x,(float)y);

	frame_count1=0;
	robo1Initialized=1; //same variable used for robo1 is used 
}

void Init_Robo4(int x,int y)
{
	 
	if(!robotex.loadFromFile("Assets/robo4.png"))
	{
		std::cout<<"\nError loading robo4";
	}
	robosprite=new sf::Sprite();
	robosprite->setTexture(robotex);
	robosprite->setTextureRect(sf::IntRect(0,0,60,93));
	robosprite->setPosition((float)x,(float)y);

	frame_count1=0;
	robo2Initialized=1; //same variable used for robo2 is used 
}

void Init_Crate(int x,int y,int num)
{
	std::string woodenCratePath = "Assets/wooden_crate" + std::to_string(num) + ".png";
	if(!robotex.loadFromFile(woodenCratePath))
	{
		std::cout<<"\nError loading woodencrate "<<num;
	}
	cratesprite[num]=new sf::Sprite();
	cratesprite[num]->setTexture(robotex);
	cratesprite[num]->setTextureRect(sf::IntRect(0,0,60,45));
	cratesprite[num]->setPosition((float)x,(float)y);

	frame_cnt[num] = -1;
	crateMove[num] = 0;
}

void animate_crate_move(int num)
{
	frame_cnt[num] = (frame_cnt[num]+1)%41;
	if(crateMove[num]==0)
	{
		if(frame_cnt[num]<40)
			cratesprite[num]->move(0,-6);
		else
		{
			frame_cnt[num] = -1;
			crateMove[num] = 1;
		}
	}
	else if(crateMove[num]==1)
	{
		if(frame_cnt[num]<39)
			cratesprite[num]->move(4,0);
		else
		{
			frame_cnt[num] = -1;
			crateMove[num] = 2;
		}
	}
	else if(crateMove[num]==2)
	{
		if(num == 0)
		{
			if(frame_cnt[num]<40)
				cratesprite[num]->move(0,6);
			else
			{
				frame_cnt[num] = -1;
				crateMove[num] = 3;
			}
		}
		else if(num==1)
		{
			if(frame_cnt[num]<39)
				cratesprite[num]->move(0,5);
			else
			{
				frame_cnt[num] = -1;
				crateMove[num] = 3;
			}
		}
		else if(num==2)
		{
			if(frame_cnt[num]<38)
				cratesprite[num]->move(0,4);
			else
			{
				frame_cnt[num] = -1;
				crateMove[num] = 3;
			}
		}
		else if(num==3)
		{
			if(frame_cnt[num]<36)
				cratesprite[num]->move(0,3);
			else
			{
				frame_cnt[num] = -1;
				crateMove[num] = 3;
			}
		}
		else if(num==4)
		{
			if(frame_cnt[num]<32)
				cratesprite[num]->move(0,2);
			else
			{
				frame_cnt[num] = -1;
				crateMove[num] = 3;
			}
		}
	}
}

void animate_robo_move(int level)
{
	if(level == 4)
	{
		frame_count1 = (frame_count1+1)%80;
		if(frame_count1<79)
			robosprite->move(-2,0);
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
		frame_count1 = (frame_count1+1)%64;
		if(frame_count1<63)
			robosprite->move(+2,0);
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
}

void animate_robo_stand(int level)
{
	if(level == 4)
	{
		frame_count2 = (frame_count2 + 1) % 80;
		if(frame_count2 >= 79)
			finishedStanding = 1;
	}
	if(level == 5)
	{
		frame_count2 = (frame_count2 + 1) % 80;
		
		if(move3  == 1)
		{
			if(frame_count2 < 21)
			{
				//display 1
				set_Image(630,78,86,51,"Assets/numbers/1.png");
			}
			else if(frame_count2 < 41)
			{
				//display 2
				set_Image(630,78,81,53,"Assets/numbers/2.png");
			}
			else if(frame_count2 < 61)
			{
				//display 3
				set_Image(630,78,84,53,"Assets/numbers/3.png");
			}
			else 
			{
				//display 4
				set_Image(630,78,87,50,"Assets/numbers/4.png");
			}
		}
		else if(move2 == 1)
		{
			if(frame_count2 < 15)
			{
				//display 1
				set_Image(501,79,86,51,"Assets/numbers/1.png");
			}
			else if(frame_count2 < 29)
			{
				//display 2
				set_Image(506,79,81,53,"Assets/numbers/2.png");
			}
			else if(frame_count2 < 43)
			{
				//display 3
				set_Image(506,79,84,53,"Assets/numbers/3.png");
			}
			else if(frame_count2 < 57)
			{
				//display 4
				set_Image(506,79,87,50,"Assets/numbers/4.png");
			}
			else if(frame_count2 < 71)
			{
				//display 5
				set_Image(506,78,84,50,"Assets/numbers/5.png");
			}
			else 
			{
				//display 6
				set_Image(506,79,80,50,"Assets/numbers/6.png");
			}
		}
		else if(move1 == 1)
		{
			if(frame_count2 < 15)
			{
				//display 1
				set_Image(371,77,86,51,"Assets/numbers/1.png");
			}
			else if(frame_count2 < 29)
			{
				//display 2
				set_Image(371,77,81,53,"Assets/numbers/2.png");
			}
			else if(frame_count2 < 43)
			{
				//display 3
				set_Image(371,77,84,53,"Assets/numbers/3.png");
			}
			else if(frame_count2 < 57)
			{
				//display 4
				set_Image(371,77,87,50,"Assets/numbers/4.png");
			}
			else if(frame_count2 < 71)
			{
				//display 5
				set_Image(372,77,84,50,"Assets/numbers/5.png");
			}
		}

		if(frame_count2 >= 79)
			finishedStanding = 1;
	}
}

void display_robo( sf::RenderWindow *window)
{
	window->draw(*robosprite);
}

void display_crate(sf::RenderWindow *window, int num)
{
	window->draw(*cratesprite[num]);
}

void changeRoboPosition(int level)
{
	if(level==1)
		myManager->changePosition(0,0,0,0,3); //3rd collision rectangle needs to be changed for level 1
	robosprite->setPosition(0,0);
}
#endif