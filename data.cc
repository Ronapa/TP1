
#include <iostream>
#include "data.h"

using namespace std;
/*
data::data()
{
	valid = false;
}

data::~data()
{
	
}*/

bool data::is_valid()
{
	return valid;
}

float data::get_data()
{
	return value;
}