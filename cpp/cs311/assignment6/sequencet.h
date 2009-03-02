// sequencet.h
// Amiel Martin
// Nov  2 2006

// For CS 311
// Header for SequenceT class:
//  Smart array class, based on ADT Sequence, version 2

#ifndef FILE_SEQUENCE_H_INCLUDED
#define FILE_SEQUENCE_H_INCLUDED

#include <cstdlib>  // for std::size_t
#include <stdexcept> // for std::out_of_range
#include <algorithm> // for std::sort, std::copy, std::rotate and std::swap


// ************************************************************************
// class SequenceT - Class definition
// ************************************************************************

// class SequenceT
// Requirements on types: T must have...
//	a default ctor
//	a public copy ctor
//	a public dctor that does not throw
//	a public op=
// Smart array class, based on ADT Sequence, version 2
// Invariants:
//     capacity_ >= size_ >= 0.
//     capacity_ >= MINCAP.
//     data_ points to an int array,
//      allocated with new [], owned by *this, of size at least capacity_.
template <typename T>
class SequenceT {

  // ***** SequenceT: types & constants *****
  public:

    typedef T value_type;         // type of items in the array
    typedef std::size_t size_type;  // type of size of a sequence
    typedef value_type * iterator;  // random-access iterator types
    typedef const value_type * const_iterator;

  private:

    enum { MINCAP = 32 };           // Minimum value for capacity_

  // ***** SequenceT: ctors, dctor, op= *****
  public:

    // default ctor
    // ADT op CreateEmpty
    // Strong Guarantee
    // may throw std::bad_alloc
    // pre: none
    // post: class invariants are true
    SequenceT()
        :size_(0),
         capacity_(MINCAP),
         data_(new value_type[capacity_])
    {}

    // 1-parameter ctor
    // ADT op CreateSized
    // Strong Guarantee
    // may throw std::bad_alloc
    // pre: none
    // post: class invariants are true, and size is theSize
    explicit SequenceT(size_type theSize)
        :size_(theSize),
         capacity_(calculate_capacity(theSize)),
         data_(new value_type[capacity_])
    {}

    // copy ctor
    // ADT op CreateCopy
    // Strong Guarantee
    // may throw anything that value_type's copy ctor throws
    // pre: none
    // post: deep copy performed
    SequenceT(const SequenceT & other);

    // copy assignment
    // ADT op SetEqual
    // Strong Guarantee
    // may throw anything that value_type's copy ctor throws
    // pre: none
    // post: this gets a deep copy of rhs
    SequenceT & operator=(const SequenceT & rhs) {
      if (this != &rhs)
        SequenceT(rhs).swap(*this);
      return *this;
    }

    // dctor
    // ADT op Destroy
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: memory for data_ is freed
    ~SequenceT()
    { delete [] data_; }

// ***** SequenceT: general public functions *****
public:

    // bracket op (const & non-const)
    // ADT op LookUp
    // Strong Guarantee
    // may throw std::out_of_range if index is out of range
    // pre: none
    // post: returns data_[index]
    const value_type & operator[](size_type index) const
    {
      if (index < 0 || index >= size_)
        throw std::out_of_range("SequenceT const operator[]: index out of range");
      return data_[index];
    }
    value_type & operator[](size_type index)
    {
      if (index < 0 || index >= size_)
        throw std::out_of_range("SequenceT operator[]: index out of range");
      return data_[index];
    }

    // size
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: returns the size (not capacity)
    size_type size() const
    { return size_; }

    // empty
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: returns true if size_ is 0
    bool empty() const
    { return size_ == 0; }

    // resize
    // Strong Guarantee
    // may throw anything that size_types copy ctor throws
    // may throw std::out_of_range
    // pre: none
    // post: resize changes size to newSize and reallocates if necesarry
    //   resize does nothing if newSize < 0
    void resize(size_type newSize);

    // begin (non-const & const)
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: returns an iterator pointing to the begining of the data
    iterator begin()
    { return data_; }
    const_iterator begin() const
    { return data_; }

    // end (non-const & const)
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: returns an iterator pointing to "one-past-the-end" of the data
    iterator end()
    { return data_ + size_; }
    const_iterator end() const
    { return data_ + size_; }

