#include "polynomial.h"
#include "fraction.h"
#include <iostream>
using namespace std;

PolyNode::PolyNode(const Fraction& coefficient, int degree, PolyNode* next)
{
	coefficient_=coefficient;
	degree_=degree;
	next_=next;
}

Polynomial::Polynomial()
{
	first_ = NULL;
}

Polynomial::Polynomial(int data[][3],int numTerms)
{
	first_ = NULL;

	for(int i = 0; i < numTerms; i++)
		addTerm( Fraction(data[i][0], data[i][1]), data[i][2] );
}


Polynomial::Polynomial(const Polynomial& poly)  
{
	first_ = NULL;
	if (poly.first_)
	{
		PolyNode* copy = poly.first_;
		while (copy)
		{
			addTerm( copy->coefficient_, copy->degree_);
			copy = copy->next_;
		}
	}
}


const Polynomial& Polynomial::operator=(const Polynomial& poly) 
{
	PolyNode* del = first_;
	PolyNode* tracker = first_;

	if(tracker!=NULL)
	{
		first_ = NULL;
		while (tracker != NULL)
		{
			tracker = tracker->next_;
			delete del;
			del = tracker;
		}
	}

	PolyNode* copy = poly.first_;
	while(copy)
	{
		addTerm( copy->coefficient_, copy->degree_);
		copy = copy->next_;
	}
	return *this;
}

Polynomial::~Polynomial() 
{
	PolyNode* del = first_;
	PolyNode* curr = first_;

	while(curr != NULL)
	{
		curr = curr->next_;
		delete del;
		del = curr;
	}
}

void Polynomial::addTerm(const Fraction& coefficient, int degree)
{
	PolyNode* curr = first_;
	
	if(!curr)
	{
		first_ = new PolyNode(coefficient, degree);
	}
	else
	{
		PolyNode* temp = new PolyNode(coefficient, degree);
		PolyNode* prv = NULL;

		if ( degree > curr->degree_)
		{
			if (degree == curr->degree_)
			{
				curr->coefficient_ += temp->coefficient_;
			}
			else
			{
				temp->next_ = curr;
				first_ = temp;
			}
		}

		else
		{
			while ( degree < curr->degree_ && curr->next_ )
			{
				prv = curr;
				curr = curr->next_;
			}

			if (degree == curr->degree_)
			{
				curr->coefficient_ += temp->coefficient_;
			}

			else if (degree < curr->degree_ && !curr->next_)
			{
				curr->next_ = temp;
			}

			else
			{
				temp->next_ = curr;
				prv->next_ = temp;
			}
		}
	}
}

