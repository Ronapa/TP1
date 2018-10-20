
#include <iostream>
#include "data.h"

using namespace std;

data::data()
{
	value = -8;
	valid = false;
}

data::~data()
{
	
}

bool data::is_valid()
{
	if (valid == true)
	{
		//cout << "true" << endl;
	}else
	{
		//cout << "false" << endl;
	}
	return valid;
}

float data::get_data()
{
	return value;
}

void data::set_data(const float & new_value)
{
	value = new_value;
}
		
void data::set_valid(const bool & new_valid)
{
	valid = new_valid;
}