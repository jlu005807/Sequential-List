#pragma once
#include"QuickSort.h"
template<class T>
class Hoare:public QuickSort<T>
{
	int Sort(T* array, int left, int right)
	{
		int idxkey = left;//key的位置

		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		while (left < right)
		{
			//右边左移找较小值
			while (left < right && array[right] >= array[idxkey])
				--right;

			//左边右移找较大值
			while (left < right && array[left] <= array[idxkey])
				++left;

			//交换
			swap(left, right);
		}
		
		//left和right相遇
		swap(left, idxkey);

		idxkey = left;

		//for (int i = 0; i < 9; i++)std::cout << array[i] << " ";
		//std::cout << std::endl;
		//system("pause");
		//测试

		return idxkey;//返回基准位置

        // 霍尔单趟排序之后， 
        // keyi 位置左边的部分都比 keyi位置的值要小，
        // keyi 位置右边的部分都比 keyi位置的值要大。
	}
};