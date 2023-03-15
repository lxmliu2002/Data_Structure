#include<iostream>
#include"MinHeap.h"
#include"BinaryTree.h"
using namespace std;

template<class T>
class Huffman {
	friend BinaryTree<int>HuffmanTree(T[], int);
public:
	operator T()const
	{
		return weight;
	}
public:
	BinaryTree<int>tree;
	T weight;
};

template<class T>
BinaryTree<int>HuffmanTree(T a[], int n)
{
	Huffman<T>* w = new Huffman<T>[n + 1];
	BinaryTree<int>z, zero;
	for (int i = 1; i <= n; i++)
	{
		z.MakeTree(i, zero, zero);
		w[i].weight = a[i];
		w[i].tree = z;
	}
	MinHeap<Huffman<T>>H(1);
	H.Initialize(w, n, n);
	Huffman<T>x, y;
	for (int i = 1; i < n; i++)
	{
		H.DeleteMin(x);
		H.DeleteMin(y);
		z.MakeTree(0, x.tree, y.tree);
		x.weight += y.weight;
		x.tree = z;
		H.Insert(x);
	}
	H.DeleteMin(x);
	H.Deactivate();
	delete[]w;
	return x.tree;
}

int main()
{
	int a[11];
	int n = 10;
	for (int i = 1; i <= n; i++)
		a[i] = 2 * i;
	BinaryTree<int> x = HuffmanTree(a, n);
	show(x.root, 1);
	return 0;
}