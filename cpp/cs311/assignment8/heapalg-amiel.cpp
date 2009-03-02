// heapalg-amiel.cpp
// Amiel Martin
// Nov 25 2006

// 


#include "heapalg.h"

#include <iostream>
#include <vector>
#include <iomanip>


template <typename RAIter>
void myPrintHeap(RAIter first, RAIter last) {
  const int WIDTH = 4;
  for (RAIter i = first ; i != last; ++i)
    std::cout << std::setw(WIDTH) << *i;
  std::cout << std::endl;
}



int main(){
  std::vector<int> v;
  int size=16;
  v.resize(size);
  for (int i = 0; i < size/2 ; ++i)
    v[i*2] = i%3 + i;
  for (int i = 0; i < size/2; ++i)
    v[((size/2)-i)*2 - 1] = i%5 + i + size;

  assert((-1/2)==0);
  std::cout << "assert((-1/2)==0): PASSED\n";

  std::cout << "my stupid random array algo" << std::endl;
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end())==false);

  std::cout << "heapMake\n";
  heapMake(v.begin(), v.end());
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end()));

  std::cout << "heapInsert\n";
  v.push_back(90);
  heapInsert(v.begin(), v.end());
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end()));

  std::vector<int>::iterator blah = v.begin();
  ++blah;

  std::cout << "v.insert, should not ruin heap\n";
  v.insert(v.begin(), 9);
  myPrintHeap(v.begin(), v.end());
  std::cout << "assert(heapTest())";
  assert(heapTest(blah, v.end()));
  std::cout << ": PASSED\n";



  std::cout << "v.insert, should ruin heap\n";
  v.insert(v.begin(), 8);
  myPrintHeap(v.begin(), v.end());
  std::cout << "assert(heapTest == false)";
  assert(heapTest(v.begin(), v.end())==false);
  std::cout << ": PASSED\n";
  
  std::cout << "heapMake2\n";
  heapMake(v.begin(), v.end());
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end()));

  

  std::cout << "heapInsert\n";
  v.push_back(90);
  heapInsert(v.begin(), v.end());
  v.push_back(1);
  heapInsert(v.begin(), v.end());
  v.push_back(11);
  heapInsert(v.begin(), v.end());
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end()));

  std::cout << "heapDelete\n";
  heapDelete(v.begin(), v.end());
  v.pop_back();
  heapDelete(v.begin(), v.end());
  v.pop_back();
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end()));

  std::cout << "heapSort\n";
  heapSort(v.begin(), v.end());
  myPrintHeap(v.begin(), v.end());
  assert(heapTest(v.begin(), v.end())==false);

  return 0;
}
