// sequencet.h
// Amiel Martin
// Nov  2 2006

// For CS 311
// Header for Sequence class:
//  Smart array class, based on ADT Sequence, version 2

#ifndef FILE_SEQUENCE_H_INCLUDED
#define FILE_SEQUENCE_H_INCLUDED

#include <cstdlib>  // for std::size_t
#include <algorithm>  // for std::copy

// ************************************************************************
// class Sequence - Class definition
// ************************************************************************

// class Sequence
// Smart array class, based on ADT Sequence, version 2
// Invariants:
//     size_ >= 0.
//     Either
//         data_ points to an int array,
//         allocated with new [], owned by *this, of size equal to size_,
//     or
//         size == 0.
class Sequence {

// ***** Sequence: types *****
public:

    typedef int value_type;         // type of items in the array
    typedef std::size_t size_type;  // type of size of a sequence
    typedef value_type * iterator;  // random-access iterator types
    typedef const value_type * const_iterator;

// ***** Sequence: ctors, dctor, op= *****
public:

    // default ctor
    // ADT op CreateEmpty
    // No-Throw Guarantee
    Sequence()
        :size_(0),
         data_(0)
    {}

    // 1-parameter ctor
    // ADT op CreateSized
    explicit Sequence(size_type theSize)
        :size_(theSize),
         data_(new value_type[theSize])
    {}

    // copy ctor
    // ADT op CreateCopy
    // Strong Guarantee
    Sequence(const Sequence & other);

    // copy assignment
    // ADT op SetEqual
    Sequence & operator=(const Sequence & rhs);

    // dctor
    // ADT op Destroy
    ~Sequence()
    { delete [] data_; }

// ***** Sequence: general public functions *****
public:

    // bracket op (const & non-const)
    // ADT op LookUp
    const value_type & operator[](size_type index) const
    { return data_[index]; }
    value_type & operator[](size_type index)
    { return data_[index]; }

    // size
    size_type size() const
    { return size_; }

    // empty
    // No-Throw Guarantee
    bool empty() const
    { return size_ == 0; }

    // resize
    void resize(size_type newSize);

    // begin (non-const & const)
    iterator begin()
    { return data_; }
    const_iterator begin() const
    { return data_; }

    // end (non-const & const)
    iterator end()
    { return data_ + size_; }
    const_iterator end() const
    { return data_ + size_; }

    // insert
	void insert(const value_type & item, size_type index);

    // del
    // ADT op delete
	void del(size_type index);

// ***** Sequence: Data members *****
private:

    size_type size_;      // size of sequence
    value_type * data_;   // pointer to int array holding sequence

};  // end class Sequence





// ************************************************************************
// class Sequence - Member function definitions
// ************************************************************************

// copy ctor
// ADT op CreateCopy
Sequence::Sequence(const Sequence & other)
    :size_(other.size_),
     data_(new value_type[other.size_])
{
    std::copy(other.begin(), other.end(), begin());
}

// copy assignment
// ADT op SetEqual
Sequence & Sequence::operator=(const Sequence & rhs)
{
    // WHAT GOES HERE ???
}

// resize
void Sequence::resize(size_type newSize)
{
    // WHAT GOES HERE ???
}

// insert
void Sequence::insert(const value_type & item, size_type index)
{
    // WHAT GOES HERE ???
}

// del
// ADT op delete
void Sequence::del(size_type index)
{
    // WHAT GOES HERE ???
}





#endif //#ifndef FILE_SEQUENCE_H_INCLUDED
