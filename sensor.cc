#ifndef SENSOR_CC
#define SENSOR_CC

#include <iostream>
#include <string>
#include "Array.h"
#include "sensor.h"
#include "utilities.h"
#include "data.h"
#include "leaf.h"

sensor::sensor()
{

}

sensor::sensor(const string &name)
{
	sensor_name = name;
}

sensor::~sensor()
{

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

data sensor::get_average_temperature_in_range(const int & left, const int & right)
{
	data aux;
	if(left < 0 || right < 0)
	{
		return INVALID_TEMPERATURE;
	}
	float accum=0;
	int i=left;
	int amount_of_values = 0;
	while (i < right && (size_t)i < temperature_values.size())
	{
		if (temperature_values[i].valid != false)
		{
			accum += temperature_values[i].value;
			amount_of_values++;
		}
		i++;
	}
	if (accum == 0)
	{
		aux.value = 0;
		aux.valid = false;
		return aux;
	}
	aux.value = accum/amount_of_values;
	aux.valid = true
	return aux;
}

data sensor::get_min_temperature_in_range(const int &left , const int &right)
{
	data aux;
	if(left < 0 || right < 0 || (size_t)left > temperature_values.size())
	{
		aux.value = 0;
		aux.valid = false;
		return aux;
	}
	int amount_of_values = 0;
	if (temperature_values[left].valid != false)		//OJO CON ESTA FUNCION
	{
		amount_of_values++;
	}
	int i=left+1;
	while (i < right && (size_t)i < temperature_values.size())
	{
		if (temperature_values[i].value < aux && temperature_values[i].valid != false)
		{
			aux = temperature_values[i];
			amount_of_values++;
		}
		i++;
	}
	if (amount_of_values == 0)
	{
		return INVALID_TEMPERATURE;
	}else
	{
		return aux;		
	}

}

data sensor::get_max_temperature_in_range(const int &left , const int &right)
{
	data aux;
	if(left < 0 || right < 0 || (size_t)left > temperature_values.size())
	{
		aux.value = 0;
		aux.valid = false;
		return aux;
	}
	data aux;
	int amount_of_values = 0;
	if ((aux = temperature_values[left]) != false)
	{
		amount_of_values++;
	}
	int i=left+1;
	while (i < right && (size_t)i < temperature_values.size())
	{
		if (temperature_values[i].value > aux && temperature_values[i].valid != false)
		{
			aux = temperature_values[i];
			amount_of_values++;
		}
		i++;
	}
	if (amount_of_values == 0)
	{
		return INVALID_TEMPERATURE;
	}else
	{
		return aux;		
	}
}

data sensor::get_temperature_at(const int &index)
{
	if (index < 0 || (size_t)index >= temperature_values.size())
	{
		return INVALID_TEMPERATURE;
	}
	return temperature_values[index];
	
}

string sensor::get_sensor_name()
{
	return sensor_name;
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
		if(temperature_values[i].valid != false)
		{
			aux++;
		}
		i++;
	}
	return aux;
}


#endif
