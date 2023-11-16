#ifndef __DLIST_H__
#define __DLIST_H__


/**********************************************************
 * INSTRUCTOR NOTE: Do not modify the class declarations! *
 * The class Dlist is a class template.                   *
 *********************************************************/
class emptyList {
  // OVERVIEW: an exception class
};

template <typename T>
class Dlist {
  // OVERVIEW: contains a double-ended list of Objects

 public:
  // Maintenance methods

  Dlist();                                // constructor
  Dlist(const Dlist &l);                  // copy constructor
  Dlist &operator=(const Dlist &l);       // assignment
  ~Dlist();                               // destructor

  // Operational methods

  // EFFECTS: returns true if list is empty, false otherwise
  bool IsEmpty() const;

  // MODIFIES: this
  // EFFECTS: inserts o at the front of the list
  void InsertFront(const T &o);

  // MODIFIES: this
  // EFFECTS: inserts o at the back of the list
  void InsertBack(const T &o);

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveFront();

  // MODIFIES: this
  // EFFECTS: removes and returns last object from non-empty list
  //          throws an instance of emptyList if empty
  T RemoveBack();

 private:
  // A private type

  struct node {
    node   *next;
    node   *prev;
    T      o;
  };

  // Private member variables 

  node   *first; // The pointer to the first node (NULL if none)
  node   *last;  // The pointer to the last node (NULL if none)

  // Private utility methods

  // EFFECTS: called by constructors to establish empty list invariant
  void MakeEmpty();

  // EFFECTS: called by copy constructor/operator= to copy nodes
  //          from a source instance l to this instance
  void CopyAll(const Dlist &l);
    
  // EFFECTS: called by destructor and operator= to remove and destroy
  //          all list nodes
  void RemoveAll();
};

// Constructor
template <typename T>
Dlist<T>::Dlist() {
  MakeEmpty();
}

// Copy constructor
template <typename T>
Dlist<T>::Dlist(const Dlist &l) {
  MakeEmpty();
  CopyAll(l);
}

// Assignment operator
template <typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l) {
  if (this != &l) {
    RemoveAll();
    CopyAll(l);
  }
  return *this;
}

// Destructor 
template <typename T>
Dlist<T>::~Dlist() {
  RemoveAll();
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/**********************************************************
 * INSTRUCTOR NOTE: Implement the member functions below. *
 * These member functions are all function templates.     * 
 *********************************************************/

// EFFECTS: returns true if list is empty, false otherwise

/*PSEDUOCODE:
*  return(first == NULL && last == NULL);
*/
template <typename T>
bool Dlist<T>::IsEmpty() const {
  // Implement this function.
  return (first == NULL && last == NULL);
}

// MODIFIES: this
// EFFECTS: inserts o at the front of the list

/*PSEDUOCODE:
   new node n
  n.next = first
  n.prev = NULL
  n.o = o
  if(first != NULL)
  {
    first.prev = n
  }
  first = n
  if(last == NULL)
  {
    first = last;
  }
* 
*/
template <typename T>
void Dlist<T>::InsertFront(const T& o) {
  // Implement this function.
    node* node_value = new node;

    node_value->next = first;
    node_value->prev = NULL;
    node_value->o = o;

    if (first != NULL)
    {
        first->prev = node_value;
    }
    first = node_value;

    if (last == NULL)
    {
        last = first;
    }
}

// MODIFIES: this
// EFFECTS: inserts o at the back of the list

/*PSEDUOCODE:
  new node n
  n.next = last
  n.prev = NULL
  n.o = o
  if(last != NULL)
  {
    last.next = n
  }
  last = n
  if(first == NULL)
  {
    first = last;
  }
*
*/
template <typename T>
void Dlist<T>::InsertBack(const T& o) {
  // Implement this function.
    node* node_value = new node;

    node_value->prev = last;
    node_value->next = NULL;
    node_value->o = o;

    if(last != NULL)
    {
        last->next = node_value;
    }
    last = node_value;;

    if(first == NULL)
    {
        first = last;
    }
}

// MODIFIES: this
// EFFECTS: removes and returns first object from non-empty list
//          throws an instance of emptyList if empty

/*PSEDUOCODE:
  new node oldfirst = first
  new node oldlast = last
  if(first == NULL)
  {
    emptyList()
  }
  if(oldfirst == oldlast)
  {
    first = NULL
    last = NULL
  }
  else
  {
    first = first.next
    first.prev = NULL
  }
  return oldfirst.o
*
*/
template <typename T>
T Dlist<T>::RemoveFront() {
  // Implement this function.

    if (first == NULL)
    {
        throw emptyList();
    }

    node* old_first = first;
    node* old_last = last;

    old_first = first;
    old_last = last;

    if(old_first == old_last)
    {
        first = NULL;
        last = NULL;
    }
    else
    {
        first = first->next;
        first->prev = NULL;
    }
    
    return old_first->o;
}

// MODIFIES: this
// EFFECTS: removes and returns last object from non-empty list
//          throws an instance of emptyList if empty

/*PSEDUOCODE:
  new node oldfirst = first
  new node oldlast = last
  if(first == NULL)
  {
    emptyList()
  }
  if(oldfirst == oldlast)
  {
    first = NULL
    last = NULL
  }
  else
  {
    last = last.prev
    last.next = NULL
  }
  return oldlast.o
*
*/

template <typename T>
T Dlist<T>::RemoveBack()
{
  // Implement this function.

    if (first == NULL)
    {
        throw emptyList();
    }

    node* old_first = first;
    node* old_last = last;

    old_first = first;
    old_last = last;

    if (old_first == old_last)
    {
        first = NULL;
        last = NULL;
    }
    else
    {
        last = last->prev;
        last->next = NULL;
    }

    return old_last->o;
}

// EFFECTS: called by constructors to establish empty list invariant

/*PSEDUOCODE:

    first = NULL
    last = NULL

*
*/

template <typename T>
void Dlist<T>::MakeEmpty() 
{ 
    // Implement this function.
    first = NULL;
    last = NULL;
}

// EFFECTS: called by copy constructor/operator= to copy nodes
//          from a source instance l to this instance

/*PSEDUOCODE:

    MakeEmpty()
    new node n = l.first
    while(n != NULL)
    {
        InsertBack(n.o)
        n = n.next
    }

*
*/
template <typename T>
void Dlist<T>::CopyAll(const Dlist &l) 
{
  // Implement this function.
    MakeEmpty();
    node* current_node = l.first;
    while(current_node != NULL)
    {
        InsertBack(current_node->o);
        current_node = current_node->next;
    }
}

// EFFECTS: called by destructor and operator= to remove and destroy
//          all list nodes

/*PSEDUOCODE:

    while(first != NULL)
    {
        RemoveFront()
    }

*
*/
template <typename T>
void Dlist<T>::RemoveAll() {
  // Implement this function.
    //destroy
    while(first != NULL)
    {
        this->RemoveFront();
    }
}

/**** INSTRUCTOR NOTE: DO NOT DELETE #endif FROM END OF FILE. ****/
#endif /* __DLIST_H__ */
