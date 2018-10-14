#ifndef LEAF_H
#define LEAF_H

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"

using namespace std;

class leaf
{
	public:
		leaf();
		~leaf();
		leaf operator||(leaf &);

		float min;
		float max;
		float sum;
		int index;
		int l_bound;
		int r_bound;
		int valid_measures;

};

#endif