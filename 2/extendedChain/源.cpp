#include<iostream>
using namespace std;

template <typename T>
class node
{
public:
	T data;
	node* next;
	node()
	{
		next = nullptr;
	}
	node(T a)
	{
		data = a;
		next = nullptr;
	}
};
template <typename T>
class Chain
{
public:
	node<T>* head;
	node<T>* tail;
	Chain()
	{
		head = tail = nullptr;
	}
	void Insert(T a)
	{
		node<T>* tmp = new node<T>(a);
		if (head == nullptr)
		{
			head = tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tmp;
		}
	}
	void Print()
	{
		node<T>* cur = head;
		while (cur != nullptr)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
	}
	int Length()
	{
		node<T>* cur = head;
		int len = 0;
		while (cur != nullptr)
		{
			len++;
			cur = cur->next;
		}
		return len;
	}
};
template <typename T>
void meld(Chain<T>c1, Chain<T>c2, Chain<T>&c3)
{
	int min = 0;
	if (c1.Length() < c2.Length())
	{
		min = c1.Length();
	}
	else
	{
		min = c2.Length();
	}
	node<T>* cur1 = c1.head;
	node<T>* cur2 = c2.head;
	for (int i = 0; i < min; i++)
	{
		c3.Insert(cur1->data);
		c3.Insert(cur2->data);
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	if (min == c1.Length() && min == c2.Length())
	{
		return;
	}
	else if (min == c1.Length())//c1¶Ì
	{
		while (cur2 != nullptr)
		{
			c3.Insert(cur2->data);
			cur2 = cur2->next;
		}
		return;
	}
	else//c2¶Ì
	{
		while (cur1 != nullptr)
		{
			c3.Insert(cur1->data);
			cur1 = cur1->next;
		}
		return;
	}

}
int main()
{
	int a[10];
	node<int>* p = new node<int>[5];
	for(int i = 0; i < 4; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c1;
	for (int i = 0; i < 4; i++)
	{
		c1.Insert(p[i].data);
	}
	c1.Print();
	cout << c1.Length();
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c2;
	for (int i = 0; i < 5; i++)
	{
		c2.Insert(p[i].data);
	}
	c2.Print();
	cout << c2.Length();
	cout << endl;
	Chain<int>c3;
	meld(c1, c2, c3);
	c3.Print();
	cout << c3.Length();


}