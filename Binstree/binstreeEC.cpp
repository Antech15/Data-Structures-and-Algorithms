// CS311 YOSHII S22 binstree.cpp
// This is the BST implementation file template by Rika Yoshii

// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.  Couts are there to test to make sure
// you set the Up links correctly!!!! (Fall 19)
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// DO not delete the ** comments, but add the code next to them
// Make sure all { } match. Doing Tab on each line helps.
// Draw pictures as you complete each **
//  NEVER delete my comments!!!!
// =========================================================
//HW#: HW4 BST
//Your name: Andres Hinojosa
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================
#include<iostream>
#include "binstreeEC.h"
using namespace std;



// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;    
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) 
    {
      dtraverse(V->Left);         // destroy left sub tree of V
      dtraverse(V->Right);       //  destroy right sub tree of V
      delete V;                  //  delete V
    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  cout << "--- Elements in the IN order: ---" << endl;
  cout << "Root is: " << Root->Elem << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
  cout << "---------------------------------" << endl;
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 

void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      INorderTraversal(V->Left); //  traverse left sub-tree of V recursively
      cout << V->Elem << "\tHeight: " << V->Height << " Balance: " << V->Balance << endl; //  display V's element, height and balance and do endl; 
      INorderTraversal(V->Right); //  traverse right sub-tree of V recursively
  }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
//PARAM: K is the element to be found
bool BST::Search(el_t K)
{
  PREorderSearch(Root, K);  // start pre-order traversal from the root
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
  if (V != NULL)
    {
      if (K == V->Elem) return true; // found the element in V

      else if (K <  V->Elem) 
	PREorderSearch(V->Left, K); // traverse left sub-tree of V recursively

      else 
	PREorderSearch(V->Right, K); // traverse right sub-tree of V recursively
    }
  else return false;
}

// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
   Vertex *N;         // N will point to the new vertex to be inserted
   N = new Vertex;    // a new vertex is created
   N->Left  = NULL;   // make sure it does not
   N->Right = NULL;   // point to anything
   N->Elem  = E;      // put element E in it
   N->Height = 0;
   N->Balance = 0;
   N->Up = NULL;      // no parent for now
   cout << "Trying to insert " << E << endl;

   if (Root == NULL)  // Special case: we have a brand new empty tree
     {
       Root = N;      // the new vertex is added as the root
       cout << "...adding " << E << " as the root" << endl; 
     }// end of the special case
   
   else  // the tree is not empty
     {
       Vertex *V;       // V will point to the current vertex
       Vertex *Parent;  // Parent will always point to V's parent
       
       V = Root;        // start with the root as V
       Parent = NULL;   // above V so it does not point to anything  
       
       // go down the tree until you cannot go any further        
       while (V != NULL)
	 {
	   if (N->Elem == V->Elem) // the element already exists
	     {
	       cout << "...error: the element already exists" << endl;
	       return;
	     }
	   else
	     if (N->Elem < V->Elem)  // what I have is smaller than V
	       {  
		 cout << "...going to the left" << endl; 
		 Parent = V; //  change Parent to be V to go down 
		 V = V->Left; // change V to be V's Left 
	       }
	     else // what I have is bigger than V
	       {  
		 cout << "...going to the right" << endl;
		 Parent = V; // change Parent to be V to go down
		 V = V->Right; // change V to be V's Right 
	       }
	 }//end of while
       
       // reached NULL -- Must add N as the Parent's child
       
       if (N->Elem < Parent->Elem)  
	 {  
	   Parent->Left = N; // Parent's Left should point to the same place as N 
	   cout << "...adding " << E << " as the left child of " 
		<< Parent->Elem << endl;
	   N->Up = Parent; // N must point UP to the Parent 
	   cout << N->Elem  << " now points UP to " << N->Up->Elem << endl;   
	   //** EC call here to adjust height and BF	
	   climbup(N);
	 }
       else 
	 {
	   Parent->Right = N; // Parent's Right should point to the same place as N 
	   cout << "...adding " << E << " as the right child of " 
		<< Parent->Elem << endl;
	   N->Up = Parent; // N must point UP to the Parent 
	   cout << N->Elem << " now points UP to " << N->Up->Elem << endl;   
	   //** EC call here to adjust height and BF
	   climbup(N);
	 }
       
     }// end of normal case
   
}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove 
void BST::DeleteVertex(el_t E)
{
  cout << "Trying to delete " << E << endl;
  
  Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent

  // case 1: Lonely Root  --------------------
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
    { cout << "...deleting the lonely root" << endl;
      delete Root; 
      Root = NULL;
      return; }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root ----------------
  else if(E == Root->Elem) // if what you want to delete is the root
  { cout << "... deleting the root with just one child" << endl; 
    if((Root->Right == NULL) && (Root->Left != NULL))// and it has only the left subtree
    {  //   change the root to the left child and return
      //   making sure the old root has been deleted and the new root's UP is NULL
      V = Root;
      Root = Root->Left;
      delete V;
      Root->Up = NULL;
      return; 
    }
    else if((Root->Left == NULL) && (Root->Right != NULL)) // and it has only the right subtree
    { // change the root to the right child and return
      // making sure the old root has been deleted and the new root's UP is NULL 
      V = Root;
      Root = Root->Right;
      delete V;
      Root->Up = NULL;
      return;
    }
  }// end of deleting the root with one subtree
  
  // ---- Otherwise deleting something else  --------------
  
  V = Root;  // start with the root to look for E
  Parent = NULL;  // above the V so does not point to anything yet

  // going down the tree looking for E
  while (V != NULL)
    { 
      if (E == V->Elem)   // found it
	{ cout << "...removing " << V->Elem << endl;
	  remove(V, Parent); // call remove here to remove V
	  return; 
	}
      else
	if (E < V->Elem)
	  {  cout << "...going to the left" << endl;
	    Parent = V; // update Parent and V here to go down
	    V = V->Left; 
	  }
	else
	  {  cout << "...going to the right" << endl;
	    Parent = V; // update Parent and V here to go down
	    V = V->Right;
	  }
      
    }// end of while
  
  // reached NULL  -- did not find it
  cout << "Did not find the key in the tree." << endl;
  
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  if((V->Left == NULL) && (V->Right == NULL)) // if V is a leaf (case 1)
    {
      cout << "removing a leaf" << endl;
      if(P->Left == V) // if V is a left child of P
	{
	  delete V; // delete V and also make Parent's left NULL
	  P->Left = NULL; 
          // ** EC call here from P to adjust height and BF  
	  climbup(P);	  
	}
      else // V is a right child of the Parent
	{ 
	  delete V; // delete V and also make Parent's right NULL
	  P->Right = NULL; 
          // ** EC call from P to adjust height and BF
	  climbup(P);
	}
    }//end of leaf case
  
  else if((V->Left != NULL) && (V->Right == NULL)) // if V has just the left child so bypass V (case 2)
    {    Vertex* C = V->Left; // C is the left child
      cout << "removing a vertex with just the left child" << endl;
      if(P->Left == V)// You need if then else to determine Parent's left or right
	P->Left = C;//    should point to C; 
      else
	P->Right = C;
      
      C->Up = P; // Make C point UP to the parent;
      cout << C->Elem << " points up to " << C->Up->Elem << endl;
      delete V; // Be sure to delete V
      //** EC call from P to adjust height and BF
      climbup(P);
    }// end of V with left child       
  
  else if((V->Right != NULL) && (V->Left == NULL)) // if V has just the right child so bypass V (case 2)
    {    Vertex* C = V->Right;  // C is the right child
      cout << "removing a vertex with just the right child" << endl;
      if(P->Left == V) // You need if then else to determine Parent's left or right
	P->Left = C;//    should point to C;
      else
	P->Right = C;
      
      C->Up = P; // Make C point UP to the parent;   
      cout << C->Elem << " points up to " << C->Up->Elem << endl;
      delete V; // Be sure to delete V
      //** EC call from P to adjust height and BF
      climbup(P); 
    }//end of V with right child
  
  else // V has two children (case 3)
    { cout << "removing an internal vertex with children" << endl;
      cout << "..find the MAX of its left sub-tree" << endl;
      el_t Melem;
      // find MAX element in the left sub-tree of V
      Melem = findMax(V); 
      cout << "..replacing " << V->Elem << " with " << Melem << endl;
      V->Elem = Melem; // Replace V's element with Melem here
    }//end of V with two children
  
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
//PARAM: V is the parent of the max node we want to find
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  while(V->Right != NULL) // while the right child of V is still available
    {
      Parent = V; // update Parent and V to go to the right
      V = V->Right;
    }
  
  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
  
}// end of FindMax

// Climbs up from the vertex to compute Height and Balance Factor
// of all ancestors and displays them as they are computed.
// This should be called whenever a vertex (N) is inserted
// This should be called whenever a vertex is deleted (i.e. delete V)
void BST::climbup(Vertex* V)
{
  cout << "...Start climbing up to adjust heights ......" << endl;
  while (V != NULL)
    {
      // ** compute V->Height based on the left/right children's heights
      if((V->Left == NULL) && (V->Right == NULL)) //If it is a leaf, gets 0
	  V->Height = 0;
      else if(V->Right == NULL)	//if left or right is NULL, add 1 from other leaf
	  V->Height = (V->Left->Height) + 1;	
      else if(V->Left == NULL)	
	  V->Height = (V->Right->Height) + 1;  
      else if(((V->Left->Height) >= (V->Right->Height)))   //adds 1 from the leaf with the greater value
	  V->Height = (V->Left->Height) + 1;   	
      else    
	  V->Height = (V->Right->Height) + 1;	

      // ** compute V->Balance based on the left/right children's heights
      if((V->Left == NULL) && (V->Right == NULL)) //If it is a leaf, BF gets 0
        V->Balance = 0;
      else if(V->Right == NULL)   //if Left or Right is NULL, adds 1 or deletes 1 from other height
	V->Balance  = -1 - (V->Left->Height);
      else if(V->Left == NULL)
	V->Balance  = (V->Right->Height) + 1;
      else    //deletes the right from the left
	V->Balance = (V->Right->Height) - (V->Left->Height);

      cout << "..." << V->Elem << "'s height: "
	   << V->Height << " with balance: "
	   << V->Balance << endl;
      if(V->Balance == -2 || V->Balance == 2)
	fixIt(V);
      //go up to the parent

      V = V->Up;

    }
}

