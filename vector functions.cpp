#pragma once
#include "stdafx.h"

int maxValue(int *arg, ...) {
	va_list arguments;
	int max = 0;

	for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, int *)) {
		if (*arg > max) {
			max = *arg;
		}
	}
	va_end(arguments);
	return max;
}

double maxValue(double *arg, ...) {
	va_list arguments;
	double max = 0;

	for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, double *)) {
		if (*arg > max) {
			max = *arg;
		}
	}
	va_end(arguments);
	return max;
}

double* arrmultiply(double* arr, int sz, double x) {
	double* n = new double[sz];
	for (int i = 0; i < sz; ++i) {
		n[i] = arr[i] * x;
	}
	return n;
}

std::vector<double> arrmultiply(std::vector<double> n, std::vector<double>  x);

std::vector<double> arrmultiply(std::vector<double> n, double x) {//multiply all elements in array by some constant
	for (int i = 0; i < n.size(); ++i) {
		n[i] *= x;
	}
	return n;
}

std::vector<double> arrmultiply(std::vector<double> n, std::vector<double>  x) {//multiply all elements in two arrays by one another
	for (int i = 0; i < n.size(); ++i) {
		n[i] *= x[i];
	}
	return n;
}

double arrsum(double* n, int size) {//sum all elements in array
	double answer = 0;
	for (int i = 0; i < size; ++i) {
		answer += n[i];
	}
	return answer;
}

double arrsum(std::vector<double> n) {//sum all elements in array
	double answer = 0;
	for (int i = 0; i < n.size(); ++i) {
		answer += n[i];
	}
	return answer;
}

double arrsumexp(double* n, int size, double p) {//sum all elements in array of power p
	double answer = 0;
	for (int i = 0; i < size; ++i) {
		answer += pow(n[i], p);
	}
	return answer;
}

double arrsumexp(std::vector<double> n, double p) {//sum all elements in array of power p
	double answer = 0;
	for (int i = 0; i < n.size(); ++i) {
		answer += pow(n[i], p);
	}
	return answer;
}

double arrmean(double* n, int sz) {
	return arrsum(n, sz) / sz;
}

double arrmean(std::vector<double> n) { return arrsum(n) / n.size(); }

std::vector<double> arrsubtract(std::vector<double> n, std::vector<double> x) {//subtract elements in two arrays
	for (int i = 0; i < n.size(); ++i) {
		n[i] -= x[i];
	}
	return n;
}

std::vector<double> arrsubtract(std::vector<double> n, double x) {//subtract elements in two arrays
	for (int i = 0; i < n.size(); ++i) {
		n[i] -= x;
	}
	return n;
}

std::wstring arrToString(double* v, int size) {
	std::wostringstream os;
	for (int i = 0; i < size - 1; ++i) {
		os << to_stringPrecision(v[i]) << L", ";
	}
	os << to_stringPrecision(v[size - 1]);
	std::wstring str = os.str();
	os.clear();
	os.flush();
	return str;
}

std::wstring arrToString(std::vector<double> v) {
	std::wostringstream os;
	for (int i = 0; i < v.size() - 1; ++i) {
		os << to_stringPrecision(v[i]) << L", ";
	}
	os << to_stringPrecision(v[v.size() - 1]);
	std::wstring str = os.str();
	os.clear();
	os.flush();
	return str;
}

double arrNorm(double* n, int size) {
	double answer = 0;
	for (int i = 0; i < size; ++i) {
		answer += pow(n[i], 2);
	}
	answer = sqrt(answer);
	return answer;
}


double arrNorm(std::vector<double> n) {
	double answer = 0;
	for (int i = 0; i < n.size(); ++i) {
		answer += pow(n[i], 2);
	}
	answer = sqrt(answer);
	return answer;
}

double arrNorm(std::vector<float> n) {
	double answer = 0;
	for (int i = 0; i < n.size(); ++i) {
		answer += pow(n[i], 2);
	}
	answer = sqrt(answer);
	return answer;
}

/*double arrNorm(std::vector<GLfloat> n) {
	double answer = 0;
	for (int i = 0; i < n.size(); ++i) {
		answer += pow(n[i], 2);
	}
	answer = sqrt(answer);
	return answer;
}*/

double* normedArray(double* n, int size) {
	double norm = (1 / arrNorm(n, size));
	for (int i = 0; i < size; ++i) {
		n[i] *= norm;
	}
	return n;
}

