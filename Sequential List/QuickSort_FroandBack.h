#pragma once
#include"QuickSort.h"
template<class T>
class FroandBack :public QuickSort<T>
{
	int Sort(T* array, int left, int right)
	{
		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		int prev = left;
		int cur = left + 1;
		int idxkey = left;//»ù×¼Î»ÖÃ

		while (cur <= right)
		{
			while (array[cur] <= array[idxkey] && ++prev != cur)
				swap(cur, prev);

			++cur;
		}

		swap(prev, idxkey);
		idxkey = prev;

		return idxkey;
	}
};
