// memowrapper-amiel.cpp
// Amiel Martin
// Dec  4 2006

// 

#include <string>
#include <iostream>
using std::cout;
using std::endl;


#include "memowrapper.h"

int foo(const std::string & s) {
  //cout << "foo called with: " << s << endl;
  sleep(1);
  int hash = 0;
  for(std::string::const_iterator i = s.begin(); i != s.end(); ++i)
    hash = (hash*33 + int(*i)) % 1009;

  return hash;
}



int main() {

    MemoWrapper<std::string, int> m(foo);
    cout << m("abc") << endl;
    cout << m("def") << endl;
    cout << m("def") << endl;
    cout << m("aef") << endl;
    cout << m("abc") << endl;
    cout << m("def") << endl;
    cout << m("aef") << endl;

    return 0;
}
