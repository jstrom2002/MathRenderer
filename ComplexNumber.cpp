#pragma once
#include "stdafx.h"

ComplexNumber::ComplexNumber() {}
ComplexNumber::~ComplexNumber() {}

ComplexNumber::ComplexNumber(double a, double b)
{  //z=a+bi
	Re = a;
	Im = b;
	int c = getLength(Re);
	if (getLength(Im) > c) { c = getLength(Im); }
	complexNumberPrecision = c;
}

ComplexNumber::ComplexNumber(double a)
{  //z=a+0i
	Re = a;
	Im = 0;
	complexNumberPrecision = getLength(Re);
}

ComplexNumber::ComplexNumber(std::complex<double> z) {
	Re = real(z);
	Im = imag(z);
	int c = getLength(Re);
	if (getLength(Im) > c) { c = getLength(Im); }
	complexNumberPrecision = c;
}

double ComplexNumber::modulus()
{//returns |z|
	return hypot(Re, Im);
}

double ComplexNumber::arg()
{//returns theta from z*e^(i*theta)
	double answer = atan2(Im, Re);
	return answer;
}

ComplexNumber ComplexNumber::cis(double n) { return ComplexNumber(cos(n), sin(n)); }

ComplexNumber ComplexNumber::conjugate() {
	//switches z to its conjugate, returns the new complex number class.
	ComplexNumber c0(Re, -Im);
	return c0;
}

void ComplexNumber::randomize() {
	srand(time(0) + clock());
	double a = (rand() / 1000000.00) * pow(-1, rand() % 2);
	Re = a;
	a = (rand() / 1000000.00) * pow(-1, rand() % 2);
	Im = a;
}

bool ComplexNumber::isIntegerComplexNumber() {
	if (Re != floor(Re) || Im != floor(Im)) { return false; }
	return true;
}

//ARITHMETIC METHODS
//===================
ComplexNumber ComplexNumber::add(ComplexNumber a, ComplexNumber b) { return ComplexNumber(a.Re + b.Re, a.Im + b.Im); }
ComplexNumber ComplexNumber::add(ComplexNumber a, double b) { return ComplexNumber(a.Re + b, a.Im); }
ComplexNumber ComplexNumber::add(double b, ComplexNumber a) { return ComplexNumber(a.Re + b, a.Im); }
ComplexNumber ComplexNumber::subtract(ComplexNumber a, ComplexNumber b) { return ComplexNumber(a.Re - b.Re, a.Im - b.Im); }
ComplexNumber ComplexNumber::subtract(ComplexNumber a, double b) { return ComplexNumber(a.Re - b, a.Im); }
ComplexNumber ComplexNumber::subtract(double b, ComplexNumber a) { return ComplexNumber(b - a.Re, a.Im); }
ComplexNumber ComplexNumber::multiply(ComplexNumber a, ComplexNumber b) { return ComplexNumber((a.Re*b.Re) - (a.Im*b.Im), (a.Im*b.Re) + (b.Im*a.Re)); }
ComplexNumber ComplexNumber::multiply(ComplexNumber a, double b) { return ComplexNumber(a.Re*b, a.Im*b); }
ComplexNumber ComplexNumber::multiply(double b, ComplexNumber a) { return ComplexNumber(a.Re*b, a.Im*b); }
ComplexNumber ComplexNumber::divide(ComplexNumber A, double a) { return ComplexNumber(A.Re / a, A.Im / a); }
ComplexNumber ComplexNumber::divide(double a, ComplexNumber A) { return ComplexNumber(A.Re / a, A.Im / a); }
ComplexNumber ComplexNumber::divide(ComplexNumber a, ComplexNumber b) {
	double temp = (1 / ((b.Re*b.Re) + (b.Im*b.Im)));
	double rl = (a.Re*b.Re + a.Im*b.Im)*temp;
	double im = (a.Im*b.Re - a.Re*b.Im)*temp;
	return ComplexNumber(rl, im);
}

