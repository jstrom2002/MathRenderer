#pragma once
#include "stdafx.h"

Vector::Vector() {};
Vector::~Vector() { vec.clear(); };
Vector::Vector(std::vector<double> v) { vec = v; }
Vector::Vector(int n) {//initialize a vector of length n, comprised of all 0's
	for (int i = 0; i < n; ++i) {
		vec.push_back(0);
	}
}
Vector::Vector(double* x, int size) {
	for (int i = 0; i < size; ++i) {
		vec.push_back(x[i]);
	}
}

//VECTOR FUNCTIONS
//================
void Vector::clear() { vec.clear(); }
size_t Vector::size() { return vec.size(); }

//vector number type conversions
void Vector::convertCartesianToPolar() {
	if (size() != 2) { return; }
	double c[2];
	c[0] = sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]));
	c[1] = atan2(vec[1], vec[0]);
	vec[0] = c[0];//r
	vec[1] = c[1];//theta
}
void Vector::convertCylindricalToRectangular() {
	double c[3];
	c[0] = vec[0] * cos(vec[1]);        //x = r*cos(theta)
	c[1] = vec[0] * sin(vec[1]);    //y = r*sin(theta)
	c[2] = vec[2];                //z = z
	vec[0] = c[0], vec[1] = c[1], vec[2] = c[2];
}
void Vector::convertCylindricalToSpherical() {
	double c[3];
	c[0] = sqrt(vec[0] * vec[0] + vec[2] * vec[2]); //rho("p") = sqrt(r^2 + z^2)
	c[1] = vec[1];                            //theta = theta
	c[2] = acos(vec[2] / c[0]);               //phi = arccos(z/p)
	vec[0] = c[0], vec[1] = c[1], vec[2] = c[2];
}
void Vector::convertPolarToCartesian() {
	if (size() != 2) { return; }
	double c[2];
	c[0] = vec[0] * cos(vec[1]);
	c[1] = vec[0] * sin(vec[1]);
	vec[0] = c[0];//x
	vec[1] = c[1];//y
}

void Vector::convertRectangularToCylindrical() {
	if (size() != 3) { return; }
	double c[2];
	c[0] = sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]));
	c[1] = atan2(vec[1], vec[0]);
	vec[0] = c[0];
	vec[1] = c[1];
}

void Vector::convertRectangularToSpherical() {
	if (size() != 3) { return; }
	double c[3];
	c[0] = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	c[2] = acos(vec[2] / c[0]);
	c[1] = asin(vec[1] / (c[0] * sin(c[2])));
	vec[0] = c[0], vec[1] = c[1], vec[2] = c[2];
}
void Vector::convertSphericalToRectangular() {
	if (size() != 3) { return; }
	double c[3];
	c[0] = vec[0] * sin(vec[2])*cos(vec[1]);          //x = p*sin(phi)*cos(theta)
	c[1] = vec[0] * sin(vec[2])*sin(vec[1]);          //y = p*sin(phi)*sin(theta)
	c[2] = vec[0] * cos(vec[2]);                    //z = p*cos(phi)
	vec[0] = c[0], vec[1] = c[1], vec[2] = c[2];
}
//=====================================
bool Vector::isIntegerVector() {
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] != floor(vec[i])) { return false; }
	}
	return true;
}


