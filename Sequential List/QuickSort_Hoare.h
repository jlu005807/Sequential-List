#pragma once
#include"QuickSort.h"
template<class T>
class Hoare:public QuickSort<T>
{
	int Sort(T* array, int left, int right)
	{
		int idxkey = left;//key��λ��

		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		while (left < right)
		{
			//�ұ������ҽ�Сֵ
			while (left < right && array[right] >= array[idxkey])
				--right;

			//��������ҽϴ�ֵ
			while (left < right && array[left] <= array[idxkey])
				++left;

			//����
			swap(left, right);
		}
		
		//left��right����
		swap(left, idxkey);

		idxkey = left;

		//for (int i = 0; i < 9; i++)std::cout << array[i] << " ";
		//std::cout << std::endl;
		//system("pause");
		//����

		return idxkey;//���ػ�׼λ��

        // ������������֮�� 
        // keyi λ����ߵĲ��ֶ��� keyiλ�õ�ֵҪС��
        // keyi λ���ұߵĲ��ֶ��� keyiλ�õ�ֵҪ��
	}
};