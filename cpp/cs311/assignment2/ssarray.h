/*
 * ssarray.h
 * Amiel Martin
 * 2006-09-15
 * 
 * For CS311
 * Header for class SSArray
 * Template for semismart array
 */
  

#include <cstdlib> // using std::size_t;

#ifndef SSARRAY_H
#define SSARRAY_H


// class SSArray
// Stores an array for any type
// template type must must have op= (assignment) and op!= (inequality)
// Invariants:
//    _ary_ptr points to allocated memory for _size of T
//    _ary_ptr is owned by *this
template <typename T>
class SSArray {
  
  // *** typedefs *** //
  public:
    typedef T * iterator;
    typedef const T * const_iterator;
    typedef std::size_t size_t;
    typedef size_t index; // use size_t because index should have the same range as the possible array size
  
  // *** Ctors, Dctor, op= *** //
  public:

    // no default ctor
    // it is not included because a 1-paramater ctor is defined below

    // Ctor
    // Pre: size > 0
    // Post: class invariants are true
    explicit SSArray(size_t size) : _size(size), _ary_ptr(new T[size]) { }

    // Dctor
    // Pre: None
    // Post: Memory for _ary_ptr is freed
    ~SSArray() { delete [] _ary_ptr; }

    // Copy Ctor
    // Pre: None
    // Post: deep copy performed
    SSArray(const SSArray<T> & other);

    // Assignment Operator
    // Pre: None
    // Post: *this has a new deep copy of other
    SSArray & operator = (const SSArray<T> & other);

  // *** General Public Functions *** //
  public:
    // size
    // returns the size of the Array
    // Pre: None
    // Post: return == _size
    size_t size() const { return _size; }

    // begin
    // returns the address of the first item in the Array
    // Pre: None
    // Post: return == &_ary_ptr[0]
          T * begin()       { return &_ary_ptr[0]; }
    const T * begin() const { return &_ary_ptr[0]; }
 
 
    // end
    // returns the address of the item one-past the end of the array
    // Pre: None
    // Post: return == &_ary_ptr[_size]
          T * end()       { return &_ary_ptr[_size]; }
    const T * end() const { return &_ary_ptr[_size]; }

  // *** operators *** //
  public:
    // Bracket operator
    // returns the address of the apropriate item
    // Pre: index is in range
    // Post: return == &_ary_ptr[index]
          T & operator [] (index i)       { return _ary_ptr[i]; }
    const T & operator [] (index i) const { return _ary_ptr[i]; }
     
  // *** Private helper functions *** //
  private:
    // copy_helper
    // copies data from an SSArray to *this
    // Pre: this->size() == other.size() 
    // Post: *this == other
    void copy_helper(const SSArray<T> &other);
    
  // *** Data Members *** //
  private:
    T *_ary_ptr; // THE ARRAY, this is where we stare all the data
    size_t _size; // the size of the array
    
};


// *** SSArray member functions *** //


// copy_helper
// copies data from an SSArray to *this
// Pre: this->size() == other.size() 
// Post: *this == other
template <typename T>
void SSArray<T>::copy_helper(const SSArray<T> &other) {
  if (this->size() != other.size())
    return; // TODO: out of scope for this project, but we need some error handling here

  iterator i;
  const_iterator j;
  for (i = begin(), j = other.begin(); i != end(); ++i, ++j)
    *i = *j;
}

// Copy Ctor
// Pre: None
// Post: deep copy performed
template <typename T>
SSArray<T>::SSArray(const SSArray<T> &other)
  : _size(other._size), _ary_ptr(new T[other._size]) {
  copy_helper(other);
}


// Assignment Operator
// Pre: None
// Post: *this has a new deep copy of other
template <typename T>
SSArray<T> & SSArray<T>::operator = (const SSArray<T> &other) {
  if (this != &other) {
    delete [] _ary_ptr;

    _size = other._size;
    _ary_ptr = new T[_size];
    copy_helper(other);
  }
  return *this;
}



// *** Assocciated Global Functions *** //


// Equality operator
// two SSArrays with the same item type are equal if they have the same size and their corresponding items are all equal
// Pre: None
// Post: returns true if a == b
template <typename T>
bool operator == (const SSArray<T> &a, const SSArray<T> &b) {
  if (a.size() != b.size())
    return false;

  // g++ told me to use typename, I'm not sure why
  typename SSArray<T>::const_iterator i;
  typename SSArray<T>::const_iterator j;
  for (i = a.begin(), j = b.begin(); i != a.end(); ++i, ++j)
    if (*i != *j)
      return false;

  return true;
}



// Inequality operator
// two SSArrays with the same item type are equal if they have the same size and their corresponding items are all equal
// Pre: None
// Post: returns false if a == b
template <typename T>
bool operator != (const SSArray<T> &a, const SSArray<T> &b) { return !(a == b); }


#endif // #ifndef SSARRAY_H
