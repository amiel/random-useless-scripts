// amiel-test.cpp
// Amiel Martin
// Mon Sep 25 2006

// a simple test file for assignment 3



#include "da3.h"

#include <exception> // for std::exception
#include <iostream>
using std::cout;
using std::endl;

#include <sstream>


#include <vector>

void myFunc1()
{ throw std::exception(); }

void myFunc2()
{ 0; }


int main(){
  cout << (doesThisThrow(myFunc2) ? "function myFunc2 throws" : "function myFunc2 does not throw") << endl;
  cout << (doesThisThrow(myFunc1) ? "function myFunc1 throws" : "function myFunc1 does not throw") << endl;

  printRev(cout, "blah");
  cout << "x" << endl;

  std::ostringstream oss;
  printRev(oss, "abc");
  cout << "ostringstream oss: " << oss.str() << endl;

  try {
    double arr[3] = { 1.0, 3.0, 2.0 };
    divideAll(arr, arr+3, 2.0);
    cout << "arr: "
         << "0("
         << arr[0]
         << ") 1("
         << arr[1]
         << ") 2("
         << arr[2]
         << ")" << endl;

    // divideAll(arr, arr+3, 0); // will throw range_error
  } catch (std::range_error & e) {
    cout << "caught error: " << e.what() << endl;
  }

  std::vector<int> v;
  v.push_back(1);
  v.push_back(5);
  v.push_back(2);
  v.push_back(0);
  v.push_back(5);
  sortDescendingInt(v.begin(), v.end());

  cout << "does a vector print? " << endl;
  std::vector<int>::iterator i;
  for (i = v.begin(); i != v.end(); ++i)
    cout << *i << " ";
  cout << endl;
  
  
  return 0;
}
