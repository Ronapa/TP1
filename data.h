#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class data
{
	public:
		data();
		~data();
		float value;
		bool valid;

		bool is_valid();
		float get_data();
};

#endif