Vector Vector::crossProduct(Vector a, Vector b) {//cross product is defined in 2,3,and 7 dimensions
	if (a.size() != b.size()) { return Vector(); }
	if (a.size() == 2) {
		std::vector<double> c;
		c.push_back(a.vec[0] * b.vec[1]);
		c.push_back(-(a.vec[1] * b.vec[0]));
		return Vector(c);
	}
	if (a.size() == 3) {
		std::vector<double> c;
		c.push_back((a.vec[1] * b.vec[2]) - (a.vec[2] * b.vec[1]));
		c.push_back(-1 * ((a.vec[0] * b.vec[2]) - (a.vec[2] * b.vec[0])));
		c.push_back((a.vec[0] * b.vec[1]) - (a.vec[1] * b.vec[0]));
		return Vector(c);
	}
	if (a.size() == 7) {
		double c[7] = {
			a.vec[1] * b.vec[3] - a.vec[3] * b.vec[1] + a.vec[2] * b.vec[6] - a.vec[6] * b.vec[2] + a.vec[4] * b.vec[5] - a.vec[5] * b.vec[4],
			a.vec[2] * b.vec[4] - a.vec[4] * b.vec[2] + a.vec[3] * b.vec[0] - a.vec[0] * b.vec[3] + a.vec[5] * b.vec[6] - a.vec[6] * b.vec[5],
			a.vec[3] * b.vec[5] - a.vec[5] * b.vec[3] + a.vec[4] * b.vec[1] - a.vec[1] * b.vec[4] + a.vec[6] * b.vec[0] - a.vec[0] * b.vec[6],
			a.vec[4] * b.vec[6] - a.vec[6] * b.vec[4] + a.vec[5] * b.vec[2] - a.vec[2] * b.vec[5] + a.vec[0] * b.vec[1] - a.vec[1] * b.vec[0],
			a.vec[5] * b.vec[0] - a.vec[0] * b.vec[5] + a.vec[6] * b.vec[3] - a.vec[3] * b.vec[6] + a.vec[1] * b.vec[2] - a.vec[2] * b.vec[1],
			a.vec[6] * b.vec[1] - a.vec[1] * b.vec[6] + a.vec[0] * b.vec[4] - a.vec[4] * b.vec[0] + a.vec[2] * b.vec[3] - a.vec[3] * b.vec[2],
			a.vec[0] * b.vec[2] - a.vec[2] * b.vec[0] + a.vec[1] * b.vec[5] - a.vec[5] * b.vec[1] + a.vec[3] * b.vec[4] - a.vec[4] * b.vec[3]
		};
		return Vector(c, 7);
	}
}

double Vector::dotProduct(Vector a, Vector b) {
	if (a.size() != b.size()) { return 0; }
	double answer = 0;
	for (int i = 0; i < a.size(); i++) { answer += (a.vec[i] * b.vec[i]); }
	return answer;
}

double Vector::scalarTripleProduct(Vector a, Vector b, Vector c) { // triple product is = a * (b x c)
	return dotProduct(a, crossProduct(b, c));
}

Vector Vector::vectorTripleProduct(Vector a, Vector b, Vector c) { // vector triple product is = a x (b x c)
	return crossProduct(a, crossProduct(b, c));
}

double Vector::mean() {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += vec[i];
	}
	return answer / vec.size();
}

double Vector::geometricMean() {
	double answer = 1;
	for (int i = 0; i < vec.size(); ++i) { answer *= vec[i]; }
	return pow(answer, (1.0 / vec.size()));
}

double Vector::norm() {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i], 2);
	}
	return sqrt(answer);
}

double Vector::pNorm(double p) {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i], p);
	}
	return sqrt(answer);
}

double Vector::normSquared() {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i], 2);
	}
	return answer;
}

void Vector::normalize() {
	double nrm = norm();
	for (int i = 0; i < vec.size(); ++i) {
		vec[i] /= nrm;
	}
}

void Vector::randomize() {
	srand(time(0) + clock());
	for (int i = 0; i < vec.size(); ++i) {
		vec[i] = ((double)rand() / 1000) * pow(-1, rand() % 2);
	}
}

void Vector::randomizeBoolean() {
	srand(time(0) + clock());
	for (int i = 0; i < vec.size(); ++i) {
		vec[i] = (rand() % 2);
	}
}

void Vector::randomizeInteger() {
	srand(time(0) + clock());
	for (int i = 0; i < vec.size(); ++i) {
		vec[i] = (floor(rand() / 1000)) * pow(-1, rand() % 2);
	}
}

double Vector::multiply(Vector A, Vector B) { return dotProduct(A, B); }

Vector Vector::multiply(Vector A, double B) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i)
		v.vec[i] *= B;
	return v;
}

Vector Vector::multiply(double B, Vector A) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i)
		v.vec[i] *= B;
	return v;
}

Vector Vector::add(Vector A, Vector B) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] + B.vec[i];
	}
	return v;
}

Vector Vector::add(Vector A, double B) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] + B;
	}
	return v;
}

Vector Vector::subtract(Vector A, Vector B) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] - B.vec[i];
	}
	return v;
}

Vector Vector::subtract(Vector A, double B) {
	Vector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] - B;
	}
	return v;
}

Vector Vector::exponent(Vector A, int b) {
	int size = A.size();
	std::vector<double> answerN;
	for (int i = 0; i < A.size(); ++i) {
		double n = A.dotProduct(A, A);
		answerN.push_back(n);
	}
	return Vector(answerN);
}

