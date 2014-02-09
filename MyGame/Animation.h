#ifndef ANIMATION_H
#define ANIMATION_H

#include<SFML\Graphics.hpp>


enum Style
{
	LOOP = 0,
	PLAYONCE,
	BIDIRECTIONAL

};

class Animation
{
public: 
	//Public Members

	//Public Methods
	Animation();
	Animation(const std::string &filename, sf::IntRect frameRect,sf::Texture *Target);

	void set_Strip(const std::string &filename);
	void set_Frame(sf::IntRect frameRect);
	void set_TargetTexture(sf::Texture *Target);
	void set_Delay(int); //For Delay
	void set_TotalFrames(int);
	void set_Step(int); //For Movement, forword or reverse, jump two or one
	void set_Style(Style newStyle);
	void set_Values(sf::IntRect frameRect,int,Style newStyle);

	void next();
	void reset();
	bool is_playing();
	
private:
	//Private Members
	sf::Image strip,crop;
	sf::IntRect currentFrame, frame;
	sf::Texture *target;
	
	int delay,step,currentDelay,totalFrames,aLeft;
	bool animateForward,donePlaying;
	Style playStyle;
	std::string zipString;
	
	//Private Methods

};

#endif