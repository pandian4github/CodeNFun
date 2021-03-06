// Tankie.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "iostream"
#include "Character.h"
#include "CollRectManager.h"
#include "Eva.h"
#include "Robo.h"
#include "ImageLoader.h"
#include "Tutorial.h"
#include "Mission.h"
#include "WinHttpClient.h"
#include "Intellisense.h"
#include "WebsiteInteractor.h"

const int LEVEL = 1;
const int TUTORIAL = 0;
const int MISSION = 2;

int deathflag;
int showhero;
int gameover;
int correctTreeInsertions = 0;
int correctEntryMade = -1;
sf::RenderWindow *window;
sf::Text attemptsText;
sf::Text treeInput;

std::string treeInp = "";

void collisionRectangleChange(int,int);

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
	else if(level == 2)
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
	else if(level == 3)
	{
		;
	}
	else if(level == 4)
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
			set_Image(370,215,180,296,"Assets/closed_door.png");//1st door close
			display_image(window);
			set_Image(190,223,180,296,"Assets/opened_door.png");//2nd door open
			display_image(window);
			set_Image(41,215,180,296,"Assets/closed_door.png");//3rd door close
			display_image(window);
			display_robo(window);
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
	else if(level == 5)
	{
		animate_eva();
		if(runsuccess == 1)
		{
			//animate
			if(finishedMoving != 1)
			{
				if(!robo1Initialized)
				{
					if(move3==1)
					{
						Init_Robo3(710,98);//end
						robo1Initialized=1;
						robo2Initialized=0;
					}
					else if(move2==1)
					{
						Init_Robo3(555,98);//middle
						robo1Initialized=1;
						robo2Initialized=0;
					}
					else if(move1==1)
					{
						Init_Robo3(400,98);//start
						robo1Initialized=1;
						robo2Initialized=0;
					}
				}
				if(!move3)
				{
					animate_robo_move(level);
					finishedStanding=0;
				}
				else
				{
					finishedStanding = 1;
					//Move Eva Up and change the collision rectangle
					changeEvaPosition(level);
				}
			}
			else
			{
				if(!robo2Initialized)
				{
					if(move3==1)
					{
						Init_Robo4(667,102);//end
						robo2Initialized=1;
						robo1Initialized=0;
					}
					else if(move2==1)
					{
						Init_Robo4(512,102);//middle
						robo2Initialized=1;
						robo1Initialized=0;
					}
					else if(move1==1)
					{
						Init_Robo4(359,102);//start
						robo2Initialized=1;
						robo1Initialized=0;
					}
				}
				animate_robo_stand(level);
				display_image(window);
				if(finishedStanding)
					finishedMoving=0;
			}
			if(move1 && move2 && move3)
			{
				if(finishedStanding)
				{
					set_Image(372,79,84,50,"Assets/numbers/5.png");
					display_image(window);
					set_Image(501,79,80,50,"Assets/numbers/6.png");
					display_image(window);
					set_Image(630,78,87,50,"Assets/numbers/4.png");
					display_image(window);
					//display 5,6 and 4
				}
				else
				{
					set_Image(372,79,84,50,"Assets/numbers/5.png");
					display_image(window);
					set_Image(501,79,80,50,"Assets/numbers/6.png");
					display_image(window);
					//display 5 and 6
				}
			}
			else if(move1 && move2)
			{
				if(finishedMoving == 0)
				{
					set_Image(372,79,84,50,"Assets/numbers/5.png");
					display_image(window);
					set_Image(501,79,80,50,"Assets/numbers/6.png");
					display_image(window);
					//display 5 and 6
				}
				else
				{
					set_Image(372,79,84,50,"Assets/numbers/5.png");
					display_image(window);
					//display 5
				}
			}
			else if(move1)
			{
				if(finishedStanding)
				{
					set_Image(372,79,84,50,"Assets/numbers/5.png");
					display_image(window);
					//display 5;
				}
				else
				{
					display_image(window);
				}
			}
			else
			{
				display_image(window);
			}
			//end animation
		}
		display_eva(window);
		display_robo(window);
	}
	else if(level == 6)
	{
		if(runsuccess == 1)
		{
			//display the text 2;
			if(isLoopUsed(level))
			{
				runsuccess = 0;
				set_Image(292,244,196,90,"Assets/level6_text1.png");
				display_image(window);
			}
			else
			{
				set_Image(292,244,196,90,"Assets/level6_text2.png");
				display_image(window);
			}
		}
		else
		{
			//display text 1;
			set_Image(292,244,196,90,"Assets/level6_text1.png");
			display_image(window);
		}
	}
	else if(level == 7 || level == 9)
	{
		if(runsuccess == 1)
		{
			//display text1
			set_Image(503,244,196,90,"Assets/level7_text2.png");
			display_image(window);
			int i;
			for(i=0;i<5;i++)
			{
				if (crateMove[i]!=3)
				{
					animate_crate_move(i);
					display_crate(window,i);
					break;
				}
			}
			for(i=0;i<5;i++)
			{
				if(crateMove[i]==3)
				{
					if(i==4)
						display_crate(window,5); //crate at the start

					display_crate(window,i);
				}
			}
		}
		else
		{
			//display text2
			set_Image(503,244,196,90,"Assets/level7_text1.png");
			display_image(window);
			display_crate(window,0);
		}
		set_Image(616,347,50,132,"Assets/scientist_front.png");
		display_image(window);
	}
	if(level == 8 || level == 10)
	{
		if(runsuccess == 1)
		{
			//process the queue and then finish the animation
			int i,flag=0;

			frame_count1 = (frame_count1+1)%41;
			if(frame_count1>39)
			{
				finishedMoving = !finishedMoving;
				if(finishedMoving)
					for(i=0;i<5;i++)
					{
						if(crateMove[i]<=5)
						{
							crateMove[i]++;
							if(crateMove[4]==6)
								collisionRectangleChange(level,subLevel);
						}
					}
			}
			if(!finishedMoving)
			{
				for(i=0;i<5;i++)
				{
					flag=1;
					switch (crateMove[i])
					{
					case 4:
						cratesprite[i]->move(-2,0);
						display_crate(window,i);
						break;
					case 3:
						cratesprite[i]->move(-1.5,0);
						display_crate(window,i);
						break;
					case 2:
						cratesprite[i]->move(-1.5,0);
						display_crate(window,i);
						break;
					case 1:
						cratesprite[i]->move(-1.5,0);
						display_crate(window,i);
						break;
					case 0:
						cratesprite[i]->move(-1.5,0);
						display_crate(window,i);
						break;
					default:
						flag=0;
						break;
					}
				}
			}
			else
			{
				for(i=0;i<5;i++)
				{
					if(crateMove[i]<=5)
					{
						display_crate(window,i);
						flag=1;
					}
				}
			}
			if(flag == 1)
			{
				if(frame_count1<11 || (frame_count1>20 && frame_count1<31))
				{
					set_Image(0,285,125,154,"Assets/charge0.png");
					display_image(window);
				}
				else
				{
					set_Image(0,285,125,154,"Assets/charge1.png");
					display_image(window);
				}
			}
		}
		else
		{
			//animate the charge
			//use frame_count1 for charge
			set_Image(110,374,41,79,"Assets/robo5.png");
			display_image(window);

			set_Image(174,374,41,79,"Assets/robo5.png");
			display_image(window);

			set_Image(238,374,41,79,"Assets/robo5.png");
			display_image(window);

			set_Image(302,374,41,79,"Assets/robo5.png");
			display_image(window);

			set_Image(366,374,41,79,"Assets/robo5.png");
			display_image(window);

			frame_count1 = (frame_count1+1)%21;
			if(frame_count1<11)
			{
				set_Image(0,285,125,154,"Assets/charge0.png");
				display_image(window);
			}
			else
			{
				set_Image(0,285,125,154,"Assets/charge1.png");
				display_image(window);
			}
		}
		set_Image(596,349,50,132,"Assets/scientist_front.png");
		display_image(window);
	}
	if(level == 11)
	{
		if(runsuccess == 1)
		{
			set_Image(705,232,197,90,"Assets/level11_text6.png");
			display_image(window);
		}
		else
		{
			set_Image(705,232,197,90,"Assets/level11_text5.png");
			display_image(window);
		}
		if(subLevel == 1)
		{
			int i=0;
			for(i=0;i<16;i++)
			{
				if(i==1 && correctTreeInsertions>=i)
				{
					set_Image(325,59,50,50, "Assets/numbers/50.png");
					display_image(window);
				}
				else if(i==2 && correctTreeInsertions>=i)
				{
					set_Image(190,152,50,50, "Assets/numbers/30.png");
					display_image(window);
				}
				else if(i==3 && correctTreeInsertions>=i)
				{
					set_Image(258,247,50,50, "Assets/numbers/40.png");
					display_image(window);
				}
				else if(i==4 && correctTreeInsertions>=i)
				{
					set_Image(223,335,50,50, "Assets/numbers/35.png");
					display_image(window);
				}
				else if(i==5 && correctTreeInsertions>=i)
				{
					set_Image(464,152,50,50, "Assets/numbers/70.png");
					display_image(window);
				}
				else if(i==6 && correctTreeInsertions>=i)
				{
					set_Image(123,247,50,50, "Assets/numbers/15.png");
					display_image(window);
				}
				else if(i==7 && correctTreeInsertions>=i)
				{
					set_Image(292,334,50,50, "Assets/numbers/45.png");
					display_image(window);
				}
				else if(i==8 && correctTreeInsertions>=i)
				{
					set_Image(395,247,50,50, "Assets/numbers/60.png");
					display_image(window);
				}
				else if(i==9 && correctTreeInsertions>=i)
				{
					set_Image(90,334,50,50, "Assets/numbers/10.png");
					display_image(window);
				}
				else if(i==10 && correctTreeInsertions>=i)
				{
					set_Image(429,334,50,50, "Assets/numbers/65.png");
					display_image(window);
				}
				else if(i==11 && correctTreeInsertions>=i)
				{
					set_Image(531,247,50,50, "Assets/numbers/80.png");
					display_image(window);
				}
				else if(i==12 && correctTreeInsertions>=i)
				{
					set_Image(565,334,50,50, "Assets/numbers/85.png");
					display_image(window);
				}
				else if(i==13 && correctTreeInsertions>=i)
				{
					set_Image(158,334,50,50, "Assets/numbers/20.png");
					display_image(window);
				}
				else if(i==14 && correctTreeInsertions>=i)
				{
					set_Image(362,334,50,50, "Assets/numbers/55.png");
					display_image(window);
				}
				else if(i==15 && correctTreeInsertions>=i)
				{
					set_Image(496,334,50,50, "Assets/numbers/75.png");
					display_image(window);
				}
				switch(correctTreeInsertions)
				{
				case 0:
					set_Image(80,70,50,50, "Assets/numbers/50.png");
					display_image(window);
					break;
				case 1:
					set_Image(80,70,50,50, "Assets/numbers/30.png");
					display_image(window);
					break;
				case 2:
					set_Image(80,70,50,50, "Assets/numbers/40.png");
					display_image(window);
					break;
				case 3:
					set_Image(80,70,50,50, "Assets/numbers/35.png");
					display_image(window);
					break;
				case 4:
					set_Image(80,70,50,50, "Assets/numbers/70.png");
					display_image(window);
					break;
				case 5:
					set_Image(80,70,50,50, "Assets/numbers/15.png");
					display_image(window);
					break;
				case 6:
					set_Image(80,70,50,50, "Assets/numbers/45.png");
					display_image(window);
					break;
				case 7:
					set_Image(80,70,50,50, "Assets/numbers/60.png");
					display_image(window);
					break;
				case 8:
					set_Image(80,70,50,50, "Assets/numbers/10.png");
					display_image(window);
					break;
				case 9:
					set_Image(80,70,50,50, "Assets/numbers/65.png");
					display_image(window);
					break;
				case 10:
					set_Image(80,70,50,50, "Assets/numbers/80.png");
					display_image(window);
					break;
				case 11:
					set_Image(80,70,50,50, "Assets/numbers/85.png");
					display_image(window);
					break;
				case 12:
					set_Image(80,70,50,50, "Assets/numbers/20.png");
					display_image(window);
					break;
				case 13:
					set_Image(80,70,50,50, "Assets/numbers/55.png");
					display_image(window);
					break;
				case 14:
					set_Image(80,70,50,50, "Assets/numbers/75.png");
					display_image(window);
					break;
				default:
					break;
				}
				if(correctEntryMade==1)
				{
					set_Image(316,430,100,50,"Assets/level11_text2.png");
					display_image(window);
				}
				else if(correctEntryMade == 0)
				{
					set_Image(316,430,100,50,"Assets/level11_text3.png");
					display_image(window);
				}
				set_Image(80,50,55,20,"Assets/level11_text1.png");
				display_image(window);
			}
		}
		else if(subLevel == 2 || subLevel == 3)
		{
			set_Image(325,59,50,50, "Assets/numbers/50.png");
			display_image(window);
			
			set_Image(190,152,50,50, "Assets/numbers/30.png");
			display_image(window);
			
			set_Image(258,247,50,50, "Assets/numbers/40.png");
			display_image(window);
			
			set_Image(223,335,50,50, "Assets/numbers/35.png");
			display_image(window);
			
			set_Image(464,152,50,50, "Assets/numbers/70.png");
			display_image(window);

			set_Image(123,247,50,50, "Assets/numbers/15.png");
			display_image(window);
			
			set_Image(292,334,50,50, "Assets/numbers/45.png");
			display_image(window);
			
			set_Image(395,247,50,50, "Assets/numbers/60.png");
			display_image(window);
			
			set_Image(90,334,50,50, "Assets/numbers/10.png");
			display_image(window);
			
			set_Image(429,334,50,50, "Assets/numbers/65.png");
			display_image(window);
			
			set_Image(531,247,50,50, "Assets/numbers/80.png");
			display_image(window);
			
			set_Image(565,334,50,50, "Assets/numbers/85.png");
			display_image(window);
			
			set_Image(158,334,50,50, "Assets/numbers/20.png");
			display_image(window);
			
			set_Image(362,334,50,50, "Assets/numbers/55.png");
			display_image(window);
			
			set_Image(496,334,50,50, "Assets/numbers/75.png");
			display_image(window);

			if(subLevel==2)
			{
				set_Image(114,412,492,20,"Assets/level11_text4.png");
				display_image(window);
			}

			window->draw(treeInput);
		}
	}
}
void otherInitializations(int level)
{
	if(level == 1)
	{
		Init_Eva(50,200);
	}
	else if(level == 4)
	{
		Init_Robo1(630,80);
	}
	else if(level == 5)
	{
		Init_Eva(169,288);
		Init_Robo3(240,98);
		finishedStanding = finishedMoving = move1 = move2 = move3 = robo1Initialized = robo2Initialized = 0;
	}
	else if(level == 7 || level == 9)
	{
		Init_Crate(191,383,0);
		Init_Crate(191,383,1);
		Init_Crate(191,383,2);
		Init_Crate(191,383,3);
		Init_Crate(191,383,4);
		Init_Crate(191,383,5);
	}
	else if(level == 8 || level == 10)
	{
		Init_Robo5(110,374,0);
		Init_Robo5(174,374,1);
		Init_Robo5(238,374,2);
		Init_Robo5(302,374,3);
		Init_Robo5(366,374,4);

		frame_count1 = 0;
		finishedMoving = 0;
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
				changeEvaPosition(level);
				display_image(window);
			 }
			 else
				 if(runsuccess == 1)
				 {
					set_Image(645, 20, 155, 136, "Assets/move_up.png");
					changeEvaPosition(level);
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
	case 4:
			break;
	case 5:
			break;
	case 6:
			frame_count1=0;
			break;
	default:
			break;
	}
}