std::vector<double> normedArray(std::vector<double> n) {
	double norm = (1 / arrNorm(n));
	for (int i = 0; i < n.size(); ++i) {
		n[i] *= norm;
	}
	return n;
}

double dotProduct(double* a, double* b, int length) {
	double* n = new double[length];
	for (int i = 0; i < length; ++i) {
		n[i] = a[i] * b[i];
	}
	return arrsum(n, length);
}

double dotProduct(std::vector<double> a, std::vector<double>  b) {
	double n = 0;
	for (int i = 0; i < a.size(); ++i) {
		n += a[i] * b[i];
	}
	return n;
}

double perpDotProduct(std::vector<double> a, std::vector<double>  b) {
	return arrNorm(a)*arrNorm(b)*sin(vectorGetAngle(a, b));
}

void displayarr(double* n, int size) {//print array
	for (int i = 0; i < size; ++i) {
		if (n[i]<99999999999999 && n[i]>-999999999999999) { std::wcout << n[i] << L","; }
	}
	std::wcout << L"\n";
}

void displayarr(std::vector<double> n) {//print vector
	for (int i = 0; i < n.size(); ++i) {
		if (n[i]<99999999999999 && n[i]>-999999999999999) { std::wcout << n[i] << L","; }
	}
	std::wcout << L"\n";
}

void displayarr(std::vector<std::wstring> n) {//print vector
	for (int i = 0; i < n.size(); ++i) {
		std::wcout << n[i] << L"\n";
	}
}

void displayarr(std::vector<int> n) {//print vector
	for (int i = 0; i < n.size(); ++i) {
		if (n[i]<99999999999999 && n[i]>-999999999999999) { std::wcout << n[i] << L","; }
	}
	std::wcout << L"\n";
}

bool arrcheck(double* n, double x, int size) {//check to see if element exists in array
	for (int i = 0; i < size; ++i) {
		if (n[i] == x) { return true; }
	}
	return false;
}

bool arrcheck(std::vector<double> n, double x) {//check to see if element exists in array
	for (int i = 0; i < n.size(); ++i) {
		if (n[i] == x) { return true; }
	}
	return false;
}

std::vector<double> deleteElement(std::vector<double> a, int elem) {
	std::vector<double> b;
	for (int i = 0; i < a.size(); ++i) {
		if (i != elem) { b.push_back(a[i]); }
	}
	return b;
}

int findPosition(std::vector<double> a, double elem) {
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] == elem) { return i; }
	}
	return 0;
}

int findPosition(std::vector<int> a, int elem) {
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] == elem) { return i; }
	}
	return 0;
}

std::vector<double> initZeros(std::vector<double> vec, int size) {
	for (int p = 0; p < size;++p) {
		vec.push_back(0);
	}
	return vec;
}

double leastElement(std::vector<double> v) {
	if (v.size() == 0) { return 0; }
	double answer = v[0];
	double sz = v.size();
	for (int i = 0; i < sz; ++i) {
		if (v[i] < answer) { answer = v[i]; }
	}
	return answer;
}

double leastElement(double* v, int sz) {
	if (sz == 0) { return 0; }
	double answer = v[0];
	for (int i = 0; i < sz; ++i) {
		if (v[i] < answer) { answer = v[i]; }
	}
	return answer;
}

double greatestElement(std::vector<double> v) {
	if (v.size() == 0) { return 0; }
	double answer = v[0];
	double sz = v.size();
	for (int i = 0; i < sz; ++i) {
		if (v[i] > answer) { answer = v[i]; }
	}
	return answer;
}

int greatestElement(std::vector<int> v) {
	if (v.size() == 0) { return 0; }
	int answer = v[0];
	int sz = v.size();
	for (int i = 0; i < sz; ++i) {
		if (v[i] > answer) { answer = v[i]; }
	}
	return answer;
}

size_t greatestElement(std::vector<size_t> v) {
	if (v.size() == 0) { return 0; }
	int answer = v[0];
	int sz = v.size();
	for (int i = 0; i < sz; ++i) {
		if (v[i] > answer) { answer = v[i]; }
	}
	return answer;
}

