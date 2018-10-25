
#include <iostream>
#include "data.h"

using namespace std;

//Crea dato
data::data()
{
	value = -8;
	valid = false;
}

//Destruye dato
data::~data()
{
	
}

//Getter de la validez del dato
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

//Getter del valor almacenado en el dato
float data::get_data()
{
	return value;
}

//Setea el valor del dato
void data::set_data(const float & new_value)
{
	value = new_value;
}

//Setea la validez del dato		
void data::set_valid(const bool & new_valid)
{
	valid = new_valid;
}