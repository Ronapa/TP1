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
	char c
	Array <data> data_array;
	data data1;

	Segment_Tree segment_tree(data_array);

	while (cin >> c) {
		switch (c) {
		case 'G':
			if(cin >> i){
				if(cin >> j){
					cout << "get value from tree: ";
					data1 = segment_tree.get_value_from_segment_tree(0,i,j,data_array);
					cout << endl;
				}
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