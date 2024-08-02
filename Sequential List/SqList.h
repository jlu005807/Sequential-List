#pragma once


#include"QuickSort_Hoare.h"
#include"QuickSort_Hole.h"
#include"QuickSort_FroandBack.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

#define MAXSIZE 100

template<class T>
class SqList
{
public:

	SqList():length(0),capcity(MAXSIZE)
	{
		this->elem = new T[MAXSIZE];
		if (!this->elem)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
	}
	SqList(T elem[], int num) :length(num), capcity(MAXSIZE)
	{
		if (num > MAXSIZE)this->capcity = num;
		this->elem = new T[this->capcity];
		for (int i = 0; i < this->length; i++)
		{
			this->elem[i] = elem[i];
		}
	}

	SqList(const SqList& other)
	{
		this->elem = new T[other.capcity];
		this->length = other.length;
		this->capcity = other.capcity;
		for(int i = 0; i < this->length; i++)
		{
			this->elem[i] = other.elem[i];
		}
	}

	SqList& operator=(const SqList& other)
	{
		delete[]elem;
		this->elem = new T[other.capcity];
		this->capcity = other.capcity;
		this->length = other.length;
		for (int i = 0; i < this->length; i++)
			this->elem[i] = other.elem[i];	
	}

	~SqList()
	{
		delete[]elem;
		this->elem = NULL;
		this->length = 0;
	}

	void ClearList()
	{
		delete[]elem;
		elem = new T[MAXSIZE];
		this->length = 0;
		this->capcity = MAXSIZE;
	}

	bool ListEmpty()const
	{
		if (this->length == 0)return true;
		else return false;
	}

	int ListLength()const
	{
		return this->length;
	}

	T& GetElem(int i)
	{
		if (i <= 0 || i >= this->length)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		else
		{
			return this->elem[i - 1];
		}
	}

	int LocateElem(const T& e)const
	{
		if (this->length == 0)
		{
			std::cout << "List is empty" << std::endl;
			exit(1);
		}
		else
		{
			for (int i = 0; i < this->length; i++)
				if (this->elem[i] == e)return i + 1;
		}
		return -1;
	}

	void ListInsert(int i, T e)
	{
		if (i <= 0 || i > length || this->length == this->capcity)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		else
		{
			for (int k = length; k >= i; k--)
			{
				this->elem[k] = this->elem[k - 1];
			}
			this->elem[i - 1] = e;
		}
		this->length++;
		return;
	}

	void ListDelete(int i)
	{
		if (i <= 0 || i > length)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		else
		{
			
			for (int k = i - 1; k < this->length - 1; k++)
				this->elem[k] = this->elem[k + 1];
			this->length--;
		}
	}

	void List_Rever()
	{
		T temp;
		int n = this->length;
		for (int i = 0; i < n / 2; i++)
		{
			temp = elem[i];
			elem[i] = elem[n - i - 1];
			elem[n - i - 1] = temp;
		}
		return;
	}


	void Bubble_Sort()
	{
		int flag = 1;
		while (flag)
		{
			flag = 0;
			int v = this->length - 1;
			for (int i = 0; i < v; i++)
			{
				if (this->elem[i] > this->elem[i + 1])
				{
					T temp = elem[i];
					elem[i] = elem[i + 1];
					elem[i + 1] = temp;
					flag = 1;
					/*std::cout << *this << std::endl;
					system("pause");*/
				}
			}
			v--;
		}
		return;
	}

	void Binary_Insertion_Sort()
	{
		int v = this->ListLength();
		for (int i = 1;i < v; i++)
		{
			T temp = this->elem[i];
			int low = 0, high = i - 1;
			while(low<=high)
			{
				//是否可以判断temp==data[i]减少比较次数？？？
				int mid = (low + high) / 2;
				if (this->elem[mid] < temp)
					low = mid + 1;
				else
					high =mid-1;
			}
			for (int j = i;j > low; j--)
			{
				this->elem[j] = this->elem[j - 1];
			}

			this->elem[low] = temp;
		}
	}

	void  Selection_Sort()
	{
		for (int i = 0; i < this->ListLength(); i++)
		{
			int min = i;
			for (int j = i + 1; j < this->ListLength(); j++)
			{
				if (this->elem[j] < this->elem[min])
					min = j;
			}

			T temp = this ->elem[min];
			this->elem[min] = this->elem[i];
			this->elem[i] = temp;
		}
	}

