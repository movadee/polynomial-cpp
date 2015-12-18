#include "polynomial.h"
#include "fraction.h"
#include <iostream>
using namespace std;

int main(void) {

//Testing constructors***************************************************
	int data[4][3] = {  {3,4,0},
						{7,3,5},
						{3,8,4},
						{9,1,2} };

	Polynomial p1(data, 4);
	cout << "I am a poly #1" << endl << p1 << endl;

	Polynomial p2(p1);
	cout << "I am a poly #2" << endl << p2 << endl;
	
//Testing ASSIGNMENT operators*******************************************
	int data2[4][3] = { {1,2,9},
						{4,5,6},
						{7,8,5},
						{9,1,2} };

	Polynomial p3(data2, 4);
	Polynomial p4 = p3;
	cout << "I am a poly #4 after ASSIGNMENT operator" << endl << p4 << endl;

//Testing PLUS & MINUS operators*****************************************
	Polynomial p5 = p1 + p3;
	cout << "I am a poly #5 after PLUS operator" << endl << p5 << endl;

	Polynomial p6 = p1 - p3;
	cout << "I am a poly #8 after MINUS operator" << endl << p6 << endl;

//Testing MULTIPLICATION operator****************************************
	int data3[3][3] = { {5,6,5},
					   {-2,9,2},
						{5,1,0} };
	Polynomial p7(data3, 3);

	int data4[2][3] = { {2,9,3},
					   {-3,2,1} };
	Polynomial p8(data4, 2);

	Polynomial p9 = p7 * p8;
	cout << "I am a poly #9 after MULTIPLICATION operator" << endl << p9 << endl;

//Testing DIVISION operator***********************************************
	Polynomial p10 = p7 / p8;
	cout << "I am a poly #10 after DIVISION operator" << endl << p10 << endl;

//Testing REMAINDER operator***********************************************
	Polynomial p11 = p7 % p8;
	cout << "I am a poly #11 after MODULUS operator" << endl << p11 << endl;

//Testing SOLVE operator***************************************************
	int data5[3][3] = { {2,3,2},
					    {3,5,1},
					   {-1,1,0}};
	Polynomial p12(data5, 3);

	
	cout << "I am a fraction after SOLVE operator" << endl << p12.solve(Fraction(1,2)) << endl;
	getchar();getchar();

}