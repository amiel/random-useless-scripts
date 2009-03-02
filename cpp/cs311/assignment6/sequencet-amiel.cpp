// sequencet-amiel.cpp
// Amiel Martin
// Nov  2 2006

// just my file to start testing the sequence class

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include "sequencet.h"


int CTOR_CALLS = 0;
int DCTOR_CALLS = 0;

class st_test {
  public:
    typedef int value_type;
  public:
    st_test() : d_(0) { ++CTOR_CALLS; }
    explicit st_test(value_type d) : d_(d) { ++CTOR_CALLS; }

    st_test(const st_test & other) : d_(other.d_)
      { cerr << "st_test: copy ctor called: d_(" << d_ << ")" << endl; ++CTOR_CALLS; }

    st_test & operator=(const st_test & rhs) {
      cerr << "st_test: op= called ";
      if(this != &rhs)
        d_ = rhs.d_;
      cerr << "d_(" << d_ << ")" << endl;
      return *this;
    }

    value_type operator=(value_type d) {
      cerr << "st_test: op= value_type setting d_ to " << d << endl;
      d_ = d;
      return d;
    }

    ~st_test() {
      ++DCTOR_CALLS;
    }

  public:
    void set(value_type d) {
      d_ = d;
    }

    value_type get() const {
      return d_;
    }

  private:
    value_type d_;
};


ostream & operator << (ostream & out, const st_test & p) {
  return out << p.get();
}

template <typename T>
void print_info(string name, const SequenceT<T> & printMe) {
  cout << "PRINTING " << name << ":" << "which has size(" << printMe.size() << ")"
    << " and cap(" << printMe.capacity() << ")" << endl;
}

template <typename T>
void print_sequence(string name, const SequenceT<T> & printMe) {
  print_info(name,printMe);
  typename SequenceT<T>::const_iterator i;
  for (i = printMe.begin(); i != printMe.end(); ++i)
    cout << '\t' << "SequenceT[" << "] is (" << *i << ")" << endl;
}

int main() {
  SequenceT<st_test> my_test0(3);
  SequenceT<st_test> my_test1(1);
  my_test0[2] = 1;
  my_test0[0] = 51;
  my_test0[1] = 3;
  print_sequence("test0",my_test0);
  cout << ">>>> creating my_test2" << endl;
  SequenceT<st_test> my_test2(my_test0);
  cout << ">>>> setting my_test1 = my_test0" << endl;
  my_test1 = my_test0;
  print_sequence("test1",my_test1);

  cout << "\n\n>>>> resizing my_test2" << endl;
  my_test2.resize(0);
  for (int i = 0;i<31;++i)
    my_test2.insert(st_test(i),i);

  print_info("test2",my_test2);
  my_test2.insert(st_test(48), 8);
  print_info("test2",my_test2);
  my_test2.insert(st_test(46), 6);
  print_sequence("test2",my_test2);

  my_test2.del(15);
  my_test2.del(15);
  print_sequence("test2",my_test2);

  return 0;
}
