CXX = g++
CXXFLAGS = -ansi -Wall

PROG = da3

default: $(PROG).h $(PROG)-test.cpp
	$(CXX) $(CXXFLAGS) $(PROG)-test.cpp -o $(PROG)


test: $(PROG).h amiel-test.cpp
	$(CXX) $(CXXFLAGS) amiel-test.cpp -o $(PROG)


.PHONY: clean

clean:
	rm -f $(PROG)



