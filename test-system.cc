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
	int i, j, k;
	char c;
	float f;
	sensor sensor1;
	string tmp;
	data data1;
	leaf leaf1;
	size_t amount;
	bool valid;

	while (cin >> i) {
		switch (i) {
		case 1:
			//Agregar sensor
			getline(cin,tmp);
			cout << "add sensor: ";
			system.add_new_sensor_to_system(tmp);
			cout << endl;
			break;
		case 2:
			//Cargar sensores de csv
			cout << "load sensors: ";
			system.load_sensors_from_csv(cin);
			cout << endl;
			break;
		case 3:
			//Obtener cantidad de sensores
			cout << "amount of sensors: ";
			cout << system.get_amount_of_sensors_in_system();
			cout << endl;
			break;
		case 4:
			//Obtener sensor en posicion
			if(cin >> i){
				cout << "sensor at index: ";
				sensor1 = system.get_sensor_in_system_at_index(i);
				cout << endl;
			}
			break;
		case 5:
			//Son validos los datos?
			cout << "is data valid: ";
			valid = system.is_data_valid();
			if(valid == true)
				cout << "true";
			else
				cout << "false";
			cout << endl;
			break;
		case 6:
			//Setear la validez de los datos
			if (cin >> c) {
				cout << "Set valid: ";
				if(c == 'v')
					system.set_valid_data(true);
				else if(c == 'f')
					system.set_valid_data(false);
			    cout << endl;
			}
			break;
		case 7:
			//Crear segment tree
			cout << "create segment tree: ";
			system.create_segment_tree_for_all_sensors();
			cout << endl;
			break;
		case 8:
			//Obtener tiempo j de sensor i
			if(cin >> i){
				if(cin >> j){
					cout << "data at time of sensor: ";
					f = system.get_temperature_at_of_sensor_at_index(i,j);
					cout << endl;
				}
			}
			break;
		case 9:
			//Obtener cantidad de datos validos en rango en sensor
			if(cin >> i){
				if(cin >> j){
					if(cin >> k){
						cout << "valid data in range in sensor";
						i = get_amount_of_valid_temperatures_in_range_at_index(k,i,j);
						cout << endl;
					}
				}
			}
			break;
		case 10:
			//Crear sensor promedio
			cout << "average sensor: ";
			system.create_avg_sensor();
			cout << endl;
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