#include "fraction.h"
#include <iostream>
using namespace std;
int abs(int v){
	return (v>=0)?v:-v;
}
int GCDR(int a,int b);

int GCD(int a, int b){
	a=abs(a);  //absolute value
	b=abs(b);
	if(a < b){
		return GCDR(a,b);
	}
	else{
		return GCDR(b,a);
	}
}
int GCDR(int a,int b){
	if(a==0){
		return b;
	}
	else if(b==0){
		return a;
	}
	else{
		return GCDR(b,a%b);
	}

}
Fraction::Fraction(){
	numerator_=0;
	denominator_=1;
}
Fraction::Fraction(int num,int denom){
	set(num,denom);
}
void Fraction::set(int num,int denom){
	numerator_=num;
	denominator_=denom;
	reduce();
}
void Fraction::reduce(){
	int divisor=GCD(numerator_,denominator_);
	numerator_=numerator_/divisor;
	denominator_=denominator_/divisor;
	//always store negative in numerator
	if((numerator_ < 0 && denominator_ < 0) || 
		(numerator_ > 0 && denominator_ < 0)){
		numerator_=numerator_*-1;
		denominator_=denominator_*-1;
	}
}

Fraction operator+(const Fraction& f1, const Fraction& f2){
	return Fraction(f1.numerator_*f2.denominator_+f2.numerator_*f1.denominator_, f1.denominator_*f2.denominator_);
	
}
Fraction operator-(const Fraction& f1, const Fraction& f2){
	return Fraction(f1.numerator_*f2.denominator_-f2.numerator_*f1.denominator_, f1.denominator_*f2.denominator_);

}
Fraction operator*(const Fraction& f1, const Fraction& f2){
	return Fraction(f1.numerator_*f2.numerator_, f1.denominator_*f2.denominator_);
}
Fraction operator/(const Fraction& f1, const Fraction& f2){
	return Fraction(f1.numerator_*f2.denominator_, f1.denominator_*f2.numerator_);
}
ostream& operator << (ostream& os, const Fraction& data){
	if(abs(data.numerator_) < abs(data.denominator_)){
		if(data.numerator_!=0){
			os << data.numerator_ << "/"  << data.denominator_;
		}
		else{
			os << "0";
		}
	}
	else{
		os << data.numerator_/data.denominator_;
		if(data.numerator_ % data.denominator_){
			os << " " << abs(data.numerator_%data.denominator_) << "/";
			os << data.denominator_;
		}
	}
	return os;
}

const Fraction& Fraction::operator+=(const Fraction& rhs){
	*this=*this+rhs;
	return *this;
}
const Fraction& Fraction::operator-=(const Fraction& rhs){
	*this=*this-rhs;
	return *this;
}
const Fraction& Fraction::operator*=(const Fraction& rhs){
	*this = *this * rhs;
	return *this;
}
const Fraction& Fraction::operator/=(const Fraction& rhs){
	*this = *this / rhs;
	return *this;
}
bool operator==(const Fraction& f1, const Fraction& f2){
	bool rc=true;
	if((f1.numerator_!=f2.numerator_) || (f1.denominator_!=f2.denominator_)){
		rc=false;
	}
	return rc;
}
bool operator!=(const Fraction& f1, const Fraction& f2){
	bool rc=true;
	if((f1.numerator_==f2.numerator_)  && (f1.denominator_==f2.denominator_)){
		rc=false;
	}
	return rc;
}