size_t greatestElementIndex(std::vector<size_t> v) {
	if (v.size() == 0) { return 0; }
	int answer = 0;
	int sz = v.size();
	for (int i = 0; i < sz; ++i) {
		if (v[i] > answer) { answer = i; }
	}
	return answer;
}

int greatestElementIndex(std::vector<int> v) {
	if (v.size() == 0) { return 0; }
	int answer = 0;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] > v[answer]) { answer = i; }
	}
	return answer;
}

double greatestElement(double* v, int sz) {
	if (sz == 0) { return 0; }
	double answer = v[0];
	for (int i = 0; i < sz; ++i) {
		if (v[i] > answer) { answer = v[i]; }
	}
	return answer;
}

std::vector<double> reverse(std::vector<double> a) {
	std::vector<double> b = a;
	std::reverse(b.begin(), b.end());
	return b;
}

void sort(double* x, int size) { std::sort(x, x + size); }
void sort(std::vector<double> v) { std::sort(v.begin(), v.end()); }

std::vector<std::vector<double>> permutations(std::vector<double> vec) {
//	int sz = factorial(vec.size());
	std::vector<std::vector<double>> perm;
/*	perm.push_back(vec);
	while (std::next_permutation(vec.begin(), vec.end())) {
		perm.push_back(vec);
	}
*/	return perm;
}

std::vector<double> removeNullValues(std::vector<double> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		if (abs(vec[i]) < 0.00000001) { vec.erase(vec.begin() + i); }
	}
	return vec;
}

/*template <typename T, typename A>
void removeDuplicates(std::vector<T,A> vec) {
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}*/



double mean(std::vector<double> v) {
	double answer = 0;
	for (int i = 0; i < v.size(); ++i) {
		answer += v[i];
	}
	return answer / v.size();
}

std::vector<double> toSTLVector(double* x, int size) {
	std::vector<double> vec;
	for (int i = 0; i < size; ++i) {
		vec.push_back(x[i]);
	}
	return vec;
}

std::vector<long double> toSTLVector(long double* x, int size) {
	std::vector<long double> vec;
	for (int i = 0; i < size; ++i) {
		vec.push_back(x[i]);
	}
	return vec;
}

std::vector<ComplexNumber> toSTLVector(ComplexNumber* x, int size) {
	std::vector<ComplexNumber> vec;
	for (int i = 0; i < size; ++i) {
		vec.push_back(x[i]);
	}
	return vec;
}

Vector toVector(double* x, int size) {
	std::vector<double> vec;
	for (int i = 0; i < size; ++i) {
		vec.push_back(x[i]);
	}
	return Vector(vec);
}

std::vector<int> STLDoubleToInt(std::vector<double> x) {
	std::vector<int> vec;
	for (int i = 0; i < x.size(); ++i) {
		vec.push_back((int)x[i]);
	}
	return vec;
}

std::vector<double> STLIntToDouble(std::vector<int> x) {
	std::vector<double> vec;
	for (int i = 0; i < x.size(); ++i) {
		vec.push_back(x[i]);
	}
	return vec;
}

std::vector<double> randomVector(int n) {
	std::vector<double> answer;
	for (int i = 0; i < n; i++) {
		answer.push_back((rand() / 10000) * pow(-1, rand() % 2)); //create a random vector with values dictated by precision variable
	}
	return answer;
}

double vectorNorm(double* a, int size) {
	double answer = 0;
	for (int i = 0; i < size; i++) {
		answer += (a[i] * a[i]);
	}
	return sqrt(answer);
}

double vectorNorm(std::vector<double> a) {
	double answer = 0;
	for (int i = 0; i < a.size(); i++) {
		answer += (a[i] * a[i]);
	}
	return sqrt(answer);
}

double* vectorUnitVector(double a[], int size) {
	double norm = vectorNorm(a, size);
	double* c = {};
	for (int i = 0; i < sizeof(a) - 1; i++) {
		c[i] = a[i] / norm;
	}
	return c;
}

double* vectorAddition(double a[], double b[], int size) {
	double* answer = new double[size];
	for (int i = 0; i < size; i++) {
		answer[i] = a[i] + b[i];
	}
	return answer;
}

double* vectorAddition(std::vector<double> a, std::vector<double> b) {
	double* answer = new double[a.size() * b.size()];

	for (int i = 0; i < a.size(); i++) {
		answer[i] = a[i] + b[i];
	}
	return answer;
}

