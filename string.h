#ifndef STRING_H
#define STRING_H
#pragma once
#include "stdafx.h"
std::wstring charToString(char c);
std::wstring replaceChar(std::wstring str, wchar_t replace, wchar_t replacer);
std::wstring replaceString(std::wstring str, std::wstring replace, std::wstring replacer);
std::wstring removeSpaces(std::wstring str);
std::wstring trim(std::wstring str);
std::wstring reverseString(std::wstring str);
std::wstring to_stringPrecision(double val);
std::wstring to_stringPrecision(double val, unsigned int precisn);
std::wstring toHex(int val);
std::wstring toHex(std::wstring input);
std::wstring charArrToString(wchar_t* s);
std::wstring matchParens(std::wstring str);
size_t findMatchingParen(std::wstring str, int pos);
std::wstring removeUnmatchedParens(std::wstring funct);
std::wstring eraseParenPair(std::wstring str, size_t pos);
std::wstring replaceConstants(std::wstring funct);
wchar_t* stringToCharArr(std::wstring str);
double stringToDouble(std::wstring str);
long double stringToLongDouble(std::wstring str);
//std::wstring TCharToString(LPCTSTR t);
std::wstring formatStringAsWString(std::wstring opt);
std::wstring s2ws(const std::string& s);
std::string ws2s(const std::wstring& s);
#endif