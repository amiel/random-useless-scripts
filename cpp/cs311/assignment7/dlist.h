// dlist.h
// Amiel Martin
// Nov 11 2006

// DList class header
// DList is a doubly linked list
// 	with attempted standard complient iterators

#ifndef DLIST_H
#define DLIST_H

#include <cstdlib>  // for std::size_t
#include <algorithm> // for std::swap
#include <iterator> // for std::iterator and std::bidirectional_iterator_tag

#include <stdexcept> // for std::runtime_error
#include <new> // for std::bad_alloc


// class DList
// class invariants:
// 	size_ is equal to how many nodes are in the list - 2 (the dummy nodes)
//	head_ and tail_ each point to dummy NodeS
//	head_->prev_ == NULL
// 	tail_->next_ == NULL
//	head_->next_->next_...->next_ should eventually == tail_
//	and visa-versa (tail_->prev_->prev_...->prev_ == head_)
// 	all NodeS are owned by *this
class DList {
  // *** DList typedefs ***
  public:
    // value_type must not throw
    // and must be a numerical type
    // its best if value_type is a built-in
    typedef int value_type;
    typedef std::size_t size_type;

    class iterator;
    class const_iterator;

  // *** DList::Node decl ***
  private:

    // class DList::Node
    // class invariants:
    //	if next_ and prev_ are not NULL, they must be valid
    // NOTES: caller must set prev_ and next_, none of the ctors do this
    class Node {
      friend class DList;
      friend class DList::iterator;
      friend class DList::const_iterator;

      // *** ctors, etc *** //
      public:
        // Node 1-parm ctor
        // No-Throw Guarantee
        // pre: none
        // post: Node constructed with value, and NULL pointers
        explicit Node(value_type value) : data_(value), next_(NULL), prev_(NULL) /* throw() */ { }

        // Node copy ctor
        // No-Throw Guarantee
        // pre: none
        // post: copies the data_ of that Node (does not copy next_ and prev_
        //	pointers)
        Node(const Node * that) : data_(that->data_), next_(NULL), prev_(NULL) /* throw() */ { }

        // use silently written big-three

      private:
        value_type data_;
        Node * next_;
        Node * prev_;
    };

  // *** DList::iterator and DList::const_iterator class defs ***
  public:

    // class DList::iterator
    // class invariants:
    // 	if ptr_ is not NULL then
    //	ptr_ points to a DList::Node *
    //	which is NOT owned by *this
    class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
      friend class DList;

      // *** ctors, dctor, op= ***
      public:

        // default ctor
        // No-Throw Guarantee
        // pre: none
        // post: ptr_ defaults to NULL
        iterator() : ptr_(NULL) /* throw() */ {}

        // use silently written big three

      private:

        // ctor from a Node *
        // No-Throw Guarantee
        // pre: none
        // post: initializes this to point to p
        explicit iterator(Node * p) : ptr_(p) /* throw() */ {}


      // *** public operators ***
      public:

        // DList::iterator dereference operator
        // Strong Guarantee
        // pre: none
        // post: returns the data_ of the current Node
        value_type & operator * () const /* throw(std::runtime_error() */ {
          if (ptr_ == NULL)
            throw std::runtime_error("DList::iterator dereference operator called on a NULL iterator");
          return ptr_->data_;
        }

        // DList::iterator arrow (->) operator
        // No-Throw Guarantee
        // pre: none
        // post: returns the address of the data_ in the current Node
        value_type * operator -> () const /* throw() */ {
          return &**this;
        }

        // DList::iterator operator ++ (pre-increment)
        // No-Throw Guarantee
        // pre: none
        // post: go to next node
        // improvement: throw if ptr_ is NULL. note: if you implement this,
        // check for functions that miht expect this to not throw
        iterator & operator ++ () /* throw() */ {
          if (ptr_ != NULL)
            ptr_ = ptr_->next_;
          return *this;
        }

        // DList::iterator operator ++ (pre-increment)
        // No-Throw Guarantee
        // pre: none
        // post: go to next node and return the current iterator
        iterator operator ++ (int) /* throw() */ {
          iterator save = *this;
          ++*this;
          return save;
        }

        // DList::iterator operator -- (pre-decrement)
        // No-Throw Guarantee
        // pre: none
        // post: go to prev node
        // improvement: throw if ptr_ is NULL. note: if you implement this,
        // check for functions that miht expect this to not throw
        iterator & operator -- () /* throw() */ {
          if (ptr_ != NULL)
            ptr_ = ptr_->prev_;
          return *this;
        }

        // DList::iterator operator -- (pre-decrement)
        // No-Throw Guarantee
        // pre: none
        // post: go to prev node and return the current iterator
        iterator operator -- (int) /* throw() */ {
          iterator save = *this;
          --*this;
          return save;
        }

