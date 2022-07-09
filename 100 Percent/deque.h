/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a binary search tree
 *        deque::iterator       : An iterator through BST
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once
#include <cstdlib>
#include <iostream>
// Debug stuff
#include <cassert>
#include <iostream>
#include <deque>

class TestDeque;    // forward declaration for TestDeque unit test class

namespace custom
{

/******************************************************
 * DEQUE
 *   0   1   2   3   4
 * +---+---+---+---+---+
 * |   | A | B | C |   |
 * +---+---+---+---+---+
 * iaFront = 1
 * numElements = 3
 * numCapacity = 5
 *****************************************************/
template <class T>
class deque
{
   friend class ::TestDeque; // give unit tests access to the privates
public:

   // 
   // Construct
   //
   deque():data(NULL), numElements(0), numCapacity(0), iaFront(0)
   {
      iaFront =0;
   }
   deque(int newCapacity);
   deque(const deque <T> & rhs);
   ~deque()
   {
      if(numCapacity >0)
      {
         delete[] data;
      }
   }

   //
   // Assign
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator begin()
   {
      return iterator(this, this->iaFront);
   }
   iterator end()
   {
      return iterator(this,(int)this->numElements);
   }

   //
   // Access
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;
   const T & operator[](size_t index) const;
   T& operator[](size_t index);

   // 
   // Insert
   //
   void push_front(const T& t);
   void push_back(const T& t);

   //
   // Remove
   //
   void clear()
   {
      numElements =0;
      numCapacity =0;
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const 
   { 
      return numCapacity;
   }
   bool empty() const 
   { 
      return numCapacity == 0;
   }

   
private:
   
   // fetch array index from the deque index
   int iaFromID(int id) const
   {
      int temp = (int)(this->iaFront + numElements);
      
      if (temp < 0)
         temp = - temp;
      
      int ia = (id+temp)% numCapacity;
      return ia ;
   }


   void resize(int newCapacity = 0);

   // member variables
   T * data;           // dynamically allocated data for the deque
   size_t numCapacity; // the size of the data array
   size_t numElements; // number of elements in the deque
   int iaFront;        // the index of the first item in the array
};



/**********************************************************
 * DEQUE ITERATOR
 * Forward and reverse iterator through a deque, just call
 *********************************************************/
template <typename T>
class deque <T> ::iterator
{
   friend class ::TestDeque; // give unit tests access to the privates
public:
   //
   // Construct
   //
   iterator():id(0)
   {
      
   }
   iterator(custom::deque<T> *pDeque, int id): pDeque(nullptr), id(0)
   {
      this->pDeque = pDeque;
      this->id = id;
   }
   iterator(const iterator& rhs)
   {
      *this = rhs;
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
      this->pDeque = rhs.pDeque;
      this->pDeque->data = rhs.pDeque->data;
      this-> id = rhs.id;
      return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return this->pDeque == rhs.pDeque; }
   bool operator != (const iterator& rhs) const { return this->pDeque != rhs.pDeque; }

   // 
   // Access
   //
   const T & operator * () const
   {
      if(pDeque)
         return pDeque->data[id];
      else
         throw "Error: Deferecning";
   }
   T& operator * () 
   {
      if(pDeque)
         return pDeque->data[id];
      else
         throw "Error: Deferecning";

   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
      return it.id -  this->id;
   }
   iterator& operator += (int offset)
   {
      id+= offset;
      return *this;
   }
   iterator& operator ++ ()
   {
      id++;
      return *this;
   }
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      id++;
      return *this;
   }
   iterator& operator -- ()
   {
      id--;
      return *this;
   }
   iterator  operator -- (int postfix)
   {
      return *this;
   }

private:

   // Member variables
   int id;             // deque index
   deque<T> *pDeque;
};


/****************************************************
 * DEQUE : CONSTRUCTOR - non-default
 ***************************************************/
template <class T>
deque <T> :: deque(int newCapacity): data(nullptr), numElements(0), numCapacity(0), iaFront(0)
{
   if(newCapacity >0)
   {
      data = new T[newCapacity];
      this->numCapacity = numCapacity;
      numElements = numCapacity;
   }
}

/****************************************************
 * DEQUE : CONSTRUCTOR - copy
 ***************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs):numElements(0), numCapacity(0), data(NULL), iaFront(0)
{

   *this = rhs;
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
   iaFront = rhs.iaFront;
   int tempCapacity = (int)numCapacity;
   this->clear();


   if(rhs.size() > tempCapacity)
      resize((int)rhs.numCapacity);
   else
      resize(tempCapacity);
   
   int tempIaFront = rhs.iaFront;
   int count = 0;
   
   if(rhs.iaFront >=0 && rhs.iaFront <(int)rhs.numElements)
   {
      while(count < rhs.numElements)
      {
         if (tempIaFront >= numElements)
            data[count] = rhs.data[tempIaFront % rhs.numElements];
         else
            data[count] = rhs.data[tempIaFront];
      
         tempIaFront++;
         count++;
      }
   }
   else {
      for(int i = ((int)rhs.numElements)-1; i>=0; i--)
      {
         int tempIdx = iaFromID(i);
         data[tempIdx] = rhs.data[i];
      }
   }
   

   numElements = rhs.numElements;
   iaFront  =0;
   
   
      
   return *this;
}


/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
   return data[0];
}
template <class T>
T& deque <T> ::front()
{
   return data[0];
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
   return data[numElements-1];
}
template <class T>
T& deque <T> ::back()
{
   return data[numElements-1];
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
   return data[index];
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
   return data[index];
}

/*****************************************************
 * DEQUE : POP_BACK
 *****************************************************/
template <class T>
void deque <T> :: pop_back()
{
   int temp = data[numElements-1];
   data[temp] = NULL;
   numElements--;
}

/*****************************************************
 * DEQUE : POP_FRONT
 *****************************************************/
template <class T>
void deque <T> :: pop_front()
{
   int temp = front();
   data[temp]= NULL;
   numElements--;
   iaFront++;
}

/******************************************************
 * DEQUE : PUSH_BACK
 ******************************************************/
template <class T>
void deque <T> :: push_back(const T & t) 
{
   if(numCapacity == 0)
      resize(1);
   else if (numElements == numCapacity)
      resize((int)numCapacity*2);
   
   data[numElements++] = t;
   iaFront =0;
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) 
{
   if(numCapacity == 0)
      resize(1);
   
   else if(numElements == numCapacity)
      resize((int)numCapacity*2);
   
   data[numCapacity-1] = t;
   numElements++;
   iaFront =-1;
   
}

/****************************************************
 * DEQUE :: GROW
 * If the deque is currently empty, allocate to size 2.
 * Otherwise, double the size
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) 
{
   
   if(newCapacity <= numCapacity)
      return;
   
   T* pNew = new T[newCapacity];
   
      
   for(int i =0; i < numElements; i++)
         pNew[i] = data[i];
   

   
   delete[] data;
   
   data = pNew;
   
   numCapacity = newCapacity;
}

} // namespace custom
