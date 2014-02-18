// Tankie.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "iostream"
#include "hero.h"
#include "CollRectManager.h"
#include "Eva.h"
#include "Robo.h"
#include "ImageLoader.h"
#include "Tutorial.h"
#include "WinHttpClient.h"
#include "Intellisense.h"
#include "WebsiteInteractor.h"

const int LEVEL = 1;
const int TUTORIAL = 0;

int deathflag;
int showhero;
int gameover;

sf::RenderWindow *window;
sf::Text attemptsText;

std::string getStringTime(int num)
{
	std::string ret = "";
	std::string digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	ret = digits[num / 10] + digits[num % 10];
	return ret;
}

std::string getStringFromSeconds(int seconds) {
	int hour = seconds / 3600;
	int rem = seconds % 3600;
	int min = rem / 60;
	int sec = rem % 60;
	std::string timeToSet = getStringTime(hour) + ":" + getStringTime(min) + ":" + getStringTime(sec);
	return timeToSet;
}


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
		;
	}
	if(level == 4)
	{
		if(runsuccess == 1)
		{
			//Animation_Code
			if(finishedMoving != 1)
			{
				if(!robo1Initialized)
				{
					if(move3==1)
					{
						Init_Robo1(150,80);//end
						robo1Initialized=1;
						robo2Initialized=0;
					}
					else if(move2==1)
					{
						Init_Robo1(310,80);//middle
						robo1Initialized=1;
						robo2Initialized=0;
					}
					else if(move1==1)
					{
						Init_Robo1(470,80);//start
						robo1Initialized=1;
						robo2Initialized=0;
					}
				}
				if(!move3)
					animate_robo_move(level);
				finishedStanding=0;
			}
			else
			{
				if(!robo2Initialized)
				{
					if(move3==1)
					{
						Init_Robo2(150,80);//end
						robo2Initialized=1;
						robo1Initialized=0;
					}
					else if(move2==1)
					{
						Init_Robo2(310,80);//middle
						robo2Initialized=1;
						robo1Initialized=0;
					}
					else if(move1==1)
					{
						Init_Robo2(470,80);//start
						robo2Initialized=1;
						robo1Initialized=0;
					}
				}
				animate_robo_stand(level);
				if(finishedStanding)
					finishedMoving=0;
			}
			display_robo(window);

			if((move1 || move2) && !move3)
			{
				set_Image(370,223,180,296,"Assets/opened_door.png");//1st door close -> open
				display_image(window);
				set_Image(190,223,180,296,"Assets/opened_door.png");//2nd door open
				display_image(window);
				set_Image(41,215,180,296,"Assets/closed_door.png");//3rd door close
				display_image(window);
				myManager->changePosition(0,0,1,1,1);
				myManager->changePosition(0,0,1,1,2);
			}
			else if(move3)
			{
				set_Image(370,223,180,296,"Assets/opened_door.png");//1st door close -> open
				display_image(window);
				set_Image(190,223,180,296,"Assets/opened_door.png");//2nd door open
				display_image(window);
				set_Image(41,223,180,296,"Assets/opened_door.png");//3rd door close -> open
				display_image(window);
				myManager->changePosition(0,0,1,1,3);
			}
			else
			{
				set_Image(370,215,180,296,"Assets/closed_door.png");//1st door close
				display_image(window);
				set_Image(190,223,180,296,"Assets/opened_door.png");//2nd door open
				display_image(window);
				set_Image(41,215,180,296,"Assets/closed_door.png");//3rd door close
				display_image(window);
			}
		}
		else if(runsuccess == 0)
		{
			//failure
		}
		else
		{
			//initial configuration
			set_Image(370,215,180,296,"Assets/closed_door.png");//1st door close
			display_image(window);
			set_Image(190,223,180,296,"Assets/opened_door.png");//2nd door open
			display_image(window);
			set_Image(41,215,180,296,"Assets/closed_door.png");//3rd door close
			display_image(window);
			display_robo(window);
		}
	}
}
void otherInitializations(int level)
{
	if(level == 1)
	{
		Init_Eva(50,200);
	}
	if(level == 4)
	{
		Init_Robo1(630,80);
	}
	Init_Image();
}

