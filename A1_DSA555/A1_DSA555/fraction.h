#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
using namespace std;

class Fraction{
private:
	int numerator_;
	int denominator_;
	friend Fraction operator+(const Fraction& f1, const Fraction& f2);
	friend Fraction operator-(const Fraction& f1, const Fraction& f2);
	friend Fraction operator*(const Fraction& f1, const Fraction& f2);
	friend Fraction operator/(const Fraction& f1, const Fraction& f2);
	friend ostream& operator << (ostream& os, const Fraction& data);
	friend bool operator==(const Fraction& f1, const Fraction& f2);
	friend bool operator!=(const Fraction& f1, const Fraction& f2);

public:
	Fraction();
	Fraction(int num,int denom);
	void set(int num,int denom);
	int numerator(){return numerator_;}
	int denominator(){return denominator_;}
	void reduce();
	const Fraction& operator+=(const Fraction& rhs);
	const Fraction& operator-=(const Fraction& rhs);
	const Fraction& operator/=(const Fraction& rhs);
	const Fraction& operator*=(const Fraction& rhs);
};
Fraction operator+(const Fraction& f1, const Fraction& f2);
Fraction operator-(const Fraction& f1, const Fraction& f2);
Fraction operator*(const Fraction& f1, const Fraction& f2);
Fraction operator/(const Fraction& f1, const Fraction& f2);
bool operator==(const Fraction& f1, const Fraction& f2);
bool operator!=(const Fraction& f1, const Fraction& f2);
ostream& operator << (ostream& os, const Fraction& data);

#endif