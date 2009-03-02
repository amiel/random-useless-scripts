CXX = g++
CXXFLAGS = -Wall -ansi

OBJS = student.o student-test.o


default: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o student


student-test.o: student-test.cpp student.h
student.o: student.cpp student.h


# my tests

OBJS2 = student.o student-test2.o

test2: $(OBJS2)
	$(CXX) $(CXXFLAGS) $(OBJS2) -o student

student-test2.o: student-test.cpp student.h


.PHONY: clean

clean:
	rm -f $(OBJS) $(OBJS2) student
