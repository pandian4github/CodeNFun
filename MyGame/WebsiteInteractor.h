#ifndef WEBSITEINTERACTOR_H
#define WEBSITEINTERACTOR_H

#include "WinHttpClient.h"
#include<iostream>

int checkLogin(std::string username, std::string password) {
	
	std::string url = "";
//	url.append("http://localhost/codenfun/checklogin-ext.php?username=");
	url.append("http://a-ligue.in/codenfun/checklogin-ext.php?username=");
	url.append(username);
	url.append("&password=");
	url.append(password);
			
	//std::cout << "url for checking login : " << url << std::endl;

	std::wstring wurl(url.begin(), url.end());
	
	WinHttpClient client(wurl);
	client.SendHttpRequest();
	wstring httpResponseHeader = client.GetResponseHeader();
	wstring httpResponseContent = client.GetResponseContent();
	
	std::string response = "";		
	int length = httpResponseContent.length();
			
	for(int i = 0; i < length; i++) {
		response += (char)httpResponseContent.at(i);
	}
	
	//std::cout << "response : " << response << std::endl;
	if(response.at(0) == 'N')
		return -1;
	else
		if(response.at(0) == 'Y') {
			int l = 0;
					
			for(int i = 1; i < length && response.at(i) >='0' && response.at(i) <= '9'; i++) {
				l = l * 10 + response.at(i) - 48;
			}
			
			return l;
		}
		else {
			return -2;
		}


}

void updateLog(std::string username, int level, int timetocomplete, int attempts, float executiontime, int programsize) {

	std::string url = "";
//	url.append("http://localhost/codenfun/updatelog-ext.php?username=");
	url.append("http://a-ligue.in/codenfun/updatelog-ext.php?username=");
	url.append(username);
	url.append("&level=");
	url.append(std::to_string(level));
	url.append("&timetocomplete=");
	url.append(std::to_string(timetocomplete));
	url.append("&attempts=");
	url.append(std::to_string(attempts));
	url.append("&executiontime=");
	url.append(std::to_string(executiontime));
	url.append("&programsize=");
	url.append(std::to_string(programsize));	
			
	//std::cout << url << std::endl;

	std::wstring wurl(url.begin(), url.end());
	
	WinHttpClient client(wurl);
	client.SendHttpRequest();
	wstring httpResponseHeader = client.GetResponseHeader();
	wstring httpResponseContent = client.GetResponseContent();
	
	std::string response = "";		
	int length = httpResponseContent.length();
			
	for(int i = 0; i < length; i++) {
		response += (char)httpResponseContent.at(i);
	}
	
	//std::cout << response << std::endl;
	if(response.at(0) == 'Y')
		std::cout << std::endl << "Log updated to the website successfully ! " << std::endl;

}
#endif