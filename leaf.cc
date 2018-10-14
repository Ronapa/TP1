#ifndef LEAF_CC
#define LEAF_CC

#include <iostream>
#include "Array.h"
#include "utilities.h"
#include "leaf.h"

using namespace std;


leaf::leaf()
{
	l_bound = -1;
	r_bound = -1;
	valid_measures = 0;
	min = INFINITE;
	max = MINUS_INFINITE;
	sum = 0; 
}

leaf::~leaf()
{

}


leaf leaf::operator||(leaf & right)
{
	leaf aux;
	if (this->min < right.min)
	{
		aux.min = this->min;
	}else
	{
		aux.min = right.min;
	}

	if (this->max > right.max)
	{
		aux.max = this->max;
	}else
	{
		aux.max = right.max;
	}

	aux.sum = this->sum + right.sum;
	aux.valid_measures = this->valid_measures + right.valid_measures;

	if (this->l_bound < right.l_bound)
	{
		aux.l_bound = this->l_bound;
	}else
	{
		aux.l_bound = right.l_bound;
	}

	if (this->r_bound > right.r_bound)
	{
		aux.r_bound = this->r_bound;
	}else
	{
		aux.r_bound = right.r_bound;
	}
	return aux;
}

#endif