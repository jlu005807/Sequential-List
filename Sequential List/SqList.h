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
				//�Ƿ�����ж�temp==data[i]���ٱȽϴ���������
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

	//Shell Sort �����ھֲ������ð������
	void Shell_Sort()//Shellԭʼ��������
	{
		int length = this->ListLength();
		for (int gap = length / 2; gap >= 0; gap /= 2)
		{
			//ֱ�Ӳ�������
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

	void Merge_Sort_1()//���¶��ϵ�����
	{
		int length = this->ListLength();
		T* a = this->elem;//ԭʼ����
		T* b = new T[length];//��ʱ����

		if (!b)//����ڴ�����Ƿ�ɹ�
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}

		int seg, start;//seg����ǰ�ָ�Ķδ�С����start����ǰ����λ�ã�

		for (seg = 1; seg < length; seg += seg)//��
		{
			for (start = 0; start < length; start += seg * 2)//�������鲢����������������
			{
				// ���㵱ǰ�ε���߽硢�м�߽磨���ܲ����������м䣬��ΪҪ����Խ�磩���ұ߽�  
				auto min = [](int x, int y)->auto {return x > y ? y : x; };
				
				int low = start, mid = min(start + seg, length), high = min(start + seg * 2, length);

				//b����Ҫ����λ�ã�
				int k = low;

				// left��right_start�ֱ�ָ��ǰ�κ���һ���ε���ʼλ��  
				int left = low, right_start = mid;

				//�ֶ���֮���ϲ�
				while (left < mid && right_start < high)
				{
					b[k++] = a[left] < a[right_start] ? a[left++] : a[right_start++];
				}

				// �����λ���ʣ��Ԫ�أ������Ǹ��Ƶ�b��  
				while (left < mid) {
					b[k++] = a[left++];
				}

				// ����ҶΣ�����һ���Σ�����ʣ��Ԫ�أ������Ǹ��Ƶ�b��  
				while (right_start < high) {
					b[k++] = a[right_start++];
				}

			}

			T* temp = a;
			a = b;
			b = temp;
		}

		// �����еݹ������ɺ�aָ�����������飨������b��ȡ���ڵݹ����ȣ�  
		// ���a����ԭʼ���飬�����������ݸ��ƻ�ԭ����
		if (a != this->elem)
		{
			for (int i = 0; i < length; i++)
				this->elem[i] = a[i];
			b = a;
		}

		delete[] b;
	}

	void Merge_Sort_2(int front, int end)//�ݹ鷨(front��end���������±����gap)
	{
		if (front >= end)//�����ݹ�����
			return;
		int mid = (front + end) / 2;//�м�λ��

		Merge_Sort_2(front, mid);
		Merge_Sort_2(mid + 1, end);
				
		Merge(front, mid, end);
	}

	void Merge(int front, int mid, int end)
	{
		//��ʱ���飬�ֱ𴢴���������������
		int leftSize = mid - front + 1;
		int rightSize = end - mid;
		T* left = new T[leftSize + 1];
		T* right = new T[rightSize + 1];

		//�������ݲ�����ڱ�ֵ

		for (int i = 0; i < leftSize; i++)
		{
			left[i] = this->elem[front + i];
		}
		left[leftSize] = std::numeric_limits<T>::max();// �ڱ�ֵ

		for (int j = 0; j < rightSize; j++)
		{
			right[j] = this->elem[mid + 1 + j];
		}
		right[rightSize] = std::numeric_limits<T>::max(); // �ڱ�ֵ  

		//�ϲ���������������
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

		//������˵���� LeftSubArray �е�Ԫ��ȫ�����ϲ����� idxLeft �ﵽ�� LeftSubArray �Ĵ�С����
		// �� RightSubArray �л���ʣ��Ԫ��ʱ����Щʣ��Ԫ����Ȼ���� Array[mid+1...end] ��ʣ��ġ�
		// ���Ѿ�������ģ���Ϊ�����ںϲ�ǰ��������ģ�����ʱ�����ǲ���Ҫ���κζ���Ĳ����������ơ���ЩԪ�أ�
		// ��Ϊ�����Ѿ�����ȷ��λ�����ˡ�

		delete[] left;
		delete[] right;

		return ;
	}


	void Quick_Sort(int begin, int end,QuickSort<T>* partSort)//����Ϊ�±�ֵ
	{
		if (begin >= end)return;//�˳��ݹ��ж�;

		//��׼
		int idxkey = partSort->Sort(this->elem, begin, end);
	
		// ���ֳɹ�����keyiΪ�߽��γ������������� [begin, keyi-1] keyi [div+1, end]
	    // �󲿷ֶ��Ǳ� keyi λ���ϵ�ֵС�Ĳ��֣��Ҳ��ֶ��Ǳ� keyi λ���ϵ�ֵ��Ĳ��֡�
	    // �ݹ����󲿷�[begin, keyi-1]
		Quick_Sort(begin, idxkey-1,partSort);

		// �ݹ����Ҳ���[keyi+1, end]
		Quick_Sort(idxkey + 1, end,partSort);


	}

	//��������--�ݹ鷨-- - ��·���ַ�
	void Quick_Sort1(int begin, int end)//�±�
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
		//����[left,right]Ϊ����ڻ�׼ֵ�����鲻��Ҫ����
		Quick_Sort1(begin, left - 1);
		Quick_Sort1(right + 1, end);
	}

	//��ε�������ݽṹ����׼�ָ��
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

	//��������
	void Counting_Sort()
	{
		//�����ֵ����Сֵ
		T max = elem[0];
		T min = elem[0];

		for (int i = 0; i < this->length; i++)
		{
			if (elem[i] > max)max = elem[i];
			if (elem[i] < min)min = elem[i];
		}
		//ͳ���������
		int gap = max - min;
		int* count_a = new int[gap + 1];

		//��ʼ��count_a
		for (int i = 0; i < gap + 1; i++)
			count_a[i] = 0;

		//����������Ҫ���������"-"
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
		//�����ֵ����Сֵ
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
			size = (max - min) / n + 1;//Ͱ�����鷶Χ
		}
		else
		{
			std::cout << "List is empty" << std::endl;
			exit(1);
		}
		
		if (n != 0)
		{
			cnt = (max - min) /size + 1;//Ͱ��(����Ϊһ
		}
		else
		{
			std::cout << "List is empty" << std::endl;
			exit(1);
		}

		//std::cout << size << " " << cnt << std::endl;
		//system("Pause");

		std::vector<std::vector<T>> buckets(cnt);

		//����Ͱ��
		for (int i = 0; i < n; i++) {
			int idx = (elem[i] - min) / size;
			buckets[idx].push_back(elem[i]);
		}
		
		//�ֱ�����
		for (int i = 0; i < cnt; i++)
		{
			sort(buckets[i].begin(), buckets[i].end());
		}

		int index = 0;
		//���·���ԭ����
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
