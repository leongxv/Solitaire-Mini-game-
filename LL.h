/*
LL.h
 - header file for LL.cpp to store predefined functions
*/
#ifndef LL_H
#define LL_H

template <class type>
class LL
{
private:

  struct node
  {
    type data;
    node * prev;
    node * next;
  };

  node * head;
  node * tail;

  public:

    class iterator
    {
    private:
      node * current;
    public:
      friend class LL;
      iterator() : current(nullptr) {}
      iterator(node * p) : current(p) {}
      type& operator*() { return current->data; }
      iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp;}
      iterator operator--(int) { iterator tmp(*this); --(*this); return tmp;}
      iterator operator++() { current = current->next; return *this; }
      iterator operator--() { current = current->prev; return *this; }
      bool operator==(const iterator& rhs) const { return current == rhs.current; }
      bool operator!=(const iterator& rhs) const { return current != rhs.current; }
    };

    LL() : head(nullptr), tail(nullptr) {}
    LL(const LL<type>&);
    const LL<type>& operator=(const LL<type>&);
    ~LL();

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(tail); }

    void tailInsert(const type&);
    void tailInsert(const iterator&);
    void tailInsert(const iterator&, const iterator&);
    void remove(iterator&);
    void headRemove();

    bool isEmpty() const { return head == nullptr; }
};
#endif