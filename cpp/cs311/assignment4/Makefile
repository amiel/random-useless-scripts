CXX = g++
CXXFLAGS = -ansi -Wall

PROGNAME = domino
OBJS = $(PROGNAME).o $(PROGNAME)-test.o


default: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGNAME)


$(PROGNAME)-test.o: $(PROGNAME)-test.cpp $(PROGNAME).h
$(PROGNAME).o: $(PROGNAME).cpp $(PROGNAME).h


# my tests

AMIELOBJS = $(PROGNAME).o $(PROGNAME)-amiel.o

test: $(AMIELOBJS)
	$(CXX) $(CXXFLAGS) $(AMIELOBJS) -o $(PROGNAME)

$(PROGNAME)-amiel.o: $(PROGNAME)-amiel.cpp $(PROGNAME).h


.PHONY: clean

clean:
	rm -f $(OBJS) $(AMIELOBJS) $(PROGNAME)