Vector& Vector::operator*=(Vector& rhs) { *this = multiply(*this, rhs); return*this; }
Vector& Vector::operator*=(double x) { *this = multiply(*this, x); return *this; }
double Vector::operator*(Vector& rhs) { return multiply(*this, rhs); }
Vector& Vector::operator*(double x) { return multiply(*this, x); }

Vector& Vector::operator+=(Vector& rhs) { *this = add(*this, rhs); return*this; }
Vector& Vector::operator+=(double x) { *this = add(*this, x); return *this; }
Vector& Vector::operator+(Vector& rhs) { return add(*this, rhs); }
Vector& Vector::operator+(double x) { return add(*this, x); }

Vector& Vector::operator-=(Vector& rhs) { *this = subtract(*this, rhs); return*this; }
Vector& Vector::operator-=(double x) { *this = subtract(*this, x); return *this; }
Vector& Vector::operator-(Vector& rhs) { return subtract(*this, rhs); }
Vector& Vector::operator-(double x) { return subtract(*this, x); }


bool Vector::operator==(Vector& B) {
	if (size() != B.size()) { return false; }
	for (int j = 0; j < size(); ++j) {
		if (vec[j] != B.vec[j]) { return false; }
	}
	return true;
}

std::wostream& operator<<(std::wostream& os, Vector& rhs) {
	os << rhs.toString();
	return os;
}
//========================


double Vector::getAngle(Vector A, Vector B) {
	if (A.size() != B.size() && A.size() != 2) { return NULL; }
	if (A.size() == 2) { return atan2(A.vec[0] * B.vec[1] - A.vec[1] * B.vec[0], A.vec[0] * B.vec[0] + A.vec[1] * B.vec[1]); }
	if (A.size() == 3) { acos(dotProduct(A, A) / (A.normSquared()*B.normSquared())); }
}

void Vector::sort() { std::sort(vec.begin(), vec.end()); }
double Vector::sum() {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += vec[i];
	}
	return answer;
}
double Vector::sumSquares() {
	double answer = 0;
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i], 2);
	}
	return answer;
}

double Vector::vectorScalarProjection(Vector a, Vector b) { return (dotProduct(a, b) / b.norm()); }
Vector Vector::unitNormal(Vector a, Vector b) {
	if (a.size() != b.size() || a.size() != 3) { return NULL; }
	Vector d = crossProduct(a, b);
	double multiplicand = (1 / (a.norm()*b.norm() * sin(getAngle(a, b))));
	for (int i = 0; i < 3; i++) { d.vec[i] *= multiplicand; }
	return d;
}



Vector Vector::directSum(Vector A, Vector B) {
	std::vector<double> v;
	for (int i = 0; i < A.size() + B.size(); ++i) {
		if (i < A.size()) { v.push_back(A.vec[i]); }
		else { v.push_back(B.vec[i - A.size()]); }
	}
	return Vector(v);
}

Vector Vector::tensorProduct(Vector A, Vector B) {
	std::vector<double> v;
	int counter = 0;
	for (int i = 0; i < A.size() * B.size(); ++i) {
		v.push_back(A.vec[counter] * B.vec[i%B.size()]);
		if (i%B.size() == B.size() - 1) { ++counter; }
	}
	return Vector(v);
}

double Vector::populationVariance() {
	double mu = mean();
	double answer = 0;
	for (int i = 0; i < size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (size());
}

double Vector::populationStandardDeviation() {
	return sqrt(populationVariance());
}

double Vector::sampleVariance() {
	double mu = mean();
	double answer = 0;
	for (int i = 0; i < size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (size() - 1);
}

double Vector::sampleStandardDeviation() {
	return sqrt(sampleVariance());
}

double Vector::standardErrorOfMean() { return sampleStandardDeviation() / sqrt(vec.size()); }

double Vector::covariance(Vector v1, Vector v2) {	//must fix
	double nk = 1.0 / (v1.size()*v2.size());
	double mu1 = v1.mean();
	double mu2 = v2.mean();
	double answer = 0;
	for (int i = 0; i < v1.size(); ++i) {
		for (int j = 0; j < v2.size(); ++j) {
			answer += (v1.vec[i] - mu1) * (v2.vec[j] - mu2);
		}
	}
	return answer * nk;
}

//Type conversions and output
std::wstring Vector::toString() {
	std::wostringstream sstr;
	sstr << L"(";
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i]<999999999999999999 && vec[i]> -999999999999999999) {
			if (vec[i] != floor(vec[i])) { vectorPrecision = precision; }
			else { vectorPrecision = 0; }
			sstr << std::setprecision(vectorPrecision) << vec[i];
			if (i < vec.size() - 1) { sstr << L","; }
		}
	}
	sstr << L")";
	std::wstring answer = sstr.str();
	sstr.clear();
	return answer;
}

