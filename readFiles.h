#ifndef READFILES_H
#define READFILES_H
#include "stdafx.h"

std::vector<double> readTxtFile(std::string filename);
std::vector<double> readTxtFile(std::wstring filename);
double ParseInputNumber(std::string in);
double ParseInputNumber(std::wstring in);
std::vector<double> ParseNInputNumbers(std::string str);
std::vector<double> ParseNInputNumbers(std::wstring str);

#endif