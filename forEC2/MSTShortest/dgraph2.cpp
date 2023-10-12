// CS311 Yoshii S22 - MST and Shortest Path Extra Credit dgraph2.cpp
// linked list classes should have been updated to use elem.h
//----------------------------------------------------------

// ========================================
// EC on Shortest Path and MST
// Name: Andres Hinojosa
// File: dgraph2.h implementation
// =========================================

using namespace std;
#include "dgraph2.h"
#include <fstream>
#include <string>

dgraph::dgraph()
{ count = 0;

  for(int i = 1; i <= MAX; i++)
    {
      G[i-1].Name = ' '; //initializing all chars
      G[i-1].Visit = 0;
      G[i-1].DistTo = 0;
      G[i-1].From = ' ';
      G[i-1].Kind = ' ';
    }

 }

dgraph::~dgraph() 
{ count = 0;}

// fill the table with a file content
void dgraph::filltable()
{
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;
  ifstream fin (filename.c_str(), ios::in);
  char n;  // note that you need to create el_t object before adding to list
  int w;

  while(fin >> G[count].Name) //If I can read the name
    {

      cout << "read " << G[count].Name << " ";

      fin >> G[count].Out;
      for(int i = 0; i < G[count].Out; i++) //adds to slist
        {
          fin >> n;
	  fin >> w;
	  
	  el_t e(n, w);

          (G[count].Adj).addRear(e); //function form HW3
        }
      count++;
    }

  cout << endl;

  fin.close();
}

// display the table in a very readable format
void dgraph::displayTable()
{
  cout << "Name Kind Dist From" << endl;

  for(int i = 1; i <= count; i++) //displays all used rows
    {
      cout << G[i-1].Name << "    " << G[i-1].Kind << "    " << G[i-1].DistTo << "    " << G[i-1].From << "    ";
      (G[i-1].Adj).displayAll();
    }
  
}


// is everyone in the Tree?
bool dgraph::allTree()
{

  for(int i = 0; i < count; i++)
    {
      if(G[i].Kind != 'T') //if at least one is not T, return false
	 return false;
    }
  return true;
}

// find the edges in the MST (at the end)
void dgraph::displayMST()
{ cout << "Edges in the MST are:" << endl;
  
  for(int i = 0; i < count; i++) //for loop to display edges
    {
      if((G[i].From) != ' ')
	cout << "From " << (G[i].From) << " to " << (G[i].Name) << " with " << (G[i].DistTo) << endl;
    }
}

// retrieve and display the shortest path to V 	(at the end)
void dgraph::displayPath(char V)
{ cout << "Edges in the shortest path are:" << endl;
 
  char next = G[V - 'A'].From;

  cout << V;

  while(next != ' ') //goes through all used slots
    {
      cout << "<-----" << next;

      next = G[next - 'A'].From; //shows path
    }
  cout << endl;
}


// find the fringe vertex with the smallest DISTO. 
// return the location in the table.
int dgraph::findSmallest()
{

  int num = MAX;
  int loc;

  for(int i = 1; i < count; i++) //for loop saves and returns location with smallest DISTO
    {
      if((G[i].DistTo < num) && (G[i].DistTo != 0) && (G[i].Kind != 'T'))
	{
	  num = G[i].DistTo;
	  loc = i;
	}
    }
  return loc;
}
   
// Adding i's vertex to tree (T)
// causing more Fringe vertices to be added
void dgraph::makeTree(int i)
{ 
  cout << "Adding " << G[i].Name << " to tree" << endl; 
  G[i].Kind = 'T'; // Make it T
  slist a = G[i].Adj; // get all adjacent vertices 
  // calls makeFringe on each adjacent vertex 
  el_t v;
  if(!a.isEmpty())
    {
      
      a.displayAll();
      
      while(!a.isEmpty()) //while is not empty
	{
	  a.deleteRear(v); //put adjacent ones on the stack

	  if(G[(v.getname())-'A'].Kind != 'T')
	    makeFringe(v, G[i].Name, G[i].DistTo);	  
	}
    }
}

// Utility: Enter or update the DISTO of a fringe vertex
void dgraph::makeFringe(el_t X, char V, int soFar)
{ 
  // X is the fringe vertex (a node's Elem from slist)
  // V is which tree vertex the edge came from
  // soFar is the distance to V so far (used for shortest path only)

  char n = (X.getname())-'A';

  if(G[n].Kind == ' ')
    {
      cout << "New Fringe: " << X.getname() << " with weight: " << X.getweight() << endl;

      G[n].Kind = 'F';

      //FOR SHORTEST PATH
      //G[n].DistTo = X.getweight() + soFar;

      //FOR MST
      G[n].DistTo = X.getweight();
      
      G[n].From = V;      
    } 
  else
    {
      cout << "Old Fringe: " << X.getname() << " with edge cost: " << X.getweight() << endl;

      //for MST
      if(X.getweight() < G[n].DistTo)
	{
	  G[n].DistTo = X.getweight();
	  G[n].From = V;
	}
    }
}


