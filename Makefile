CCFLAGS= -Wall -g -pedantic -ansi
CC= g++ 

all: TP0 clean 							# TP

data_gen: Data_generator clean 			# COMPILAR GENERADOR DE SENSORES

query_gen: Query_generator clean 		# COMPILAR GENERADOR DE QUERYS

generate_data: generate_data 			# EJECUTAR GENERADOR DE SENSORES

generate_querys: generate_querys 		# EJECUTAR GENERADOR DE QUERYS

test_data: data 						# PROBAR CASOS DE PRUEBA BAD DATA

test_query: query 						# PROBAR CASOS DE PRUEBA BAD QUERY

bench: Bench

#-----------------------------------------------------------------------------------------
TP0: main.o sensor.o system.o query.o cmdline.o utilities.o leaf.o data.o seg_tree.o
	$(CC) $(CCFLAGS) -o TP0 main.o sensor.o query.o system.o cmdline.o utilities.o leaf.o data.o seg_tree.o

main.o: main.cc 
	$(CC) $(CCFLAGS) -c main.cc -o main.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

query.o: query.cc
	$(CC) $(CCFLAGS) -c query.cc -o query.o	

system.o: system.cc
	$(CC) $(CCFLAGS) -c system.cc -o system.o	

sensor.o: sensor.cc
	$(CC) $(CCFLAGS) -c sensor.cc -o sensor.o	

leaf.o: leaf.cc
	$(CC) $(CCFLAGS) -c leaf.cc -o leaf.o	

data.o: data.cc
	$(CC) $(CCFLAGS) -c data.cc -o data.o	

seg_tree.o: segment-tree.cpp
	$(CC) $(CCFLAGS) -c segment-tree.cpp -o seg_tree.o	

utilities.o: utilities.cc
	$(CC) $(CCFLAGS) -c utilities.cc -o utilities.o	
#----------------------------------------------------------------------------------------

Data_generator: random_data_generator.o cmdline.o utilities.o
	$(CC) $(CCFLAGS) -o data_gen random_data_generator.o cmdline.o utilities.o 

random_data_generator: random_data_generator.cpp
	$(CC) $(CCFLAGS) -c random_data_generator.cpp -o random_data_generator.o

#----------------------------------------------------------------------------------------

Query_generator: random_query_generator.o cmdline.o utilities.o
	$(CC) $(CCFLAGS) -o query_gen random_query_generator.o cmdline.o utilities.o 

random_query_generator: random_query_generator.cc
	$(CC) $(CCFLAGS) -c random_query_generator.cc -o random_query_generator.o

#----------------------------------------------------------------------------------------

Bench: 
	./TP0 -o out.csv -d data_4_8.csv -i query_4_1.csv
	./TP0 -o out.csv -d data_4_9.csv -i query_4_1.csv
	./TP0 -o out.csv -d data_4_10.csv -i query_4_1.csv
	./TP0 -o out.csv -d data_4_11.csv -i query_4_1.csv
	./TP0 -o out.csv -d data_4_12.csv -i query_4_2.csv
#----------------------------------------------------------------------------------------

generate_query:
	./query_gen -s sensor_names.csv -a 100 -o query_100_100000.csv

generate_data:
	./data_gen -s sensor_names.csv -a 100 -o data_4_100.csv



data: 
	@echo "\n Errores de Contenido\n"
	./TP0 -d BadDataC1_letra.csv -i query_4_2.csv
	./TP0 -d BadDataC2_simbolo.csv -i query_4_2.csv
	./TP0 -d BadDataC3_doblePunto.csv -i query_4_2.csv
	./TP0 -d BadDataC4_puntoSolo.csv -i query_4_2.csv
	./TP0 -d BadDataC5_letrayNumero.csv -i query_4_2.csv
	./TP0 -d BadDataC6_simboloyNumero.csv -i query_4_2.csv

	@echo "\n Errores de Formato\n"
	./TP0 -d BadDataF1_missingSensor.csv -i query_4_2.csv
	./TP0 -d BadDataF2_extraData.csv -i query_4_2.csv
	./TP0 -d BadDataF3_missingData.csv -i query_4_2.csv

query: 
	./TP0 -d Consultas_CPU_Temp2.csv -i BadQueries.csv


clean:
	$(RM) *.o 