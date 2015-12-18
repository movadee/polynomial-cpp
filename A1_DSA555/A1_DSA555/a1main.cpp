/***********************************************************/
/*                                                         */
/*   Written by: Catherine Leung                           */
/*   Version 1.0                                           */
/*   This is the official test main for assignment 1.      */
/*   DSA555-Fall 2014                                      */
/*                                                         */
/*   You will need to make sure you also have the files    */
/*   a1testing.txt and results.txt                         */
/***********************************************************/

#include "polynomial.h"
//comment out next 2 lines if you did not implement division and/or modulus
#define DODIV
#define DOMOD
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

void checkcopy(Polynomial copyp1,Polynomial copyp2, Polynomial copyp3,
  const Polynomial& p1,const Polynomial& p2,const Polynomial& p3);
int readPolyData(ifstream& fs,int data[][3]);

int main(int argc,char* argv[]){
  ifstream input("a1testing.txt");
  ifstream checkfile("results.txt");
  int data1[40][3];
  int data2[40][3];
  int data3[40][3];
  int numdata;
  int numterms1,numterms2,numterms3;
  Polynomial* p1;
  Polynomial* p2;
  Polynomial p3;
  Polynomial p4;
  Polynomial* check1;
  Polynomial* check2;
  Polynomial* check3;
  if(!input || !checkfile){
    cout << "Could not open data files, please get a1testing.txt and results.txt"<< endl;
    exit(0);
  }

  cout << "Testing default Polynomial constructor and printing" << endl;
  cout << "of empty polynomials" << endl;
  cout << "P4 = " << p4 << endl;
  cout << endl;
  input >> numdata;
  if(!(p3 == p4)){
    cout << "ERROR: Default constructor is not correctly created" << endl;
  }
  cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;

  for(int j=0;j<numdata;j++){
    numterms1=readPolyData(input,data1);
    numterms2=readPolyData(input,data2);
    cout << endl;
    numterms3=readPolyData(checkfile,data3);

    cout << "Check constructor" << endl;
    p1=new Polynomial(data1,numterms1);
    p2=new Polynomial (data2,numterms2);
    check1= new Polynomial(data3,numterms3);
    cout << "P1 = " << *p1 << endl;
    if(!(*check1==*p1)){
      cout << "ERROR: Constructor is incorrect" << endl;
      cout << "    Correct poly is: " << *check1 << endl;
      cout << "    Your poly is: " << *p1 << endl;
    }
    numterms3=readPolyData(checkfile,data3);
    check2= new Polynomial(data3,numterms3);    
    cout << "P2 = " << *p2 << endl;
    if(!(*check2==*p2)){
      cout << "ERROR: Constructor is incorrect" << endl;
      cout << "    Correct poly is: " << *check2 << endl;
      cout << "    Your poly is: " << *p2 << endl;
    }

    p3=*p1;

    cout << endl;
    cout << "Checking = op on the polynomial" << endl;
    cout << "P3 = " << p3 << endl;
    if(!(p3 == *p1)){
      cout << "ERROR: assignment (=) operator is incorrect" << endl;
      cout << "    Correct poly is: " << *p1 << endl;
      cout << "    Your poly is: " << p3 << endl;
    }

    checkcopy(*p1,*p2,p3,*p1,*p2,p3);

    cout << "After calling check copy... p1, p2 and p3 should be" << endl;
    cout << "same as before checking copy constructor" << endl;
    cout << "P1 = " << *p1 << endl;
    if(!(*check1 == *p1)){
      cout << "ERROR: P1 is incorrect after copy constructor check"<< endl;
      cout << "    Correct P1 = " << *check1 << endl;
      cout << "    Your P1 = " << *p1 << endl;
    }
    cout << "P2 = " << *p2 << endl;
    if(!(*check2 == *p2)){
      cout << "ERROR: P2 is incorrect after copy constructor check"<< endl;
      cout << "    Correct P2 = " << *check2 << endl;
      cout << "    Your P2 = " << *p2 << endl;
    }
    cout << "P3 = " << p3 << endl;
    if(!(*check1 == p3)){
      cout << "ERROR: P3 is incorrect after copy constructor check"<< endl;
      cout << "    Correct P3 = " << *check1 << endl;
      cout << "    Your P3 = " << p3 << endl;
    }
    Fraction solvecheck;
    Fraction solveresult;
    int a,b;
    cout << "Checking solve() function" << endl;
    checkfile >> a >> b;
    solvecheck=Fraction(a,b);
    solveresult=p1->solve(Fraction(1,2));
    if(solvecheck!=solveresult){
      cout << "ERROR: solve is incorrect" << endl;
      cout << "    Correct result for P1(1/2): " << solvecheck << endl;
      cout << "    Your result for P1(1/2) = " << solveresult << endl;    
    }
    checkfile >> a >> b;
    solvecheck=Fraction(a,b);
    solveresult=p2->solve(Fraction(3,1));
    if(solvecheck!=solveresult){
      cout << "ERROR: solve is incorrect" << endl;
      cout << "    Correct result for P2(3/1): " << solvecheck << endl;
      cout << "    Your result for P2(3/1) = " << solveresult << endl;    
    }
    checkfile >> a >> b;
    solvecheck=Fraction(a,b);
    solveresult=p3.solve(Fraction(3,7));
    if(solvecheck!=solveresult){
      cout << "ERROR: solve is incorrect" << endl;
      cout << "    Correct result for P3(3/7): " << solvecheck << endl;
      cout << "    Your result for P3(3/7) = " << solveresult << endl;    
    }

    cout << endl;
    cout << "Checking + operator" << endl;
    numterms3=readPolyData(checkfile,data3);
    check3= new Polynomial(data3,numterms3); 
    p3=(*p1)+(*p2);
    cout << "P1 + P2 = " << p3 << endl;
    if(!(*check3 == p3)){
      cout << "ERROR: + operator error"<< endl;
	  cout << "I am p1" << *p1 << endl;
	  cout << "I am p2" << *p2 << endl;
      cout << "    Correct result = " << *check3 << endl;
      cout << "    Your result = " << p3 << endl;
    }
    cout << endl;
    cout << "Checking - operator" << endl;
    numterms3=readPolyData(checkfile,data3);
    delete check3;
    check3= new Polynomial(data3,numterms3); 
    p3=(*p1)-(*p2);
    cout << "P1 - P2 = " << p3 << endl;
    if(!(*check3 == p3)){
      cout << "ERROR: - operator error"<< endl;
      cout << "    Correct result = " << *check3 << endl;
      cout << "    Your result = " << p3 << endl;
    }
    cout << endl;
    cout << "Checking * operator" << endl;
    numterms3=readPolyData(checkfile,data3);
    delete check3;
    check3= new Polynomial(data3,numterms3); 
    p3=(*p1)*(*p2);
    cout << "P1 * P2 = " << p3 << endl;
    if(!(*check3 == p3)){
      cout << "ERROR: * operator error"<< endl;
      cout << "    Correct result = " << *check3 << endl;
      cout << "    Your result = " << p3 << endl;
    } 
    numterms3=readPolyData(checkfile,data3);
    #ifdef DODIV
    delete check3;
    check3= new Polynomial(data3,numterms3); 
    p3=(*p1)/(*p2);
    cout << endl;
    cout << "Checking / operator" << endl;

    cout << "P1 / P2 = " << p3 << endl;
    if(!(*check3 == p3)){
      cout << "ERROR: / operator error"<< endl;
      cout << "    Correct result = " << *check3 << endl;
      cout << "    Your result = " << p3 << endl;
    }
    #endif
    numterms3=readPolyData(checkfile,data3);
    #ifdef DOMOD
    delete check3;
    check3= new Polynomial(data3,numterms3); 
    p3=(*p1)%(*p2);
    cout << endl;
    cout << "Checking % operator" << endl;
    cout << "P1 % P2 = " << p3 << endl;
    if(!(*check3 == p3)){
      cout << "ERROR: % operator error"<< endl;
      cout << "    Correct result = " << *check3 << endl;
      cout << "    Your result = " << p3 << endl;
    }
    #endif
	
    cout << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	
    delete p1;
    delete p2;
    delete check1;
    delete check2;
    delete check3;
  }//for

}//main


