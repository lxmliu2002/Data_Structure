#include<iostream>
#include"myExceptions.h"

using namespace std;

//最大堆定义：
//每个节点的值都大于等于其子节点的值同时是一棵完全二叉树
template<class T>
class MaxHeap {
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap() { delete[]heap; }
	int Size()const { return CurrentSize; }
	//返回优先级最高的元素
	T Max()
	{
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax();
	//建堆函数
	void Initialize(T a[], int size, int ArraySize);
	// 将堆设置为空，但不释放空间——不销毁a
	void deactivateArray()
	{
		heap = NULL; CurrentSize = MaxSize = 0;
	}

	void print()
	{
		for (int i = 1; i <= CurrentSize; i++)
		{
			cout << heap[i] << " ";
		}
		cout << endl;
	}
private:
	int CurrentSize, MaxSize;
	//一维数组有效描述
	//堆节点从1开始编号，左孩子是2i，右孩子是2i+1
	T* heap;
	T maxElement = 100000000;
	T minElement = -1;
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[2 * MaxSize + 2];
	CurrentSize = 0;
	heap[0] = maxElement;
	for (int i = MaxSize + 1; i <= 2 * MaxSize + 1; i++)
	{
		heap[i] = minElement;
	}
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	int i = ++CurrentSize;
	//判断子节点是否比父节点大，是的话父节点下移

	//优化点在于有了heap[0]，可以省略i！=1的判断条件
	//因为无论如何x最后都小于heap[1/2]=heap[0]，然后跳出while
	//while (i != 1 && x > heap[i / 2])

	while (x > heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//将x插入合理位置
	heap[i] = x;
	return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax()
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	//将数组第一个元素删除
	//y是数组中最后一个元素，删除后填到根节点的位置
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;

	//有了极小值之后在比较的时候不需要设置下限，修改后如下
	while (true)
	{
		if (heap[ci] < heap[ci + 1])
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}

	heap[i] = y;
	heap[CurrentSize + 2] = minElement;
	return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
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
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;
			if (y >= heap[c])
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
	MaxHeap<T>H(1);
	H.Initialize(a, n, n);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		a[i + 1] = x;
	}
	H.deactivateArray();
}

int main() {
	int n;
	cout << "请输入数字个数n：";
	cin >> n;
	int* a = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		a[i] = rand() % 1000000;
	}
	MaxHeap<int> A(n);
	for (int i = 1; i <= n; i++)A.Insert(a[i]);
	A.print();
	cout << endl;
	A.DeleteMax();
	A.print();

	return 0;
}