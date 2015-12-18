#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "fraction.h"
#include <iostream>
using namespace std;
class Polynomial;

class PolyNode{
private:
	Fraction coefficient_;
	int degree_;
	PolyNode* next_;
public:
	friend class Polynomial;
	PolyNode(const Fraction& coefficient, int degree, PolyNode* next = NULL);
	const Fraction& coefficient() const{return coefficient_;}
	int degree() const{return degree_;}
	void changeCoefficient(const Fraction& coefficient){
		coefficient_=coefficient;
	}
    PolyNode* next() const{return next_;}

	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator/(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator%(const Polynomial& p1, const Polynomial& p2);
	friend bool operator==(const Polynomial& p1, const Polynomial& p2);
	friend ostream& operator<<(ostream& os, const Polynomial& dat);
};
Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
Polynomial operator/(const Polynomial& p1, const Polynomial& p2);
Polynomial operator%(const Polynomial& p1, const Polynomial& p2); 
bool operator==(const Polynomial& p1, const Polynomial& p2);
ostream& operator<<(ostream& os, const Polynomial& dat);

class Polynomial{
	PolyNode* first_;
	void clear();
public:
	Polynomial();
	Polynomial(int data[][3],int numTerms);
	Polynomial(const Polynomial& poly);
	const Polynomial& operator=(const Polynomial& poly);
	~Polynomial();
	void addTerm(const Fraction& coefficient, int degree);
	Fraction solve(const Fraction& x);
	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator/(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator%(const Polynomial& p1, const Polynomial& p2);
	friend bool operator==(const Polynomial& p1, const Polynomial& p2);
	friend ostream& operator<<(ostream& os, const Polynomial& dat);
	friend void divide(const Polynomial& p1,const Polynomial& p2, 
					   Polynomial& quotient, Polynomial& remainder);
};


#endif