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

//Constructor de sistema
System::System()
{
   valid_data = true;
}

//Destructor de sistema
System::~System()
{
	int i=0;
	while ( i < get_amount_of_sensors_in_system() )
	{
		delete sensor_array[i];
		i++;
	}
}

//Agrega un sensor al sistema. Crea el sensor y lo añade al vector de sensores y
//al vector de nombres de sensores
void System::add_new_sensor_to_system(const string & sensor_name)
{
	sensor_array.push_back(new sensor(sensor_name));
	sensor_names.push_back(sensor_name);
}

//Carga los sensores del archivo csv
void System::load_sensors_from_csv(istream &in)
{
   Array<string> *v;
   v = new(Array<string>);
   string tmp;

   if(!in.eof())
   {
      getline(in, tmp, '\n');
      _split(tmp, ',', *v);
      number_of_sensors = (int)(*v).size();
      for (int i = 0; i < number_of_sensors; ++i)
      {
         if (i == (int)(*v).size()-1)
         {
            (*v)[i].erase((*v)[i].size()-1); //Borra el \r para que el nombre del
         }                                   //sensor sea correcto
         add_new_sensor_to_system((*v)[i]);  //Añade el sensor al sistema
      }
      delete v;
   }

   while (!in.eof() && valid_data == true) //Añade cada linea de valores al sistema
   {
      getline(in, tmp, '\n');
      stringstream str_st (tmp);
      str_st>>*this;
      tmp.clear();
   }  

}

//Devuelve la cantidad de sensores en el sistema
int System::get_amount_of_sensors_in_system()
{
	return sensor_array.size();
}

//Devuelve el sensor ubicado en la posicion pedida
sensor * System::get_sensor_in_system_at_index(const int &index)
{
	return sensor_array[index];
}

float System::get_temperature_at_of_sensor_at_index(const int & index , const int &temp_index)
{
	return (sensor_array[index]->get_temperature_at(temp_index)).get_data();
}

//Devuelve la cantidad de valores validos en el rango pedido en el sensor con posicion=index
int System::get_amount_of_valid_temperatures_in_range_at_index(const int & index, const int & left, const int &right)
{
   if (index >= (int) sensor_array.size()) //Posicion invalida
   {
      return -1;
   }
   return (sensor_array[index]->get_amount_of_valid_temperatures_in_range(left,right));
}

//Agrega una linea de valores al sistema
std::istream & operator>>(std::istream &in, System & system)
{
   data measure;
   int i=0;
   char aux;
   float aux_value;

   for (i=0 ; i<(system.number_of_sensors) ; i++)
   {
      if ( (in >> aux) && (aux != ','))
      {
         in.putback(aux);
         if(!(in>>aux_value)) //Dato invalido
         {
            measure.set_data(99999);
            measure.set_valid(false);
         }else
         {
            measure.set_data(aux_value); //Seta el valor pedido en el dato
            measure.set_valid(true);
         }
         system.sensor_array[i]->add_temperature_to_sensor(measure); //Agrega el dato en el sensor
         if ((i<(system.number_of_sensors -1)) && ((in >> aux) && (aux == ',')))
         {
            continue;
         }
      }else if (aux == ',') //Dos comas seguidas, dato invalido
      {
         measure.set_data(99999);
         measure.set_valid(false);
         system.sensor_array[i]->add_temperature_to_sensor(measure);
      }else
      {
         system.set_valid_data(false);
      }

   }
   //Error al cargar los datos
   if ((in>>aux) && ((aux != '\n') && (aux != '\r')))
   {
      system.set_valid_data(false);
   }
   return in;
}

//Crea al arbol de segmento para todos los sensores
void System::create_segment_tree_for_all_sensors()
{
   int i=0;
   create_avg_sensor();
   for (i=0 ; i<sensor_array.size() ; i++)
   {
      sensor_array[i]->build_segment_tree();
   }
}

//Crea el sensor promedio y lo agrega al array de sensores
void System::create_avg_sensor()
{
   float accum = 0;
   data aux_data;
   size_t valid_measures = 0;
   int amount_of_sensors = get_amount_of_sensors_in_system();
   int amount_of_values_in_sensor = sensor_array[0]->get_amount_of_temperature_measures();

   add_new_sensor_to_system("");
   //Para cada tiempo recorre todos los sensores, verifica que sean validos y los va sumando
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
      if(valid_measures == 0) //Todos los datos eran invalidos
      {
         aux_data.set_valid(false);
      }
      else //Promedio de los datos validos
      {
         aux_data.set_data(accum/valid_measures);
         aux_data.set_valid(true);
      }
      //Agrega el sensor al array de sensores
      sensor_array[amount_of_sensors]->add_temperature_to_sensor(aux_data);

      accum = 0;
      valid_measures = 0;
   }
}

//Indica si la lectura de datos fue exitosa
bool System::is_data_valid()
{
   return valid_data;
}

//Setea si la lectura de datos fue exitosa
void System::set_valid_data(bool valid)
{
   valid_data = valid;
}

#endif