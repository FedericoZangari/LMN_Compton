CFLAGS=-Wall -pedantic -pedantic-errors -g -ansi -Wextra -Weffc++ -std=c++14 -O3
ROOTFL=`root-config --cflags --libs`
RFLAGS:=`root-config --cflags` `root-config --libs`



fit: main2.cc
	g++ $^ -o $@ ${RFLAGS} 

plot: main3.cc
	g++ $^ -o $@ ${RFLAGS} 