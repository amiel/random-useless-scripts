CXX = g++
CXXFLAGS = -ansi -Wall

PROGNAME = memowrapper


default: main

main: $(PROGNAME).h $(PROGNAME)-test.cpp
	$(CXX) $(CXXFLAGS) $(PROGNAME)-test.cpp -o $(PROGNAME)




# my tests
amiel: test

test: $(PROGNAME)-amiel.cpp $(PROGNAME).h
	$(CXX) $(CXXFLAGS) $(PROGNAME)-amiel.cpp -o $(PROGNAME)



.PHONY: clean

clean:
	rm -f $(PROGNAME)

