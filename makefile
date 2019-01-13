elis: main.o 
	g++ -Wall -std=c++11 main.o -lncurses -o elis
	-rm *.o
main.o:
	g++ -Wall -std=c++11 -c src/main.cpp -o main.o