void collisionRectangleChange(int level,int subLevel)
{
	if(level == 2 && subLevel == 4)
		myManager->changePosition(20,490,690,1,1);	//include the complete platform
	else if(level == 3)
		myManager->changePosition(0,0,1,1,1);		//gate opened
	else if(level == 6)
		myManager->changePosition(0,0,0,0,2);		//scientist gives way for player
	else if(level == 7 || level == 9)
		myManager->changePosition(0,0,0,0,2);		//scientist gives way for player
	else if(level == 8 || level == 10)
		myManager->changePosition(0,0,0,0,2);		//scientist gives way for player
	else if(level == 11)
		myManager->changePosition(0,0,0,0,2);		//scientist gives way for player
}

int main()
{
 
	int SCENE = TUTORIAL;
	int level = 0, tutorial = 1, subLevel = 1;

	int noOfTutorials[13] = {6,6,10,2,12,6,3,6,6,7,4,9,4};
	int noOfSubLevels[13] = {0,0,3,0,0,0,0,0,0,0,0,3,0};
	int collisionRects[13] = {0,5,4,4,6,4,15,4,4,4,4,4,4};
	int targetTimeInt[13] = {0, 75, 255, 120, 100, 100,150,230,250,450,500,550, 200};

	bool firsttime = true;
	bool usernameEntered = false;
	int playerTypeDefined = 0;
	int timeForThisLevel;

	//Choice between guest play and login play
	std::string user ="";
	std::string username = "";
	std::string password = "";
	std::string passwordStar = "";

	char choice;
	
	std::cout << "Welcome to Code N Fun. Have fun while learning programming ! " << std::endl << std::endl;
	
	//while begins
	/*while(true) {
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
	*/

	window=new sf::RenderWindow(sf::VideoMode(1000,562), "Code N Fun",sf::Style::Close);
	window->setFramerateLimit(20);

	showhero = 1;
	gameover = 0;

	sf::Sprite *bgsprite = new sf::Sprite;
	sf::Texture bgtex;
	sf::Clock lClock;
	sf::Time lTime;
	sf::Text timer;
	sf::Font font,comicFont;
	
	std::string input;

	if(!(font.loadFromFile("Assets/arial.ttf")))
	{
		std::cout << "Error loading font ! " << std::endl;
	}

	if(!(comicFont.loadFromFile("Assets/Comic_Book.ttf")))
	{
		std::cout << "Error loading font ! " << std::endl;
	}

	sf::Text guestInfo("Press 'G' to play as a guest or 'L' to login",comicFont,30);
	sf::Text usernameText("Username:",comicFont,35);
	sf::Text passwordText("Password:",comicFont,35);
	sf::Text userText("type username",font,35);
	sf::Text passText("type password",font,35);

	guestInfo.setColor(sf::Color::Black);
	guestInfo.setPosition(128,265);
	
	treeInput.setFont(font);
	treeInput.setCharacterSize(18);
	treeInput.setPosition(84,433);
	treeInput.setString("");
	
	usernameText.setColor(sf::Color::Black);
	passwordText.setColor(sf::Color::Black);
	userText.setColor(sf::Color::Black);
	passText.setColor(sf::Color::Black);
	treeInput.setColor(sf::Color::Black);
	
	usernameText.setPosition(270,245);
	passwordText.setPosition(270,305);
	userText.setPosition(530,245);
	passText.setPosition(530,305);

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
	bool gameCompleted = 0;
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
		if(gameCompleted == 1)
		{
			set_Image(0,0,1000,562,"Assets/background12.png");
			display_image(window);
		}
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
			else if(level == 0 && tutorial == 1)
			{
				if(playerTypeDefined)
				{
					//check player type
					if(playerTypeDefined==1)
					{
						user = "guest";
						++tutorial;
						init_tutorial(level,tutorial);
					}
					else if(playerTypeDefined==2)//provide login if the player is not a guest
					{
						if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace)
						{
							if(!usernameEntered)
							{
								if(username.length() > 0)
								{
									username = username.substr(0,username.length() - 1);
									userText.setString(username);
								}
								else
								{
									userText.setString("type username");
								}
							}
							else
							{
								if(password.length() > 0)
								{
									password = password.substr(0,password.length() - 1);
									passwordStar = passwordStar.substr(0,password.length() - 1);
									passText.setString(passwordStar);
								}
								else
								{
									usernameEntered = false;
									username = username.substr(0,username.length() - 1);
									userText.setString(username);
									passText.setString("type password");
								}
							}
						}
						else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
						{
							if(password.length() > 0)
							{
								//do validation
								int ret = 1;
								ret = checkLogin(username, password);
								if(ret == -1) {
									std::cout << "Invalid username/password combination ! Try again." << std::endl << std::endl;
									password = "";
									passwordStar = "";
									passText.setString("type password");
									continue;
								}
								else
									if(ret == -2) {
										std::cout << "Server down ! Please try again." << std::endl << std::endl;
										password = "";
										passwordStar = "";
										passText.setString("type password");
										continue;
									}
									else {
										level = ret;
										std::cout << "Successfully logged in ! level : " << level << std::endl << std::endl;
										user = username;
										if(level != 1)
											++tutorial;
										init_tutorial(level, tutorial);
										levelChanged = 1;
										break;

									}
							}
							else
								if(username.length() > 0)
									usernameEntered = true;

						}
						else if (event.type == sf::Event::TextEntered)
						{
							if(!usernameEntered)
							{
								if(event.text.unicode < 128 && event.text.unicode > 31)
								{
									username += static_cast<char>(event.text.unicode);
									userText.setString(username);
								}
							}
							else
							{
								if(event.text.unicode < 128 && event.text.unicode > 31)
								{
									password += static_cast<char>(event.text.unicode);
									passwordStar += "*";
									passText.setString(passwordStar);
								}
							}
						}
					}
				}
				else
				{
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
					{
						std::cout<<"playerdefined";
						playerTypeDefined = 1;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::L)
					{
						playerTypeDefined = 2;
					}
					else
					{
						;
					}

				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				if(SCENE!=TUTORIAL)
					SCENE=TUTORIAL;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			{
				SCENE = MISSION;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if(SCENE == TUTORIAL)
				{
					end_tutorial(level,tutorial);
					if(level == 0)
						levelChanged =1;
					SCENE = LEVEL;
				}
				if(SCENE == MISSION)
				{
					//end_tutorial(level, noOfTutorials[level]);
					SCENE = LEVEL;
				}
			}
			else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::N)//f(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
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
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				if(SCENE == LEVEL && level < 11)
				{
					firsttime = true;
					levelChanged = 1;
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				if(SCENE == LEVEL && level > 1)
				{
					level = level - 2;
					levelChanged = 1;
					firsttime = true;
				}
			}
			if(level == 11)
			{
				if(subLevel == 1)
				{
					if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num0)
					{
						if(correctTreeInsertions==0)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
					{
						if(correctTreeInsertions==1)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
					{
						if(correctTreeInsertions==4)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num3)
					{
						if(correctTreeInsertions==5)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num4)
					{
						if(correctTreeInsertions==2)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num5)
					{
						if(correctTreeInsertions==7)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num6)
					{
						if(correctTreeInsertions==10)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num7)
					{
						if(correctTreeInsertions==8)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num8)
					{
						if(correctTreeInsertions==12)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num9)
					{
						if(correctTreeInsertions==3)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
					{
						if(correctTreeInsertions==6)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
					{
						if(correctTreeInsertions==13)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
					{
						if(correctTreeInsertions==9)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E)
					{
						if(correctTreeInsertions==14)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
							subLevelChanged = 1;
						}
						else
							correctEntryMade = 0;
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F)
					{
						if(correctTreeInsertions==11)
						{
							correctTreeInsertions++;
							correctEntryMade = 1;
						}
						else
							correctEntryMade = 0;
					}
				}
				else if(subLevel == 2)
				{
					if (event.type == sf::Event::TextEntered)
					{
						if(event.text.unicode < 128 && event.text.unicode > 31)
						{
							treeInp += static_cast<char>(event.text.unicode);
							treeInput.setString(treeInp);
						}
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace)
					{
						if(treeInp.length() > 0)
						{
							treeInp = treeInp.substr(0,treeInp.length() - 1);
							treeInput.setString(treeInp);
						}
					}
					else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
					{
						if(treeInp.compare("10,15,20,30,35,40,45,50,55,60,65,70,75,80,85") == 0)
						{
							subLevelChanged = 1;
						}
					}
				}
			}
        }

	//	std::cout << "level : " << level << std::endl;

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
				if(level == 11)
					myHero->setPosition(900, 350);
				else
					myHero->setPosition(800, 300);
			}
		}

		if((subLevelChanged && runsuccess == 1) || (subLevelChanged && level == 11))
		{
			if(subLevel <= noOfSubLevels[level])
			{
				subLevel++;
			}
			collisionRectangleChange(level,subLevel);
			subLevelChanged = 0;

			if(level==11 && subLevel==3)
			{
				treeInput.setString("Simulate the tree using a C program");
			}
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
				if(user.compare("guest") != 0){
					updateLog(username, level, secondsTakenToComplete, numberOfAttemptsTaken, executionTime, pSize);
				}
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
			
			if(level == 11)
				myHero = new Hero(900,350);
			else
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
				if(level==12)
				{
					window->draw(*bgsprite);
					break;
				}
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
				if(level == 0 && tutorial == 1)
				{
					if(playerTypeDefined==0)
						window->draw(guestInfo);
					else if(playerTypeDefined==2)
					{
						window->draw(usernameText);
						window->draw(passwordText);
						if(usernameEntered)
							window->draw(passText);
						window->draw(userText);
					}
				}
				break;
			case MISSION:
				window->clear();
				//init_tutorial(level, noOfTutorials[level]);
				//show_tutorial(window);
				init_mission(level, 1);
				show_mission(window);
				break;
		}
		window->display();
    }

	return 0;
}

