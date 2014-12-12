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

points_round: points_round.cpp
	g++ -o points_round points_round.cpp

up_dim: up_dim.cpp
	g++ -o up_dim up_dim.cpp
	
unite: unite.cpp
	g++ -o unite unite.cpp
