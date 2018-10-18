#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Array.h"
#include "utilities.h"
#include "cmdline.h"

using namespace std;

static void opt_sensors(string const &arg);
static void opt_output(string const &arg);
static void opt_rows(string const &arg);
static void opt_help(string const &arg);
void load_sensors_from_csv(istream &in , Array<string> & sensor_array);

static option_t options[] = {
	{1, "s", "sensors", "-", opt_sensors, OPT_MANDATORY},
	{1, "a", "amount", "-", opt_rows, OPT_MANDATORY},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};


static int rows;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;			// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static void opt_sensors(string const &arg)
{
	if (arg == "-") 
	{
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else 
	{
		ifs.open(arg.c_str(), ios::in); 
		iss = &ifs;
	}

	if (!iss->good()) 
	{
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void opt_rows(string const &arg)
{
   //Tomo el argumento y lo convierto a int
   rows  = atoi(arg.c_str());
}

static void opt_help(string const &arg)
{
	cout << "cmdline [-s file] [-a entero] [-o file]"
	     << endl;
	exit(0);
}

void load_sensors_from_csv(istream &in , Array<string> & sensor_array)
{
   	string tmp;

   	if(!in.eof())
   	{
      	getline(in, tmp, '\n');
      	_split(tmp, ',', sensor_array);
   	}
}

int main (int argc , char* const argv[])
{
	Array<string> sensor_array;
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	load_sensors_from_csv(*iss,sensor_array);
	int i=0;
	int cols=sensor_array.size();
	for (i=0 ; i<(cols-1) ; i++)
	{
		*oss << sensor_array[i] << ',';
	}
	*oss << sensor_array[i];
	cout << rows << endl;
	for (i=0 ; i<rows ; i++)
	{
		int k=0;
		*oss << endl;
		for (k=0 ; k<cols-1 ; k++)
		{
			*oss << ((float)(rand()*10000-5000)) << ',';
		}
		*oss << ((float)(rand()*10000-5000));
	}


	return 0;

}