std::vector<double> vectorAddition2(std::vector<double> a, std::vector<double> b) {
	std::vector<double> answer;

	for (int i = 0; i < a.size(); i++) {
		answer.push_back(a[i] + b[i]);
	}
	return answer;
}

std::vector<double> vectorAddition2(double a[], double b[], int size) {
	std::vector<double> answer;
	for (int i = 0; i < size; i++) {
		answer.push_back(a[i] + b[i]);
	}
	return answer;
}

double vectorDotProduct(double a[], double b[], int size) {
	double answer = 0;
	for (int i = 0; i < size; i++) {
		answer += a[i] * b[i];
	}
	return answer;
}

double vectorDotProduct(std::vector<double> a, std::vector<double> b) {
	double answer = 0;

	if (a.size() != b.size()) {
		std::wcout << L"ERROR! Vector size mismatch.";
		return 0;
	}

	for (int i = 0; i < a.size(); i++) {
		answer += (a[i] * b[i]);
	}
	return answer;
}

double vectorGetAngle(double a[], double b[], int size) {
	double answer = vectorDotProduct(a, b, size);
	answer = answer / (vectorNorm(a, size)*vectorNorm(b, size));
	answer = acos(answer);
	return answer;
}

double* vectorCrossProduct2D(double a[], double b[]) {
	if (sizeof(a) != sizeof(b) && sizeof(a) != 2) {
		std::wcout << L"ERROR! Vector size mismatch.";
		return NULL;
	}
	double c[2];
	c[0] = (a[0] * b[1]);
	c[1] = -1 * (a[1] * b[0]);
	return c;
}

std::vector<double> vectorCrossProduct2D2(std::vector<double> a, std::vector<double> b) {
	if (a.size() != b.size() && a.size() != 2) {
		std::wcout << L"ERROR! Vector size mismatch.";
		return a;
	}
	std::vector<double> c;
	c.push_back(a[0] * b[1]);
	c.push_back(-(a[1] * b[0]));
	return c;
}

double* vectorCrossProduct3D(double a[], double b[]) {
	if (sizeof(a) != sizeof(b) && sizeof(a) != 3) {
		std::wcout << L"ERROR! Vector size mismatch.";
		return NULL;
	}
	double c[3];

	c[0] = (a[1] * b[2]) - (a[2] * b[1]);
	c[1] = -1 * ((a[0] * b[2]) - (a[2] * b[0]));
	c[2] = (a[0] * b[1]) - (a[1] * b[0]);
	return c;
}

std::vector<double> vectorCrossProduct3D2(std::vector<double> a, std::vector<double> b) {
	if (a.size() != b.size() && a.size() != 3) {
		std::wcout << L"ERROR! Vector size mismatch.";
		return a;
	}
	std::vector<double> c;

	c.push_back((a[1] * b[2]) - (a[2] * b[1]));
	c.push_back(-1 * ((a[0] * b[2]) - (a[2] * b[0])));
	c.push_back((a[0] * b[1]) - (a[1] * b[0]));
	return c;
}

double vectorGetAngle(std::vector<double> a, std::vector<double> b) {
	double answer = vectorDotProduct(a, b);
	answer = answer / (vectorNorm(a)*vectorNorm(b));
	answer = acos(answer);
	return answer;
}

double vectorScalarProjection(double a[], double b[], int size) {
	return vectorDotProduct(a, b, size) / vectorNorm(b, size);
}



void vectorScalarMultiplication(double n, double a[]) {
	for (int i = 0; i < sizeof(a) - 1; i++) {
		a[i] *= n;
	}
	return;
}
void vectorScalarMultiplication(std::vector<double> v1, double n) {
	for (int i = 0; i < v1.size(); i++) {
		v1[i] *= n;
	}
}

std::vector<double> vectorScalarMultiplication2(std::vector<double> v1, double n) {
	std::vector<double> answer;
	for (int i = 0; i < v1.size(); i++) {
		answer.push_back(v1[i] * n);
	}
	return answer;
}

double* vectorUnitNormal3D(double a[], double b[]) {
	double* D = new double[3];
	D = { vectorCrossProduct3D(a, b) };
	double d[3];
	d[0] = D[0], d[1] = D[1], d[2] = D[2];
	double multiplicand = (1 / (vectorNorm(a, 3)*vectorNorm(b, 3) * sin(vectorGetAngle(a, b, 3))));
	for (int i = 0; i < 3; i++) {
		d[i] *= multiplicand;
	}
	return d;
}