void Vector::display() { std::wcout << toString() << std::endl; }
//====================================================================

ComplexVector::ComplexVector() {}

ComplexVector::~ComplexVector() { vec.clear(); }

ComplexVector::ComplexVector(std::vector<ComplexNumber> v) { vec = v; }

ComplexVector::ComplexVector(std::vector<std::complex<double>> v) {
	std::vector<ComplexNumber> v1;
	for (int i = 0; i < v.size(); ++i) {
		v1.push_back(ComplexNumber(v[i]));
	}
	vec = v1;
}

ComplexVector::ComplexVector(int n) {}

ComplexVector::ComplexVector(ComplexNumber n) { vec.push_back(n); }

//ComplexVector::ComplexVector(ComplexNumber* x, int size) { vec = toSTLVector(x, size); }

void ComplexVector::clear() { vec.clear(); }

size_t ComplexVector::size() { return vec.size(); }

ComplexVector ComplexVector::toExponentialForm() {
	std::vector<ComplexNumber> v;
	for (int i = 0; i < vec.size(); ++i) {
		v.push_back(vec[i].toExponentialForm());
	}
	return ComplexVector(v);
}

bool ComplexVector::isIntegerVector() {
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i].Re != floor(vec[i].Re) || vec[i].Im != floor(vec[i].Im)) { return false; }
	}
	return true;
}

ComplexVector ComplexVector::crossProduct(ComplexVector a, ComplexVector b) {
	/* cross product for two vectors (in 3D) is defined the same for C^3 as R^3 as a consequence
	of properties of the exterior product of two vectors in a Grassman algebra */

	if (a.size() != b.size()) { return ComplexVector(); }
	if (a.size() == 0) { return ComplexVector(); }
	if (a.size() == 1) {
		return ComplexVector(ComplexNumber(a*b));
	}
	if (a.size() == 2) {
		a.vec.push_back(ComplexNumber(0));
		b.vec.push_back(ComplexNumber(0));
	}
	if (a.size() == 3) {
		std::vector<std::complex<double>> A, B;
		for (int i = 0; i < 3; ++i) {
			A.push_back(a.vec[i].toComplex());
			B.push_back(b.vec[i].toComplex());
		}

		std::vector<std::complex<double>> c;
		c.push_back((A[1] * B[2]) - (A[2] * B[1]));
		c.push_back((A[2] * B[0]) - (A[0] * B[2]));
		c.push_back((A[0] * B[1]) - (A[1] * B[0]));
		return ComplexVector(c);
	}
	if (a.size() == 7) {
		if (a.size() == 7) {
			std::complex<double> c[7] = {
				a.vec[1].toComplex() * b.vec[3].toComplex() - a.vec[3].toComplex() * b.vec[1].toComplex() + a.vec[2].toComplex() * b.vec[6].toComplex() - a.vec[6].toComplex() * b.vec[2].toComplex() + a.vec[4].toComplex() * b.vec[5].toComplex() - a.vec[5].toComplex() * b.vec[4].toComplex(),
				a.vec[2].toComplex() * b.vec[4].toComplex() - a.vec[4].toComplex() * b.vec[2].toComplex() + a.vec[3].toComplex() * b.vec[0].toComplex() - a.vec[0].toComplex() * b.vec[3].toComplex() + a.vec[5].toComplex() * b.vec[6].toComplex() - a.vec[6].toComplex() * b.vec[5].toComplex(),
				a.vec[3].toComplex() * b.vec[5].toComplex() - a.vec[5].toComplex() * b.vec[3].toComplex() + a.vec[4].toComplex() * b.vec[1].toComplex() - a.vec[1].toComplex() * b.vec[4].toComplex() + a.vec[6].toComplex() * b.vec[0].toComplex() - a.vec[0].toComplex() * b.vec[6].toComplex(),
				a.vec[4].toComplex() * b.vec[6].toComplex() - a.vec[6].toComplex() * b.vec[4].toComplex() + a.vec[5].toComplex() * b.vec[2].toComplex() - a.vec[2].toComplex() * b.vec[5].toComplex() + a.vec[0].toComplex() * b.vec[1].toComplex() - a.vec[1].toComplex() * b.vec[0].toComplex(),
				a.vec[5].toComplex() * b.vec[0].toComplex() - a.vec[0].toComplex() * b.vec[5].toComplex() + a.vec[6].toComplex() * b.vec[3].toComplex() - a.vec[3].toComplex() * b.vec[6].toComplex() + a.vec[1].toComplex() * b.vec[2].toComplex() - a.vec[2].toComplex() * b.vec[1].toComplex(),
				a.vec[6].toComplex() * b.vec[1].toComplex() - a.vec[1].toComplex() * b.vec[6].toComplex() + a.vec[0].toComplex() * b.vec[4].toComplex() - a.vec[4].toComplex() * b.vec[0].toComplex() + a.vec[2].toComplex() * b.vec[3].toComplex() - a.vec[3].toComplex() * b.vec[2].toComplex(),
				a.vec[0].toComplex() * b.vec[2].toComplex() - a.vec[2].toComplex() * b.vec[0].toComplex() + a.vec[1].toComplex() * b.vec[5].toComplex() - a.vec[5].toComplex() * b.vec[1].toComplex() + a.vec[3].toComplex() * b.vec[4].toComplex() - a.vec[4].toComplex() * b.vec[3].toComplex()
			};
			std::vector<ComplexNumber> c2;
			for (int i = 0; i < 7; ++i) {
				c2.push_back(c[i]);
			}
			return ComplexVector(c2);
		}
	}
}

