#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include "Array.h"
#include "utilities.h"
#include "data.h"
#include "segment_tree.h"
#include "leaf.h"

using namespace std;

class sensor
{
	private:

		Array<data> temperature_values; 
		string sensor_name;
		Segment_Tree *seg_tree;
		
	public:
		
		sensor();
		sensor(const string &);
		~sensor();

		void add_temperature_to_sensor(const data &);
		void set_sensor_name(const string &);

		void build_segment_tree();
		leaf get_query_from_sensor(int ,int);

		string get_sensor_name();
		size_t get_amount_of_temperature_measures();
		
		data get_temperature_at(const int &);
		int get_amount_of_valid_temperatures_in_range(const int & , const int &);
	
};

#endif