std::vector<double> vectorUnitNormal3D2(std::vector<double> a, std::vector<double> b) {
	std::vector<double> D;
	D = { vectorCrossProduct3D2(a, b) };
	std::vector<double> d;
	d.push_back(D[0]);
	d.push_back(D[1]);
	d.push_back(D[2]);
	double multiplicand = (1 / (vectorNorm(a)*vectorNorm(b) * sin(vectorGetAngle(a, b))));
	for (int i = 0; i < 3; i++) {
		d[i] *= multiplicand;
	}
	return d;
}

//the following Cartesian/Polar/Cylindrical/Spherical converstions are for vectors of length 2 or 3, ie point sets in R2/R3.
void vectorConvertCartesianToPolar(double a[]) {
	double c[2];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
}

void vectorConvertCartesianToPolar(std::vector<double> a) {
	double c[2];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
}

std::vector<double> vectorConvertCartesianToPolar2(std::vector<double> a) {
	if (a.size() != 2) {
		std::wcout << L"ERROR! Vector is not of length 2.";
		std::vector<double> answer;
		return answer;
	}
	double c[2];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	return answer;
}

void vectorConvertPolarToCartesian(double a[]) {
	double c[2];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
}

std::vector<double> vectorConvertPolarToCartesian2(std::vector<double> a) {
	if (a.size() != 2) {
		std::wcout << L"ERROR! Vector is not of length 2.";
		std::vector<double> answer;
		return answer;
	}
	double c[2];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	return answer;
}

void vectorConvertRectangularToCylindrical(double a[]) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
}

std::vector<double> vectorConvertRectangularToCylindrical2(std::vector<double> a) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1]);
	c[1] = atan(a[1] / a[0]);
	a[0] = c[0];
	a[1] = c[1];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	answer.push_back(c[2]);
	return answer;
}

void vectorConvertRectangularToSpherical(double a[]) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	c[2] = acos(a[2] / c[0]);
	c[1] = asin(a[1] / (c[0] * sin(c[2])));
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
}

std::vector<double> vectorConvertRectangularToSpherical2(std::vector<double> a) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	c[2] = acos(a[2] / c[0]);
	c[1] = asin(a[1] / (c[0] * sin(c[2])));
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	answer.push_back(c[2]);
	return answer;
}

void vectorConvertCylindricalToSpherical(double a[]) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[2] * a[2]); //rho("p") = sqrt(r^2 + z^2)
	c[1] = a[1];                            //theta = theta
	c[2] = acos(a[2] / c[0]);               //phi = arccos(z/p)
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
}

std::vector<double> vectorConvertCylindricalToSpherical2(std::vector<double> a) {
	double c[3];
	c[0] = sqrt(a[0] * a[0] + a[2] * a[2]); //rho("p") = sqrt(r^2 + z^2)
	c[1] = a[1];                            //theta = theta
	c[2] = acos(a[2] / c[0]);               //phi = arccos(z/p)
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	answer.push_back(c[2]);
	return answer;
}

void vectorConvertSphericalToRectangular(double a[]) {
	double c[3];
	c[0] = a[0] * sin(a[2])*cos(a[1]);          //x = p*sin(phi)*cos(theta)
	c[1] = a[0] * sin(a[2])*sin(a[1]);          //y = p*sin(phi)*sin(theta)
	c[2] = a[0] * cos(a[2]);                    //z = p*cos(phi)
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
}

std::vector<double> vectorConvertSphericalToRectangular2(std::vector<double> a) {
	double c[3];
	c[0] = a[0] * sin(a[2])*cos(a[1]);          //x = p*sin(phi)*cos(theta)
	c[1] = a[0] * sin(a[2])*sin(a[1]);          //y = p*sin(phi)*sin(theta)
	c[2] = a[0] * cos(a[2]);                    //z = p*cos(phi)
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	answer.push_back(c[2]);
	return answer;
}

void vectorConvertCylindricalToRectangular(double a[]) {
	double c[3];
	c[0] = a[0] * cos(a[1]);        //x = r*cos(theta)
	c[1] = a[0] * sin(a[1]);    //y = r*sin(theta)
	c[2] = a[2];                //z = z
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
}