//This function fixes an unbalanced tree by calling the appropriate rotations about Red
// Red is where +2 or -2 was found
void BST::fixIt(Vertex* Red)
{ cout << ">>>Fixing an unbalanced node at " << Red->Elem << endl;

  Vertex* Pivot;
  bool tf;
  if (Red->Balance == 2 && Red->Right->Balance == 1) // case 1
    {
      cout << "   case 1: right heavy so rotate to left" << endl;
      Pivot = rotateLeft(Red);
    }
  // handle all other cases here
  
  if (Red->Balance == -2 && Red->Left->Balance == -1) // case 2
    {
      cout << "   case 2: left heavy so rotate to right" << endl;
      Pivot = rotateRight(Red);
    }
      
  if (Red->Balance == 2 && Red->Right->Balance == -1) // case 3
    {
      cout << "   case 3: right heavy with left heavy subtree" << endl;
      rotateRight(Red->Right);
      Pivot = rotateLeft(Red);
    }
  
  if (Red->Balance == -2 && Red->Left->Balance == 1) // case 4
    {
      cout << "   case 4: left heavy with right heavy subtree" << endl;
      rotateLeft(Red->Left);
      Pivot = rotateRight(Red);
    }
 

  if (Root == Red)
    { Root = Pivot; // new Root
      cout << "   New root is: " << Root->Elem << endl;}
  cout << ">>>Fixed" << endl;
  Display();
}
  
//This function rotates three nodes to the left from Red
//Red is where +2 or -2 was found
Vertex* BST::rotateLeft(Vertex* Red)
{
  Vertex* Pivot;

  Pivot = Red-> Right; ///gets pivot
  
  Pivot->Up = Red->Up; //pivot gets new up
  
  if(Red->Up != NULL) //if Red's up is not null
    {   
      if(Pivot->Elem > Red->Up->Elem)//Compares pivot and red's up
	Red->Up->Right = Pivot; //if pivot > Red-> Up
      else //if Pivot < Red->Up
	Red->Up->Left = Pivot;
	}
  if(Pivot->Left != NULL) //if pivot has a left child Y
    {
      Red -> Right = Pivot -> Left; //Y
      Red->Right->Up = Red;
    }
  else // if pivot has no child
    Red->Right = NULL;
  
  Pivot -> Left = Red; //red comes down
  
  Red->Height = 0; //base heights
  Pivot->Height = 1;
  if(Red->Left != NULL || Red->Right != NULL)//if red has any children, heights are +1
    {
      Red->Height = 1;
      Pivot->Height = 2;
    }
  
  Red->Balance = 0; //new BF
  Pivot -> Balance = 0; 

  Red->Up = Pivot; //new up for red

  return Pivot;
}

//This function rotates three nodes to the right from Red
//Red is where +2 or -2 was found
Vertex* BST::rotateRight(Vertex* Red)
{
  Vertex* Pivot;
  Pivot = Red-> Left; ///gets pivot

  Pivot->Up = Red->Up; //pivot gets new up

  if(Red->Up != NULL) //if red's up is not null
    {
      if(Pivot->Elem > Red->Up->Elem) //compares picot and Red->Up if it exists
	Red->Up->Right = Pivot; //if pivot > Red-> Up
      else //if pivot < Red-> Up
	Red->Up->Left = Pivot;
    }

  if(Pivot->Right != NULL) //if pivot has a left child Y
    {
      Red -> Left = Pivot -> Right; //Y
      Red->Right->Up = Red;
    }
  else // if pivot has no child
    Red->Left = NULL;

  if((Red->Elem) > (Pivot->Elem)) //if Red > Pivot
    Pivot -> Right = Red; //red comes down to right of pivot
  else //if Red < Pivot
    {
      Pivot->Left = Red; //Red comes down to left of pivot
      Red->Right = NULL; //Red's right is now null
    }
  
  Red->Height = 0; //base heights
  Pivot->Height = 1;
  if(Red->Left != NULL || Red->Right != NULL)//if red has any children, heights are +1
    {
      Red->Height = 1;
      Pivot->Height = 2;
    }

  Red->Balance = 0; //new BF //change
  Pivot -> Balance = 0;

  Red->Up = Pivot; //new up for red
  
  return Pivot;
}
