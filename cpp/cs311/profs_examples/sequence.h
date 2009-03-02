// sequence.h (UNFINISHED)
// Revision 2
// Glenn G. Chappell
// 30 Oct 2006
//
// For CS 311
// Header for Sequence class:
//  Smart array class, based on ADT Sequence, version 2

#ifndef FILE_SEQUENCE_H_INCLUDED
#define FILE_SEQUENCE_H_INCLUDED

#include <cstdlib>  // for std::size_t

// ************************************************************************
// class Sequence - Class definition
// ************************************************************************

// class Sequence
// Smart array class, based on ADT Sequence, version 2
// Invariants:
//     capacity_ >= size_ >= 0.
//     capacity_ >= MINCAP.
//     data_ points to an int array,
//      allocated with new [], owned by *this, of size at least capacity_.
class Sequence {

// ***** Sequence: types & constants *****
public:

    typedef int value_type;         // type of items in the array
    typedef std::size_t size_type;  // type of size of a sequence
    typedef value_type * iterator;  // random-access iterator types
    typedef const value_type * const_iterator;

private:

    enum { MINCAP = 32 };           // Minimum value for capacity_

// ***** Sequence: ctors, dctor, op= *****
public:

    // default ctor
    // ADT op CreateEmpty
    // Strong Guarantee
    Sequence()
        :size_(0),
         capacity_(MINCAP),
         data_(new value_type[capacity_])
    {}

    // 1-parameter ctor
    // ADT op CreateSized
    // Strong Guarantee
    explicit Sequence(size_type theSize)
        :size_(theSize),
         capacity_(theSize < MINCAP ? MINCAP : theSize),
         data_(new value_type[capacity_])
    {}

    // copy ctor
    // ADT op CreateCopy
    // Strong Guarantee
    Sequence(const Sequence & other);

    // copy assignment
    // ADT op SetEqual
    // ??? Guarantee
    Sequence & operator=(const Sequence & rhs);

    // dctor
    // ADT op Destroy
    // No-Throw Guarantee
    ~Sequence()
    { delete [] data_; }

// ***** Sequence: general public functions *****
public:

    // bracket op (const & non-const)
    // ADT op LookUp
    // No-Throw Guarantee
    const value_type & operator[](size_type index) const
    { return data_[index]; }
    value_type & operator[](size_type index)
    { return data_[index]; }

    // size
    // No-Throw Guarantee
    size_type size() const
    { return size_; }

    // empty
    // No-Throw Guarantee
    bool empty() const
    { return size_ == 0; }

    // resize
    // ??? Guarantee
    void resize(size_type newSize);

    // begin (non-const & const)
    // No-Throw Guarantee
    iterator begin()
    { return data_; }
    const_iterator begin() const
    { return data_; }

    // end (non-const & const)
    // No-Throw Guarantee
    iterator end()
    { return data_ + size_; }
    const_iterator end() const
    { return data_ + size_; }

    // insert
    // ??? Guarantee
	void insert(const value_type & item, size_type index);

    // del
    // ADT op delete
    // ??? Guarantee
	void del(size_type index);

// ***** Sequence: Data members *****
private:

    size_type size_;      // size of sequence
    size_type capacity_;  // number of items in allocated array
    // capacity_ must be declared before data_,
    //  so that initializers work correctly.
    value_type * data_;   // pointer to int array holding sequence

};  // end class Sequence

#endif //#ifndef FILE_SEQUENCE_H_INCLUDED