#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H

#include<iostream>
#include<cstring>
#include<fstream>
#include "Eva.h"

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

void openCodingArea(int level)
{
	//write your function here
	char command[1024];

	std::string cmd = "C:\\Installations\\Dev-Cpp\\devcpp.exe C:\\Users\\Ashwin\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + ".cpp";

	std::cout<<"Start Coding";
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);
}

bool compileCode(int level)
{
	//write your function here
	std::cout<<"Compile Code";

	char command[1024];
	std::string cmd,ret;

	//create .exe
	cmd = "C:\\Installations\\Dev-Cpp\\bin\\g++.exe C:\\Users\\Ashwin\\FYP\\";
	cmd += "codeForLevel" + std::to_string(level) + ".cpp -o C:\\Users\\Ashwin\\FYP\\execForLevel" + std::to_string(level);
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);

	//run the .exe
	cmd = "C:\\Users\\Ashwin\\FYP\\execForLevel";
	cmd += std::to_string(level) + ".exe > C:\\Users\\Ashwin\\FYP\\solForLevel" + std::to_string(level) + ".txt";
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);

	//compare the files
	cmd = "FC C:\\Users\\Ashwin\\FYP\\solForLevel" + std::to_string(level) + ".txt" + " C:\\Users\\Ashwin\\FYP\\correctSolForLevel" + std::to_string(level) + ".txt" + " > C:\\Users\\Ashwin\\FYP\\diff.txt";
	strcpy(command,cmd.c_str());
	std::cout<<exec(command);

	std::ifstream inp;
	inp.open("C:\\Users\\Ashwin\\FYP\\diff.txt");
	std::getline(inp, ret);
	std::getline(inp, ret);
	std::cout<<"return :: " << ret << "\n";
	size_t temp = ret.find("no differences encountered");

	if(temp!=std::string::npos)
	{
		std::cout<<"Success";
		changeEvaPosition(level);
		return 1;
	}
	else
	{
		std::cout<<"Failure";
		return 0;
	}
}



#endif