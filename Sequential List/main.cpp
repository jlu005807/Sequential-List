#include"SqList.h"
using namespace std;
int main()
{
	int a[9] = { 9,8,7,6,4,2,3,2,1 };
	SqList<int> one(a, 9);
	std::cout << one << std::endl;
	std::cout << one.length << std::endl;
	std::cout << one.capcity << std::endl;
	one.Bucket_Sort();
	cout << one << endl;
	one.List_Rever();
	cout << one << endl;
	system("pause");
	
}