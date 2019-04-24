#pragma once
#include "stdafx.h"

//constructor overload
std::wstring charToString(char c) {
	std::wstring str = L" ";
	str[0] = c;
	return str;
}

std::wstring replaceChar(std::wstring str, wchar_t replace, wchar_t replacer) {
	std::replace(str.begin(), str.end(), replace, replacer);
	return str;
}

std::wstring replaceString(std::wstring str, std::wstring replace, std::wstring replacer) {
	for (int i = 0; i <= str.length(); ++i) {//run replace loop ONCE only
		std::wstring sub = str.substr(i, str.length());
		int pos = sub.find(replace) + i;
		if (sub.find(replace) == std::wstring::npos || pos < 0 || sub.find(replace) >= str.length() - 1) {
			//break if done replacing
			i = str.length() + 1;
			pos = std::wstring::npos;//set position to NULL for string type
		}
		if (pos >= 0) {
			str.erase(pos, replace.length());
			str.insert(pos, replacer);
			i = pos + replacer.length();
		}
	}
	return str;
}

std::wstring removeSpaces(std::wstring str) {
	std::wstring::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
	str.erase(end_pos, str.end());
	return str;
}

std::wstring trim(std::wstring str) {//removes spaces in front/back of string
	while (str[str.length() - 1] == L' ') { str.pop_back(); }
	while (str[0] == ' ') { str = str.substr(1); }
	return str;
}

std::wstring reverseString(std::wstring str) {
	std::wstring s = str;
	std::reverse(s.begin(), s.end());
	return s;
}

std::wstring to_stringPrecision(double val){
	std::wostringstream out;
	int p = precision;
	if (val == floor(val)) { p = 0; }
	out << std::fixed;
	out << std::setprecision(p) << val;
	out << std::scientific;
	return out.str();
}

std::wstring to_stringPrecision(double val, unsigned int precisn){
	std::wostringstream out;
	int p = precisn;
	if (val == floor(val)) { p = 0; }
	out << std::fixed;
	out << std::setprecision(p) << val;
	out << std::scientific;
	return out.str();
}

std::wstring toHex(int val){
	std::wstringstream stream;
	stream << L"0x";
	if (val < 16) {
		stream << L"0";
	}
	stream << std::hex << std::uppercase << val;
	return stream.str();
}

std::wstring to_hex(std::wstring input){
	int val = stringToDouble(input);
	return toHex(val);
}

std::wstring charArrToString(wchar_t* s) {
	std::wstring str(s);
	return str;
}

std::wstring matchParens(std::wstring str) {
	int frontParens = 0;
	int backParens = 0;
	for (int i = 0; i <= str.length(); ++i) {
		if (str[i] == L'(') { ++frontParens; }
		if (str[i] == L')') { ++backParens; }
	}
	while (frontParens > backParens) {
		str.append(L")");
		++backParens;
	}
	return str;
}

size_t findMatchingParen(std::wstring str, int pos) {
	/*given the position 'pos' of a front paren at a position in string 'str',
	this function returns the position of the matching closing paren (or std::wstring::npos if it does not exist). */
	int backParens = 0;
	if (str[pos] == L'(') {//case: str[pos] is an open bracket
		for (int i = pos + 1; i <= str.length(); ++i) {
			if (str[i] == L'(') { ++backParens; }
			if (str[i] == L')') { --backParens; }
			if (backParens < 0) { return i; }
		}
	}
	if (str[pos] == L')') {//case: str[pos] is an closing bracket
		for (int i = pos - 1; i >= 0; --i) {
			if (str[i] == L'(') { --backParens; }
			if (str[i] == L')') { ++backParens; }
			if (backParens < 0) { return i; }
		}
	}
	return std::wstring::npos;//else, return null position
}

std::wstring removeUnmatchedParens(std::wstring funct) {
	for (int i = 0; i < funct.length(); ++i) {
		if (funct[i] == L'(' &&  findMatchingParen(funct, i) == std::wstring::npos) {
			funct.erase(i, 1);
		}
	}
	return funct;
}

std::wstring eraseParenPair(std::wstring str, size_t pos) {
	str.erase(findMatchingParen(str,pos),1);
	str.erase(pos, 1);
	return str;
}

