#ifndef _datastructure_h_
#define _datastructure_h_
using namespace std;

template <typename T>
class DataStructure
{
public:
	virtual int getLength() const = 0;
	virtual T getData(int index) const = 0;
	virtual void setElement(int index, T value) = 0;
	virtual void insertElement(int index, T value) = 0;
	virtual void removeElement(int index) = 0;
	virtual void clear() = 0;
	virtual void pushBack(T value) = 0;
	virtual void pushFront(T value) = 0;
	virtual void popFront() = 0;
	virtual void popBack() = 0;
};
#endif