ComplexNumber ComplexVector::dotProduct(ComplexVector a, ComplexVector b) {
	/*for complex vectors, dot product is the sum of multiplied values where the vector b's values are conjugated.
	therefore, it is not commutative. a*b = conj(b*a) */
	if (a.size() != b.size()) { return ComplexNumber(0); }
	std::complex<double> answer = 0;
	for (int i = 0; i < a.size(); i++) { answer += (a.vec[i].toComplex() * b.vec[i].conjugate().toComplex()); }
	return ComplexNumber(answer);
}

ComplexNumber ComplexVector::scalarTripleProduct(ComplexVector a, ComplexVector b, ComplexVector c) { // triple product is = a * (b x c)
	return dotProduct(a, crossProduct(b, c));
}

ComplexVector ComplexVector::vectorTripleProduct(ComplexVector a, ComplexVector b, ComplexVector c) { // vector triple product is = a x (b x c)
	return crossProduct(a, crossProduct(b, c));
}

ComplexNumber ComplexVector::mean() {
	std::complex<double> answer(0);
	for (int i = 0; i < vec.size(); ++i) {
		answer += vec[i].toComplex();
	}
	return ComplexNumber(answer / (double)vec.size());
}

ComplexNumber ComplexVector::geometricMean() {
	std::complex<double> answer(1);
	for (int i = 0; i < vec.size(); ++i) { answer *= vec[i].toComplex(); }
	return pow(ComplexNumber(answer), (1.0 / vec.size()));
}

double ComplexVector::norm() {
	return sqrt(normSquared());
}

ComplexNumber ComplexVector::pNorm(double p) {
	std::complex<double> answer(0);
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i], p).toComplex();
	}
	return ComplexNumber(sqrt(answer));
}

double ComplexVector::normSquared() {
	std::complex<double> answer(0);
	for (int i = 0; i < vec.size(); ++i) {
		answer += (vec[i].toComplex() * (vec[i].toComplex()));
	}
	return std::real(answer);
}

void ComplexVector::normalize() {
	double nrm = norm();
	for (int i = 0; i < vec.size(); ++i) {
		std::complex<double> temp = vec[i].toComplex() / nrm;
		vec[i] = ComplexNumber(temp);
	}
}

void ComplexVector::randomize() {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].randomize();
	}
}

void ComplexVector::randomizeBoolean() {
	/*	srand(time(0) + clock());
		for (int i = 0; i < vec.size(); ++i) {
			vec[i] = (rand() % 2);
		}*/
}

void ComplexVector::randomizeInteger() {
	srand(time(0) + clock());
	for (int i = 0; i < vec.size(); ++i) {
		vec[i] = (floor(rand() / 1000)) * pow(-1, rand() % 2);
	}
}

