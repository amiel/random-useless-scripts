/*
 * student.cpp
 * Amiel Martin
 * 2006-9-11
 *
 * For CS311
 * Assignment 1
 * Student class source file
 */

#include "student.h"

#include <sstream> // for std::ostringstream

// setID
// sets the id
// pre: none
// post: if id is negative then id_ == 0, otherwise, id_ == id 
void Student::setID(int id) {
   if (id >= 0 )
    id_ = id;
  else
    id_ = 0;
}


// toString
// returns the students name and id in one string
// Example: "John Doe 30"
// pre: none
// post: return == name_ + " " + id_
string Student::toString() const {
  std::ostringstream o;
  o << name_ << " " << id_;
  return o.str();
}


// operator << (stream insertion)
// prints a Students name and id as defined in toString()
// Example: "John Doe 30"
// pre: none
// post: Student is printed as above to the stream
std::ostream & operator << (std::ostream & os, const Student & stud) {
  return os << stud.toString();
}


// operator == (equality test)
// checks equality of two Students
// two Students are equal if both ids and names are equal
// pre: none
// post:
//  returns true if a.id_ == a.id
//  and _a.name_ == b.name_
//  returns false otherwise
bool operator == (const Student & a, const Student & b) {
  return a.getName() == b.getName() &&
         a.getID() == b.getID();
}

// operator =! (inequality test)
// check inequality of two Students
// two Students are equal if both ids and names are equal
// pre: none
// post: returns !(a == b)
bool operator != (const Student & a, const Student & b) {
  return !(a == b);
}


// end of file
