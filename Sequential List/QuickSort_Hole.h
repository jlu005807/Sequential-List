#pragma once
#include"QuickSort.h"

template<class T>
class Hole : public QuickSort<T>
{
	int Sort(T* array, int left, int right)//������Hoare
	{
		T key = array[left];//�����׼ֵ
		int hole = left;//��һ����

		while (left < right)
		{
			while (left < right && array[right] >= key)
			{
				--right;
			}

			array[hole] = array[right];//���
			hole = right;//�¿�

			while (left < right && array[left] <= key)
			{
				++left;
			}

			array[hole] = array[left];
			hole = left;
		}

		array[hole] = key; //���һ����Ϊ��׼
		return hole;

	}
};