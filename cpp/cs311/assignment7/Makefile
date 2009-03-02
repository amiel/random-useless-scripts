CXX = g++
CXXFLAGS = -ansi -Wall -g

PROGNAME = dlist
OBJS = $(PROGNAME)-test-iterator.o $(PROGNAME).o


default: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGNAME)

$(PROGNAME)-test-iterator.o: $(PROGNAME)-test-iterator.cpp $(PROGNAME).h

$(PROGNAME).o: $(PROGNAME).cpp $(PROGNAME).h


# my tests

AMIELOBJS = $(PROGNAME)-amiel.o $(PROGNAME).o

test: $(AMIELOBJS)
	$(CXX) $(CXXFLAGS) $(AMIELOBJS) -o $(PROGNAME)

$(PROGNAME)-amiel.o: $(PROGNAME)-amiel.cpp $(PROGNAME).h


.PHONY: clean

clean:
	rm -f $(OBJS) $(AMIELOBJS) $(PROGNAME)