Fraction Polynomial::solve(const Fraction& x)
{
	PolyNode* curr = this->first_;
	Fraction result;
	Fraction temp;

	for (; curr; curr = curr->next_ )
	{
		if (curr->degree_)
		{
			temp = x;
			for (int i = 1; i < curr->degree_; i++)
			{
				temp *= x;
			}
			result += curr->coefficient_ * temp;
		}
		else
		{
			result += curr->coefficient_;
		}
	}
	return result;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
	PolyNode* currP1 = p1.first_;
	PolyNode* currP2 = p2.first_;
	Polynomial temp;
	Fraction tempFrac(0,1);

	while ( currP1 && currP2 )  // go over loop till both p1 and p2 nodes are exist
	{
		if( currP1->degree() == currP2->degree() ) // if degrees are the same
		{
			if ( currP1->coefficient() + currP2->coefficient() != tempFrac )
			{
				temp.addTerm(currP1->coefficient() + currP2->coefficient(), currP1->degree() );
			}
			currP1 = currP1->next();
			currP2 = currP2->next();
		}
		else if ( currP1->degree() > currP2->degree() )  // if p1 is greater than p2 degree
		{
			temp.addTerm(currP1->coefficient(), currP1->degree() );
			currP1 = currP1->next();
		}
		else if ( currP1->degree() < currP2->degree() ) // if p2 is greater than p1 degree
		{
			temp.addTerm(currP2->coefficient(), currP2->degree() );
			currP2 = currP2->next();
		}
	}
	while (currP1)
	{
		temp.addTerm(currP1->coefficient(), currP1->degree() );
		currP1 = currP1->next_;
	}
	while (currP2)
	{
		temp.addTerm(currP2->coefficient(), currP2->degree() );
		currP2 = currP2->next_;
	}
	return temp;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
	PolyNode* currP1 = p1.first_;
	PolyNode* currP2 = p2.first_;
	Polynomial temp;
	Fraction tempFrac(-1,1);

	while ( currP1 && currP2 )  // go over loop till both p1 and p2 nodes are exist
	{
		if( currP1->degree() == currP2->degree() ) // if degrees are the same
		{
			if ( currP1->coefficient() != currP2->coefficient() )
			{
				temp.addTerm(currP1->coefficient() - currP2->coefficient(), currP1->degree() );
			}
			currP1 = currP1->next();
			currP2 = currP2->next();
		}
		else if ( currP1->degree() > currP2->degree() )  // if p1 is greater than p2 degree
		{
			temp.addTerm(currP1->coefficient(), currP1->degree() );
			currP1 = currP1->next();
		}
		else if ( currP1->degree() < currP2->degree() ) // if p2 is greater than p1 degree
		{
			temp.addTerm(currP2->coefficient() * tempFrac, currP2->degree() );
			currP2 = currP2->next();
		}
	}
	while (currP1)
	{
		temp.addTerm(currP1->coefficient(), currP1->degree() );
		currP1 = currP1->next_;
	}
	while (currP2)
	{
		temp.addTerm(currP2->coefficient() * tempFrac, currP2->degree() );
		currP2 = currP2->next_;
	}
	return temp;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial temp;
	
	for (PolyNode* currP2 = p2.first_ ; currP2; currP2 = currP2->next() )
	{
		PolyNode* currP1 = p1.first_;
		while ( currP1 )  // go over loop till p2 is empty
		{
			temp.addTerm(currP1->coefficient()*currP2->coefficient(), currP1->degree()+currP2->degree() );
			currP1 = currP1->next();
		}
	}
	return temp;
}

void divide(const Polynomial& p1,const Polynomial& p2, Polynomial& quotient, Polynomial& remainder)
{
	if (remainder.first_)
	{
		if ( (p2.first_->degree() < remainder.first_->degree()) || (p2.first_->degree() == remainder.first_->degree()) )
		{	
			Polynomial result;
			result.addTerm(remainder.first_->coefficient() / p2.first_->coefficient() , remainder.first_->degree() - p2.first_->degree());
			quotient.addTerm( result.first_->coefficient(), result.first_->degree() );
			remainder = remainder - result * p2;
			divide(p1, p2, quotient, remainder );
		}
	}
}

Polynomial operator/(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial remainder = p1;
	Polynomial quotient;
	divide(p1, p2, quotient, remainder);
	return quotient;
}

Polynomial operator%(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial remainder = p1;
	Polynomial quotient;
	divide(p1, p2, quotient, remainder);
	return remainder;
}

ostream& operator<<(ostream& os, const Polynomial& dat)
{
	const PolyNode* curr = dat.first_;
	while(curr)
	{
		cout << curr->coefficient() << "x^" << curr->degree() << endl;
		curr = curr->next();
	}
	return os;
}

bool operator==(const Polynomial& p1, const Polynomial& p2){
	PolyNode* p1curr=p1.first_;
	PolyNode* p2curr=p2.first_;
	bool rc=true;
	while(rc && (p1curr && p2curr)){
		if( (p1curr->coefficient_ != p2curr->coefficient_) || (p1curr->degree_ != p2curr->degree_)){
			rc=false;
		}
		p1curr=p1curr->next_;
		p2curr=p2curr->next_;
	}
	if(rc){
		if(p1curr || p2curr){
			rc=false;
		}
	}
	return rc;
}