#ifndef SENSOR_CC
#define SENSOR_CC

#include <iostream>
#include <string>
#include <cmath>
#include "Array.h"
#include "sensor.h"
#include "utilities.h"
#include "data.h"
#include "leaf.h"
#include "segment_tree.h"

sensor::sensor()
{
	seg_tree = NULL;
}

sensor::sensor(const string &name)
{
	sensor_name = name;
	seg_tree = NULL;
}

sensor::~sensor()
{
	if (seg_tree != NULL)
	{
		delete seg_tree;
	} 

}

string sensor::get_sensor_name()
{
	return sensor_name;
}

void sensor::set_sensor_name(const string &name)
{
	sensor_name = name;
}

void sensor::add_temperature_to_sensor(const data& value)
{
	temperature_values.push_back(value);
}

size_t sensor::get_amount_of_temperature_measures()
{
	return temperature_values.size();
}

data sensor::get_temperature_at(const int &index)
{
	data aux;
	if (index < 0 || (size_t)index >= temperature_values.size())
	{
		aux.set_data(0);
		aux.set_valid(false);
		return aux;
	}
	return temperature_values[index];
	
}

int sensor::get_amount_of_valid_temperatures_in_range(const int &left , const int &right)
{
	int aux = 0 , i=left;
	if (left < 0 || right <0)
	{
		return -1;
	}
	while (i < right && (size_t)i<temperature_values.size())
	{
		if(temperature_values[i].is_valid() != false)
		{
			aux++;
		}
		i++;
	}
	return aux;
}

void sensor::build_segment_tree()
{
	int number_of_values = temperature_values.size();
	int pow_2 = ceil(log2(number_of_values));
	int expanded_value = pow(2,pow_2);
	int i=number_of_values; 
	data aux;
	aux.set_valid(false);
	while (i<expanded_value)
	{
		temperature_values.push_back(aux);
		i++;
	}
	seg_tree = new Segment_Tree(temperature_values);
}

leaf sensor::get_query_from_sensor(int q_left , int q_right)
{
	return (seg_tree)->get_value_from_segment_tree(0, q_left  , q_right , temperature_values);
}


#endif