ComplexNumber ComplexVector::multiply(ComplexVector A, ComplexVector B) { return dotProduct(A, B); }

ComplexVector ComplexVector::multiply(ComplexVector A, double B) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i)
		v.vec[i] *= B;
	return v;
}

ComplexVector ComplexVector::multiply(double B, ComplexVector A) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i)
		v.vec[i] *= B;
	return v;
}

ComplexVector ComplexVector::add(ComplexVector A, ComplexVector B) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] + B.vec[i];
	}
	return v;
}

ComplexVector ComplexVector::add(ComplexVector A, double B) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] + B;
	}
	return v;
}

ComplexVector ComplexVector::subtract(ComplexVector A, ComplexVector B) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] - B.vec[i];
	}
	return v;
}

ComplexVector ComplexVector::subtract(ComplexVector A, double B) {
	ComplexVector v(A.vec);
	for (int i = 0; i < A.size(); ++i) {
		v.vec[i] = A.vec[i] - B;
	}
	return v;
}

ComplexVector ComplexVector::exponent(ComplexVector A, int b) {
	int size = A.size();
	std::vector<ComplexNumber> answerN;
	for (int i = 0; i < A.size(); ++i) {
		ComplexNumber n = A.dotProduct(A, A);
		answerN.push_back(n);
	}
	return ComplexVector(answerN);
}

ComplexVector& ComplexVector::operator*=(ComplexVector& rhs) { *this = multiply(*this, rhs); return*this; }
ComplexVector& ComplexVector::operator*=(double x) { *this = multiply(*this, x); return *this; }
ComplexNumber ComplexVector::operator*(ComplexVector& rhs) { return multiply(*this, rhs); }
ComplexVector& ComplexVector::operator*(double x) { return multiply(*this, x); }

ComplexVector& ComplexVector::operator+=(ComplexVector& rhs) { *this = add(*this, rhs); return*this; }
ComplexVector& ComplexVector::operator+=(double x) { *this = add(*this, x); return *this; }
ComplexVector& ComplexVector::operator+(ComplexVector& rhs) { return add(*this, rhs); }
ComplexVector& ComplexVector::operator+(double x) { return add(*this, x); }

ComplexVector& ComplexVector::operator-=(ComplexVector& rhs) { *this = subtract(*this, rhs); return*this; }
ComplexVector& ComplexVector::operator-=(double x) { *this = subtract(*this, x); return *this; }
ComplexVector& ComplexVector::operator-(ComplexVector& rhs) { return subtract(*this, rhs); }
ComplexVector& ComplexVector::operator-(double x) { return subtract(*this, x); }

bool ComplexVector::operator==(ComplexVector& B) {
	if (size() != B.size()) { return false; }
	for (int j = 0; j < size(); ++j) {
		if (vec[j] != B.vec[j]) { return false; }
	}
	return true;
}

std::wostream& operator<<(std::wostream& os, ComplexVector& rhs) {
	os << rhs.toString();
	return os;
}


/*	Quaternion ComplexVector::createRotationQuaternion() {//used for rotating around an axis other than the central origin
												   /*  given a = angle to rotate
												   [x, y, z] = axis to rotate around
												   then input vector must be of form [a, x, y, z].
												   Then, return rotation Quaternion R = [cos(a / 2), sin(a / 2)*x, sin(a / 2)*y, sin(a / 2)*z]			*/
												   /*		return Quaternion(cos(vec[0] / 2), sin(vec[0] / 2)*vec[1], sin(vec[0] / 2)*vec[2], sin((vec[0] / 2)*vec[3]));
													   }

													   Quaternion ComplexVector::createRotationQuaternion(std::vector<double> v) {
														   /*  given theta = angle to rotate by, vector <x,y,z> is the axis to rotate around
														   input vector must be of form [theta, x, y, z]		*/
														   /*		return Quaternion(cos(v[0] / 2), sin(v[0] / 2)*v[1], sin(v[0] / 2)*v[2], sin((v[0] / 2))*v[3]);
															   }*/

double ComplexVector::getAngle(ComplexVector A, ComplexVector B) {
	return acos(A.dotProduct(A, B).Re / (A.norm()*B.norm()));
}

void ComplexVector::sort() {
	std::vector<double> moduli;
	for (int i = 0; i < vec.size(); ++i) {

	}
	std::sort(moduli.begin(), moduli.end());
}

