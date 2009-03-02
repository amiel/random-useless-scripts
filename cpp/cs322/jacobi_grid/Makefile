CXX = g++
CXXFLAGS = -ansi -Wall -DDEBUG=true
LDFLAGS = -lpthread

PROGNAME = program2
OBJS = jacobi_grid.o jacobi_thread_group.o

default: main

jacobi_grid.o: jacobi_grid.h jacobi_grid.cpp

jacobi_thread_group.o: jacobi_thread_group.h jacobi_grid.o jacobi_thread_group.cpp


main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(PROGNAME).cpp -o $(PROGNAME)


.PHONY: clean

clean:
	rm -f $(PROGNAME) $(OBJS)
