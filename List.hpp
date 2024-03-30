#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if(first == nullptr){
      return true;
    }
    return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    return _size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(first != nullptr);
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(last != nullptr);
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node* new_f = new Node;
    new_f->datum = datum;
    new_f->prev = nullptr;

    if(_size == 0){
      new_f->next =  nullptr;
      first = last = new_f;
    }
    else{
      new_f->next = first;
      first->prev = new_f;
      first = new_f;
    }

    _size++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node* new_b = new Node;
    new_b->datum = datum;
    new_b->next = nullptr;

    if(_size == 0){
      new_b->prev =  nullptr;
      first = last = new_b;
    }
    else{
      new_b->prev = last;
      last->next = new_b;
      last = new_b;
    }

    _size++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(_size != 0); 
    Node* to_del = first;
    first = first->next;
    if (_size == 1) {
        last = nullptr;
    }
    delete to_del;
    _size--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(_size != 0);
    Node* to_del = last;
    last = last->prev;
    if (_size == 1) {
        first = nullptr;
    }
    delete to_del;
    _size--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    while(_size > 0){pop_front();}
  }

  // def ctor
  List()
  :first(nullptr), last(nullptr), _size(0){ }

  //copy ctor
  List(const List &copyctor)
  : first(nullptr), last(nullptr), _size(0){
    copy_all(copyctor);
  }

  //dtor
  ~List(){
    clear();
  }

  //assignment op
  List & operator=(const List &rhs){
    if(this == &rhs){return *this;}
    clear();
    copy_all(rhs);
    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Node* p = other.first; p; p = p->next){
      push_back(p->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  size_t _size;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.

    Iterator()
    :list_ptr(nullptr), node_ptr(nullptr){ }

    T & operator*() const{
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator & operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    Iterator operator++(int){
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator==(Iterator rhs) const{
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const{
      return node_ptr != rhs.node_ptr;
    }


    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.





    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    friend class List;
    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np)
    :list_ptr(lp), node_ptr(np) { }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{
    return Iterator(this,first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(this,nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
    assert(i != end());
    Node* to_del = i.node_ptr;
    Node* nb = to_del->prev;
    Node* nn = to_del->next;

    if (nb){nb->next = nn;}
    else{first = nn;}

    if (nn){nn->prev = nb;}
    else{last = nb;}

    delete to_del;
    _size--;

    return Iterator(this, nn);
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){
    if(i == begin()){
      push_front(datum);
      i--;
      return i;
    }
    if(i == end()){
      push_back(datum);
      Iterator edgeb(this,last);
      return edgeb;
    }

    Iterator n2 = i--;
    Iterator n0 = i;
    Node* n1 = new Node;
    n1->datum = datum;

    n1->next = n0.node_ptr->next;
    n0.node_ptr->next = n1;
    
    n1->prev = n2.node_ptr->prev;
    n2.node_ptr->prev = n1;

    return Iterator(this,n1);
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