	//Shell Sort 类似于局部分组的冒泡排序
	void Shell_Sort()//Shell原始增量序列
	{
		int length = this->ListLength();
		for (int gap = length / 2; gap >= 0; gap /= 2)
		{
			//直接插入排序
			for (int i = gap; i < length; i++)
			{
				T temp = this->elem[i];
				int j = i - gap;
				for (j; j >= 0; j -= gap)
				{
					if (this->elem[j] > temp)
						this->elem[j + gap] = this->elem[i];
					else
						break;
				}
				this->elem[j + gap] = temp;
			}
		}
	}

	void Merge_Sort_1()//自下而上迭代法
	{
		int length = this->ListLength();
		T* a = this->elem;//原始数组
		T* b = new T[length];//临时数组

		if (!b)//检查内存分配是否成功
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}

		int seg, start;//seg（当前分割的段大小），start（当前段起位置）

		for (seg = 1; seg < length; seg += seg)//分
		{
			for (start = 0; start < length; start += seg * 2)//遍历数组并处理相邻两段数组
			{
				// 计算当前段的左边界、中间边界（可能不是真正的中间，因为要避免越界）和右边界  
				auto min = [](int x, int y)->auto {return x > y ? y : x; };
				
				int low = start, mid = min(start + seg, length), high = min(start + seg * 2, length);

				//b中需要填充的位置；
				int k = low;

				// left和right_start分别指向当前段和下一个段的起始位置  
				int left = low, right_start = mid;

				//分而治之（合并
				while (left < mid && right_start < high)
				{
					b[k++] = a[left] < a[right_start] ? a[left++] : a[right_start++];
				}

				// 如果左段还有剩余元素，将它们复制到b中  
				while (left < mid) {
					b[k++] = a[left++];
				}

				// 如果右段（或下一个段）还有剩余元素，将它们复制到b中  
				while (right_start < high) {
					b[k++] = a[right_start++];
				}

			}

			T* temp = a;
			a = b;
			b = temp;
		}

		// 当所有递归调用完成后，a指向排序后的数组（可能是b，取决于递归的深度）  
		// 如果a不是原始数组，则将排序后的数据复制回原数组
		if (a != this->elem)
		{
			for (int i = 0; i < length; i++)
				this->elem[i] = a[i];
			b = a;
		}

