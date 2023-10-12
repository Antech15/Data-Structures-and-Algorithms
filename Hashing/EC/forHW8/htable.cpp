// CS311 Yoshii S22 - Hash Table - complete all ** parts.
// Note: this class does not know the parts of element except for key
// so that it would work even if each element in the hash table changed
//  NEVER delete my comments!!
//-----------------------------------------------------

// ============================================
// HW#: HW8 Hash Table
// Name: Andres Hinojosa
// File Type: implementation htable.cpp
// =============================================

using namespace std;
#include <iostream>
#include "htable.h"

htable::htable()
{}

htable::~htable()
{}

// a simple hash function that uses % TSIZE simply
int htable::hash(string key)
{
  int converted = 0;
  int length = key.length();
  int count = 1;

  for(int i = 0; i < length; i++) //converts the string into an integer
    converted = (converted + (key[i])) + length;

  //IF Statements used to shorten or elongate the key to be 3 integers long
  if(converted > 999)
    {
      while(converted > 999)
	{
	  converted = converted / (length * count);
	  count++;
	}
    }
  else if(converted < 100)
    {
      while(converted < 100)
	{
	  converted = converted * (length * count);
	  count++;
	}
    }

  //cout << "The new key is:" << converted << endl;

  return (converted % TSIZE);  
}

// adds the element to the table and returns slot#
int htable::add(el_t element)
{
  int slot = hash(element.getkey());  // hash with the key part
  (table[slot]).addRear(element);// Note that this means adding the element to a slist in the slot (call addRear)

  return slot;
}

// finds element using the skey and returns the found element itself
// or a blank element  -- there is no cout in here
el_t htable::find(string skey)
{ 
 int slot = hash(skey); // hash with skey
 el_t selement;  // this is the element to look for in slist
 selement.setkey(skey);// initialize selement with just the skey (call setkey)
 selement = table[slot].search2(selement); // call slist's search2 with selement which returns the found element 
 return selement;// return the found element from here (it could be blank)
}

// finds the element given the key  and deletes it from the table.
//  Returns the slot number.
int htable::deleteIt(string key)
{
  int num;
  int slot = hash(key); // hash with skey
  el_t selement;  // this is the element to look for in slist
  selement.setkey(key); //  initialize selement with just the skey
  num = (table[slot]).search(selement); //  call slist's search which gives you the location I and then deleteIth
  (table[slot]).deleteIth(num, selement); 
  return slot; //  return the slot number
}

// fills the table using the specified input file 
void htable::fillTable(istream& fin)
{ 
  string akey;
  string aname;
  string aphone;
  int aage;
  char newl;
  //  model this after HW6 to get data from the file the user specified
  //  which elem and slist functions do you call? List them here first.
  while(fin >> akey) 
    {
      // fin other parts and create an element
      fin >> aname;
      fin >> aphone;
      fin >> aage;
      // YOu can call the add function to add the created element to the table
      el_t temp(akey, aname, aphone, aage);
      
      add(temp);
    }
}

// displays the entire table with slot#s too
void htable::displayTable()
{
  for (int i = 0; i < 37; i++)
    { cout << i << ":" ;   
      table[i].displayAll(); // call slist's displayAll
    }
}

// saves into the specified file in the same format as the input file
void htable::saveTable(ostream& fout) 
{
  el_t temp;

  // for each non-empty slot of the table, retrieve the slist to a local variable
  for(int i = 0; i < TSIZE; i++)
    {
      if(!(table[i]).isEmpty())
	{
	  while(!(table[i]).isEmpty())
	    {
	      // and fout each removed element
	      (table[i]).deleteFront(temp);
	      fout << temp << endl;
	    }
	}
    }
}
