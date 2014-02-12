#ifndef TUTORIAL_H
#define TUTORIAL_H
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>

sf::Sprite *tutsprite;
sf::Texture tuttex;
sf::Music musicBuffer;
bool playing;
bool soundForLevelTutorial[10][10];

void setSound(int level,int tutorial)
{
	if(level == 0)
	{
		soundForLevelTutorial[level][1]=soundForLevelTutorial[level][2]=soundForLevelTutorial[level][3]=soundForLevelTutorial[level][4]=soundForLevelTutorial[level][5]=1;
	}
}
    
void init_tutorial(int tutorialLevel,int tutorialNo)
{
	
	std::string imageLocation = "Assets/tut";
	imageLocation += std::to_string(tutorialLevel);
	imageLocation += "_";
	imageLocation += std::to_string(tutorialNo);
	imageLocation += ".png";

	std::cout<<imageLocation;

	if(!tuttex.loadFromFile(imageLocation))
	{
		std::cout<<"\nError loading tut "<<imageLocation ;
	}
	tutsprite=new sf::Sprite();
	tutsprite->setTexture(tuttex);
	tutsprite->setTextureRect(sf::IntRect(0,0,1000,562));
	tutsprite->setPosition(0,0);

	if(soundForLevelTutorial[tutorialLevel][tutorialNo]==1)
		return;

	std::string soundLocation = "Assets/sound";
	soundLocation += std::to_string(tutorialLevel);
	soundLocation += "_";
	soundLocation += std::to_string(tutorialNo);
	soundLocation += ".wav";

	std::cout<<soundLocation;

	if (!musicBuffer.openFromFile(soundLocation))
	{
       std::cout<<"\nError loading sound file";
	}

	playing = false;
	setSound(tutorialLevel,tutorialNo);
}

void show_tutorial( sf::RenderWindow *window)
{
	if(playing==false)
	{
		musicBuffer.play();
		playing=true;
	}
	window->draw(*tutsprite);
}

void end_tutorial(int level,int tutorial)
{
	if(soundForLevelTutorial[level][tutorial+1]==1)
		return;

	playing=false;
	musicBuffer.stop();
}
#endif