		delete[] b;
	}

	void Merge_Sort_2(int front, int end)//递归法(front、end都是数组下标而非gap)
	{
		if (front >= end)//结束递归条件
			return;
		int mid = (front + end) / 2;//中间位置

		Merge_Sort_2(front, mid);
		Merge_Sort_2(mid + 1, end);
				
		Merge(front, mid, end);
	}

	void Merge(int front, int mid, int end)
	{
		//临时数组，分别储存左右两个子数组
		int leftSize = mid - front + 1;
		int rightSize = end - mid;
		T* left = new T[leftSize + 1];
		T* right = new T[rightSize + 1];

		//复制数据并添加哨兵值

		for (int i = 0; i < leftSize; i++)
		{
			left[i] = this->elem[front + i];
		}
		left[leftSize] = std::numeric_limits<T>::max();// 哨兵值

		for (int j = 0; j < rightSize; j++)
		{
			right[j] = this->elem[mid + 1 + j];
		}
		right[rightSize] = std::numeric_limits<T>::max(); // 哨兵值  

		//合并两个有序子数组
		int idxleft = 0, idxright = 0, idxarray = front;

		while (idxleft < leftSize && idxright < rightSize)
		{
			if (left[idxleft] < right[idxright])
			{
				this->elem[idxarray++] = left[idxleft++];
			}
			else
			{
				this->elem[idxarray++] = right[idxright++];
			}
		}

		while (idxleft < leftSize)
			this->elem[idxarray++] = left[idxleft++];

		//具体来说，当 LeftSubArray 中的元素全部被合并（即 idxLeft 达到了 LeftSubArray 的大小），
		// 但 RightSubArray 中还有剩余元素时，这些剩余元素自然就是 Array[mid+1...end] 中剩余的、
		// 且已经是有序的（因为它们在合并前就是有序的）。此时，我们不需要做任何额外的操作来“复制”这些元素，
		// 因为它们已经在正确的位置上了。

		delete[] left;
		delete[] right;

		return ;
	}


	void Quick_Sort(int begin, int end,QuickSort<T>* partSort)//传递为下标值
	{
		if (begin >= end)return;//退出递归判断;

		//基准
		int idxkey = partSort->Sort(this->elem, begin, end);
	
		// 划分成功后以keyi为边界形成了左右两部分 [begin, keyi-1] keyi [div+1, end]
	    // 左部分都是比 keyi 位置上的值小的部分，右部分都是比 keyi 位置上的值大的部分。
	    // 递归排左部分[begin, keyi-1]
		Quick_Sort(begin, idxkey-1,partSort);

		// 递归排右部分[keyi+1, end]
		Quick_Sort(idxkey + 1, end,partSort);


	}

	//快速排序--递归法-- - 三路划分法
	void Quick_Sort1(int begin, int end)//下标
	{
		T* array = this->elem;
		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		if (begin >= end)
		{
			return;
		}

		int left = begin;
		int right = end;
		T key = this->elem[left];

		int cur = left + 1;

		while (cur <= right)
		{
			if (elem[cur] > key)
			{
				swap(cur, right);
				--right;
			}
			else if (elem[cur] < key) 
			{
				swap(cur, left);
				++left;
			}
			else
			{
				++cur;
			}
		}

		// [begin,left-1][left,right][righ+1,end]
		//其中[left,right]为相等于基准值的数组不需要排序
		Quick_Sort1(begin, left - 1);
		Quick_Sort1(right + 1, end);
	}

	//严蔚敏《数据结构》标准分割函数
	void Quick_Sort2(T a[], int left, int right)
	{   
		int low = left;
		int high = right;
		if (low >= high)return;
		T pivot = a[low];
		

		while (low < high)
		{
			while (low < high && a[high] >= pivot)
				--high;

			a[low] = a[high];

			while (low < high && a[low] <= pivot)
				++low;

			a[high] = a[low];
		}

		a[low] = pivot;
		
		Quick_Sort2(a, left, low - 1);
		Quick_Sort2(a, low + 1, right);
	}

	//计数排序
	void Counting_Sort()
	{
		//求最大值和最小值
		T max = elem[0];
		T min = elem[0];

		for (int i = 0; i < this->length; i++)
		{
			if (elem[i] > max)max = elem[i];
			if (elem[i] < min)min = elem[i];
		}
		//统计数组个数
		int gap = max - min;
		int* count_a = new int[gap + 1];

		//初始化count_a
		for (int i = 0; i < gap + 1; i++)
			count_a[i] = 0;

		//特殊类型需要重载运算符"-"
		for (int i = 0; i < this->length; i++)
			count_a[elem[i] - min]++;

		for (int i = 1; i < gap+1; i++)
			count_a[i] += count_a[i - 1];

		T* sorted_a = new T[capcity];
		for (int i = this->length - 1; i >= 0; i--)
		{
			int idx = --count_a[elem[i] - min];
			sorted_a[idx] = elem[i];

		}
		T* temp = elem;
		this->elem = sorted_a;
		delete[] temp;
	}

	void Bucket_Sort()
	{
		//求最大值和最小值
		T max = elem[0];
		T min = elem[0];

		for (int i = 0; i < this->length; i++)
		{
			if (elem[i] > max)max = elem[i];
			if (elem[i] < min)min = elem[i];
		}
		int n = this->length;
		int size = 1, cnt = 1;
		if(n!=0)
		{
			size = (max - min) / n + 1;//桶中数组范围
		}
		else
		{
			std::cout << "List is empty" << std::endl;
			exit(1);
		}
		
		if (n != 0)
		{
			cnt = (max - min) /size + 1;//桶数(至少为一
		}
		else
		{
			std::cout << "List is empty" << std::endl;
			exit(1);
		}

		//std::cout << size << " " << cnt << std::endl;
		//system("Pause");

		std::vector<std::vector<T>> buckets(cnt);

		//放入桶中
		for (int i = 0; i < n; i++) {
			int idx = (elem[i] - min) / size;
			buckets[idx].push_back(elem[i]);
		}
		
		//分别排序
		for (int i = 0; i < cnt; i++)
		{
			sort(buckets[i].begin(), buckets[i].end());
		}

		int index = 0;
		//重新放入原数组
		for (int i = 0; i < cnt; i++)
		{
			for (int j = 0; j < buckets[i].size(); j++)
			{
				elem[index++] = buckets[i][j];
			}
		}

	}

	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const SqList<K>& other);


	T* elem;
	int length;
	int capcity;
	Hoare<T> m_hoare;
	Hole<T> m_hole;
	FroandBack<T> m_froandback;
};


template<class K>
std::ostream& operator<<(std::ostream& out, const SqList<K>& other)
{
	if (other.length == 0)
	{
		out << "List is empty" << std::endl;
		return out;
	}
	for (int i = 0; i <other.length; i++)
	{
		out << other.elem[i] << std::endl;
	}
	return out;
}
