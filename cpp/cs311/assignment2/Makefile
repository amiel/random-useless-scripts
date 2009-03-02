CXX = g++
CXXFLAGS = -ansi -Wall


default: ssarray.h ssarray-test.cpp
	$(CXX) $(CFLAGS) ssarray-test.cpp -o ssarray


test: ssarray.h ssarray-simple-test.cpp
	$(CXX) $(CFLAGS) ssarray-simple-test.cpp -o ssarray


.PHONY: clean

clean:
	rm -f ssarray



