#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"
#include "sensor.h"
#include "utilities.h"
#include "leaf.h"

using namespace std;

class System
{
	private:

		Array<sensor *> sensor_array;
		Array<string> sensor_names;
		int number_of_sensors;
		bool valid_data;

	public:

		System();
		~System();

		void add_new_sensor_to_system(const string &);

		void load_sensors_from_csv(istream &);
		
		int get_amount_of_sensors_in_system();
		sensor* get_sensor_in_system_at_index(const int &);

		bool is_data_valid();
		void set_valid_data(bool);

		void create_segment_tree_for_all_sensors();
		
		float get_temperature_at_of_sensor_at_index(const int & , const int &);
		int get_amount_of_valid_temperatures_in_range_at_index(const int & , const int & , const int &);
		void create_avg_sensor();

		friend std::istream & operator >>(std::istream &, System &);

};

#endif