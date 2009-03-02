// dlist.cpp
// Amiel Martin
// Nov 11 2006

// DList class implementation
// DList is a doubly linked list
// 	with attempted standard complient iterators


#include "dlist.h"


// copy ctor
// Strong Guarantee
// pre: none
// post: deep copy performed
// TODO: we could throw our own exception or std::bad_alloc with a message
DList::DList(const DList & that) // throw(std::bad_alloc)
    : size_(0), // because we use insert, which increases the size for us
      head_(NULL),
      tail_(new Node(0)) {
  try {
    head_ = new Node(0);
  } catch (const std::bad_alloc & e) {
    delete tail_;
    throw;
  }

  head_->next_ = tail_;
  tail_->prev_ = head_;
  if(that.empty())
    return;

  try {
    iterator this_iter = begin();
    for (const_iterator that_iter = that.begin(); that_iter != that.end(); ++that_iter)
      insert(this_iter, *that_iter);
  } catch (...) { // operator * can throw std::runtime_error easier to just catch them both
    this->~DList();
    throw;
  }
}


// insert
// Strong Guarantee
// pre: to_here is a valid iterator for this DList
// post: allocates a new Node with value and inserts it before to_here
void DList::insert(iterator to_here, value_type value) /* throw(std::bad_alloc) */ {
  // this could be a good idea but we handle it with the preconditions
  // if(to_here == begin()) return;
  Node * new_node = new Node(value);
  Node * here = to_here.ptr_;
  new_node->next_ = here;
  new_node->prev_ = here->prev_;
  here->prev_ = new_node;
  new_node->prev_->next_ = new_node;
  ++size_;
}

// del
// No-Throw Guarantee
// pre: to_here is a valid iterator into this DList and != end()
// post: deletes the Node at to_here, invalidates to_here
// idea for next ADT: del could return an iterator or take an iterator by
// 	reference, either returning a valid iterator to the next Node or
// 	keeping to_here valid by setting it to the next Node
//	so that this is possible:
//
//	while(i != mylist.end())
//		mylist.del(i);
void DList::del(iterator to_here) /* throw() */ {
  // this could be a good idea but we handle it with the preconditions
  // if(to_here == begin() || to_here == end()) return;
  if(empty())
    return;
  Node * here = to_here.ptr_;
  // if del took an iterator by reference, we could ++ it here to keep it valid
  // 	NOTE: in the future, op++ may throw
  here->prev_->next_ = here->next_;
  here->next_->prev_ = here->prev_;
  delete here;
  --size_;
}


// splice
// No-Throw Guarantee
// pre: to_here is a valid iterator into this DList
// post: that is spliced before to_here, that is cleared
//	transfers ownership from that NodeS to *this
void DList::splice(iterator to_here, DList & that) /* throw() */ { 
  // this could be a good idea but we handle it with the preconditions
  // if(to_here == begin()) return;
  if(this == &that)
    return;
  if(that.empty())
    return;
  Node * here = to_here.ptr_;
  Node * that_first = that.head_->next_;
  Node * that_last = that.tail_->prev_;

  here->prev_->next_ = that_first;
  that_first->prev_ = here->prev_;
  that_last->next_ = here;
  here->prev_ = that_last;

  that.head_->next_ = that.tail_;
  that.tail_->prev_ = that.head_;

  size_ += that.size_;
  that.size_ = 0;
}





// DList::iterator equality opetator
// No-Throw Guarantee
// pre: none
// post: returns true if iterators point to the same Node
bool operator == (const DList::const_iterator & a, const DList::const_iterator & b) /* throw() */ {
  return a.ptr_ == b.ptr_;
}

// DList::iterator inequality opetator
// No-Throw Guarantee
// pre: none
// post: returns false if iterators point to the same Node
bool operator != (const DList::const_iterator & a, const DList::const_iterator & b) /* throw() */ {
  return !(a == b);
}


