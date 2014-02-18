#ifndef HERO_H
#define HERO_H

#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "CollRectManager.h"
#include "CompilationUnit.h"

//Collision checking functions
const int SOLID=0;
const int INTERACTIVE_OBJECT=1;
bool levelChanged = 0, subLevelChanged = 0;
int wpressed;

enum State
{
	IDLE_R=0,IDLE_L,WALK_R,WALK_L,JUMP_R,JUMP_L,GRAB_R,GRAB_L
};

const int VELOCITY=10;
const int GRAVITY=-3;
const int JUMP_VELOCITY=22;
const int TERMINAL_VELOCITY=-20;

class Hero
{
      private:
			  sf::IntRect box;
              int xVel,yVel;
			  int HERO_WIDTH,HERO_HEIGHT;
			  sf::Sprite *herosprite;
			  sf::Texture herotex;
			  Animation anim;

			  int herostate,level,subLevel;
			  bool jump,idle;
			  sf::IntRect walk_right,walk_left,idle_right,idle_left;
			  bool touches_computer;

			  void set_state_frames();
			  void enableJump();

      public:
           
             Hero(int x,int y);
			 void handle_input();
			 void handle_input(const sf::Event &evt);
			 void update(collRectManager *myManager);
			 void display(sf::RenderWindow *window);
			
			 void setPosition(int x,int y);
			 void setState(int);
			 void setLevel(int l);
			 void setSubLevel (int _subLevel);
            
             sf::IntRect getPosition();
			 int getState();
			 sf::Vector2f getCentre();

			 //collision functions
			 bool check_collision(sf::IntRect A, sf::IntRect B,int coll_type=SOLID);
			 bool Touches_Level_Edges_Horizontal(collRectManager *myManager);
			 bool Touches_Level_Edges_Vertical(collRectManager *myManager);
			 bool Touches_Bricks(collRectManager *myManager);
			
};


Hero::Hero(int x, int y)
{
          xVel=0; 
          yVel=0;
          HERO_WIDTH=78;
		  HERO_HEIGHT=95;
		  box.left=x;
		  box.top=y;
		  box.width=HERO_WIDTH;
		  box.height=HERO_HEIGHT;

		  herotex.create(HERO_WIDTH,HERO_HEIGHT);
		  herosprite=new sf::Sprite();
		  herosprite->setTexture(herotex);

		  set_state_frames();

		  anim.set_Strip("Assets/herosprite.png");
		  anim.set_Frame(idle_right);
		  anim.set_TargetTexture(&herotex); // link the spider's texture to the animator
		  anim.set_TotalFrames(1);
		  anim.set_Delay(2);
		  anim.set_Step(1);
		  anim.set_Style(Style::PLAYONCE);

		  jump=false;
		  idle=true;
		  touches_computer=false;
}


void Hero::handle_input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if(jump==false)
			{
				jump=true;
				idle=false;
				yVel=JUMP_VELOCITY;
				if(herostate==IDLE_L || herostate==WALK_L || herostate==GRAB_L)
				{
					anim.set_Values(idle_left,1,Style::PLAYONCE);
					setState(JUMP_L);
				}
				else if(herostate==IDLE_R || herostate==WALK_R || herostate==GRAB_R)
				{
					anim.set_Values(idle_right,1,Style::PLAYONCE);
					setState(JUMP_R);
				}
			}
	}
	else
	{
		idle=true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		xVel=-VELOCITY;
		idle=false;
		anim.set_Values(walk_left,6,Style::LOOP);
		setState(State::WALK_L);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xVel=VELOCITY;
		idle=false;
		anim.set_Values(walk_right,6,Style::LOOP);
		setState(State::WALK_R);
	}
	else
	{
		xVel=0;
		idle=true;
		if(herostate==WALK_L )
		{
			anim.set_Values(idle_left,1,Style::PLAYONCE);
			setState(State::IDLE_L);
		}
		else if(herostate==WALK_R )
		{
			anim.set_Values(idle_right,1,Style::PLAYONCE);
			setState(State::IDLE_R);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//do if anything needed for up key
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//do anything if needed for down key
	}
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if(touches_computer==true)
		{
			openCodingArea(level,subLevel);
			touches_computer=false;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(touches_computer==true)
		{
			wpressed = 1;
			if(compileCode(level,subLevel))			//successful execution of program
			{
				subLevelChanged = 1;
			}
			touches_computer=false;
		}
	}
	
}

void Hero::update(collRectManager *myManager)
{
	box.left+=xVel;
		
	if( Touches_Level_Edges_Horizontal(myManager)||Touches_Bricks(myManager))
	{
		box.left-=xVel;
	}
	
	if(yVel>TERMINAL_VELOCITY)
		yVel=yVel+GRAVITY;
	
	if(box.top > 560) {
		wpressed = 1;
		runsuccess = 0;
		setPosition(800, 300);
	}
	box.top-=yVel;
	
	//if( Touches_Level_Edges_Vertical(myManager)||Touches_Bricks(myManager))
	if(Touches_Bricks(myManager))
	{
		box.top+=yVel;
		yVel=0;
		jump=false;
	}
	
	//if y > screen height -> fell down -> game over
	anim.next();
}

