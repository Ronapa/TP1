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
      for (int i = 0; i < (int)v.size(); ++i)
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
	return (sensor_array[index]->get_temperature_at(temp_index)).value;
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
   char ch = 0;
   int i=0;
   
   if(!(in>>measure.value))
   {
      measure.value = 99999;
      measure.valid = false;
   }else
   {
      measure.valid = true;
   }
   system.sensor_array[i]->add_temperature_to_sensor(measure);
   while( (in >> ch) && ((ch == ',') || (ch == '\n')))
   {  
      cout << ch << endl;
      i++; 
      if(!(in>>measure.value))
      {
         measure.value = 99999;
         measure.valid = false;
      }else
      {
         measure.valid = true;
      }
      system.sensor_array[i]->add_temperature_to_sensor(measure);
   }
   cout << ch << endl; 
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

#endif