std::wstring replaceConstants(std::wstring funct) {
/*	if (funct.find(L"PI") != std::wstring::npos) { funct = replaceString(funct, L"PI", to_stringPrecision(PI)); }//replace string "PI" with its value
	if (funct.find(L"EMconstant") != std::wstring::npos) { funct = replaceString(funct, L"EMconstant", to_stringPrecision(EMconstant)); }
	if (funct.find(L"EulersNumber") != std::wstring::npos) { funct = replaceString(funct, L"EulersNumber", to_stringPrecision(EulersNumber)); }

	if (funct.find(L"R_constant") != std::wstring::npos) { funct = replaceString(funct, L"R_constant", to_stringPrecision(R_constant)); }
	if (funct.find(L"speedOfLight") != std::wstring::npos) { funct = replaceString(funct, L"speedOfLight", to_stringPrecision(speedOfLight)); }
	if (funct.find(L"g_constant") != std::wstring::npos) { funct = replaceString(funct, L"g_constant", to_stringPrecision(g_constant)); }
	if (funct.find(L"gravitationalConstant") != std::wstring::npos) { funct = replaceString(funct, L"gravitationalConstant", to_stringPrecision(gravitationalConstant)); }
	if (funct.find(L"idealGasConstantATMs") != std::wstring::npos) { funct = replaceString(funct, L"idealGasConstantATMs", to_stringPrecision(idealGasConstantATMs)); }
	if (funct.find(L"idealGasConstantKiloPascals") != std::wstring::npos) { funct = replaceString(funct, L"idealGasConstantKiloPascals", to_stringPrecision(idealGasConstantKiloPascals)); }
	if (funct.find(L"EPSILON") != std::wstring::npos) { funct = replaceString(funct, L"EPSILON", to_stringPrecision(EPSILON)); }
	if (funct.find(L'ɛ') != std::wstring::npos) { funct = replaceString(funct, L"ɛ", to_stringPrecision(EPSILON)); }
	if (funct.find(L"AvogadrosNumber") != std::wstring::npos) { funct = replaceString(funct, L"AvogadrosNumber", to_stringPrecision(AvogadrosNumber)); }//replace string "AvogadrosNumber" with its value
	if (funct.find(L"BoltzmannsConstant") != std::wstring::npos) { funct = replaceString(funct, L"BoltzmannsConstant", to_stringPrecision(BoltzmannsConstant)); }//replace string "BoltzmannsConstant" with its value
	if (funct.find(L"elementaryCharge") != std::wstring::npos) { funct = replaceString(funct, L"elementaryCharge", to_stringPrecision(elementaryCharge)); }//replace string "elementaryCharge" with its value
	if (funct.find(L"vacuumPermitivitty") != std::wstring::npos) { funct = replaceString(funct, L"vacuumPermitivitty", to_stringPrecision(vacuumPermitivitty)); }//replace string "vacuumPermitivitty" with its value
	if (funct.find(L"vacuumPermeability") != std::wstring::npos) { funct = replaceString(funct, L"vacuumPermeability", to_stringPrecision(vacuumPermeability)); }//replace string "vacuumPermeability" with its value
	if (funct.find(L"PlancksConstantJoules") != std::wstring::npos) { funct = replaceString(funct, L"PlancksConstantJoules", to_stringPrecision(PlancksConstantJoules)); }//replace string "PlancksConstantJoules" with its value
	if (funct.find(L"PlancksConstanteVs") != std::wstring::npos) { funct = replaceString(funct, L"PlancksConstanteVs", to_stringPrecision(PlancksConstanteVs)); }//replace string "PlancksConstanteVs" with its value
	if (funct.find(L"atomicMassUnit") != std::wstring::npos) { funct = replaceString(funct, L"atomicMassUnit", to_stringPrecision(atomicMassUnit)); }
	if (funct.find(L"electronMasskg") != std::wstring::npos) { funct = replaceString(funct, L"electronMasskg", to_stringPrecision(electronMasskg)); }//replace string "electronMasskg" with its value
	if (funct.find(L"electronMassMeV") != std::wstring::npos) { funct = replaceString(funct, L"electronMassMeV", to_stringPrecision(electronMassMeV)); }//replace string "electronMassMeV" with its value
	if (funct.find(L"electronMassAMU") != std::wstring::npos) { funct = replaceString(funct, L"electronMassAMU", to_stringPrecision(electronMassAMU)); }//replace string "electronMassAMU" with its value
	if (funct.find(L"protonMasskg") != std::wstring::npos) { funct = replaceString(funct, L"protonMasskg", to_stringPrecision(protonMasskg)); }//replace string "protonMasskg" with its value
	if (funct.find(L"protonMassMeV") != std::wstring::npos) { funct = replaceString(funct, L"protonMassMeV", to_stringPrecision(protonMassMeV)); }//replace string "protonMassMeV" with its value
	if (funct.find(L"protonMassAMU") != std::wstring::npos) { funct = replaceString(funct, L"protonMassAMU", to_stringPrecision(protonMassAMU)); }//replace string "protonMassAMU" with its value
	if (funct.find(L"neutronMasskg") != std::wstring::npos) { funct = replaceString(funct, L"neutronMasskg", to_stringPrecision(neutronMasskg)); }//replace string "neutronMasskg" with its value
	if (funct.find(L"neutronMassMeV") != std::wstring::npos) { funct = replaceString(funct, L"neutronMassMeV", to_stringPrecision(neutronMassMeV)); }//replace string "neutronMassMeV" with its value
	if (funct.find(L"neutronMassAMU") != std::wstring::npos) { funct = replaceString(funct, L"neutronMassAMU", to_stringPrecision(neutronMassAMU)); }//replace string "neutronMassAMU" with its value
	if (funct.find(L"HubbleConstantkm") != std::wstring::npos) { funct = replaceString(funct, L"HubbleConstantkm", to_stringPrecision(HubbleConstantkm)); }//replace string "HubbleConstantkm" with its value
	if (funct.find(L"HubbleConstantsec") != std::wstring::npos) { funct = replaceString(funct, L"HubbleConstantsec", to_stringPrecision(HubbleConstantsec)); }//replace string "HubbleConstantsec" with its value

	if (funct.find(L"ATMsPerPascal") != std::wstring::npos) { funct = replaceString(funct, L"ATMsPerPascal", to_stringPrecision(ATMsPerPascal)); }//replace string "ATMsPerPascal" with its value
	if (funct.find(L"PascalsPerATM") != std::wstring::npos) { funct = replaceString(funct, L"PascalsPerATM", to_stringPrecision(PascalsPerATM)); }
	if (funct.find(L"mmHgPerPascal") != std::wstring::npos) { funct = replaceString(funct, L"mmHgPerPascal", to_stringPrecision(mmHgPerPascal)); }//replace string "mmHgPerPascal" with its value
	if (funct.find(L"PascalsPermmHg") != std::wstring::npos) { funct = replaceString(funct, L"PascalsPermmHg", to_stringPrecision(PascalsPermmHg)); }//replace string "PascalsPermmHg" with its value
*/
	return funct;
}