void Hero::display(sf::RenderWindow *window)
{
	herosprite->setPosition((float)box.left,(float)box.top);
	window->draw(*herosprite);
}
sf::Vector2f Hero::getCentre()
{
	return sf::Vector2f((float) box.left+box.width/2,(float) box.top+box.height/2);
}
sf::IntRect Hero::getPosition()
{
     return box;
}

void Hero::setPosition(int x,int y)
{
     box.left=x; //door in's x pos
     box.top=y;    //door in's y pos
	 box.width=HERO_WIDTH;
	 box.height=HERO_HEIGHT;
}
void Hero::setState(int a)
{
	herostate=a;
}

void Hero::setLevel(int l)
{
	level = l;
}

void Hero::setSubLevel(int _subLevel)
{
	subLevel = _subLevel;
}

int Hero::getState()
{
	return herostate;
}
void Hero::set_state_frames()
{
	walk_right.left=0;
	walk_right.top=0;
	walk_right.width=HERO_WIDTH;
	walk_right.height=HERO_HEIGHT;

	walk_left.left=0;
	walk_left.top=HERO_HEIGHT;
	walk_left.width=HERO_WIDTH;
	walk_left.height=HERO_HEIGHT;

	idle_right.left=0;
	idle_right.top=HERO_HEIGHT*2;
	idle_right.width=HERO_WIDTH;
	idle_right.height=HERO_HEIGHT;

	idle_left.left=0;
	idle_left.top=HERO_HEIGHT*3;
	idle_left.width=HERO_WIDTH;
	idle_left.height=HERO_HEIGHT;

}
void Hero::enableJump()
{
	jump=true;	idle=false;
	yVel=JUMP_VELOCITY;
	if(herostate==IDLE_L || herostate==WALK_L || herostate==GRAB_L)
	{
		anim.set_Values(idle_left,1,Style::PLAYONCE);
		setState(JUMP_L);
	}
	else if(herostate==IDLE_R || herostate==WALK_R || herostate==GRAB_R)
	{
		anim.set_Values(idle_right,1,Style::PLAYONCE);
		setState(JUMP_R);
	}
}


bool Hero::check_collision(sf::IntRect A, sf::IntRect B,int coll_type)
{

     int leftA, leftB;
     int rightA, rightB;
     int topA,topB;
     int bottomA,bottomB;
     
     leftA=A.left;
     rightA=A.left+A.width;
     topA=A.top;
     bottomA=A.top+A.height;
  
     leftB=B.left;
     rightB=B.left+B.width;
	 topB=B.top;
     bottomB=B.top+B.height;

	// if(coll_type==SOLID)
     //{     
         if( (bottomA>topB) && (topA<bottomB) && (rightA>leftB) && (leftA<rightB) )
         {
             return true;
         }
         else 
			 return false;
     //}
	 

}
bool Hero::Touches_Level_Edges_Horizontal(collRectManager *myManager)
{
	
	if(box.left<0)
		return true;
	else if(box.left+box.width>myManager->LEVEL_WIDTH)
		return true;
	else return false;
}
bool Hero::Touches_Level_Edges_Vertical(collRectManager *myManager)
{
	
	if(box.top<0)
		return true;
	else if(box.top+box.height>myManager->LEVEL_HEIGHT)
		return true;
	else return false;
}
bool Hero::Touches_Bricks(collRectManager *myManager)
{
	for(int i=0;i<myManager->totalRects;i++)
	{
		if(myManager->myCollRect[i].type==SOLID)
		{
			if(check_collision(box,myManager->myCollRect[i].box)==true)
				return true;
		}
		if(myManager->myCollRect[i].type==INTERACTIVE_OBJECT)
		{
			switch(level)
			{
				case 1:
					if(check_collision(box,myManager->myCollRect[i].box)==true)
					{
						if(touches_computer==false && i==2 )
						{
							touches_computer=true;
						}
						else if( i == 4 )
						{
							levelChanged=1;
						}
					}
					else
					{
						if(i==2)
						{
							touches_computer = false;
						}
					}
					break;

				case 2:
					if(check_collision(box,myManager->myCollRect[i].box)==true)
					{
						if(touches_computer==false && i==2 ) //2nd  collision rectangle is computer collision rectangle
						{
							touches_computer=true;
						}
						else if( i == 3 )
						{
							levelChanged=1;
						}
					}
					else
					{
						if( i == 2 )
						{
							touches_computer = false;
						}
					}
					break;
				case 3:
					if(check_collision(box,myManager->myCollRect[i].box)==true)
					{
						if(touches_computer==false && i==2 ) //2nd  collision rectangle is computer collision rectangle
						{
							touches_computer=true;
						}
						else if( i == 3 )
						{
							levelChanged=1;
						}
					}
					else
					{
						if( i == 2 )
						{
							touches_computer = false;
						}
					}
					break;
				case 4:
					if(check_collision(box,myManager->myCollRect[i].box)==true)
					{
						if(touches_computer==false && i==4 ) //4th  collision rectangle is computer collision rectangle
						{
							touches_computer=true;
						}
						else if( i == 5 )
						{
							levelChanged=1;
						}
					}
					else
					{
						if( i == 4 )
						{
							touches_computer = false;
						}
					}
					break;
				default:
					std::cout<<"\nError with collision rectangle detection";
					break;
			}

		}
	}
			
	return false;
}




#endif
