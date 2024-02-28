/*
LL.cpp
 - Utilizes various linked list concepts
    - Creation of linked list
    - Setting data into the nodes of the linked list
    - Tail insert = inserting a deck of cards to the end of another deck
    - Head removal = removing a deck of cards (those that are faced up) from the rest of its' pile
*/

#include "LL.h"
#include <iostream>
using namespace std;

template <class type>
LL<type>::LL(const LL<type> &copy)
{
  this->head = nullptr;
  this->tail = nullptr;

  node *copyHeadNode = copy.head;

  while (copyHeadNode != nullptr)
  {
    tailInsert(copyHeadNode->data);
    copyHeadNode = copyHeadNode->next;
  }
}

// Deep copy of rhs's template linked list object
template <class type>
const LL<type> &LL<type>::operator=(const LL<type> &rhs)
{
  if (this != &rhs)
  {
    // Create a node that will copy the contents of the object passed in
    node *copyRhs = new node();

    copyRhs->data = rhs.head->data;
    copyRhs->prev = nullptr;
    copyRhs->next = nullptr;

    if (this->head != nullptr)
    {
      // If the head and tail are equal, meaning there is only one item in the list
      if (this->head == this->tail)
      {
        delete this->head;
      }
      else
      {
        // Create a node to parse through the list
        node *nodeParse = this->head->next;

        // While loop while the node is not at the object's tail
        while (nodeParse != this->tail)
        {
          // Deallocate memory from the previous node
          delete nodeParse->prev;

          // Set the parse node to the next node in the list
          nodeParse = nodeParse->next;
        }

        // Once the parsing node equals the tail, we know we are at the end of the list
        // Thus, we have deallocated all the nodes up until the tail node
        delete nodeParse->prev;
        delete nodeParse;
      }
    }

    // Set the copyRhs to the head
    this->head = copyRhs;

    // Creating a node to parse through the copy starting at head
    node *parseNode = rhs.head;

    // Creating a node to parse through the deep copy
    node *copyNodeParsed = copyRhs;

    // While loop for until the parse node hits the copy's tail pointer
    while (parseNode != rhs.tail)
    {
      node *temp = new node();

      temp->data = parseNode->next->data;
      temp->prev = copyNodeParsed;
      temp->next = nullptr;

      // Set the deep copy parse node's next to the copy node's next
      copyNodeParsed->next = temp;
      // Set the deep copy parse node to the next node
      copyNodeParsed = temp;
      // Set the copy's parsed node to the next node
      parseNode = parseNode->next;
    }

    // Set the this' tail to the nodeParsedCopy node
    this->tail = copyNodeParsed;
  }
  return *this;
}

// Destructor of templated LL class
template <class type>
LL<type>::~LL()
{
  if (this->head != nullptr)
  {
    // if the head and tail are equal, meaning there is only one item in the list
    if (this->head == this->tail)
    {
      delete this->head;
    }
    else
    {
      // Deallocation of linked list
      node *nodeParse = this->head->next;

      while (nodeParse != this->tail)
      {
        delete nodeParse->prev;

        nodeParse = nodeParse->next;
      }

      delete nodeParse->prev;
      delete nodeParse;
    }
  }
}

// Creates a node object and inserts it to the back of the end of the linked list
template <class type>
void LL<type>::tailInsert(const type &data)
{
  node *insertNode = new node();
  insertNode->data = data;

  // If inserting to a blank linked list
  if (this->head == nullptr)
  {
    // Set the insertNode prev and next to nullptr
    insertNode->prev = nullptr;
    insertNode->next = nullptr;

    // Set current head to insertNode
    this->head = insertNode;

    // Set currect tail to insertNode
    this->tail = insertNode;
  }
  else
  {
    // If the linked list is not blank when inserting
    insertNode->next = nullptr;
    insertNode->prev = this->tail;

    // Set the original tail to the insertNode
    this->tail->next = insertNode;

    // Declare insertNode as the new head
    this->tail = insertNode;
  }
}

// Inserts an existing linked list at the end of the this linked list
template <class type>
void LL<type>::tailInsert(const iterator &s, const iterator &t)
{
  node *tmp;
  node *tmp2;

  tmp = s.current;
  tmp2 = t.current;

  if (this->head == nullptr)
  {
    this->head = tmp;
    this->tail = tmp2;
  }
  else
  {
    // Set the s' current pointer to the new node's head
    this->tail->next = tmp;

    // Setting the head iterator previous to current tail
    this->tail->next->prev = this->tail;

    this->tail = tmp2;
  }
}

// Inserts an existing node to the end of the this linked list
template <class type>
void LL<type>::tailInsert(const iterator &s)
{
  node *tmp;
  tmp = s.current;

  if (this->head == nullptr)
  {
    this->head = tmp;
    this->tail = tmp;
  }
  else
  {
    this->tail->next = tmp;
    this->tail->next->prev = this->tail;
    this->tail = tmp;
  }
}

// Cuts off the linked list from it iterator to the end of the linked list
template <class type>
void LL<type>::remove(iterator &it)
{
  node *tmp;
  node *tmp2;

  // Set tmp to equal it current node
  tmp = it.current;

  // Have tmp point to the previous node
  tmp = tmp->prev;

  // Set tmp as the new tail
  this->tail = tmp;

  // Have another pointer point to it current
  tmp2 = it.current;

  // Set the t prev pointer to nullptr to fully dissociate them
  tmp2->prev = nullptr;

  if (tmp != nullptr)
  {
    // Set the tmp next pointer to point to nullptr
    tmp->next = nullptr;
  }
  else
  {
    this->head = nullptr;
  }
}

// Removes the head node of the linked list
template <class type>
void LL<type>::headRemove()
{
  if (this->head != nullptr)
  {
    node *tmp = head;
    head = head->next;

    delete tmp;
  }
  return;
}
