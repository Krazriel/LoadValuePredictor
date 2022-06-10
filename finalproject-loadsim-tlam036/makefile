CC = g++

loadsim: loadsim.o loadValueSim.o
	$(CC) -o loadsim loadsim.o loadValueSim.o

loadsim.o: loadsim.cpp
	$(CC) -c loadsim.cpp

loadValueSim.o: loadValueSim.cpp
	$(CC) -c loadValueSim.cpp

clean:
	rm *.o