void checkCodeCompiled(int level, int subLevel)
{
	if(wpressed == 1) {
		if(runsuccess == 0)
		{
			attempts--;
			deathflag = 1;
		}
		if(attempts < 0)
		{
			gameover = 1;
			attempts = 0;
		}
		wpressed = 0;
		attemptsText.setString("Lives : " + std::to_string(attempts));
	}
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

int main()
{
 
	int SCENE = TUTORIAL;
	int level = 0, tutorial = 1, subLevel = 1;
<<<<<<< HEAD
	int noOfTutorials[6] = {5,6,10,2,3,4};
	int noOfSubLevels[6] = {0,0,3,0,0,0};
	int collisionRects[6] = {0,5,4,4,6,5};
=======
	int noOfTutorials[4] = {5,6,10,2};
	int noOfSubLevels[4] = {0,0,3,0};
	int collisionRects[4] = {0,5,4,4};
	int targetTimeInt[5] = {0, 75, 255, 120, 200};
>>>>>>> 2c7aee5add09be9d67a90facf022a508f3ebd460
	bool firsttime = true;
	int timeForThisLevel;

	//Choice between guest play and login play
	std::string user ="";
	std::string username = "";
	std::string password = "";
	char choice;
	
	std::cout << "Welcome to Code N Fun. Have fun while learning programming ! " << std::endl << std::endl;
	
	//while begins
	while(true) {
		std::cout << "Press 'G' to play as a guest or 'L' to login with your account : ";
		std::cin >> choice;
		if(choice == 'G' || choice == 'g') {
			user="guest";
			break;
		}
		else 
			if(choice == 'L' || choice == 'l')
			{
				std::cout << "Enter your username : ";
				std::cin >> username;
				std::cout << "Enter your password : ";
				std::cin >> password;

				int ret = checkLogin(username, password);
				if(ret == -1) {
					std::cout << "Invalid username/password combination ! Try again." << std::endl << std::endl;
					continue;
				}
				else
					if(ret == -2) {
						std::cout << "Server down ! Please try again." << std::endl << std::endl;
						continue;
					}
					else {
						level = ret;
						std::cout << "Successfully logged in ! " << std::endl << std::endl;
						user = username;
						break;

					}


			}
			else
				continue;
	}//while loop ends
	

	window=new sf::RenderWindow(sf::VideoMode(1000,562), "Final Year Project",sf::Style::Close);
	window->setFramerateLimit(20);

	showhero = 1;
	gameover = 0;

	sf::Sprite *bgsprite = new sf::Sprite;
	sf::Texture bgtex;
	sf::Clock lClock;
	sf::Time lTime;
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
	
	sf::Text targetTime;
	targetTime.setFont(font);
	targetTime.setCharacterSize(35);
	targetTime.setString("00:00:00");
	targetTime.setColor(sf::Color::Green);
	targetTime.setStyle(sf::Text::Bold);
	targetTime.setPosition(240, 10);
	
	sf::Text levelText;
	levelText.setFont(font);
	levelText.setCharacterSize(35);
	levelText.setString("Level : 0");
	levelText.setColor(sf::Color::Green);
	levelText.setStyle(sf::Text::Bold);
	levelText.setPosition(830, 10);

	sf::Text oopsText;
	oopsText.setFont(font);
	oopsText.setCharacterSize(25);
	oopsText.setString("Oops ! Nefario dies.");
	oopsText.setColor(sf::Color::Blue);
	oopsText.setStyle(sf::Text::Bold);
	oopsText.setPosition(350, 200);

	hintText.setFont(font);
	hintText.setCharacterSize(20);
	hintText.setString("");
	hintText.setColor(sf::Color::White);
	hintText.setStyle(sf::Text::Bold);
	hintText.setPosition(100, 70);

	attemptsText.setFont(font);
	attemptsText.setCharacterSize(35);
	attemptsText.setColor(sf::Color::Red);
	attemptsText.setPosition(580, 10);
	attemptsText.setStyle(sf::Text::Bold);
	attemptsText.setString("Lives : 3");


	Hero *myHero;

	//BACKGROUND

	//std::cout << "levels completed : " << level << std::endl;
	init_tutorial(level,tutorial);
	if(level >=1) {
		SCENE = LEVEL;
		levelChanged = 1;
	}
    while (window->isOpen())
    {
        sf::Event event;
		if(gameover == 1)
			break;
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
			std::string timeToSet = getStringFromSeconds(seconds);
			timer.setString(timeToSet);
			levelText.setString("Level : " + getStringTime(level));

		}

		if(deathflag == 1) {
			showhero = 0;
			lClock.restart();
			deathflag = 0;
		}

		if(showhero == 0) {
			lTime = lClock.getElapsedTime();
			int sec = (int)lTime.asSeconds();
			if(sec >=3) {
				showhero = 1;
				myHero->setPosition(800, 300);
			}
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
			levelDifficulty = AVERAGE;
			timeToIncrease = timeToDecrease = 0;
			hintRequired = false;
			hintText.setString("");

			wpressed = 0;
			deathflag = 0;

			//Do not get the metrics for the first time the user enters the game
			if(!firsttime){
				int secondsTakenToComplete = printTimetakentoCompleteLevel(level);
				int performance = getPerformance(level, secondsTakenToComplete);
				setDifficultyForNextLevel(level, performance);
				setTimeVariance();
				if(level == 2)
						subLevel--;
				int pSize = programSize(level, subLevel);
				int numberOfAttemptsTaken = 3 - attempts + 1;
				printReport(secondsTakenToComplete, targetTimeInt[level], pSize, numberOfAttemptsTaken, performance, level, executionTime);
				if(username.compare("guest") != 0)
					updateLog(username, level, secondsTakenToComplete, numberOfAttemptsTaken, executionTime, pSize);
			}

			attempts = 3;
			executionTime = 0.0;
			firsttime = false;
			level++;

			//Set number of lives remaining
			attemptsText.setString("Lives : 3");

			//Set target time
			timeForThisLevel = targetTimeInt[level];
			timeForThisLevel = timeForThisLevel + timeToIncrease - timeToDecrease;
			//std::cout << timeToIncrease << "  " << timeToDecrease << std::endl;
			//std::cout << "time for this level-" << level << " is : " << timeForThisLevel << std::endl;
			//std::cout << getStringFromSeconds(timeForThisLevel) << std::endl;
			targetTime.setString("Target : " + getStringFromSeconds(timeForThisLevel));

			runsuccess = 2;
			gClock.restart();
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

			myHero = new Hero(800,300);
			myHero->setLevel(level);
			myHero->setSubLevel(subLevel);
			myManager->setTotalRects(collisionRects[level]);
			myManager->initRects(level);

			levelChanged = 0;
		}
	
		displayHintIfRequired(level);

		switch(SCENE)
		{
			case LEVEL:
				myHero->handle_input();
				myHero->update(myManager);
				window->clear();
				window->draw(*bgsprite);
				window->draw(targetTime);
				window->draw(levelText);
				window->draw(hintText);
				otherDisplays(level,subLevel);
				window->draw(timer);
				checkCodeCompiled(level,subLevel);
				window->draw(attemptsText);
				myHero->setSubLevel(subLevel);
				if(showhero == 1) {
					myHero->display(window);
				}
				else {
					window->draw(oopsText);
				}
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