void checkcopy(Polynomial copyp1,Polynomial copyp2, Polynomial copyp3,
  const Polynomial& p1,const Polynomial& p2,const Polynomial& p3){
  cout << endl;
  cout << "Checking out copy constructor" << endl;
  if(!(copyp1==p1)){
      cout << "ERROR: Copy constructor is incorrect" << endl;
      cout << "    Correct copy of p1 is: " << p1 << endl;
      cout << "    Your copy of P1 = " << copyp1 << endl;
  }

  if(!(copyp2==p2)){
      cout << "ERROR: Copy constructor is incorrect" << endl;
      cout << "    Correct copy of p2 is: " << p2 << endl;
      cout << "    Your copy of P2 = " << copyp2 << endl;
  }
  if(!(copyp3==p3)){
      cout << "ERROR: Copy constructor is incorrect" << endl;
      cout << "    Correct copy of p3 is: " << p3 << endl;
      cout << "    Your copy of P3 = " << copyp3 << endl;
  }

  cout << "Modify a copy, should have no effect on original";
  copyp3=copyp2;
  cout << endl;
}
int readPolyData(ifstream& fs,int data[][3]){
    int rc;
    fs >> rc;
    for(int i=0;i<rc;i++){
      fs >> data[i][0] >> data[i][1] >> data[i][2];
    }
    return rc;
}