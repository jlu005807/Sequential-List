#pragma once
#include"QuickSort.h"

template<class T>
class Hole : public QuickSort<T>
{
	int Sort(T* array, int left, int right)//类似于Hoare
	{
		T key = array[left];//储存基准值
		int hole = left;//第一个坑

		while (left < right)
		{
			while (left < right && array[right] >= key)
			{
				--right;
			}

			array[hole] = array[right];//填坑
			hole = right;//新坑

			while (left < right && array[left] <= key)
			{
				++left;
			}

			array[hole] = array[left];
			hole = left;
		}

		array[hole] = key; //最后一个坑为基准
		return hole;

	}
};