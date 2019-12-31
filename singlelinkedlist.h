#ifndef _singlelinkedlist_h_
#define _singlelinkedlist_h_
#include "datastructure.h"
#include <stdexcept>
#include <iostream>
using namespace std;


// struct for nodes containing a pointer to the next node in the list, and int 
// data member.
template <typename T>
struct Node 
{
	T data = 0;
	Node<T>* next = NULL;
};

// class declaration and description for list class.  This will contain pointers
// to the head node and tail node and a size property reflecting the number of 
// nodes in the list.
template <typename T>
class List:public DataStructure <T>
{

public:
	Node <T>* head = NULL;
	Node <T>* tail = NULL;
	int size = 0;

	// member function that returns number of node  in list as an int.
	int getLength() const
	{
		return size;
	}

	// member function to insert a new node into the list. function will take
	// an int argument 'index' to reflect the position that the node will be
	// inserted into the list, and an template 'value' that will populate the data
	// member of the node.
	void insertElement(int index, T value)
	{
		// check if user is accessing an invalid position in the list. If so
		// throw exception.

		if (index < 0 || index>size)
		{
			throw exception("Invalid index position!");
		}

		// create new node and pointer to that node. fill in data field with
		// passed T	value and increase size of list by one.
		Node<T>*
		nodeToBeInserted = new Node<T>;
		nodeToBeInserted->data = value;
		++size;

		// check to see if the element being inserted is going to be the head
		// or of the list.  also checks to see if the list is currently empty. 
		if (index == 0)
		{
			nodeToBeInserted->next = head;
			head = nodeToBeInserted;
			if (head->next == NULL)
			{
				tail = head;
			}

		}

		// check to see if this is being inserted at the end of the list
		else if (index == size - 1)
		{
			tail->next = nodeToBeInserted;
			tail = nodeToBeInserted;
			tail->next = NULL;
		}

		// if it is not the first or last element of the list, start at the 
		// head of the list and iterate through the list until you reach the 
		//position before the position to insert. Insert element there and 
		// change the previous and following nodes pointers accordingly.
		else
		{
			Node<T>* nodeToInsertAfter = head;
			for (int i = 0; i < index - 1; ++i)
			{
				nodeToInsertAfter = nodeToInsertAfter->next;
			}
			nodeToBeInserted->next = nodeToInsertAfter->next;
			nodeToInsertAfter->next = nodeToBeInserted;

		}
	}
	void removeElement(int index)
	{
		// check if user is accessing an invalid position in the list. If so
		// throw exception. 
		if (index < 0 || index>size - 1)
		{
			throw exception("Invalid index position!");
		}

		// Decrease size by one. If there is only one node, delete it and set
		// head and tail to NULL and return.
		--size;
		if (head->next == NULL)
		{
			delete head;
			head = NULL;
			tail = NULL;
			return;
		}

		// check to see if you are deleting the head. If so, create a pointer
		// to the head and set the second node to head, then delete the previous
		// head and return.
		if (index == 0)
		{
			Node<T>* nodeToBeRemoved = head;
			head = head->next;
			delete nodeToBeRemoved;
			return;
		}


		// Start a pointer at the head and iterate through the list until you
		// reach the node before the node to be removed.
		Node<T>* nodeBeforeNodeBeingRemoved = head;
		for (int i = 0; i < index - 1; ++i)
		{
			nodeBeforeNodeBeingRemoved = nodeBeforeNodeBeingRemoved->next;

			// if this condition happens that would indicate the next element
			// is the tail of the list.  If that is the case, delete the tail
			// and make the current element the new tail.
			if (nodeBeforeNodeBeingRemoved->next->next == NULL)
			{
				tail = nodeBeforeNodeBeingRemoved;
				delete nodeBeforeNodeBeingRemoved->next;
				nodeBeforeNodeBeingRemoved->next = NULL;
				return;
			}
		}

		// if the loop reaches here, then the element being removed is not the
		// head or the tail. create a new pointer at the next node. move the 
		// next pointer of the current element over the node to be removed then
		// delete that node.
		Node<T>* nodeToBeRemoved = nodeBeforeNodeBeingRemoved->next;
		nodeBeforeNodeBeingRemoved->next = nodeBeforeNodeBeingRemoved->next->next;
		delete nodeToBeRemoved;



	}
	void clear()
	{
		// check to see if list is empty. if so,  return.
		if (size == 0)
		{
			return;
		}

		// create a pointer to the head. while there is more than one node
		// in the list move the head forward one node and delete the old head.
		// Then move the pointer to the new head.
		Node<T>* nodeToRemove = head;
		while (head->next != NULL)
		{
			head = head->next;
			delete nodeToRemove;
			nodeToRemove = head;
		}

		// there should only be the head remaining. delete the head and set
		// head and tail pointers to NULL. Size set to 0.
		delete head;
		head = NULL;
		tail = NULL;
		size = 0;
	}

