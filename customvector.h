#ifndef _customvector_h_
#define _customvector_h_
#include "datastructure.h"

#include <stdexcept>
#include <iostream>
using namespace std;

// customVector class will be a templatized vector like class with the ability
// to process different data types.
template <typename T>
class CustomVector: public DataStructure <T>
{
	// size refers to the actual number of elements in the vector. maxSize 
	// refers to the current space allocated to the vector. element is a pointer
	// to the beginning of the vector.
	int size = 0;
	int maxSize = 0;
	T* element = NULL;

	// if the vector outgrows the space allocated to it, member functions will call
	// this to allocate a new array and copy everything over to it and delete the old
	// vector.
	void reallocateMemory()
	{
		T* copyVector = new T[(int)size * 1.5];
		for (int i = 0; i < size; ++i)
		{
			copyVector[i] = element[i];
		}
		delete[] element;
		element = copyVector;
		maxSize = ((int)size * 1.5);
	}

public:

	// default constructor sets the maxSize to 5 and creates an array of 5 elements.
	CustomVector()
	{
		maxSize = 5;
		element = new T[5];
	}
	~CustomVector()
	{
		delete[] element;
	}

	// getLength will return the current number of elements in the vector.
	int getLength() const
	{
		return size;
	}

	// getData will return the value found at the indexed position. will perform an
	// out of bounds check before proceeding.
	T getData(int index) const
	{
		if (index<0 || index>size - 1)
		{
			throw runtime_error("Invalid index position!");
		}
		return element[index];
	}

	// sets the element value at the requested position. also performs an out of bounds
	// check before proceeding.
	void setElement(int index, T value)
	{
		if (index<0 || index>size - 1)
		{
			throw runtime_error("Invalid index position!");
		}
		element[index] = value;
	}

	// insert an element at the requested position in the vector. this will shift all
	// other elements to the left. we will perform out of bounds check before proceeding.
	// size will increase by one.
	void insertElement(int index, T value)
	{
		if (index<0 || index>size)
		{
			throw runtime_error("Invalid index position!");
		}
		++size;
		// next check to see if increasing the size by one will require allocation
		// of more space for the vector. if so, call that function.
		if (size > maxSize)
		{
			reallocateMemory();
		}


		// set element at indexed position to passed value and shift all other 
		// elements to the right.
		T elementBeingSwapped;
		while (index < size - 1)
		{
			elementBeingSwapped = element[index];
			element[index] = value;
			value = elementBeingSwapped;
			++index;
		}
		element[index] = value;
	}

	// remove element from vector. this will shift all other elements to the left.
	// we will perform and out of bounds check before proceeding. size will decrease by
	// one.
	void removeElement(int index)
	{
		if (index<0 || index>size - 1)
		{
			throw runtime_error("Invalid index position!");
		}


		// valueToBeSwapped stores the value of the element at the end of the array.
		// current value 
		T previousElement = element[size - 1];
		T elementToBeOverwritten;

		// loop swaps values moving each value to the left one position. size decreases
		// by one.
		for (int i = size - 2; i >= index; --i)
		{
			elementToBeOverwritten = element[i];
			element[i] = previousElement;
			previousElement = elementToBeOverwritten;
		}
		--size;
	}

	// function will 'clear' the contents of the vector by setting size to 0.
	void clear()
	{
		size = 0;
	}

	// adds a new element to the end of the vector.
	void pushBack(T value)
	{
		insertElement(size, value);
	}


	// adds a new element to the front of the vector.
	void pushFront(T value)
	{
		insertElement(0, value);
	}

	// remove first item of vector.
	void popFront()
	{
		removeElement(0);
	}

	// remove last item of vector.
	void popBack()
	{
		removeElement(size - 1);
	}

	// reverses order of elements in vector. if vector contains 0 or 1 simply return.
	void reverseElements()
	{
		if (size==0 || size==1)
		{
			return;
		}
		// loop goes through array moving the last element to first. each iteration 
		// moves the left position forward one and right positon back one until they
		// meet.
		for (int i = 0; i < (size-1)-i; ++i)
		{
			T valueToMove = element[i];
			element[i] = element[(size - 1) - i];
			element[(size - 1) - i] = valueToMove;
		}
	}

	// returns a reference to the requested position in the list. This version allows
	// changes.
	T& operator [] (T valueInBrackets)
	{
		return getData(valueInBrackets);
	}

	// returns a reference to the requested position in the list. This version allows
	// no changes.
	T& operator [] (T valueInBrackets) const
	{
		return getData(valueInBrackets);
	}


	// operator overload uses '=' to create a copy of the array on the right side with 
	// same elements and properties. A pointer is returned to the left side to point to 
	// this new array.
	CustomVector& operator = (const CustomVector& vectorToBeCopied)
	{
		delete[] element;
		T* copyOfVector = vectorToBeCopied.element;
		element = new T[(int)(vectorToBeCopied.maxSize)];
		for (int i = 0; i < vectorToBeCopied.size; ++i)
		{
			element[i] = copyOfVector[i];
		}

		size = vectorToBeCopied.size;
		maxSize = vectorToBeCopied.maxSize;
		return *this;
	}
	
};
#endif
