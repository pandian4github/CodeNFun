// Tankie.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "iostream"
#include "hero.h"
#include "CollRectManager.h"
#include "Eva.h"
#include "ImageLoader.h"
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

void otherDisplays(int level, int subLevel)
{
	if(level == 1)
	{	
		animate_eva();
		display_eva(window);
	}
	if(level == 2)
	{
		if(subLevel == 1) //display int question 
		{
			set_Image(109,133,185,146,"Assets/int_mul_question.png");	//set int question
			display_image(window);										//display
		}
		else if(subLevel == 2)//display int result for 3 secs and switch over to float
		{
			set_Image(148,385,60,85,"Assets/green_button_level2.png");		//first green light
			display_image(window);
			set_Image(109,133,185,146,"Assets/float_div_question.png");		//float question
			display_image(window);//display
		}
		else if(subLevel == 3)//display double result and display platform
		{
			set_Image(148,385,60,85,"Assets/green_button_level2.png");		//first green light
			display_image(window);
			set_Image(199,384,60,85,"Assets/green_button_level2.png");		//second green light
			display_image(window);
			set_Image(109,133,185,146,"Assets/double_add_question.png");	//double question
			display_image(window);//display
		}
		else
		{
			set_Image(148,385,60,85,"Assets/green_button_level2.png");		//first green light
			display_image(window);
			set_Image(199,384,60,85,"Assets/green_button_level2.png");		//second green light
			display_image(window);
			set_Image(252,384,60,85,"Assets/green_button_level2.png");		//third green light
			display_image(window);
			set_Image(109,133,185,146,"Assets/double_add_answer.png");		//double answer question
			display_image(window);											//display
			set_Image(314,448, 294, 59,"Assets/floor_level2.png");
			display_image(window);
		}
	}
	if(level == 3)
	{
		
	}
}
void otherInitializations(int level)
{
	if(level == 1)
	{
		Init_Eva(50,200);
	}
	Init_Image();
}

void checkCodeCompiled(int level, int subLevel)
{
	switch(level)
	{
	case 1 : if(runsuccess == 0)
			 {
				set_Image(645, 20, 155, 136, "Assets/try_again.png");
				display_image(window);
			 }
			 else
				 if(runsuccess == 1)
				 {
					set_Image(645, 20, 155, 136, "Assets/move_up.png");
					display_image(window);
				 }
			break;
	case 2: 
			break;
	case 3: if(runsuccess == 0)
			{
				set_Image(0,218,131,284,"Assets/closed_gate.png");
				display_image(window);
			}
			else
			{
				if(runsuccess == 1)
				{
					set_Image(0, 215, 117, 280, "Assets/opened_gate.png");
					display_image(window);
				}
				else
				{
					set_Image(0,218,131,284,"Assets/closed_gate.png");
					display_image(window);
				}
			}
			break;
	default:
			break;
	}
}

void collisionRectangleChange(int level,int subLevel)
{
	if(level == 2 && subLevel == 4)
		myManager->changePosition(20,490,690,1,1);	//include the complete platform
	if(level == 3)
		myManager->changePosition(0,0,1,1,1);		//gate opened
}
std::string getStringTime(int num)
{
	std::string ret = "";
	std::string digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	ret = digits[num / 10] + digits[num % 10];
	return ret;
}

int main()
{
 
	window=new sf::RenderWindow(sf::VideoMode(1000,562), "Final Year Project",sf::Style::Close);
	window->setFramerateLimit(20);

	int SCENE = TUTORIAL;
	int level = 0, tutorial = 1, subLevel = 1;
	int noOfTutorials[4] = {5,6,10,2};
	int noOfSubLevels[4] = {0,0,3,0};
	int collisionRects[4] = {0,5,4,4};
	
	sf::Sprite *bgsprite = new sf::Sprite;
	sf::Texture bgtex;
	sf::Clock lClock;
	sf::Text timer;
	sf::Font font;
	if(!(font.loadFromFile("Assets/arial.ttf")))
	{
		std::cout << "Error loading font ! " << std::endl;
	}

	
	timer.setFont(font);
	timer.setCharacterSize(35);
	timer.setString("00:00:00");
	timer.setColor(sf::Color::Red);
	timer.setStyle(sf::Text::Bold);
	timer.setPosition(10, 10);
	
	sf::Text levelText;
	levelText.setFont(font);
	levelText.setCharacterSize(35);
	levelText.setString("Level : 0");
	levelText.setColor(sf::Color::Red);
	levelText.setStyle(sf::Text::Bold);
	levelText.setPosition(830, 10);

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


		sf::Time time = gClock.getElapsedTime();
		if(level >=1)
		{
			int seconds = (int)time.asSeconds();
			//std::cout << (int)time.asSeconds() << std::endl;
			int hour = seconds / 3600;
			int rem = seconds % 3600;
			int min = rem / 60;
			int sec = rem % 60;
			std::string timeToSet = getStringTime(hour) + ":" + getStringTime(min) + ":" + getStringTime(sec);
			timer.setString(timeToSet);

			levelText.setString("Level : " + getStringTime(level));
		}

		if(subLevelChanged)
		{
			if(subLevel <= noOfSubLevels[level])
			{
				subLevel++;
			}
			collisionRectangleChange(level,subLevel);
			subLevelChanged = 0;
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
			runsuccess = 2;
			gClock.restart();
			level++;
			tutorial = 1;
			subLevel = 1;

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
			myHero->setSubLevel(subLevel);
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
				window->draw(timer);
				window->draw(levelText);
				otherDisplays(level,subLevel);
				checkCodeCompiled(level,subLevel);
				myHero->setSubLevel(subLevel);
				myHero->display(window);
				break;
			case TUTORIAL:
				window->clear();
				runsuccess = 2;
				show_tutorial(window);
				break;
		}
		window->display();
    }

	return 0;
}

