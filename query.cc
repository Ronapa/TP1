#ifndef QUERY_CC
#define QUERY_CC


#include <iostream>
#include <string>
#include "Array.h"
#include "query.h"
#include "system.h"
#include "sensor.h"
#include "utilities.h"
#include "data.h"
#include "leaf.h"

using namespace std;

Query::Query(const string & query_name)
{
	int i=0;
	valid_query = false;
	type_of_query = MONO_SENSOR;
	left_bound = -1;
	right_bound = -1;
	int amount_of_sensors_in_system = target_system->get_amount_of_sensors_in_system();
	for (i=0 ; i<amount_of_sensors_in_system ; i++)
	{
		if ((target_system->get_sensor_in_system_at_index(i))->get_sensor_name() == query_name)
		{
			sensors_in_query.push_back(target_system->get_sensor_in_system_at_index(i));
			valid_query = true;
			break;
		}
	}	
}

Query::Query()
{
	type_of_query = MONO_SENSOR;
	left_bound = -1;
	right_bound = -1;
}

Query::~Query()
{

}

void Query::load_querys_from_csv(istream& in, Array<Query *>& querys , System * target_system) 
{
   string tmp;
   Array<string> v;
   Query * query;

   while(getline(in, tmp, '\n'))
   {
      query = new Query();
      stringstream str_st (tmp);
      query->set_target_system(target_system);
      str_st >> (*query);
      querys.push_back(query);
      tmp.clear();
   }
}

void Query::set_target_system(System * target)
{
	if (target == NULL)
	{
		cerr << "NULL POINTER";
		return;
	}
	target_system = target;
}

void Query::set_left_bound(const int & left)
{
	if (left < 0)
	{
		return;
	}
	left_bound = left;
}

void Query::set_right_bound(const int & right)
{
	if (right < left_bound)
	{
		return;
	}
	right_bound = right;
}

void Query::set_left_bound(const string & left)
{
   char aux;

   stringstream str_st(left);
   if(!(str_st>>left_bound) || (left_bound < 0))
      left_bound = -1;
   //str_st >> aux;
   //if(aux != '\n' && aux != '\r' && aux != '\0')
   //  left_bound = -1;
}

void Query::set_right_bound(const string & right)
{
   char aux;

   stringstream str_st(right);
   if(!(str_st>>right_bound) || (right_bound < 0))
      right_bound = -1;
   //str_st >> aux;
   //if(aux != '\n' && aux != '\r' && aux != '\0')
   //	  right_bound = -1;
}

void Query::add_sensor_to_query(const string &query_name)
{
	int i=0;
	valid_query = false;
	type_of_query = MONO_SENSOR;
	left_bound = -1;
	right_bound = -1;
	int amount_of_sensors_in_system = target_system->get_amount_of_sensors_in_system();
	for (i=0 ; i<amount_of_sensors_in_system ; i++)
	{
		if ((target_system->get_sensor_in_system_at_index(i))->get_sensor_name() == query_name)
		{
			sensors_in_query.push_back(target_system->get_sensor_in_system_at_index(i));
			valid_query = true;
			break;
		}
	}
}

int Query::get_amount_of_sensors_in_query()
{
	return (int)sensors_in_query.size();
}

sensor * Query::get_sensor_in_query_at_index(const int &index)
{
	return sensors_in_query[index];
}

void Query::execute_query(ostream & os)
{
	_validate_query();

	if (valid_query == true)
	{
		if (type_of_query == MONO_SENSOR)
		{
			leaf aux = sensors_in_query[0]->get_query_from_sensor(left_bound,right_bound);
			if (aux.valid_measures > 0)
			{
				os << aux.min << " " << aux.max << " " << aux.sum/aux.valid_measures << " " << aux.valid_measures << endl;				
			}else
			{
				os << MSG_NO_DATA << endl;
			}

		}
	}else
	{
		if ((left_bound < 0 || right_bound < 0) || (left_bound>= right_bound))
		{
			os << MSG_BAD_QUERY << endl;
		}else
		{
			os << MSG_UNKNOWN_ID << endl;
		}
	}	
}

void Query::_validate_query()
{
	if ((left_bound < 0 || right_bound < 0) || (left_bound>= right_bound))
	{
		valid_query = false;
	}
}

istream & operator>>(std::istream &in, Query & query)
{
   	Array<string> v, sensors_to_add;
   	string tmp;

   	getline(in, tmp, '\n');
   	_split(tmp, ',', v);
   	if(v.size() != 3)
   	{
      	query.left_bound = query.right_bound = -1;
      	query.valid_query = false;
   	}
   	query.add_sensor_to_query(v[0]);
   	query.set_left_bound(v[1]);
   	query.set_right_bound(v[2]);

   	return in;
}

#endif
