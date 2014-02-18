#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H

#include<iostream>
#include<cstring>
#include<fstream>
#include "Eva.h"
#include "ImageLoader.h"
int runsuccess;

std::string exec(char* cmd) {
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    _pclose(pipe);
    return result;
}

int numberofLinesOfCode(int level, int subLevel)
{
	std::ifstream inp;
	std::string fileLocation = "C:\\Users\\FYP\\codeForLevel" + std::to_string(level) + "_" + std::to_string(subLevel) + ".cpp";
	inp.open(fileLocation);
	int lineCount = 0;
	for( std::string line; getline( inp, line ); )
	{
		if(line.compare("") == 0)
			continue;
		lineCount++;
	}
	std::cout << std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl <<  std::endl ;
	std::cout << std::endl << "..................................................." << std::endl;
	std::cout << "Number of Lines of code : " << lineCount <<  std::endl;
	std::cout <<"..................................................." << std::endl;
	return lineCount;
}
void openCodingArea(int level, int sublevel)
{
	//write your function here
	char command[1024];

	std::string cmd = "C:\\Dev-Cpp\\devcpp.exe C:\\Users\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) +".cpp";

	std::cout<<"Start Coding";
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);
}

bool compileCode(int level, int sublevel)
{
	//write your function here
	std::cout<<"Compile Code";

	char command[1024];
	std::string cmd,ret;

	//create .exe
	cmd = "C:\\Dev-Cpp\\MinGW64\\bin\\g++.exe C:\\Users\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".cpp -o C:\\Users\\FYP\\execForLevel" + std::to_string(level) + "_" + std::to_string(sublevel);
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);

	//run the .exe
	if(level !=3 )
	{
		cmd = "C:\\Users\\FYP\\execForLevel";
		cmd += std::to_string(level) + "_" + std::to_string(sublevel) + ".exe > C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt";
		strcpy(command,cmd.c_str());
		std::cout<<exec(command);
	}
	else
	{
		cmd = "C:\\Users\\FYP\\execForLevel";
		cmd += std::to_string(level) + "_" + std::to_string(sublevel) + ".exe < C:\\Users\\FYP\\inputForLevel3_1.txt > C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt";
		strcpy(command,cmd.c_str());
		std::cout<<exec(command);
	}

	//compare the files
	cmd = "FC C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt" + " C:\\Users\\FYP\\correctSolForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt" + " > C:\\Users\\FYP\\diff.txt";
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);

	std::ifstream inp;
	inp.open("C:\\Users\\FYP\\diff.txt");
	std::getline(inp, ret);
	std::getline(inp, ret);
	std::cout<<"return :: " << ret << "\n";
	size_t temp = ret.find("no differences encountered");

	numberofLinesOfCode(level,sublevel);

	if(temp!=std::string::npos)
	{
		if(level == 1)
		{
			std::cout<<"\nSuccess for level 1";
			runsuccess = 1;
			changeEvaPosition(level);
			return 1;
		}
		if(level == 2)
		{
			std::cout<<"\nSuccess for level 2";
			runsuccess = 1;
			return 1;
		}
		if(level == 3)
		{
			std::cout<<"\nSuccess for level 3";
			runsuccess = 1;
			return 1;
		}
	}
	else
	{
		std::cout<<"Failure";
		runsuccess = 0;
		return 0;
	}
}

void testingFunction()
{
	// Do nothing.
}

#endif