wchar_t* stringToCharArr(std::wstring str) {
	return &str[0u];
}

double stringToDouble(std::wstring str) {
	int neg = 1;
	str = removeSpaces(str);
	str = replaceConstants(str);
	if (str[0] == '-') { neg = -1; str.erase(str.begin()); }
	double x = 0;
	//std::wstringstream ss(tempStr); // stringstream used for the conversion initialized with the contents of Text
	std::wstringstream ss;
	for (std::wstring::const_iterator i = str.begin(); i != str.end(); ++i)
		if (isdigit(*i) || *i == 'e' || *i == '-' || *i == '+' || *i == '.')
			ss << *i;
	ss >> x;
	x *= neg;
	return x;
}

long double stringToLongDouble(std::wstring str) {
	int neg = 1;
	str = removeSpaces(str);
	str = replaceConstants(str);
	if (str[0] == '-') { neg = -1; str.erase(str.begin()); }
	long double x = 0;
	//std::wstringstream ss(tempStr); // stringstream used for the conversion initialized with the contents of Text
	std::wstringstream ss;
	for (std::wstring::const_iterator i = str.begin(); i != str.end(); ++i)
		if (isdigit(*i) || *i == 'e' || *i == '-' || *i == '+' || *i == '.')
			ss << *i;
	ss >> x;
	x *= neg;
	return x;
}

/*
std::wstring TCharToString(LPCTSTR t) {
// Handy for converting TCHAR to std::wstring (char)
// If the conversion fails, an empty string is returned.
std::wstring str;
#ifdef UNICODE
// calculate the size of the char string required
// Note: If wcstombs encounters a wide character it cannot convert
//       to a multibyte character, it returns 1.
int len = 1 + wcstombs(0, t, 0);
if (0 == len) return str;

char* c = new char[len];
if (NULL == c) throw std::bad_alloc();
c[0] = '\0';

wcstombs(c, t, len);
str = c;
delete[]c;
#else
str = t;
#endif
return str;
}*/

std::wstring formatStringAsWString(std::wstring opt) {
	size_t pos = 0;
	std::wstring search = L"\n";
	std::wstring replace = L"\r\n";
	while ((pos = opt.find(search, pos)) != std::wstring::npos) {
		opt.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return opt;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}
