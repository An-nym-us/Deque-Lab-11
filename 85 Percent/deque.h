/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque 
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a binary search tree
 *        deque::iterator       : An iterator through BST
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>  // for assert()
#include <list>     // for std::list

class TestDeque;    // forward declaration for TestDeque unit test class

namespace custom
{

/******************************************************
 * DEQUE
 *****************************************************/
template <typename T>
class deque
{
   friend class ::TestDeque; // give unit tests access to the privates
public:

   // 
   // Construct
   //
   deque() 
   { 
   }
   deque(deque& rhs)
   {
   }
   ~deque()
   {
   }

   //
   // Assign
   //
   deque & operator = (deque& rhs)
   {
      return *this;
   }

   // 
   // Iterator
   //
   class iterator;
   iterator begin() 
   { 
      return iterator(); 
   }
   iterator end()   
   { 
      return iterator(); 
   }

   // 
   // Access
   //
   T & front()       
   { 
      return *(new int(90));
   }
   const T & front() const 
   {
      return *(new int(90));
   }
   T & back()
   {
      return *(new int(90));
   }
   const T & back() const
   {
      return *(new int(90));
   }


   //
   // Insert
   //
   void push_back(const T& t)
   {
   }
   void push_back(T && t)
   {
   }
   void push_front(const T& t)
   {
   }
   void push_front(T&& t)
   {
   }

   //
   // Remove
   //
   void pop_front()
   {
   }
   void pop_back()
   {
   }
   void clear()
   {
   }

   //
   // Status
   //
   size_t size()  const { return 99; }
   bool   empty() const { return false; }
   
private:
   std::list <T> container;
};

/**************************************************
 * DEQUE ITERATOR
 * An iterator through deque.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <typename T>
class deque <T> ::iterator
{
   friend class ::TestDeque; // give unit tests access to the privates
public:
   // 
   // Construct
   //
   iterator() 
   {
   }
   iterator(typename const std::list<T>::iterator& itList) 
   {
   }
   iterator(const iterator& rhs) 
   { 
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
      return *this;
   }

   // 
   // Compare
   //
   bool operator != (const iterator& rhs) const { return true; }
   bool operator == (const iterator& rhs) const { return true; }

   // 
   // Access
   //
   T& operator * ()
   {
      return *(new int(50));
   }

   // 
   // Arithmetic
   //
   iterator& operator ++ ()
   {
      return *this;
   }
   iterator operator ++ (int postfix)
   {
      return *this;
   }
   iterator& operator -- ()
   {
      return *this;
   }
   iterator operator -- (int postfix)
   {
      return *this;
   }

private:
   typename std::list<T>::iterator it;
};




} // namespace custom
