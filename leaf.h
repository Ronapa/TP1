#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"

using namespace std;

class leaf
{
	private:

	public:
		float min;
		float max;
		float sum;
		int index;
		int l_bound;
		int r_bound;
		int valid_measures;
		
		leaf();
		~leaf();
		leaf & operator|(leaf & , leaf &);
}

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


leaf & leaf::operator|(leaf & left , leaf & right)
{
	leaf aux;

	if (left.min < right.min)
	{
		aux.min = left.min;
	}else
	{
		aux.min = right.min;
	}

	if (left.max > right.max)
	{
		aux.max = left.max;
	}else
	{
		aux.max = right.max;
	}

	aux.sum = left.sum + right.sum;
	aux.valid_measures = left.valid_measures + right.valid_measures;

	if (left.l_bound < right.l_bound)
	{
		aux.l_bound = left.l_bound;
	}else
	{
		aux.l_bound = right.l_bound;
	}

	if (left.r_bound > right.r_bound)
	{
		aux.r_bound = left.r_bound;
	}else
	{
		aux.r_bound = right.r_bound;
	}
	return aux;
}