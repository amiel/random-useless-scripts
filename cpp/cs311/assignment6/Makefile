CXX = g++
CXXFLAGS = -ansi -Wall -g

PROGNAME = sequencet
OBJS = $(PROGNAME)-test.o


default: main

main: $(PROGNAME).h $(PROGNAME)-test.cpp
	$(CXX) $(CXXFLAGS) $(PROGNAME)-test.cpp -o $(PROGNAME)

#$(OBJS)

#$(PROGNAME)-test.o: $(PROGNAME)-test.cpp $(PROGNAME).h


# my tests

AMIELOBJS = $(PROGNAME)-amiel.o

test: $(AMIELOBJS)
	$(CXX) $(CXXFLAGS) $(AMIELOBJS) -o $(PROGNAME)

$(PROGNAME)-amiel.o: $(PROGNAME)-amiel.cpp $(PROGNAME).h


.PHONY: clean

clean:
	rm -f $(OBJS) $(AMIELOBJS) $(PROGNAME)

