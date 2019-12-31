#include "customvector.h"
#include "singlelinkedlist.h"
#include "datastructure.h"
template <typename T>
void printElements(const DataStructure <T>& ds1)
{
	cout << "List contents:\n";
	for (int i = 0; i < ds1.getLength(); ++i)
	{
		cout << ds1.getData(i) << endl;
	}
}
int main()
{
	try
	{
		List <int> vector1;
		vector1.pushBack(0);
		vector1.pushBack(1);
		vector1.pushBack(2);
		vector1.insertElement(3, 3);
		printElements(vector1);
		vector1.clear();
		vector1.pushFront(0);
		vector1.pushBack(1);
		vector1.insertElement(2, 1);
		vector1.setElement(2 , 2);
		printElements(vector1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.pushBack(1);
		vector1.removeElement(0);
		vector1.removeElement(0);
		vector1.popBack();
		printElements(vector1);
	}
	
	catch (runtime_error)
	{
		cout << "Invalid index position";
	};
}