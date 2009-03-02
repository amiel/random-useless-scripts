// month.cpp
// Glenn G. Chappell
// 11 Sep 2006
//
// For CS 311
// Source for class Month
// Example of simple class with operators

#include "month.h"

#include <iostream>  // for std::ostream

// ************************************************************************
// class Month - Definitions of member functions
// ************************************************************************

// operator++ (pre-increment)
// Goes to the next month (12/1980 goes to 1/1981)
// Pre: None.
// Post:
//     Month/year is the month and year of the next month.
//     Return is reference to self.
Month & Month::operator++()
{
    ++month_;
    if (month_ > 12)
    {
        month_ = 1;
        ++year_;
    }
    return *this;
}

// operator++ (post-increment)
// Goes to the next month (12/1980 goes to 1/1981)
// Pre: None.
// Post:
//     Month/year is the month and year of the next month.
//     Return is old value of self.
Month Month::operator++(int)
{
    Month save = *this;
    ++*this;
    return save;
}

// operator-- (pre-decrement)
// Goes to the previous month (1/1980 goes to 12/1979)
// Pre: None.
// Post:
//     Month/year is the month and year of the previous month.
//     Return is reference to self.
Month & Month::operator--()
{
    --month_;
    if (month_ < 1)
    {
        month_ = 12;
        --year_;
    }
    return *this;
}

// operator-- (post-decrement)
// Goes to the previous month (1/1980 goes to 12/1979)
// Pre: None.
// Post:
//     Month/year is the month and year of the previous month.
//     Return is old value of self.
Month Month::operator--(int)
{
    Month save = *this;
    --*this;
    return save;
}

// ************************************************************************
// class Month - Definitions of associated global operators
// ************************************************************************

// operator<< (stream insertion)
// Prints a Month, as month/year, no padding with spaces/zeroes.
// For example, "3/2006".
// Pre: None.
// Post:
//     Month is printed, as above, to the given stream.
std::ostream & operator<<(std::ostream & theStream,
                          const Month & theMonth)
{
    theStream << theMonth.getMonth()
              << "/"
              << theMonth.getYear();
    return theStream;
}

// operator== (equality test)
// Checks equality of two Month's.
// Month's are equal if both months and years are equal.
// Pre: None.
// Post:
//     Returns true if month_ members are equal for a, b
//      and year_ members are equal for a, b.
//     Returns false otherwise.
bool operator==(const Month & a,
                const Month & b)
{
    return a.getMonth() == b.getMonth()
        && a.getYear() == b.getYear();
}

// operator!= (inequality test)
// Checks inequality of two Month's.
// Month's are equal if both months and years are equal.
// Pre: None.
// Post:
//     Returns !(a == b)
bool operator!=(const Month & a,
                const Month & b)
{
    return !(a == b);
}
