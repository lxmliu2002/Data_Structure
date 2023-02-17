#pragma once
#include<iostream>
#include"myExceptions.h"
using namespace std;

//最大堆定义：
//每个节点的值都大于等于其子节点的值同时是一棵完全二叉树
template<class T>
class MinHeap {
public:
	MinHeap(int MaxHeapSize = 10);
	~MinHeap() { delete[]heap; }
	int Size()const { return CurrentSize; }
	//返回优先级最高的元素
	T Min()
	{
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MinHeap<T>& Insert(const T& x);
	MinHeap<T>& DeleteMin(T& x);
	//建堆函数
	void Initialize(T a[], int size, int ArraySize);
	// 将堆设置为空，但不释放空间——不销毁a
	void Deactivate()
	{
		heap = NULL; CurrentSize = MaxSize = 0;
	}

private:
	int CurrentSize, MaxSize;
	//一维数组有效描述
	//堆节点从1开始编号，左孩子是2i，右孩子是2i+1
	T* heap;
};

template<class T>
MinHeap<T>::MinHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}

template<class T>
MinHeap<T>& MinHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	int i = ++CurrentSize;
	//判断子节点是否比父节点小，是的话父节点下移
	while (i != 1 && x < heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//将x插入合理位置
	heap[i] = x;
	return *this;
}

template<class T>
MinHeap<T>& MinHeap<T>::DeleteMin(T& x)
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	//将数组第一个元素删除
	x = heap[1];
	//y是数组中最后一个元素，删除后填到根节点的位置
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;
	while (ci <= CurrentSize)
	{
		//使ci指向i的两个孩子中较小的一个
		if (ci < CurrentSize && heap[ci] > heap[ci + 1])
			ci++;
		//如果数组最后一个元素比ci小的话则正确，跳出循环赋值即可
		if (y <= heap[ci])
			break;
		//大于父节点的孩子节点上升，然后判断下一层
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}

template<class T>
void MinHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	//进行初始赋值工作
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;

	//从n/2处开始到根节点依次整理使其构建成最大堆
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];
		int c = 2 * i;
		while (c <= CurrentSize)
		{
			if (c < CurrentSize && heap[c] > heap[c + 1])
				c++;
			if (y <= heap[c])
				break;
			heap[c / 2] = heap[c];
			c *= 2;
		}
		heap[c / 2] = y;
	}
}

template<class T>
void HeapSort(T a[], int n)
{
	MinHeap<T>H(1);
	H.Initialize(a, n, n);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMin(x);
		a[i + 1] = x;
	}
	H.deactivateArray();
}