	// add a node to the tail position of the list.  create a pointer to a new
	// node and set it's data to the passed value.  
	void pushBack(T value)
	{
		++size;
		Node<T>* nodeToAdd = new Node<T>;
		nodeToAdd->data = value;

		// if this is the first element it becomes the head and the tail.
		if (head == NULL)
		{
			head = nodeToAdd;
			tail = nodeToAdd;
		}

		// Set the tail's next pointer to the new node and then set the new node
		// as the tail.
		else
		{
			tail->next = nodeToAdd;
			tail = nodeToAdd;
		}
	}

	// add an element to the head of the list using the insertElementAt function.
	void pushFront(T value)
	{
		insertElement(0, value);
	}

	// remove the head of the list using the removeElementAt function.
	void popFront()
	{
		removeElement(0);
	}

	// remove the last node of the list using the removeElementAt function.
	void popBack()
	{
		removeElement(size - 1);
	}

	void setElement(int index, int value)
	{
		// check if user is accessing an invalid position in the list. If so
		// throw exception. 
		if (index < 0 || index>size - 1 || head == NULL)
		{
			throw exception("Invalid index position!");
			return;
		}

		// create a pointer and start at the list moving from node to node
		// until the indexed position is reached. Set data field of node to passed
		// value.
		Node<T>* nodeToSet = head;
		for (int i = 0; i < index; ++i)
		{
			nodeToSet = nodeToSet->next;
		}

		nodeToSet->data = value;
	}

	// reverses order of nodes in list.
	void reverseElements()
	{
		// check to see if list is empty or there is only one node. If so return.
		if (size == 0 || size == 1)
		{
			return;
		}
		Node<T>* currentNode = head;
		Node<T>* nextNode = head;
		Node<T>* previousNode = NULL;

		// iterating through the list, keep changing each node's next pointer to the
		// previous node in the list, moving the node pointers through the list until
		// they hit the end. Each node pointer will be one position ahead from where
		// they were in the last iteration.
		while (currentNode != NULL)
		{
			nextNode = currentNode->next;
			currentNode->next = previousNode;
			previousNode = currentNode;
			currentNode = nextNode;
		}

		// at the end of the reversal, swap the head and tail pointers.
		currentNode = head;
		head = tail;
		tail = currentNode;

	}

	// gets the int data value from the requested node and returns it.
	T getData(int index) const
	{
		// check if user is accessing an invalid position in the list. If so
		// throw exception. 

		if (index < 0 || index>size || head == NULL)
		{
			throw exception("Invalid index position!");
		}

		// create a pointer and start at the list moving from node to node
		// until the indexed position is reached. Return data value found there.
		Node<T>* nodeToAccess = head;
		for (int i = 0; i < index; ++i)
		{
			nodeToAccess = nodeToAccess->next;
		}
		return nodeToAccess->data;

	}

	// when copying one list to another.  This will first clear the contents of the left
	// value list.  then while there is a valid node to copy, will copy to the new list
	// then return a list object.
	List& operator = (const List& listToBeCopied)
	{
		clear();
		Node<T>* nodeToCopy = listToBeCopied.head;
		while (nodeToCopy != NULL)
		{
			pushBack(nodeToCopy->data);
			nodeToCopy = nodeToCopy->next;
		}
		return *this;
	}

	// returns a reference to the requested position in the list.
	T& operator [] (int valueInBrackets)
	{
		return getData(valueInBrackets);
	}
};
#endif
