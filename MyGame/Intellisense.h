#ifndef INTELLISENSE_H
#define INTELLISENSE_H

#include<iostream>
#include "SFML\Graphics.hpp"
#include "SFML\System\Clock.hpp"

sf::Clock gClock;

const int POOR = 0;
const int BELOWAVERAGE = 1;
const int AVERAGE = 2;
const int ABOVEAVERAGE = 3;
const int GOOD = 4;
int levelDifficulty;
int timeToIncrease;
int timeToDecrease;
bool hintRequired;
int attempts;
sf::Text hintText;

int printTimetakentoCompleteLevel(int level) {

	sf::Time time = gClock.getElapsedTime();
	/*std::cout << std::endl << "..................................................." << std::endl;
	std::cout << std::endl << "Time taken to complete level " << level << " : " << time.asSeconds() << " seconds." << std::endl;
	std::cout << std::endl << "..................................................." << std::endl;
	std::cout << std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl ;
	*/return (int)time.asSeconds();
}

int getPerformance(int level, int secondsTaken) {
	int averageTime = 0;
	int ret = AVERAGE;
	switch(level) {
		case 1 : averageTime = 75;
				 break;
		case 2 : averageTime = 255;
				 break;
		case 3 : averageTime = 120;
				 break;
		case 4 : averageTime = 200;
				 break;
	}

	if(secondsTaken > averageTime) {
		int diff = secondsTaken - averageTime;
		//std::cout << "diff : " << diff << std::endl;
		if(diff <= 10) 
			ret = AVERAGE;
		else
			if(diff <= 25)
				ret = BELOWAVERAGE;
			else
				ret = POOR;
	}

	if(secondsTaken <= averageTime) {
		int diff = averageTime - secondsTaken;
		//std::cout << "diff : " << diff << std::endl;
		if(diff <= 10) 
			ret = AVERAGE;
		else
			if(diff <= 25)
				ret = ABOVEAVERAGE;
			else
				ret = GOOD;
	}

	return ret;
}
void setDifficultyForNextLevel(int level, int performance) {
	//std::cout << "Setting levelDifficulty to : " << performance << std::endl;
	levelDifficulty = performance;
}
void setTimeVariance() {
	
	switch(levelDifficulty) {
		case POOR			:	timeToIncrease = 45;
								timeToDecrease = 0;
								hintRequired = true;
								break;
		case BELOWAVERAGE	:	timeToIncrease = 25;
								timeToDecrease = 0;
								hintRequired = false;
								break;
		case AVERAGE		:	timeToIncrease = 0;
								timeToDecrease = 0;
								hintRequired = false;
								break;
		case ABOVEAVERAGE	:	timeToIncrease = 0;
								timeToDecrease = 25;
								hintRequired = false;
								break;
		case GOOD			:	timeToIncrease = 0;
								timeToDecrease = 45;
								hintRequired = false;
								break;
	}
}

void displayHintIfRequired(int level) {
	
	if(attempts <=1 ) {

		switch(level) {
			case 1 : hintText.setString("Hint : Just type 'move_up' within double quotes inside printf statement");
					 hintText.setPosition(10, 460);
					 break;
			case 2 : hintText.setString("Hint : Do the appropriate operations, store them in variables and print them");
					 hintText.setPosition(10, 460);
					 break;
			case 3 : hintText.setString("Hint : All you need is to use two statements scanf and printf, with the variables in the same order");
					 hintText.setPosition(10, 460);
					 break;
	
		}
	}

}

int programSize(int level, int subLevel)
{
	std::ifstream inp;
	std::string fileLocation = "C:\\Users\\FYP\\codeForLevel" + std::to_string(level) + "_" + std::to_string(subLevel) + ".cpp";
	inp.open(fileLocation);
	int lineCount = 0;
	int charcount = 0;
	for( std::string line; getline( inp, line ); )
	{
		if(line.compare("") == 0)
			continue;
		charcount += line.length();
		lineCount++;
	}
	/*std::cout << std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl ;
	std::cout << std::endl << "..................................................." << std::endl;
	std::cout << "Program size written by you : " << charcount <<  std::endl;
	std::cout <<"..................................................." << std::endl;
	*/
	return charcount;
}

void printReport(int seconds, int targetSeconds, int pSize, int attempts, int performance, int level, float execTime) {
	string performanceString[] = {"NEED TO WORK HARD", "NOT BAD", "AVERAGE", "GOOD", "EXCELLENT"};
	std::cout << std::endl << "---------------------- Report for level " << level << " ----------------------" << std::endl;
	std::cout << "Target time for the level         :	" << targetSeconds << std::endl;
	std::cout << "Time taken to complete the level  :	" << seconds << std::endl;
	std::cout << "Program size                      :	" << pSize << std::endl;
	std::cout << "Program execution time            :	" << execTime << std::endl;
	std::cout << "Overall performace                :	" << performanceString[performance] << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;
}

#endif