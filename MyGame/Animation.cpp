#include "Animation.h"


Animation::Animation():crop()
{
	
	this->donePlaying = false;

	this->currentFrame.top = 0;
	this->currentFrame.left = 0;
	this->currentFrame.height = 0;
	this->currentFrame.width = 0;

	this->frame.top = 0;
	this->frame.left = 0;
	this->frame.height = 0;
	this->frame.width = 0;

	this->target = NULL;
	this->delay = 1;
	this->currentDelay = 0;

	this->strip.create(40,50);
	this->animateForward = true;
	this->aLeft = 0;

	crop.create(40,50);
}

Animation::Animation(const std::string &filename, sf::IntRect frameRect,sf::Texture *Target)
{
	
	this->strip.loadFromFile(filename);
	this->frame = frameRect;
	this->currentFrame.top = 0;
	this->currentFrame.left = 0;
	this->currentFrame.height = frameRect.height;
	this->currentFrame.width = frameRect.width;
	this->target = Target;
}

void Animation::set_Strip(const std::string &filename)
{
	
	this->strip.loadFromFile(filename);
	
}

void Animation::set_Frame(sf::IntRect frameRect)
{
	this->crop.create(frameRect.width,frameRect.height);
	this->frame = frameRect;
	this->currentFrame.top = frameRect.top;
	this->currentFrame.left = frameRect.left;
	this->currentFrame.height = frameRect.height;
	this->currentFrame.width = frameRect.width;
}

void Animation::set_TargetTexture(sf::Texture *Target)
{
	this->target = Target;
}

void Animation::set_Delay(int val)
{
	this->delay = val;
}

void Animation::set_TotalFrames(int val)
{
	this->totalFrames = val;
}

void Animation::set_Step(int val)
{
	this->step = val;
}

void Animation::set_Style(Style newStyle)
{
	this->playStyle = newStyle;
}
void Animation::set_Values(sf::IntRect frameRect,int val,Style newStyle)
{
	this->crop.create(frameRect.width,frameRect.height);
	this->frame = frameRect;
	this->currentFrame.top = frameRect.top;
	this->currentFrame.left = frameRect.left;
	this->currentFrame.height = frameRect.height;
	this->currentFrame.width = frameRect.width;

	this->totalFrames = val;

	this->playStyle = newStyle;
}
void Animation::next()
{
	// Animation play styles :
	// LOOP : Keep going forward until left crosses the last frame, and then resets the left to 0.
	// PLAYONCE : Keep going froward until left crosses the last frame, and then do nothing.
	// BIDIRECTIONAL : Keep going forward until left crosses the last frame, and then reversers the direction.

	if(currentDelay >= delay)
	{
		switch(playStyle)
		{
		case Style::LOOP:
			if(aLeft >= frame.width * totalFrames)
				this->aLeft = 0;
			else
			{
				currentFrame.left = aLeft;
				crop.copy(this->strip,0,0,currentFrame);
				target->update(crop);
				currentDelay = 0;
				aLeft = currentFrame.left + step * frame.width;
			}
			break;
		case Style::PLAYONCE:
			
			if(!(aLeft >= frame.width * totalFrames))
			{
			currentFrame.left = aLeft;
			crop.copy(this->strip,0,0,currentFrame);
			target->update(crop);
			currentDelay = 0;
			aLeft = currentFrame.left + step * frame.width;
			}
			else
				this->donePlaying = true;
			break;
		case Style::BIDIRECTIONAL:
			 if(animateForward)
			 {
				 if(aLeft >= frame.width * totalFrames)
				 {
					 animateForward = false;
					 aLeft = aLeft - frame.width * 2;
					 currentFrame.left = aLeft;
					 crop.copy(this->strip,0,0,currentFrame);
					 target->update(crop);
					 currentDelay = 0;
				 }
				 else
				 {
					 currentFrame.left = aLeft;
					 crop.copy(this->strip,0,0,currentFrame);
					 target->update(crop);
					 aLeft = currentFrame.left + step * frame.width;
					 currentDelay = 0;
				 }
			 }
			 else
			 {
				 
				 if(aLeft < 0)
				 {
					 animateForward = true;
					 aLeft = 0;
					 aLeft = currentFrame.left + step * frame.width;
					 currentFrame.left = aLeft;
					 crop.copy(this->strip,0,0,currentFrame);
					 target->update(crop);
					 currentDelay = 0;
				 }
				 else
				 {
					 currentFrame.left = aLeft;
					 crop.copy(this->strip,0,0,currentFrame);
					 target->update(crop);
					 aLeft = currentFrame.left - step * frame.width;
					 currentDelay = 0;
				 }
			 }
			 
			break;
		}

	}
	else
	{
		currentDelay++;
	}
}

bool Animation::is_playing()
{
	return (!donePlaying);
}

void Animation::reset()
{
	this->aLeft = 0;
	this->donePlaying = false;
}