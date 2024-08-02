#pragma once
#include<iostream>


template<class T>
class QuickSort
{
public:
	virtual int Sort(T *array,int left,int right) = 0;
};