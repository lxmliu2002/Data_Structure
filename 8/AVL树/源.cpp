#include<iostream>
#include<math.h>
#include"myExceptions.h"
#include"BinaryTree.h"
using namespace std;

template<class T>
class AVLTree :public BinaryTree<T> {
public:
	BinaryTreeNode<T>* Search(int x);//返回值为x的节点指针
	BinaryTreeNode<T>* TreeMax(BinaryTreeNode<T>* t);//返回子树中最大值的节点，即连续的最右侧的节点
	BinaryTreeNode<T>* TreeMin(BinaryTreeNode<T>* t);//返回子树中最小树的节点，及连续的最左侧的节点

	BinaryTreeNode<T>* LL(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* LR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RL(BinaryTreeNode<T>* t);

	int BalanceFactor(BinaryTreeNode<T>* t);//得到某个节点的平衡因子
	BinaryTreeNode<T>* Balance(BinaryTreeNode<T>* t);//根据平衡因子的大小判断是如何旋转

	AVLTree<T>& Insert(const T& t);
	BinaryTreeNode<T>* Insert(BinaryTreeNode<T>* temp, const T& t);
	AVLTree<T>& Delete(const T& t);
	BinaryTreeNode<T>* Delete(BinaryTreeNode<T>* temp, const T& t);

	int GetHeight(BinaryTreeNode<T>* t)const;
	void LeftNear(BinaryTreeNode<T>* t);

};

//返回值为x的节点指针
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Search(int x)
{
	BinaryTreeNode<T>* temp = AVLTree<T>::root;
	while (temp)
	{
		if (temp->data == x)
			break;
		else
		{
			if (temp->data < x)
				temp = temp->RightChild;
			else
				temp = temp->LeftChild;
		}
	}
	return temp;
}

//返回子树中最大值的节点，即连续的最右侧的节点
template<class T>
BinaryTreeNode<T>* AVLTree<T>::TreeMax(BinaryTreeNode<T>* t)
{
	if (!t)
		return NULL;
	while (t->RightChild)
	{
		t = t->RightChild;
	}
	return t;
}

//返回子树中最小树的节点，及连续的最左侧的节点
template<class T>
BinaryTreeNode<T>* AVLTree<T>::TreeMin(BinaryTreeNode<T>* t)
{
	if (!t)
		return NULL;
	while (t->LeftChild)
	{
		t = t->LeftChild;
	}
	return t;
}

//左侧的节点数多，使部分树根节点t向右旋转
//原来t的左孩子成为部分树的根，t的左孩子的右孩子成为t的左孩子
template<class T>
BinaryTreeNode<T>* AVLTree<T>::LL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	t->LeftChild = temp->RightChild;
	temp->RightChild = t;
	t->height = AVLTree<T>::Height(t);
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

//右侧的节点数多，是部分树的根节点t向左移动
//原来t的右孩子成为部分树的根，t的右孩子的左孩子成为t的右孩子
template<class T>
BinaryTreeNode<T>* AVLTree<T>::RR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	t->RightChild = temp->LeftChild;
	temp->LeftChild = t;
	t->height = AVLTree<T>::Height(t);
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

//左子树的右子树节点过多，先让左子树进行RR操作，再让部分根进行LL操作
template<class T>
BinaryTreeNode<T>* AVLTree<T>::LR(BinaryTreeNode<T>* t)
{
	t->LeftChild = RR(t->LeftChild);
	return LL(t);
}

//右子树的左子树节点过多，先让右子树进行LL操作，再让部分根进行RR操作
template<class T>
BinaryTreeNode<T>* AVLTree<T>::RL(BinaryTreeNode<T>* t)
{
	t->RightChild = LL(t->RightChild);
	return RR(t);
}

//返回某个节点的平衡因子
template<class T>
int AVLTree<T>::BalanceFactor(BinaryTreeNode<T>* t)
{
	return GetHeight(t->LeftChild) - GetHeight(t->RightChild);
}

//根据平衡因子的大小判断是如何旋转
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Balance(BinaryTreeNode<T>* t)
{
	int bf = BalanceFactor(t);
	if (bf > 1)
	{
		if (BalanceFactor(t->LeftChild) >= 0)
			t = LL(t);
		else
			t = LR(t);
	}
	else
	{
		if (bf < -1)
		{
			if (BalanceFactor(t->RightChild) <= 0)
				t = RR(t);
			else
				t = RL(t);
		}
	}
	return t;
}

//插入的接口函数
template<class T>
AVLTree<T>& AVLTree<T>::Insert(const T& t)
{
	AVLTree<T>::root = Insert(AVLTree<T>::root, t);
	return *this;
}

//插入函数
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Insert(BinaryTreeNode<T>* temp, const T& t)
{
	//函数终止的条件是找到了一个空节点，为其分配内存空间
	if (temp == 0)
	{
		temp = new BinaryTreeNode<T>(t);
	}
	else
	{
		if (t > temp->data)
		{
			temp->RightChild = Insert(temp->RightChild, t);
			//在右子树插入节点可能导致不平衡，故需对右子树进行平衡操作
			//而平衡操作可能导致子树根节点发生变化，故需更新当前根节点
			temp = Balance(temp);
		}
		if (t < temp->data)
		{
			temp->LeftChild = Insert(temp->LeftChild, t);
			//在左子树插入节点可能导致不平衡，故需对左子树进行平衡操作
			//而平衡操作可能导致子树根节点发生变化，故需更新当前根节点
			temp = Balance(temp);
		}
	}
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

template<class T>
AVLTree<T>& AVLTree<T>::Delete(const T& t)
{
	AVLTree<T>::root = Delete(AVLTree<T>::root, t);
	return *this;
}

template<class T>
BinaryTreeNode<T>* AVLTree<T>::Delete(BinaryTreeNode<T>* temp, const T& t)
{
	if (!Search(t))
	{
		cout << "无法删除，因为不存在值为" << t << "的节点！" << endl;
	}
	if (!AVLTree<T>::root)
	{
		return AVLTree<T>::root;
	}
	//情况一：要删除的节点位于左子树
	if (t < temp->data)
	{
		//调用递归，在temp的左子树上进行删除操作
		//并返回新的左子树根节点来更新旧节点
		temp->LeftChild = Delete(temp->LeftChild, t);
		if (BalanceFactor(temp) < -1)
			temp = Balance(temp);
	}
	else
	{
		//情况二：要删除的节点位于右子树
		if (t > temp->data)
		{
			//调用递归，在temp的右子树上进行删除操作
			//并返回新的右子树根节点来更新旧节点
			temp->RightChild = Delete(temp->RightChild, t);
			if (BalanceFactor(temp) > 1)
				temp = Balance(temp);
		}
		//情况三：要删除的节点就是当前的根节点
		else
		{
			//当根节点的左右子树都存在的情况下
			//使用前驱后继的好处是删除前驱/后继AVL树依旧是平衡的
			if (temp->LeftChild && temp->RightChild)
			{
				//左子树高于右子树，根节点的值替换为其直接前驱的值，转化为删除直接前驱
				if (BalanceFactor(temp) > 0)
				{
					//直接前驱是左子树中最大值的节点
					BinaryTreeNode<T>* node = TreeMax(temp->LeftChild);
					temp->data = node->data;
					//删除左子树上的前驱节点并更新左子树
					temp->LeftChild = Delete(temp->LeftChild, temp->data);
				}
				//右子树高于或等于左子树，根节点的值替换为其直接后继的值，转化为删除直接后继
				else
				{
					//直接后继是右子树中最小值的节点
					BinaryTreeNode<T>* node = TreeMin(temp->RightChild);
					temp->data = node->data;
					//删除右子树上的后继节点并更新右子树
					temp->RightChild = Delete(temp->RightChild, temp->data);
				}
			}
			//根节点只有一颗子树或不存在子树
			else
			{
				BinaryTreeNode<T>* node = temp;
				//把左子树或右子树赋值给根节点
				temp = (temp->LeftChild) ? (temp->LeftChild) : (temp->RightChild);
				delete node;
				node = NULL;
			}

		}
	}
	return temp;
}

//获得某个节点的高度
template<class T>
int AVLTree<T>::GetHeight(BinaryTreeNode<T>* t)const
{
	if (t == nullptr)
		return 0;
	return t->height;
}

template<class T>
void AVLTree<T>::LeftNear(BinaryTreeNode<T>* t)
{
	if (t == 0)
		return;
	if (t->LeftChild == 0 && t->RightChild == 0)
	{
		cout << t->data << " ";
		return;
	}
	int l = AVLTree<T>::Height(t->LeftChild);
	int r = AVLTree<T>::Height(t->RightChild);
	if (l < r && l != 0)
	{
		LeftNear(t->LeftChild);
	}
	else
	{
		if (l > r && r != 0)
		{
			LeftNear(t->RightChild);
		}
		else
		{
			LeftNear(t->LeftChild);
			LeftNear(t->RightChild);
		}
	}
}

int main()
{
	AVLTree<int> avl;
	srand(time(NULL));
	int tmp;
	cout << endl << "-----插入随机数-----" << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		tmp = rand() % 100;
		cout << tmp << " ";
		avl.Insert(tmp);
	}
	cout << endl;
	cout << endl << "-----树的高度-----" << endl << endl;
	cout << avl.Height(avl.root) << endl;
	cout << endl << "-----树的最初模样-----" << endl << endl;
	show(avl.root, 1);

	cout << endl << "-----删除最后一个插入的随机数-----" << endl << endl;
	avl.Delete(tmp);
	show(avl.root, 1);
	cout << endl;

	cout << endl << "-----距离根最近的叶节点的值-----" << endl << endl;
	avl.LeftNear(avl.root);
	cout << endl << endl;
	return 0;
}