      public:
        Node * ptr_;
    };

    // class DList::const_iterator
    // class invariants:
    // 	if ptr_ is not NULL then
    //	ptr_ points to a DList::Node *
    //	which is NOT owned by *this
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
      friend class DList;
      friend bool operator == (const const_iterator &, const const_iterator &);

      // *** ctors, etc *** //
      public:

        // default ctor
        // No-Throw Guarantee
        // pre: none
        // post: ptr_ defaults to NULL
        const_iterator() : ptr_(NULL) { }

        // ctor from an iterator
        // No-Throw Guarantee
        // pre: none
        // post: creates a const_iterator from an iterator
        const_iterator(const DList::iterator & i) : ptr_(i.ptr_) { }

      private:

        // ctor from a Node *
        // No-Throw Guarantee
        // pre: none
        // post: initializes this to point to p
        explicit const_iterator(Node * p) : ptr_(p) /* throw() */ { }

      public:
        // DList::const_iterator dereference operator
        // Strong Guarantee
        // pre: none
        // post: returns the data_ of the current Node
        const value_type & operator * () const /* throw(std::runtime_error) */ {
          if (ptr_ == NULL)
            throw std::runtime_error("DList::const_iterator dereference operator called on a NULL const_iterator");
          return ptr_->data_;
        }

        // DList::const_iterator arrow (->) operator
        // No-Throw Guarantee
        // pre: none
        // post: returns the address of the data_ in the current Node
        const value_type * operator -> () const /* throw() */ {
          return &**this;
        }

        // DList::const_iterator operator ++ (pre-increment)
        // No-Throw Guarantee
        // pre: none
        // post: go to next node
        // improvement: throw if ptr_ is NULL. note: if you implement this,
        // check for functions that miht expect this to not throw
        const_iterator & operator ++ () /* throw() */ {
          if (ptr_ != NULL)
            ptr_ = ptr_->next_;
          return *this;
        }

        // DList::const_iterator operator ++ (pre-increment)
        // No-Throw Guarantee
        // pre: none
        // post: go to next node and return the current iterator
        const_iterator operator ++ (int) /* throw() */ {
          const_iterator save = *this;
          ++*this;
          return save;
        }

        // DList::const_iterator operator -- (pre-decrement)
        // No-Throw Guarantee
        // pre: none
        // post: go to prev node
        // improvement: throw if ptr_ is NULL. note: if you implement this,
        // check for functions that miht expect this to not throw
        const_iterator & operator -- () /* throw() */ {
          if (ptr_ != NULL)
            ptr_ = ptr_->prev_;
          return *this;
        }

        // DList::const_iterator operator -- (pre-decrement)
        // No-Throw Guarantee
        // pre: none
        // post: go to prev node and return the current iterator
        const_iterator operator -- (int) /* throw() */ {
          const_iterator save = *this;
          --*this;
          return save;
        }

      private:
        Node * ptr_;
    };


  // *** DList ctors, op=, and dctor ***
  public:

    // default ctor
    // Strong Guarantee
    // pre: none
    // post: DList is constructed
    DList() : size_(0), head_(NULL), tail_(new Node(0)) /* throw(std::bad_alloc) */ {
      try {
        head_ = new Node(0);
        head_->next_ = tail_;
        tail_->prev_ = head_;
      } catch (const std::bad_alloc & e) {
        delete tail_;
        throw;
      }
    }

    // copy ctor
    // Strong Guarantee
    // pre: none
    // post: deep copy performed
    DList(const DList & that) /* throw(std::bad_alloc) */;

    // copy assignment (op =)
    // Strong Guarantee
    // pre: none
    // post: deep copy performed
    DList & operator = (const DList & rhs) /* throw(std::bad_alloc) */ {
      if (this != &rhs)
        DList(rhs).swap(*this);
      return *this;
    }

    // dtor
    // No-Throw Guarantee
    // pre: none
    // post: none
    ~DList() {
      while(!empty())
        del(begin());
      delete tail_;
      delete head_;
    }

  // *** public member functions ***
  public:

    // empty
    // No-Throw Guarantee
    // pre: none
    // post: returns true if DList is empty
    bool empty() const /* throw() */ {
      return size_ == 0;
    }

    // size
    // No-Throw Guarantee
    // pre: none
    // post: returns the size of DList
    size_type size() const /* throw() */ {
      return size_;
    }

    // begin
    // No-Throw Guarantee
    // pre: none
    // post: returns an iterator pointing to the first Node
    const_iterator begin() const /* throw() */ {
      return const_iterator(head_->next_);
    }
    iterator begin() /* throw() */ {
      return iterator(head_->next_);
    }
    
    // end
    // No-Throw Guarantee
    // pre: none
    // post: returns an iterator to one past the last Node
    const_iterator end() const /* throw() */ {
      return const_iterator(tail_);
    }
    iterator end() /* throw() */ {
      return iterator(tail_);
    }

    // swap
    // No-Throw Guarantee
    // pre: none
    // post: this swaped with that
    void swap(DList & that) /* throw() */ {
      std::swap(size_, that.size_);
      std::swap(head_, that.head_);
      std::swap(tail_, that.tail_);
    }

    // insert
    // Strong Guarantee
    // pre: to_here is a valid iterator for this DList
    // post: allocates a new Node with value and inserts it before to_here
    void insert(iterator to_here, value_type); // throw()

    // del
    // No-Throw Guarantee
    // pre: to_here is a valid iterator into this DList and != end()
    // post: deletes the Node at to_here, invalidates iterator to_here
    void del(iterator to_here); // throw()

    // splice
    // No-Throw Guarantee
    // pre: to_here is a valid iterator into this DList
    // post: that is spliced before to_here, that is cleared
    //	transfers ownership from that NodeS to *this
    void splice(iterator to_here, DList & that); // throw()


  // *** data members ***
  private:
    size_type size_;
    Node * head_;
    Node * tail_;
};



// DList::iterator equality opetator
// No-Throw Guarantee
// pre: none
// post: returns true if iterators point to the same Node
bool operator == (const DList::const_iterator & a, const DList::const_iterator & b); // throw()

// DList::iterator inequality opetator
// No-Throw Guarantee
// pre: none
// post: returns false if iterators point to the same Node
bool operator != (const DList::const_iterator & a, const DList::const_iterator & b); // throw()


#endif // ifndef DLIST_H
