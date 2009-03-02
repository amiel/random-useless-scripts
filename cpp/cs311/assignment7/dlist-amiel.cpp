// dlist-amiel.cpp
// Amiel Martin
// Nov 11 2006

// for testing cs311 - Assignment 7


#include "dlist.h"

#include <iostream>
using std::cout;
using std::endl;

int main() {
	DList mylist;
	mylist.insert(mylist.begin(), 5);
	mylist.insert(mylist.begin(), 3);
	mylist.insert(mylist.begin(), 33);
	mylist.insert(mylist.end(), 34);

	for (DList::iterator i = mylist.begin(); i != mylist.end(); ++i) {
		if(*i == 3)
			mylist.insert(i, 30);
		if(*i == 5)
			mylist.insert(i, 50);
	}


	for (DList::iterator i = mylist.begin(); i != mylist.end(); ++i) {
		if(*i == 3)
			mylist.del(i);
		if(*i == 5)
			mylist.del(i);
	}

	
	DList::iterator i = mylist.begin();
	*i = 4;

	
	return 0;
}


