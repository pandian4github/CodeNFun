#ifndef COMPILATIONUNIT_H
#define COMPILATIONUNIT_H

#include<iostream>
#include<cstring>
#include<fstream>
#include<time.h>
#include "Eva.h"
#include "ImageLoader.h"
int runsuccess;
float executionTime;

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

void openCodingArea(int level, int sublevel)
{
	//write your function here
	char command[1024];

	std::string cmd = "C:\\Dev-Cpp\\devcpp.exe C:\\Users\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) +".cpp";

	std::cout << std::endl << "Start Coding ! " << std::endl << std::endl;
	strcpy(command,cmd.c_str());
	exec(command);
}

bool compileCode(int level, int sublevel)
{
	//write your function here
	std::cout<<"Compiling Code . . . " << std::endl << std::endl;

	char command[1024];
	std::string cmd,ret;

	/*if(level == 4)
	{
		runsuccess=1;
		return 1;
	}*/
	//create .exe
	cmd = "C:\\Dev-Cpp\\MinGW64\\bin\\g++.exe C:\\Users\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".cpp -o C:\\Users\\FYP\\execForLevel" + std::to_string(level) + "_" + std::to_string(sublevel);
	strcpy(command,cmd.c_str());
	exec(command);

	clock_t t1, t2;
	t1 = clock();
	//run the .exe
	if(level ==1 || level == 2 || level ==4)
	{
		cmd = "C:\\Users\\FYP\\execForLevel";
		cmd += std::to_string(level) + "_" + std::to_string(sublevel) + ".exe > C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt";
		strcpy(command,cmd.c_str());
		exec(command);
	}
	else if(level == 3)
	{
		cmd = "C:\\Users\\FYP\\execForLevel";
		cmd += std::to_string(level) + "_" + std::to_string(sublevel) + ".exe < C:\\Users\\FYP\\inputForLevel3_1.txt > C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt";
		strcpy(command,cmd.c_str());
		exec(command);
	}
	/*else if(level == 4 )
	{
		//give correct input file
		cmd = "C:\\Users\\FYP\\execForLevel";
		cmd += std::to_string(level) + "_" + std::to_string(sublevel) + ".exe < C:\\Users\\FYP\\inputForLevel4_1.txt > C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt";
		strcpy(command,cmd.c_str());
		std::cout<<exec(command);
		return 1;
	}*/
	t2 = clock();
	executionTime = (float)((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	std::cout << executionTime;

	//compare the files
	cmd = "FC C:\\Users\\FYP\\solForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt" + " C:\\Users\\FYP\\correctSolForLevel" + std::to_string(level) + "_" + std::to_string(sublevel) + ".txt" + " > C:\\Users\\FYP\\diff.txt";
	strcpy(command,cmd.c_str());
	exec(command);

	std::ifstream inp;
	inp.open("C:\\Users\\FYP\\diff.txt");
	std::getline(inp, ret);
	std::getline(inp, ret);
	//std::cout<<"return :: " << ret << "\n";
	size_t temp = ret.find("no differences encountered");

	//programSize(level,sublevel);

	if(temp!=std::string::npos)
	{
		if(level == 1)
		{
			//std::cout<<"\nSuccess for level 1";
			runsuccess = 1;
			changeEvaPosition(level);
			return 1;
		}
		else if(level == 2)
		{
			//std::cout<<"\nSuccess for level 2";
			runsuccess = 1;
			return 1;
		}
		else if(level == 3)
		{
			//std::cout<<"\nSuccess for level 3";
			runsuccess = 1;
			return 1;
		}
		else if(level == 4)
		{
			std::cout<<"\nSuccess for level 4";
			runsuccess = 1;
			return 1;
		}
	}
	else
	{
		//std::cout<<"Failure";
		runsuccess = 0;
		return 0;
	}
}

void testingFunction()
{
	// Do nothing.
}

#endif
