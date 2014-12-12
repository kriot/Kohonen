all: project

project: main.o kohonen.o
	g++ main.o kohonen.o -o main

main.o: main.cpp
	g++ -c main.cpp

kohonen.o: kohonen.cpp
	g++ -c kohonen.cpp

clean:
	rm *.o main visual

visual: visualize.o
	g++ visualize.o -o visual

visualize.o: visualize.cpp
	g++ -c visualize.cpp
