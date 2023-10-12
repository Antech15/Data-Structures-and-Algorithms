//CS311 Yoshii S22 Linked List class

//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//  You can copy from a Word document to emacs (contrl-right click)
//  Highly recommended to copy HW3P1-help as PURPOSE of each function.
//
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//  NEVER delete my comments!!!!
//EMACS HINT:
//  cntr-K cuts and cntr-Y pastes. 
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Andres Hinojosa
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include"llist.h" 

//PURPOSE: This function initializes count, front and rear
llist::llist()
{ 
  //cout << "calling the llist constructor" << endl; 

 Count = 0;
 Front = NULL;
 Rear = NULL;
}

//PURPOSE: This function deletes all nodes until LL is empty
llist::~llist()
{ 
  //cout << "calling the llist destructor" << endl; 

 while(!isEmpty()) //while nodes still exist
   {
     el_t temp; //holds an element
     deleteFront(temp);
   }
}

//PURPOSE: This function checks to see if the list is empty by checking
//count, front, and rear
//PARAMETER: None
bool llist::isEmpty() // be sure to check all 3 data members
{
  if(Count == 0 && Front == NULL && Rear == NULL) //if it is empty returns true
    return true;
  else
    return false;
}

//PURPOSE: This function displays all the elements in the list
//using a while loop. If empty, it shows "empty" instead.
//PARAMETER: None
void llist::displayAll()  // be sure to display horizontally in [  ] with
// blanks between elements e.g. [ 1 2 3 4]
// You MUST use while (P != NULL) loop or you will not get the credit!
{
  if(isEmpty()) //if empty displays message
    cout << "[empty]" << endl;
  else //if not empty, displays all elements
    {
      Node* P = Front; //temporary node will go through all nodes
      cout << "[";
      while(P != NULL)//while P isnt pointing to NULL
	  {
	    cout << P -> Elem << ", ";
	    P = P -> Next; //P visits all nodes
	  }
	cout << "]" << endl;
    }
}

//PURPOSE:Adds a Node to the rear of LL. If it is empty,
//There is a different way the Node is added.
//PARAMETER: el_t NewNum passes the element to be added by value
void llist::addRear(el_t NewNum) // comment the 2 cases
{
  if(isEmpty()) //Case 1 (special): It is the first node
    {
      Front = new Node; //New node becomes front and rear
      Front->Elem = NewNum;
      Rear = Front;
    }
  else //Case 2: Regular case
    {
      Rear -> Next = new Node; //New node becomes Rear
      Rear = Rear -> Next;
      Rear -> Elem = NewNum;
    }
  Rear -> Next = NULL;
  Count++;
}

//PURPOSE: Adds a Node to the Front of LL. If it is empty,
//There is a different way the Node is added.
//PARAMETER: el_t NewNum passes the element to be added by value
void llist::addFront(el_t NewNum) // comment the 2 cases
{
  if(isEmpty())//Case 1 (special): It is the first node
    {
      Front = new Node; //adds node which is both front and rear
      Front->Elem = NewNum;
      Rear = Front;
      Rear -> Next = NULL;
    }
  else //Case 2: Regular case
    {
      Node* temp = new Node; //
      temp -> Elem = NewNum;
      temp -> Next = Front;
      Front = temp;
    }
  Count++;
}

//PURPOSE: This function deletes the node at the front of the LL if it
//Has one (case 2) or more (case 3) nodes. If it is empty, it displays an error instead.
//PARAMETER: el_t& OldNum passes back the element deleted by reference
void llist::deleteFront(el_t& OldNum) // comment the 3 cases
{
  if(isEmpty()) //Case 1 (error): If it is empty, throws exception
    throw Underflow();
  else if(Front -> Next == NULL && Count == 1) //Case 2: If it is going to make the LL empty
    {
      OldNum = Front -> Elem;
      delete Front;
      Front = Rear = NULL;
    }
  else //Case 3 (regular)
    {
      OldNum = Front -> Elem;
      Node* Second = Front -> Next; //Gets second Node to become Front
      delete Front;
      Front = Second;
    }
  Count--;
}
//PURPOSE: This function deletes the node at the Rear of LL if it
//has one (case 2) or more (case 3) nodes. If empty, throws exception.
//PARAMETER: el_t& OldNum passes back the element deleted by reference
void llist::deleteRear(el_t& OldNum) // comment the 3 cases
{
  if(isEmpty()) //Case 1 (error): If it is empty, throws exception
    throw Underflow();
  else if(Front -> Next == NULL && Count == 1) //Case 2: If it is going to make the LL empty
    {
      OldNum = Rear -> Elem;
      delete Rear;
      Front = Rear = NULL;
    }
  else //Case 3 (regular)
    {
      OldNum = Rear-> Elem;
      Node* P = Front;
      while(P->Next != Rear) //P gets second to last Node 
	{
	  P = P->Next;
	}
      delete Rear;
      Rear = P;
      Rear -> Next = NULL;
    }
  Count--;
}
//--- harder ones for case 2 and 3 follow -- 

