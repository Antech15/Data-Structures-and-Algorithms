// CS311 Yoshii S22 slist.cpp
// Complete all functions with their comments
// NEVER delete my comments!!
// ====================================================
//HW#: HW8 hash
//Your name: Andres Hinojosa
//Complier:  g++
//File type: slist.cpp implementation file
//=====================================================
using namespace std;
#include <iostream>
#include"slist.h" 

// ** Make sure llist constructor and destructors have couts in them


// do not change this one
//Constructor
slist::slist()
{ /*cout << "slist constructor:" << endl;*/}


// positions always start at 1
//PURPOSE: This function searches the list using a for loop
//and returns the position where key is found, if not found, returns 0
//PARAMETERS: key is the element passed by value to be found in the list
int slist::search(el_t key)
{
  Node* P = Front; //temporary pointer starts at front

  for(int K = 1; K <= Count; K++) //goes through all nodes
    {
      if(P -> Elem == key) //if found, return position
	return K;
      
      P = P -> Next;
    }
  return 0; //if not found
}


//PURPOSE: This function searches the list using a for loop
//and returns the elememt where key is found, if not found, returns an empty element
//PARAMETERS: X is the element passed by value to be found in the list
el_t slist::search2(el_t X)
{
  el_t M; //blank

  Node* P = Front; //temporary pointer starts at front

  for(int K = 1; K <= Count; K++) //goes through all nodes
    {
      if(P -> Elem == X) //if found, return position
        return P -> Elem;
    
      P = P -> Next;
    }
  return M;
}

// don't forget to throw OutOfRange for bad pos 
// You must use moveTo to go to the pos
//PURPOSE: This function uses moveTo to replace
//the element in a certain position.
//PARAMETERS: element is the replacement of elem.
//pos, is the position of the element to be replaced 
void slist::replace(el_t element, int pos)
{
  if(pos > Count || pos < 1) //if pos is out of bounds throws exception
    throw OutOfRange();
  else //if can be replaced
    {
      Node* P; //temporary pointer

      moveTo(pos, P); //gets the node

      P -> Elem = element; //replaces elem
    }
}

//PURPOSE: This function overloads '==' so that
//it is able to check if two lists are the same
//PARAMETERS: Otherone is the list to the right of
//the operator
bool slist::operator==(const slist& OtherOne)
{
  // if not the same length, return false immediately
  // if the same lengths,
  //check each node to see if the elements are the same

  if(this -> Count != OtherOne.Count)//if different lengths, return false
    return false;
  else //if same length
    {
      Node* P = this -> Front; //temporary nodes point to both fronts
      Node* Q = OtherOne.Front;

      for(int K = 1; K <= this -> Count; K++) //for loop goes through every node
	{
	  if(P -> Elem != Q -> Elem) //if elements aren't equal, returns false
	    return false;

	  P = P -> Next; //goes to next node
	  Q = Q -> Next;
	}
      return true; //returns true if all nodes are the same
    }
}

