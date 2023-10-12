// CS311 Yoshii S22 slist.h
// HW3P2 Instruction: Inherit everything publicly from llist
// Put only the following in class slist.h 
//    inheriting everything from llist.h
//
// Then create slist.cpp with only the following functions
// Complete all ** parts 
//=================================================
// HW#: HW3P2 slist
// Name: Andres Hinojosa
// File: Header file slist.h
//=================================================
#include "llist.h"  // for includes, for llist class


class slist : public llist //publicly inherits llist member functions & data members
{

 public:
  
  slist();
  // constructor. cout "in slist constructor".
  // Make it do nothing else.
  // Experiment and see what happens.
  // Taking this out completely would not work.
  // But note that there is no destructor.
  // PLEASE DO NOT delete the couts in slist and llist
  // constructors and destructors for HW6!!!!!

  int search(el_t key);
    // search through the list to see if any node contains the key.
    // If so, return its position (>=1). Otherwise, return 0.

  el_t search2(el_t X);
    
  void replace(el_t element, int pos);
    // go to the Ith node (if I is between 1 and Count) and 
    // replace the element there with the new element. 
    // If I was an illegal value, throw OutOfRange 
    
  bool operator==(const slist& OtherOne);
    // checks to see of the two lists look the same
    
};
