#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class data
{
	public:
		data();
		~data();
		

		bool is_valid();
		float get_data();
		void set_data(const float &);
		void set_valid(const bool &);
	private:
		float value;
		bool valid;
};

#endif