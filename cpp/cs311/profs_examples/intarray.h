// intarray.h
// Glenn G. Chappell
// 15 Sep 2006
//
// For CS 311
// Header for IntArray class:
//  RAII class for dynamically allocated array of int's.
// There is no associated source file.

#ifndef FILE_INTARRAY_H_INCLUDED
#define FILE_INTARRAY_H_INCLUDED

#include <cstdlib>  // for std::size_t

// ************************************************************************
// class IntArray - Class definition
// ************************************************************************

// class IntArray
// Simple RAII class for dynamically allocated arrays of int's.
// A const IntArray does not allow modifications of its array items.
// Invariants:
//     arrayPtr_ points to memory allocated with new[],
//      owned by *this.
class IntArray {

// ***** IntArray: Types *****
public:

    typedef std::size_t size_type;  // Unsigned type for size of array
    typedef int value_type;         // Value type of this container

// ***** IntArray: Ctors, dctor, op= *****
public:

    // ctor from size
    // Not an implicit type conversion.
    // Pre: size >= 0.
    // Post:
    //     arrayPtr_ points to array with given size.
    explicit IntArray(size_type size)
        :arrayPtr_(new value_type[size])
    {}

    // Dctor
    // Pre: None.
    // Post: (Array is delete'd.)
    ~IntArray()
    { delete [] arrayPtr_; }

private:

    // Uncopyable class. Do not define copy ctor, copy assignment.
    IntArray(const IntArray &);
    IntArray & operator=(const IntArray &);

// ***** IntArray: General public operators *****
public:

    // Bracket operator (non-const & const)
    // Pre:
    //     0 <= index < size of allocated array.
    // Post:
    //     Return is reference to arrayPtr_[index].
    value_type & operator[](size_type index)
    { return arrayPtr_[index]; }
    const value_type & operator[](size_type index) const
    { return arrayPtr_[index]; }

// ***** IntArray: Data members *****
private:

    int * arrayPtr_;  // Pointer to our array.

};  // End class IntArray

#endif //#ifndef FILE_INTARRAY_H_INCLUDED
