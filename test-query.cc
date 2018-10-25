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
	int i;
	char c;
	float f;
	Query query;
	string tmp1, tmp2;
	System system;
	sensor sensor1;
	Array<Query *> query_array;

	while (cin >> i) {
		switch (i) {
		case 1:
			// Setear límites
			cout << "bounds: " << endl
			getline(in, tmp);
			getline(in,tmp2);
			query.set_bounds(tmp1,tmp2);
			break;
		case 2:
			//Setear sistema
			cout << "set system:";
			query.set_target_system(&system);
			cout << endl;
			break;
		case 3:
			//Agregar sensor
			cout << "add sensor: ";
			getline(in,tmp);
			query.add_sensor_to_query(tmp);
			break;
		case 4:
			//Obtener cantidad de sensores en la consulta
			cout << "amount of sensors in query: ";
			cout <<  query.get_amount_of_sensors_in_query();
			break;
		case 5:
			//Obtener sensor en la posicion indicada
			if(cin >> i){
				cout << "get sensor: ";
				sensor1 = query.get_sensor_in_query_at_index(i);
				cout << endl;
			}
			break;
		case 6:
			//Obtener limite izquierdo
			cout << "left bound: ";
			query.get_left_bound();
			cout << endl;
			break;
		case 7:
			//Obtener limite derecho
			cout << "right bound: ";
			query.get_right_bound();
			cout << endl;
			break;
		case 8:
			//Ejecutar query
			cout << "execute query: ";
			query.execute_query();
			cout << endl;
			break;
		case 9:
			//Cargar una query
			cout << ">>: ";
			getline(cin, tmp);
			tmp>>query;
			cout << endl;
			break;
		case 10:
			//Cargar querys de un csv
			cout << "load querys: ";
			Query::load_querys_from_csv(cin,query_array,&system);
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