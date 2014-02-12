// Tankie.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "iostream"
#include "hero.h"
#include "CollRectManager.h"
#include "Eva.h"
#include "Tutorial.h"

const int LEVEL = 1;
const int TUTORIAL = 0;
sf::RenderWindow *window;
sf::Clock gClock;

std::string getBgLocation(int level)
{
	std::string bgLocation = "Assets/background";
	bgLocation += std::to_string(level);
	bgLocation += ".png";
	return bgLocation;
}

void otherDisplays(int level)
{
	if(level == 1)
	{	
		animate_eva();
		display_eva(window);
	}
}
void otherInitializations(int level)
{
	if(level == 1)
	{
		Init_Eva(50,200);
	}
}
int main()
{
 
	window=new sf::RenderWindow(sf::VideoMode(1000,562), "Final Year Project",sf::Style::Close);
	window->setFramerateLimit(20);

	int SCENE = TUTORIAL;
	int level = 0, tutorial = 1;
	int noOfTutorials[3] = {5,3,3};
	int collisionRects[3]={0,5,2};
	
	sf::Sprite *bgsprite = new sf::Sprite;
	sf::Texture bgtex;
	sf::Clock lClock;
	Hero *myHero;

	//BACKGROUND

	init_tutorial(level,tutorial);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				if(SCENE!=TUTORIAL)
					SCENE=TUTORIAL;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				if(SCENE == TUTORIAL)
				{
					end_tutorial(level,tutorial);
					if(level == 0)
						levelChanged =1;
					SCENE=LEVEL;
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				if(SCENE == TUTORIAL)
				{
					++tutorial;
					if(tutorial > noOfTutorials[level])
					{
						--tutorial;
					}
					else
					{
						init_tutorial(level,tutorial); //move through tutorials
					}
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				if( SCENE == TUTORIAL )
				{
					--tutorial;
					if(tutorial<1)
					{
						++tutorial;
					}
					else
					{
						init_tutorial(level,tutorial); //move through tutorials
					}
				}
			}
        }

		if(levelChanged)
		{
			sf::Time time = gClock.getElapsedTime();
			if(level >= 1)
			{
				std::cout << std::endl << "..................................................." << std::endl;
				std::cout << std::endl << "Time taken to complete level " << level << " : " << time.asSeconds() << " seconds." << std::endl;
				std::cout << std::endl << "..................................................." << std::endl;
				std::cout << std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl ;
			}
			gClock.restart();
			level++;
			tutorial = 1;

			std::string bgLocation = getBgLocation(level);

			if(!bgtex.loadFromFile(bgLocation))
			{
				std::cout<<"\nError loading background";
			}

			bgsprite->setTexture(bgtex);
			bgsprite->setTextureRect(sf::IntRect(0,0,1000,562));

			init_tutorial(level,tutorial);
			otherInitializations(level);
			//HERO
			myHero = new Hero(700,300);
			myHero->setLevel(level);
			myManager->setTotalRects(collisionRects[level]);
			myManager->initRects(level);

			levelChanged = 0;
		}

		switch(SCENE)
		{
		case LEVEL:
				myHero->handle_input();
				myHero->update(myManager);
				window->clear();
				window->draw(*bgsprite);
				otherDisplays(level);
				myHero->display(window);
				break;
		case TUTORIAL:
				window->clear();
				show_tutorial(window);
				break;
		}
		window->display();
    }

	return 0;
}

