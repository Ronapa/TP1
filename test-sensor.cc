#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "cmdline.h"
#include "system.h"
#include "query.h"
#include "sensor.h"
#include "leaf.h"
#include "data.h"
#include "segment_tree.h"

using namespace std;

int
main()
{
	int i, j;
	char c;
	float f;
	sensor sensor1;
	string tmp;
	data data1;
	leaf leaf1;
	size_t amount;

	while (cin >> i) {
		switch (i) {
		case 1:
			//Setear nombre
			cout << "set name: ";
			getline(cin,tmp);
			sensor1.set_sensor_name(tmp);
			cout << endl;
			break;
		case 2:
			//Agregar dato
			cout << "add data: ";
			sensor1.add_temperature_to_sensor(data1);
			cout << endl;
			break;
		case 3:
			//Construir segment tree
			cout << "build segment tree: ";
			sensor1.build_segment_tree();
			cout << endl;
			break;
		case 4:
			//Obtener query del sensor
			if(cin >> i){
				if(cin >> j){
					cout << "get query from sensor: ";
					leaf1 = sensor1.get_query_from_sensor(i,j);
					cout << endl;
				}
			}
			break;
		case 5:
			//Obtener nombre del sensor
			cout << "get name: ";
			cout << sensor1.get_sensor_name() << endl;
			break;
		case 6:
			//Obtener cantidad de mediciones
			cout << "amount of measures: ";
			cout << sensor1.get_amount_of_temperature_measures() << endl;
			break;
		case 7:
			//Obtener dato en posicion
			if(cin >> i){
				cout << "get temperature at: ";
				data = sensor1.get_temperature_at(i);
				cout << endl;
			}
			break;
		case 8:
			//Obtener cantidad de mediciones validas
			cout << "amount of valid measures: ";
			cout << sensor1.get_amount_of_valid_temperatures_in_range() << endl;
			break;
		
		default:
			cout << "error: unknown command (";
			cout << i;
			cout << ")";
			cout << endl;
			break;
		}
	}

	return 0;
}