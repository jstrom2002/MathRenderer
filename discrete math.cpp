#pragma once
#include "stdafx.h"
int getLength(double x) {//get the number of digits in a double
	double n = abs(x);
	int length = 0;
	if (n < 1) { return 0; }
	while (n > 1) {
		n /= 10;
		++length;
	}
	return length;
}

int getMantissaLength(double x) {//get the number of digits in a double's mantissa
	double n = abs(x);
	int length = 0;
	if (n == (int)n) { return 0; }
	while (n != int(n) || std::floor(n) != n) {
		n *= 10;
		++length;
	}
	return length;
}

double randDouble() { return ((double)rand() / RAND_MAX)*pow(-1, rand() % 2); }//returns a random value between [-1,1]

double fRand(double fMin, double fMax, int y) {
	srand(y);                       // seeds the random number generator
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

double boundedRand(double a, double b)
{
	int rv = rand();
	return fRand(a, b, rv);   // the random number is within [x,k] and has a random integer as a seed
}

double convertIntToDecimalValue(int n) {
	int lnt = getLength(n);
	return (n / pow(10.0, lnt));
}

double getFractionalPart(double n) {
	double intpart;
	return modf(n, &intpart);
}

int convertDecimalToInt(double n) {
	double temp = getFractionalPart(n);
	while (temp < 0) { temp *= 10; }
	int temp2 = floor(temp);
	return temp2;
}

double convertRadiansToDegrees(double n) {
	double p = 180;
	return ((n * 180) / PI);
}

double convertDegreesToRadians(double n) {
	long double p = ((n * PI) / 180.0);
	double b = p;
	return b;
}

double getWholePart(double n) {
	return floor(n);
}

bool isPrime(unsigned long long int n)
{
	unsigned long long int val = 2;
	while (val < ULLONG_MAX) {
		if ((n%val) == 0 && n != val) {
			return false;
		}
		if (val >= n) { return true; }
		val++;
	}
	return true;
}

void toDegrees(double x) { x = (PI*x / 180); }
void toRadians(double x) { x = (180 * x / PI); }

int sgn(double x) {//returns the sign of a number or 0 if the value is 0.
	if (x == 0) { return 0; }
	if (x < 0) { return -1; }
	return 1;
}

int GCD(int a, int b) {//find GCD by repeated division
	//old code:
	if (a == 0 || b == 0) { return 1; }
	if (a == 1 || b == 1) { return 1; }
	if (a == b) { return a; }

	int x = abs(a);
	int y = abs(b);
	if (x < y) {
		x = abs(b);
		y = abs(a);
	}
	while (x%y != 0) {
		int r = x%y;
		x = y;
		y = r;
	}
	return y;
}

int LCM(int a, int b) {//LCM is the product of two values divided by the GCD
	int gcd = GCD(a, b);
	return((a*b) / gcd);
}

bool checkBounds(double n) { //see if integer is larger/smaller than the maximum value for an 'if' statement check
	if (n >= 0) { if (abs(n) < ULLONG_MAX) { return true; } }
	if (n < 0) { if (abs(n) < LLONG_MAX) { return true; } }
	return false;
}

bool isInteger(double n) {
	if (floor(n) == n) { return true; }
	return false;
}

bool isEven(double n) { if ((int)floor(n) % 2 == 0) { return true; } }
bool isOdd(double n) { if ((int)floor(n) % 2 != 0) { return true; } }

bool isDivisor(int n, int s) {
	if (n%s == 0) { return true; }
	return false;
}

int numberOfDivisors(int n) {
	if (n == 0) { return 0; }
	std::vector<int> vec;
	vec.push_back(1);
	for (int i = 2; i <= n; ++i) {
		if (n%i == 0) { vec.push_back(n); }
	}
	return vec.size();
}

std::vector<int> divisors(int n) {
	if (n == 0) { return std::vector<int>(); }
	std::vector<int> vec;
	vec.push_back(1);
	for (int i = 2; i <= n; ++i) {
		if (n%i == 0) { vec.push_back(i); }
	}
	return vec;
}

double PidgeonholePrinciple(double items, double containers) {
	return ceil((items - 1) / containers);
}

double PidgeonholePrincipleInverse(double items, double k) {//IN PROGRESS
	for (double i = 0.0001; i < items; i += 0.0001) {
		//if (ceil((items - 1) / i) == k + 1) { return answer };
	}
	return 0;
}

int RamseyNumber(int r, int s) { //terms which are "0" are not known
	int numbers[10][10] =
	{ { 1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,3,4,5,6,7,8,9,10 },
	{ 1,3,6,9,14,18,23,28,36,0 },
	{ 1,4,9,18,25,0,0,0,0,0 },
	{ 1,5,14,25,0,0,0,0,0,0 },
	{ 1,6,18,0,0,0,0,0,0,0 },
	{ 1,7,23,0,0,0,0,0,0,0 },
	{ 1,8,28,0,0,0,0,0,0,0 },
	{ 1,9,36,0,0,0,0,0,0,0 },
	{ 1,10,0,0,0,0,0,0,0,0 } };
	return numbers[r - 1][s - 1];
}

int partitionNumber(int n) {
	int a[50] = { 1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 176, 231,
		297, 385, 490, 627, 792, 1002, 1255, 1575, 1958, 2436, 3010, 3718,
		4565, 5604, 6842, 8349, 10143, 12310, 14883, 17977, 21637, 26015,
		31185, 37338, 44583, 53174, 63261, 75175, 89134, 105558, 124754,
		147273, 173525 };   //Lookup table for 1st 50 partition numbers
	return a[n];
}

int partitionNumber(int n, int k) {	//divisions of number n into partitions of size k (i.e. p(n,k))
	if (n - k < k && n != k) { return partitionNumber(n - 1, k - 1); }
	if (n == k || k < 2 || n < 4) { return 1; }
	if (n == 4) {
		if (k != 2) { return 1; }
		if (k == 2) { return 2; }
	}
	return partitionNumber(n - 1, k - 1) + partitionNumber(n - k, k);
}


//Discrete functions
//==================
double squarewave(double t)
{   //by default period = 2 PI, amplitude = 1
	int test = ceil(t / PI);
	test %= 2;      //test to see if 0 <= t/pi < pi (i.e. amp = 1)

	double amplitude;
	if (test == 0)  //case: t < Pi
	{
		amplitude = -1;
		return amplitude;
	}
	else    //case: t >= Pi
	{
		amplitude = 1;
		return amplitude;
	}
}

double step(double t) {//the Heaviside Step function
	if (t < 0) { return 0; }
	return 1;
}

double rect(double x) {
	if (abs(x) == 0.5) { return 0.5; }
	if (abs(x) > 0.5) { return 0; }
	return 1;
}

double boxcar(double start, double stop, double amplitude, double t)
{   //a boxcar is a variable amplitude square pulse of duration = stop-start
	if (t < start) { return 0; }
	if (t > stop) { return 0; }
	return amplitude;
}

double tri(double x) {   //triangle function == tri(6x)
	if (abs(x) < 1) { return ((1 - abs(x))); }
	return 0;
}

double sinc(double x) {   //sinc is the function representing single slit interference in light waves
	if (x == 0) { return 1; }
	return(sin(x) / x);
}

ComplexNumber sinc(ComplexNumber z2) {   //sinc is the function representing single slit interference in light waves
	std::complex<double> z = z2.toComplex();
	if (real(z) == 0 && imag(z) == 0) { return ComplexNumber(1); }
	std::complex<double> answer = (sin(z) / z);
	return ComplexNumber(answer);
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}