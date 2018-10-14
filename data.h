#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class data
{
	public:
		float value;
		bool valid=false;

		bool is_valid();
		float get_data();
};

#endif