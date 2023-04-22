#include <iostream>
#include <ctype.h>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>



void removeAllDigits(std::string & strIn) {
	for (int i = 0; i < strIn.length(); i++) {
		if (isdigit(strIn[i])) {
			strIn.erase(i);
		}
	}
}

void toLowerString(std::string & strIn) {
	for (int i = 0; i < strIn.length(); i++) {
		strIn[i] = tolower(strIn[i]);
	}
}



void preProcessString(std::string &strIn) {

	toLowerString(strIn);

	strIn = std::regex_replace(strIn, std::regex(" "), "");
	strIn = std::regex_replace(strIn, std::regex("/"), "");
	strIn = std::regex_replace(strIn, std::regex("&"), "");
	strIn = std::regex_replace(strIn, std::regex("_"), "");
	strIn = std::regex_replace(strIn, std::regex("-"), "");
	strIn = std::regex_replace(strIn, std::regex("'"), "");

	removeAllDigits(strIn);
}


void preProcessArrayString(std::vector<std::string>& strArrIn) {
	for (int i = 0; i < strArrIn.size(); i++)
	{
		preProcessString(strArrIn[i]);
	}
}

void removeDuplicates(std::vector<std::string> &strArrIn) {
	std::sort(strArrIn.begin(), strArrIn.end());
	strArrIn.erase(std::unique(strArrIn.begin(), strArrIn.end()), strArrIn.end());

}