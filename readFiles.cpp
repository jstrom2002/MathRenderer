#pragma once
#include "stdafx.h"

std::vector<double> readTxtFile(std::wstring filename) {
	return readTxtFile(ws2s(filename));
}

std::vector<double> readTxtFile(std::string filename) {
	std::vector<double> vec;
	std::string line = "";	
	std::string path = "C:\\Users\\--\\Documents\\Visual Studio 2015\\Projects\\openGL test\\openGL test\\";
	path = path.append(filename);
	FILE *fptr;
	//fptr = fopen(filename.c_str(), "r");
	fptr = fopen(path.c_str(), "r");
		
	while(!feof(fptr)) {
		char c;
		fread(&c, sizeof(char), 1, fptr);
		if (c != ',') {
			if (c != '\n') {
				line += c;
			}
		}
		else {
			vec.push_back(ParseInputNumber(line));
			line.clear();
		}
	}
	
	fclose(fptr);
	return vec;
}

double ParseInputNumber(std::string in) { return ParseInputNumber(s2ws(in)); }
double ParseInputNumber(std::wstring in) { return stringToDouble(in); }

std::vector<double> ParseNInputNumbers(std::string str) {
	return ParseNInputNumbers(s2ws(str));
}

std::vector<double> ParseNInputNumbers(std::wstring str) {
	str = removeSpaces(str);
	str = replaceConstants(str);	//replace a constant like "speedOfLight" in the string with the actual value for the speed of light

	std::vector<double> answer;
	std::vector<int> position;

	//get the number of values in the string by finding all ',' chars
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ',') {
			position.push_back(i);
		}
		if (str[i] == ')') {//break if you've hit the end
			i = str.length();
		}
	}
	if (position.size() == 0) { answer.push_back(ParseInputNumber(str)); return answer; }//if there is only one single value in the string
	if (position.size() > 0) {//if there are multiple values in the string
		std::wstring tempStr = str.substr(0, position[0]);   //get first substring
		answer.push_back(stringToDouble(tempStr));
		for (int i = 1; i < position.size();++i) {
			tempStr = str.substr(position[i - 1] + 1, position[i] - position[i - 1] - 1);
			answer.push_back(stringToDouble(tempStr));
		}
		tempStr = str.substr(position[position.size() - 1] + 1);
		answer.push_back(stringToDouble(tempStr));
	}

	return answer;
}