std::vector<double> vectorConvertCylindricalToRectangular2(std::vector<double> a) {
	double c[3];
	c[0] = a[0] * cos(a[1]);        //x = r*cos(theta)
	c[1] = a[0] * sin(a[1]);    //y = r*sin(theta)
	c[2] = a[2];                //z = z
	a[0] = c[0], a[1] = c[1], a[2] = c[2];
	std::vector<double> answer;
	answer.push_back(c[0]);
	answer.push_back(c[1]);
	answer.push_back(c[2]);
	return answer;
}

/*Matrix vectorChangeOfBasis2D(double a[], Matrix P) {
double b[4] = { 0,0,0,0 };
b[0] = a[0];
b[3] = a[1];
MatrixXd B(b, 2, 2);
MatrixXd Final = matrixMultiplication(P, B);
return Final;
}*/

bool vectorTestIndependence(double a[], double b[]) {        // In progress
	bool areSame = false;
	for (double j = 0; j < 999; j += 0.1) {
		for (double i = 0; i < 999; i += 0.1) {
			vectorScalarMultiplication(i, a);
			vectorScalarMultiplication(j, b);
		}
		for (int k = 0; k < sizeof(a); k++) {
			if (a[k] != b[k]) {
				areSame = false;
			}
		}
		if (areSame == true) {
			return false;
		}
	}

	return true;
}

double arrayPopulationVariance(std::vector<double> vec) {
	double mu = mean(vec);
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (vec.size());
}

double arrayPopulationStandardDeviation(std::vector<double> vec) {
	return sqrt(arrayPopulationVariance(vec));
}

double arraySampleVariance(std::vector<double> vec) {
	int sz = vec.size();
	double mu = arrmean(vec);
	double answer = 0;
	for (int i = 0; i < sz; ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (sz - 1);
}

double arraySampleStandardDeviation(std::vector<double> vec) {
	return sqrt(arraySampleVariance(vec));
}

double arrPopulationVariance(double* vec, int sz) {
	double mu = arrmean(vec, sz);
	double answer = 0;
	for (int i = 0; i < sz; ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (sz);
}

double arrPopulationStandardDeviation(double* vec, int sz) {
	return sqrt(arrPopulationVariance(vec, sz));
}

double arrSampleVariance(double* vec, int sz) {
	double mu = arrmean(vec, sz);
	double answer = 0;
	for (int i = 0; i < sz; ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (sz - 1);
}
double arrSampleVariance(std::vector<double> vec) {
	double mu = arrmean(vec);
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (vec.size() - 1);
}

double arrSampleStandardDeviation(double* vec, int sz) {
	return sqrt(arrSampleVariance(vec, sz));
}
double arrSampleStandardDeviation(std::vector<double> vec) {
	return sqrt(arrSampleVariance(vec));
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

void vectorList(std::vector<double> v1) {
	std::wcout << L"<";
	for (int i = 0; i < v1.size(); i++) {
		std::wcout << v1[i] << L",";
	}
	std::wcout << L">";
}

std::wstring toString(double* n, int sz) {
	std::wostringstream sstr;
	sstr << L"(";
	for (int i = 0; i < sz; ++i) {
		if (n[i]<999999999999999999 && n[i]> -999999999999999999) {
			sstr << n[i];
			if (i < sz - 1) { sstr << L","; }
		}
	}
	sstr << L")";
	std::wstring answer = sstr.str();
	sstr.clear();
	return answer;
}

std::wstring toString(std::vector<double> n) {
	std::wostringstream sstr;
	sstr << L"(";
	for (int i = 0; i < n.size(); ++i) {
		if (n[i]<999999999999999999 && n[i]> -999999999999999999) {
			sstr << n[i];
			if (i < n.size() - 1) { sstr << L","; }
		}
	}
	sstr << L")";
	std::wstring answer = sstr.str();
	sstr.clear();
	return answer;
}

std::wstring toString(std::vector<ComplexNumber> n) {
	std::wostringstream sstr;
	sstr << L"(";
	for (int i = 0; i < n.size(); ++i) {
		sstr << n[i].toString();
		if (i < n.size() - 1) { sstr << L","; }
	}
	sstr << L")";
	std::wstring answer = sstr.str();
	sstr.clear();
	return answer;
}

void display(std::vector<double> n) { std::wcout << toString(n) << std::endl; }
