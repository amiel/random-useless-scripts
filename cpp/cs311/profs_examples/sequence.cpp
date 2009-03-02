// sequence.cpp (UNFINISHED)
// Revision 2
// Glenn G. Chappell
// 30 Oct 2006
//
// For CS 311
// Source for Sequence class:
//  Smart array class, based on ADT Sequence, version 2

#include "sequence.h"

#include <algorithm>  // for std::copy

// ************************************************************************
// class Sequence - Member function definitions
// ************************************************************************

// copy ctor
// ADT op CreateCopy
// Strong Guarantee
Sequence::Sequence(const Sequence & other)
    :size_(other.size_),
     capacity_(other.capacity_),
     data_(new value_type[other.capacity_])
{
    std::copy(other.begin(), other.end(), begin());
}

// copy assignment
// ADT op SetEqual
// ??? Guarantee
Sequence & Sequence::operator=(const Sequence & rhs)
{
    // WHAT GOES HERE ???
}

// resize
// ??? Guarantee
void Sequence::resize(size_type newSize)
{
    // WHAT GOES HERE ???
}

// insert
// ??? Guarantee
void Sequence::insert(const value_type & item, size_type index)
{
    // WHAT GOES HERE ???
}

// del
// ADT op delete
// ??? Guarantee
void Sequence::del(size_type index)
{
    // WHAT GOES HERE ???
}
