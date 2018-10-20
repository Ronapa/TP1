#ifndef SYSTEM_CC
#define SYSTEM_CC

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"
#include "system.h"
#include "sensor.h"
#include "utilities.h"
#include "data.h"
#include "leaf.h"

using namespace std;

System::System()
{

}

System::~System()
{
	int i=0;
	while ( i < get_amount_of_sensors_in_system() )
	{
		delete sensor_array[i];
		i++;
	}
}

void System::add_new_sensor_to_system(const string & sensor_name)
{
	sensor_array.push_back(new sensor(sensor_name));
	sensor_names.push_back(sensor_name);
}

void System::load_sensors_from_csv(istream &in)
{
   Array<string> v;
   string tmp;

   if(!in.eof())
   {
      getline(in, tmp, '\n');
      _split(tmp, ',', v);
      number_of_sensors = (int)v.size();
      for (int i = 0; i < number_of_sensors; ++i)
      {
         if (i == (int)v.size()-1)
         {
            v[i].erase(v[i].size()-1);
         }
         add_new_sensor_to_system(v[i]);
      }
      v.clear();
   }

   while (!in.eof()) 
   {
      getline(in, tmp, '\n');
      stringstream str_st (tmp);
      str_st>>*this;
      tmp.clear();
   }  

   create_avg_sensor();
}

int System::get_amount_of_sensors_in_system()
{
	return sensor_array.size();
}

sensor * System::get_sensor_in_system_at_index(const int &index)
{
	return sensor_array[index];
}

float System::get_temperature_at_of_sensor_at_index(const int & index , const int &temp_index)
{
	return (sensor_array[index]->get_temperature_at(temp_index)).get_data();
}

int System::get_amount_of_valid_temperatures_in_range_at_index(const int & index, const int & left, const int &right)
{
   if (index >= (int) sensor_array.size())
   {
      return -1;
   }
   return (sensor_array[index]->get_amount_of_valid_temperatures_in_range(left,right));
}

std::istream & operator>>(std::istream &in, System & system)
{
   data measure;
   //char ch = 0;
   int i=0;
   char aux;
   float aux_value;

   for (i=0 ; i<(system.number_of_sensors) ; i++)
   {
      if ( (in >> aux) && (aux != ','))
      {
         in.putback(aux);
         if(!(in>>aux_value))
         {
            measure.set_data(99999);
            measure.set_valid(false);
         }else
         {
            measure.set_data(aux_value);
            measure.set_valid(true);
         }
         system.sensor_array[i]->add_temperature_to_sensor(measure);
         if ((i<(system.number_of_sensors -1)) && ((in >> aux) && (aux == ',')))
         {
            continue;
         }
      }else if (aux == ',')
      {
         measure.set_data(99999);
         measure.set_valid(false);
         system.sensor_array[i]->add_temperature_to_sensor(measure);
      }else
      {
         system.~System();
         cout <<"BAD DATA FILE - FEW DATA" << endl;
         exit(1);
      }

   }
   if ((in>>aux) && ((aux != '\n') && (aux != '\r')))
   {
      system.~System();
      cout << "BAD DATA FILE - MUCH DATA" << endl;
      exit(1);  
   }
   return in;
}

void System::create_segment_tree_for_all_sensors()
{
   int i=0;
   for (i=0 ; i<sensor_array.size() ; i++)
   {
      sensor_array[i]->build_segment_tree();
   }
}

void System::create_avg_sensor()
{
   sensor *aux_sensor = new sensor("");
   float accum = 0;
   data aux_data;
   size_t valid_measures = 0;
   int amount_of_sensors = get_amount_of_sensors_in_system();
   int amount_of_values_in_sensor = sensor_array[0]->get_amount_of_temperature_measures();

   add_new_sensor_to_system(aux_sensor->get_sensor_name());

   for (int j = 0; j < amount_of_values_in_sensor; ++j)
   {  
      for (int i=0; i < amount_of_sensors; i++)
      {
         aux_data = sensor_array[i]->get_temperature_at(j);
         if(aux_data.is_valid() == true)
         {
            accum += aux_data.get_data();
            valid_measures++;
         }
      }
      if(valid_measures == 0)
      {
         aux_data.set_valid(false);
      }
      else
      {
         aux_data.set_data(accum/valid_measures);
         aux_data.set_valid(true);
      }
      sensor_array[amount_of_sensors]->add_temperature_to_sensor(aux_data);

      accum = 0;
      valid_measures = 0;
   }
}

#endif