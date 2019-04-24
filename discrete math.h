#ifndef DISCRETEMATH_H
#define DISCRETEMATH_H
#pragma once
#include "stdafx.h"
int getLength(double x);
int getMantissaLength(double x);//get the number of digits in a double's mantissa
double randDouble();
double fRand(double fMin, double fMax, int y);
double boundedRand(double a, double b);
double convertIntToDecimalValue(int n);
double getFractionalPart(double n);
int convertDecimalToInt(double n);
double convertRadiansToDegrees(double n);
double convertDegreesToRadians(double n);
double getWholePart(double n);
bool isPrime(unsigned long long int n);
void toDegrees(double x);
void toRadians(double x);
int sgn(double x);
int GCD(int a, int b);
int LCM(int a, int b);
bool checkBounds(double n);
bool isInteger(double n);
bool isEven(double n);
bool isOdd(double n);
bool isDivisor(int n, int s);
int numberOfDivisors(int n);
std::vector<int> divisors(int n);
double PidgeonholePrinciple(double items, double containers);
double PidgeonholePrincipleInverse(double items, double k);
int RamseyNumber(int r, int s);
int partitionNumber(int n);
int partitionNumber(int n, int k);
double squarewave(double t);
double step(double t);
double rect(double x);
double boxcar(double start, double stop, double amplitude, double t);
double tri(double x);
double sinc(double x);
ComplexNumber sinc(ComplexNumber z2);
template <typename T> int sgn(T val);
#endif