ComplexNumber ComplexVector::sum() {
	std::complex<double> answer(0);
	for (int i = 0; i < vec.size(); ++i) {
		answer += vec[i].toComplex();
	}
	return ComplexNumber(answer);
}
ComplexNumber ComplexVector::sumSquares() {
	std::complex<double> answer(0);
	for (int i = 0; i < vec.size(); ++i) {
		answer += pow(vec[i].toComplex(), 2);
	}
	return ComplexNumber(answer);
}

//double ComplexVector::vectorScalarProjection(ComplexVector a, ComplexVector b) { return (dotProduct(a, b) / b.norm()); }

ComplexVector ComplexVector::unitNormal(ComplexVector a, ComplexVector b) {
	if (a.size() != b.size() || a.size() != 3) { return NULL; }
	ComplexVector d = a.crossProduct(a, b);
	double multiplicand = (1 / (a.norm()*b.norm() * sin(a.getAngle(a, b))));
	for (int i = 0; i < 3; i++) {
		d.vec[i] *= multiplicand;
	}
	return d;
}


/*ComplexVector ComplexVector::directSum(ComplexVector A, ComplexVector B) {
	std::vector<double> v;
	for (int i = 0; i < A.size() + B.size(); ++i) {
		if (i < A.size()) { v.push_back(A.vec[i]); }
		else { v.push_back(B.vec[i - A.size()]); }
	}
	return ComplexVector(v);
}

ComplexVector ComplexVector::tensorProduct(ComplexVector A, ComplexVector B) {
	std::vector<double> v;
	int counter = 0;
	for (int i = 0; i < A.size() * B.size(); ++i) {
		v.push_back(A.vec[counter] * B.vec[i%B.size()]);
		if (i%B.size() == B.size() - 1) { ++counter; }
	}
	return ComplexVector(v);
}

ComplexNumber ComplexVector::populationVariance() {
	double mu = mean();
	double answer = 0;
	for (int i = 0; i < size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (size());
}

ComplexNumber ComplexVector::populationStandardDeviation() {
	return sqrt(populationVariance());
}

ComplexNumber ComplexVector::sampleVariance() {
	double mu = mean();
	double answer = 0;
	for (int i = 0; i < size(); ++i) {
		answer += pow(vec[i] - mu, 2);
	}
	return answer / (size() - 1);
}

ComplexNumber ComplexVector::sampleStandardDeviation() {
	return sqrt(sampleVariance());
}

double ComplexVector::standardErrorOfMean() { return sampleStandardDeviation() / sqrt(vec.size()); }

double ComplexVector::covariance(ComplexVector v1, ComplexVector v2) {	//must fix
	double nk = 1.0 / (v1.size()*v2.size());
	double mu1 = v1.mean();
	double mu2 = v2.mean();
	double answer = 0;
	for (int i = 0; i < v1.size(); ++i) {
		for (int j = 0; j < v2.size(); ++j) {
			answer += (v1.vec[i] - mu1) * (v2.vec[j] - mu2);
		}
	}
	return answer * nk;
}*/


ComplexNumber ComplexVector::interiorProduct(ComplexVector a, ComplexVector b) {
	ComplexNumber dp1 = a.dotProduct(a, b);
	ComplexNumber dp2 = a.dotProduct(b, a);
	return ComplexNumber(0.5*(dp1.toComplex() + dp2.toComplex()));
}

ComplexNumber ComplexVector::exteriorProduct(ComplexVector a, ComplexVector b) {
	ComplexNumber dp1 = a.dotProduct(a, b);
	ComplexNumber dp2 = a.dotProduct(b, a);
	return ComplexNumber(0.5*(dp1.toComplex() - dp2.toComplex()));
}

std::wstring ComplexVector::toString() {
	std::wostringstream sstr;
	sstr << L"(";
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i].modulus() < 9999999999999999 && vec[i].modulus() > -9999999999999999) {
			if (vec[i] != floor(vec[i])) { complexVectorPrecision = precision; }
			else { complexVectorPrecision = 0; }
			sstr << std::setprecision(complexVectorPrecision) << vec[i].toString();
			if (i < vec.size() - 1) { sstr << L","; }
		}
	}
	sstr << L")";
	std::wstring answer = sstr.str();
	sstr.clear();
	return answer;
}

void ComplexVector::display() { std::wcout << toString() << std::endl; }