ComplexNumber ComplexNumber::inverse() {
	double temp = (1 / (Re*Re + Im * Im));
	double re = temp * Re;
	double im = temp * -Im;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::exponent(ComplexNumber z, double a) {
	ComplexNumber c = z;
	if (a < 0) {
		c = c.inverse();
		a = abs(a);
	}
	if (a > 0) {
		for (int i = 0; i < a - 1; i++) {
			c = c.multiply(c, z);
		}
		return c;
	}
	if (a == 0) { return ComplexNumber(1, 0); }
}
ComplexNumber ComplexNumber::exponent(double a) {
	ComplexNumber z = *this;
	if (a < 0) {
		z = inverse();
		a = abs(a);
	}
	if (a > 0) {
		for (int i = 0; i < a - 1; i++) {
			z = multiply(z, *this);
		}
		return z;
	}
	if (a == 0) { return ComplexNumber(1, 0); }
}
ComplexNumber ComplexNumber::exponent(ComplexNumber z)
{   //(x+yi)^a+bi
	double x = Re;
	double y = Im;
	double arg1 = arg();
	double rho = (x*x) + (y*y);
	double part1 = z.Re * arg1 + (.5 * z.Im * (log(rho)));
	double part2 = pow(rho, z.Re / 2) * exp(-z.Im * arg1);
	double newRe = cos(part1) * part2;
	double newIm = sin(part1) * part2;
	ComplexNumber c0(newRe, newIm);
	return c0;
}

//OVERLOADED OPERATORS
//====================
ComplexNumber& ComplexNumber::operator*=(ComplexNumber& rhs) { *this = multiply(*this, rhs); return *this; }
ComplexNumber& ComplexNumber::operator*=(double x) { *this = multiply(*this, x); return *this; }
ComplexNumber& ComplexNumber::operator/=(ComplexNumber& rhs) { *this = divide(*this, rhs); return *this; }
ComplexNumber& ComplexNumber::operator/=(double x) { *this = divide(*this, x); return *this; }
ComplexNumber& ComplexNumber::operator+=(ComplexNumber& rhs) { *this = add(*this, rhs); return *this; }
ComplexNumber& ComplexNumber::operator+=(double x) { *this = add(*this, x); return *this; }
ComplexNumber& ComplexNumber::operator-=(ComplexNumber& rhs) { *this = subtract(*this, rhs); return *this; }
ComplexNumber& ComplexNumber::operator-=(double x) { *this = subtract(*this, x); return *this; }

ComplexNumber& ComplexNumber::operator*(ComplexNumber& rhs) { return multiply(*this, rhs); }
ComplexNumber& ComplexNumber::operator*(double x) { ComplexNumber p = multiply(*this, x); return p; }
ComplexNumber& ComplexNumber::operator/(ComplexNumber& rhs) { return divide(*this, rhs); }
ComplexNumber& ComplexNumber::operator/(double x) { ComplexNumber p = divide(*this, x); return p; }
ComplexNumber& ComplexNumber::operator+(ComplexNumber& rhs) { return add(*this, rhs); }
ComplexNumber& ComplexNumber::operator+(double x) { return add(*this, x); }
ComplexNumber& ComplexNumber::operator-(ComplexNumber& rhs) { return subtract(*this, rhs); }
ComplexNumber& ComplexNumber::operator-(double x) { return subtract(*this, x); }

// topology in C is such that there is no comparison between complex numbers, only their moduli.
bool ComplexNumber::operator<(ComplexNumber& rhs) { return  modulus() < rhs.modulus(); }
bool ComplexNumber::operator<=(ComplexNumber& rhs) { return  modulus() <= rhs.modulus(); }
bool ComplexNumber::operator>(ComplexNumber& rhs) { return  modulus() > rhs.modulus(); }
bool ComplexNumber::operator>=(ComplexNumber& rhs) { return  modulus() >= rhs.modulus(); }
bool ComplexNumber::operator==(ComplexNumber& rhs) { return  modulus() == rhs.modulus(); }
bool ComplexNumber::operator!=(ComplexNumber& rhs) { return  modulus() != rhs.modulus(); }

std::wostream& operator<<(std::wostream& os, ComplexNumber& rhs) {
	os << rhs.toString();
	return os;
}

double ComplexNumber::abs(ComplexNumber z) { return z.modulus(); }

ComplexNumber ComplexNumber::polar() { return ComplexNumber(modulus(), arg()); }

ComplexNumber ComplexNumber::dotProduct(ComplexNumber z1, ComplexNumber z2) {//Hermitian inner product = z1*conj(z2)
	return ComplexNumber(z1.Re*z2.Re + z1.Im*z2.Im, z1.Im*z2.Re - z1.Re*z2.Im);
}

ComplexNumber ComplexNumber::crossProduct(ComplexNumber z1, ComplexNumber z2) {
	return ComplexNumber(z1.Re*z2.Im, -z1.Im*z2.Re);
}

double ComplexNumber::angle(ComplexNumber z1, ComplexNumber z2) {
	return z2.arg() - z1.arg();
}

std::complex<double> ComplexNumber::toComplex() { return std::complex<double>(Re, Im); }

ComplexNumber ComplexNumber::toExponentialForm() { return ComplexNumber(modulus(), arg()); }

std::wstring ComplexNumber::toString() {
	std::wstring answer;
	std::wostringstream strs;
	complexNumberPrecision = precision;
	if (Re == floor(Re)) { complexNumberPrecision = 0; }
	strs << std::fixed << std::setprecision(complexNumberPrecision) << Re;
	answer.append(strs.str());
	complexNumberPrecision = precision;
	if (Im == floor(Im)) { complexNumberPrecision = 0; }
	if (Im != 0) {
		if (Im < 0) {
			answer.append(L"-");
		}
		else {
			answer.append(L"+");
		}
		if (abs(Im) != 1) {
			std::wostringstream strs2;
			strs2 << std::fixed << std::setprecision(complexNumberPrecision) << abs(Im);
			answer.append(strs2.str());
		}
		answer.append(L"i");
	}
	return answer;
}

std::wstring ComplexNumber::toStringBothParts() {
	std::wstring str = toString();
	if (Im == 0) {
		str.append(L"+0i");
	}
	return str;
}

std::wstring ComplexNumber::toStringExponentialForm() {//exponential form -- z = |z|e^arg
	std::wstring answer;
	std::wostringstream strs;
	complexNumberPrecision = precision;
	if (isIntegerComplexNumber() == true) { complexNumberPrecision = 0; }
	strs << std::fixed << std::setprecision(complexNumberPrecision) << modulus() << L"e^" << std::setprecision(complexNumberPrecision) << arg();
	answer = strs.str();
	strs.clear();
	return answer;
}

void ComplexNumber::display() { std::wcout << toString() << std::endl; }
void ComplexNumber::displayExponentialForm() { std::wcout << toStringExponentialForm() << std::endl; }

void ComplexNumber::printToFile(std::wstring filename) {
	std::wofstream outf(filename, std::ios_base::app);
	outf << toString() << L"\n";
	outf.close();
}
void ComplexNumber::printToFileExponentialForm(std::wstring filename) {
	std::wofstream outf(filename, std::ios_base::app);
	outf << toStringExponentialForm() << L"\n";
	outf.close();
}
//END COMPLEX NUMBER CLASS FUNCTIONS==================================================================

  /*===================================
  List of all Complex Functions
  ===================================*/
bool isNan(ComplexNumber z) {
	if (z.Re != z.Re || z.Im != z.Im) { return true; }
	return false;
}

ComplexNumber abs(ComplexNumber z) {
	return ComplexNumber(abs(z.Re), abs(z.Im));
}

ComplexNumber ceil(ComplexNumber z) {
	return ComplexNumber(ceil(z.Re), ceil(z.Im));
}

ComplexNumber floor(ComplexNumber z) {
	return ComplexNumber(floor(z.Re), floor(z.Im));
}

ComplexNumber round(ComplexNumber z) {
	return ComplexNumber(round(z.Re), round(z.Im));
}

ComplexNumber sqrt(ComplexNumber z) {
	double Real = sqrt(z.modulus())*(cos(z.arg() / 2));
	double Imag = sqrt(z.modulus())*(sin(z.arg() / 2));
	return ComplexNumber(Real, Imag);
}

//Logarithmic functions
//=====================
ComplexNumber log(ComplexNumber z) { // aka 'ln(z)'
									 //Returns the principal value for log(z).
									 //Note: the complex logarithm is a function with inherent range issues.
									 //Be aware of these issues before using this function.
	return ComplexNumber(log(sqrt((z.Re*z.Re) + (z.Im*z.Im))), atan2(z.Im, z.Re));
}

ComplexNumber log2(ComplexNumber z) {	//for all log bases, log_b(x) = log(x)/log(b)
	return z.divide(log(z), log(2));
}

ComplexNumber log10(ComplexNumber z) {	//for all log bases, log_b(x) = log(x)/log(b)
	return z.divide(log(z), log(10));
}

ComplexNumber logarithm(ComplexNumber z, double b) {
	return z.divide(log(z), log(b));
}

//Trig functions
//==============
//Note: all inverse hyperbolic functions return their principal value

ComplexNumber cos(ComplexNumber z) {
	double a = cos(z.Re)*cosh(z.Im);
	double b = -1 * sin(z.Re)*sinh(z.Im);
	return ComplexNumber(a, b);
}

ComplexNumber cosh(ComplexNumber z) { return ComplexNumber(cosh(z.Re)*cos(z.Im), sinh(z.Re)*sin(z.Im)); }

ComplexNumber sin(ComplexNumber z) {
	double a = sin(z.Re)*cosh(z.Im);
	double b = cos(z.Re)*sinh(z.Im);
	return ComplexNumber(a, b);
}

ComplexNumber sinh(ComplexNumber z) { return ComplexNumber(sinh(z.Re)*cos(z.Im), cosh(z.Re)*sin(z.Im)); }

ComplexNumber tan(ComplexNumber z) {
	return z.divide(sin(z), cos(z));
}

ComplexNumber tanh(ComplexNumber z) { return z.divide(sinh(z), cosh(z)); }

ComplexNumber exp(ComplexNumber z) {
	double n = exp(z.Re);
	return ComplexNumber(n*cos(z.Im), n*sin(z.Im));
}

ComplexNumber pow(ComplexNumber a, double b) {//will only return the first root if the exponent is <1 (ie principal value)
	ComplexNumber n1 = log(a);
	ComplexNumber n2 = a.multiply(b, n1);
	return exp(n2);
}

ComplexNumber pow(ComplexNumber a, ComplexNumber b) {	//a^b = exp(b*log(a))
	ComplexNumber n1 = log(a);
	ComplexNumber n2 = a.multiply(b, n1);
	return exp(n2);
}

std::complex<double> pow(std::complex<double> a, double b) { return std::complex<double>(pow(std::abs(a), b), exp(std::arg(a)*b)); }
std::complex<double> pow(std::complex<double> a, std::complex<double> b) { return exp(b*log(a)); }

std::vector<ComplexNumber> roots(ComplexNumber a, double b) {//returns a vector of all complex roots of a complex function
	std::vector<ComplexNumber> z;
	int i = 0;
	double arg = a.arg();
	while (b*((arg)+(i * 2 * PI)) < (2 * PI)) {
		double r = pow(a.modulus(), b);
		double theta = (a.arg() + (i * 2 * PI))*b;
		ComplexNumber w(r*cos(theta), r*sin(theta));
		z.push_back(w);
		++i;
	}
	return z;
}

ComplexNumber cot(ComplexNumber z) {
	return z.divide(cos(z), sin(z));
}

ComplexNumber csc(ComplexNumber z) {
	return z.divide(ComplexNumber(1, 0), sin(z));
}

ComplexNumber sec(ComplexNumber z) {
	return z.divide(ComplexNumber(1, 0), cos(z));
}

ComplexNumber acosh(ComplexNumber z) {	//acosh = log(z + (z+1)^2 (z-1)^2) )
	ComplexNumber z2(z.Re + 1, z.Im);
	ComplexNumber z3(z.Re - 1, z.Im);
	return log(z.add(z, z.multiply(sqrt(z2), sqrt(z3))));
}

ComplexNumber asin(ComplexNumber z) {	//asin(z) = -i ln(iz + sqrt(1-z^2) )
	ComplexNumber argument = z.multiply(z, z);
	argument = ComplexNumber(1 - argument.Re, argument.Im);
	argument = sqrt(argument);
	argument = argument.add(argument.multiply(ComplexNumber(0, 1), z), argument);
	argument = log(argument);
	return z.multiply(ComplexNumber(0, -1), argument);
}

ComplexNumber acos(ComplexNumber z) { //acos(z) = PI/2 - asin(z)
	return z.subtract((PI / 2), asin(z));
}

ComplexNumber asinh(ComplexNumber z) {//asinh(z) = log(z + sqrt(z^2 + 1))
	ComplexNumber z2 = z.multiply(z, z);
	z2 += 1.0;
	return z.add(z, z2);
}

ComplexNumber acsch(ComplexNumber z) {	//acsch(z) = log(1/z + sqrt(1/z^2 + 1) )
	ComplexNumber z2 = z.multiply(z, z);
	z = z.inverse();
	z2 = z2.inverse();
	ComplexNumber z3(z2.Re + 1, z2.Im);
	return log(z.add(z, sqrt(z3)));
}

ComplexNumber asech(ComplexNumber z) {	//asech(z) = log(1/z + sqrt(1/z + 1)sqrt(1/z - 1))
	z = z.inverse();
	ComplexNumber z2(z.Re + 1, z.Im);
	ComplexNumber z3(z.Re - 1, z.Im);
	z2 = z2.multiply(sqrt(z2), sqrt(z3));
	return  log(z.add(z, z2));
}

ComplexNumber atan(ComplexNumber z) {	//atan(z) = 0.5 *i *(ln(1-zi) - ln(1+zi))
	ComplexNumber iz1 = z.subtract(ComplexNumber(1, 0), z.multiply(ComplexNumber(0, 1), z));
	ComplexNumber iz2 = z.add(ComplexNumber(1, 0), z.multiply(ComplexNumber(0, 1), z));;
	iz1 = z.subtract(log(iz1), log(iz2));
	ComplexNumber a(0, 0.5);
	return a.multiply(a, iz1);
}

ComplexNumber atanh(ComplexNumber z) {	//atanh(z) = 0.5[log(1+z) - log(1-z)]
	ComplexNumber z2(1 + z.Re, z.Im);
	ComplexNumber z3(1 - z.Re, z.Im);
	z2 = log(z2);
	z3 = log(z3);
	z2 *= 0.5;
	z3 *= 0.5;
	return z2.subtract(z2, z3);
}

ComplexNumber acoth(ComplexNumber z) {	//acoth = 0.5[log(1 + 1/z) - log(1 - 1/z)]
	z = z.divide(1.0, z);
	ComplexNumber z2(1 + z.Re, z.Im);
	ComplexNumber z3(1 - z.Re, z.Im);
	z2 = log(z2);
	z3 = log(z3);
	z2 *= 0.5;
	z3 *= 0.5;
	return z2.subtract(z2, z3);
}