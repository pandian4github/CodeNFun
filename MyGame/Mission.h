#ifndef MISSION_H
#define MISSION_H
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Audio\Music.hpp"
#include <iostream>

sf::Sprite *missionsprite;
sf::Texture missiontex;

void init_mission(int tutorialLevel,int tutorialNo)
{
	std::string imageLocation = "Assets/mission";
	imageLocation += std::to_string(tutorialLevel);
	imageLocation += "_";
	imageLocation += std::to_string(tutorialNo);
	imageLocation += ".png";

	//std::cout<<imageLocation;

	if(!missiontex.loadFromFile(imageLocation))
	{
		std::cout<<"\nError loading mission : " << imageLocation << std::endl;
	}
	missionsprite=new sf::Sprite();
	missionsprite->setTexture(missiontex);
	missionsprite->setTextureRect(sf::IntRect(0,0,1000,562));
	missionsprite->setPosition(0,0);

}

void show_mission( sf::RenderWindow *window)
{
	window->draw(*missionsprite);
}

#endif