// Utility Function to move a local pointer to the Jth node
// moves temp J-1 times to go to the Jth node
// for ( int K = ... ) temp = temp->Next;
//PURPOSE: This Function moves a temporary pointer to the Jth node and returns it by reference
//PARAMETER: J is the node the user wants temp to point at. temp is a Node pointer that will point to the Jth node
void llist::moveTo(int J, Node*& temp)
{
  temp = Front;
  for(int K = 1; K <= J-1; K++) // loop makes temp visit each node until it reaches the Jth node
    temp = temp -> Next;
}

//PURPOSE: This function deletes the Ith node from the list and returns its element by reference.
// It calls deleteFront and deleteRear if I is 0 or Count, It gives an error if I is out of range.
//PARAMETER: I is the node the user wants to delete, OldNum gives back the element of the deleted node
void llist::deleteIth(int I, el_t& OldNum) // must use moveTo to move local pointers. Be sure to comment to which node you are moving them. Do not forget to set OldNum.  
{
  if(I > Count || I < 1) //If I is out of range throws exception (case 1)
    throw OutOfRange();
  else if(I == 1) //If I is 1 (case 2)
    deleteFront(OldNum);
  else if(I == Count) //If I is Count (case 3)
    deleteRear(OldNum);
  else //regular process (case 3)
    {
      Node* left; //pointer to the left of I
      Node* right; //Pointer to the right of I
      Node* del; //Ith node, to be deleted

      moveTo(I - 1, left); //moves pointers to correct spot
      moveTo(I + 1, right);
      moveTo(I, del);

      OldNum = del -> Elem; //returns elem and makes the left point to right
      left -> Next = right;
      Count--;

      delete del;
    }
}
//PURPOSE: This function inserts a node to the Ith position. It calls addFront ot addRear if I is 1 or
//Count + 1. Throws an exception error if I is out of range.
//PARAMETER: I is the position the node will be in. newNum is the element that goes in the new node.
void llist::insertIth(int I, el_t newNum) // must use moveTo to move local pointers. Be sure to comment to which node you are moving them.
{
  if(I > Count + 1 || I < 1) //Case 1: I is out of range
    throw OutOfRange();
  else if(I == 1) //Case 2: I is the first Node
    addFront(newNum);
  else if(I == Count + 1) //Case 3: I is the Node after rear
    addRear(newNum);
  else //Case 4: regular
    {
      Node* temp = new Node; //new pointer to a node with newNum
      Node* left; //pointer to the left of I
      Node* right; //Pointer to the right of new node

      moveTo(I - 1, left); //moves nodes to correct place
      moveTo(I, right);

      temp -> Elem = newNum; //new node gets newnum, then goes in between left and right
      left -> Next = temp;
      temp -> Next = right;

      Count++;
    }
}
//PURPOSE: This function creates a new linked list that copies the Original list passed.
//PARAMETER: Original is the list the constructor will copy.
llist::llist(const llist& Original) // use my code
{
  this -> Front = NULL; this -> Rear = NULL; this -> Count = 0; //data members initialized

  Node* P; //Pointer to original's first
  P = Original.Front;

  while(P != NULL) //copies all nodes from original
    {
      this -> addRear(P -> Elem);
      P = P->Next;
    }
}
//PURPOSE: This function overloads = to make a list equal to another by copying
//the elements.
//PARAMETER: OtherOne is the list to the right of the operator which will be copied
llist& llist::operator=(const llist& OtherOne) // use my code
{
  el_t x; //temporary element holder
  if(&OtherOne != this) //if they are not the same
    {
      while(!this -> isEmpty()) //while list is not empty, empties it
	this -> deleteRear(x);

      Node* P; //pointer to otherone's front
      P = OtherOne.Front;

      while(P != NULL) //copies all elements to the list
	{
	  this -> addRear(P -> Elem);
	  P = P->Next;
	}
    }
  return *this; //returns the new copied list 
}

