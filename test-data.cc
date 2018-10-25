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
	data data1;

	while (cin >> i) {
		switch (i) {
		case 1:
			// Valido?
			cout << "valid: ";
			if(data1.is_valid()==true)
				cout << "true" << endl;
			else
				cout << "false" << endl;
			break;
		case 2:
			//Ver dato
		cout << "data:";
			cout << data1.get_data() << endl;
			break;
		case 3:
			//Setear dato 
			cout << "Set data: ";
			if(cin >> f){
				data1.set_data(f);
			}
			cout << endl;
			break;
		case 4:
			// Setear validez
			if (cin >> c) {
				cout << "Set valid: ";
				if(c == 'v')
					data1.set_valid(true);
				else if(c == 'f')
					data1.set_valid(false);
			    cout << endl;
			}
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