    // insert
    // Basic Guarantee
    // may throw anything that value_type's copy ctor throws
    // may throw std::out_of_range
    // pre: none
    // post: inserts item after index
    void insert(const value_type & item, size_type index);

    // del
    // ADT op delete
    // Basic Guarantee
    // may throw anything that value_type's copy ctor throws
    // may throw std::out_of_range
    // pre: none
    // post: deletes the item at index
    void del(size_type index);


// ***** SequenceT: Private member functions *****
private:

    // swap
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: swaps data_ with other data_
    void swap(SequenceT<T> & other) {
      std::swap(capacity_, other.capacity_);
      std::swap(size_, other.size_);
      std::swap(data_, other.data_);
    }


    // calculate_capacity
    // 	thank you juri for finding this algorithm
    // 	from http://paste.lisp.org/display/214
    // No-Throw Guarantee
    // does not throw
    // pre: none
    // post: returns the least power of 2 greater than or equal to new_size
    // 	returns MINCAP if the least power of 2 is less than MINCAP
    // NOTE: this function may promote a portability issue
    size_type calculate_capacity(size_type new_size) const {
      size_type tmp = new_size - 1;
      tmp = tmp | (tmp >> 1);
      tmp = tmp | (tmp >> 2);
      tmp = tmp | (tmp >> 4);
      tmp = tmp | (tmp >> 8);
      tmp = tmp | (tmp >>16);
      tmp = tmp + 1;
      // this eleminates the possibilty that we will return a negative value
      // due to numeric overflow
      return (tmp < MINCAP) ? MINCAP : tmp;
    } 

// ***** SequenceT: Data members *****
private:

    size_type size_;      // size of sequence
    size_type capacity_;  // number of items in allocated array
    // capacity_ must be declared before data_,
    //  so that initializers work correctly.
    value_type * data_;   // pointer to int array holding sequence

};  // end class SequenceT




// ************************************************************************
// class SequenceT - Member function definitions
// ************************************************************************

// copy ctor
// ADT op CreateCopy
// Strong Guarantee
// may throw anything that value_type's copy ctor throws
// pre: none
// post: deep copy performed
template <typename T>
SequenceT<T>::SequenceT(const SequenceT<T> & other)
    :size_(other.size_),
     capacity_(other.capacity_),
     data_(new value_type[other.capacity_])
{
  try {
    std::copy(other.begin(), other.end(), begin());
  } catch (...) {
    delete [] data_;
    throw;
  }

}


// resize
// Strong Guarantee
// may throw anything that size_types copy ctor throws
// may throw std::out_of_range
// pre: none
// post: resize changes size to newSize and reallocates if necesarry
//   resize does nothing if newSize < 0
template <typename T>
void SequenceT<T>::resize(size_type newSize)
{
  if (newSize < 0)
    throw std::out_of_range("SequenceT resize: cannot resize to a negative size");

  if (newSize > capacity_) {
    SequenceT<T> tmp(newSize);
    std::copy(begin(), end(), tmp.begin());
    swap(tmp);
  } else { // we have enough capacity
    size_ = newSize;
  }
}

// insert
// Basic Guarantee
// may throw anything that value_type's copy ctor throws
// may throw std::out_of_range
// pre: none
// post: inserts item after index
template <typename T>
void SequenceT<T>::insert(const value_type & item, size_type index)
{
  // the loic here is purposefully different than all the other ones,
  // because you can insert at the end of a list
  if (index < 0 || index > size_)
    throw std::out_of_range("SequenceT insert: index out of range");
  resize(size_+1);
  data_[size_-1] = item;
  std::rotate(data_+index, data_+size_-1, data_+size_);
}

// del
// ADT op delete
// Basic Guarantee
// may throw anything that value_type's copy ctor throws
// may throw std::out_of_range
// pre: none
// post: deletes the item at index
template <typename T>
void SequenceT<T>::del(size_type index)
{
  if (index < 0 || index >= size_)
    throw std::out_of_range("SequenceT del: index out of range");
  std::rotate(data_+index, data_+index+1, data_+size_);
  resize(size_-1);
}



#endif // #ifndef FILE_SEQUENCE_H_INCLUDED
