// contains collection and node classes
// Dan Fabian
// 2/1/2019

#ifndef LIST_H_
#define LIST_H_

#include <iostream>

using std::cout; using std::endl;

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node {
 public:

 node() : next_(nullptr) {}

  // functions can be inlined
  T getData()const { return data_; }
  void setData(const T& data) { data_ = data; }

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

 private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const {
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next) {
  next_ = next;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// forward declarations
template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
  
  // constructor
  Collection() : first(nullptr) {}

  // methods
  void addItem(T);
  void removeItem(T);
  void printCollection();
  T lastItem();

  // friends
  friend bool equal<T>(const Collection&, const Collection&);

 private:
  node<T> *first;
};

template <typename T>
void Collection<T>::addItem(T item)
{
  node<T> *currentNode;
  currentNode = new node<T>;

  // check if list is empty
  if (first == nullptr)
    {
      // if list is empty set node data and return
      currentNode->setData(item);
      first = currentNode;
      return;
    }

  currentNode = first;

  // move to the end of the collection
  while (currentNode->getNext() != nullptr)
    currentNode = currentNode->getNext();

  // create new node to be added
  node<T> *newNode;
  newNode = new node<T>;
  newNode->setData(item);

  // add item to end of list
  currentNode->setNext(newNode);
}

template <typename T>
void Collection<T>::removeItem(T item)
{
  node<T> *previousNode, *currentNode, *deleteNode;
  
  // check if list is empty
  if (first == nullptr)
    return;

  currentNode = first;

  // check first nodes
  while (currentNode->getData() == item)
    {
      deleteNode = currentNode;

      currentNode = currentNode->getNext();

      delete deleteNode;

      // check if at the end of collection
      if (currentNode == nullptr)
	{
	  first = nullptr;
	  return;
	}
    }

  // move first pointer to the new begining
  first = currentNode;

  // check all middle nodes
  while (currentNode->getNext() != nullptr)
    {
      previousNode = currentNode;
      currentNode = currentNode->getNext();

      if (currentNode->getData() == item)
	{
	  deleteNode = new node<T>;
	  deleteNode = currentNode;

	  currentNode = currentNode->getNext();

	  delete deleteNode;

	  previousNode->setNext(currentNode);
	}
    }

  // check end node
  if (currentNode->getData() == item)
    {
      delete currentNode;
      previousNode->setNext(nullptr);
    }
}

template <typename T>
void Collection<T>::printCollection()
{
  node<T> *currentNode;
  currentNode = new node<T>;
  currentNode = first;

  while (currentNode != nullptr)
    {
      cout << currentNode->getData() << "\n";
      currentNode = currentNode->getNext();
    }
}

template <typename T>
T Collection<T>::lastItem()
{
  node<T> *currentNode;
  currentNode = new node<T>;
  currentNode = first;

  // move to the end of the collection
  while (currentNode->getNext() != nullptr)
    currentNode = currentNode->getNext();
  
  return currentNode->getData();
}

template <typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs)
{
  node<T> *lhsIterator, *rhsIterator;
  lhsIterator = new node<T>;
  rhsIterator = new node<T>;

  lhsIterator = lhs.first;
  rhsIterator = rhs.first;

  // check all elements up to the final one
  while ((lhsIterator != nullptr) && (rhsIterator != nullptr))
    {
      if (lhsIterator->getData() != rhsIterator->getData())
	return false;

      lhsIterator = lhsIterator->getNext();
      rhsIterator = rhsIterator->getNext();
    }

  if (lhsIterator == nullptr && rhsIterator != nullptr)
    return false;
  else if (lhsIterator != nullptr && rhsIterator == nullptr)
    return false;

  return true;
}
#endif // LIST_H_
