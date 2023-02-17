#include <iostream>
#include<stdio.h>
#include <stack>
#include<queue>
#include<cmath>
#include <fstream>
#include <iomanip>

using namespace std;
int yx[128];//表示优先级
string transform(string zhongzhui)//中缀转后缀
{
/*借助栈
1）遇到左括号，入栈
2）遇到右括号，弹出栈中元素，直到弹出的是左括号为止
3）遇到运算符，如果栈为空，运算符直接入栈；否则栈中优先级大于等于该运算符的出栈，该运算符入栈
4）遇到数字，直接输出
最后把栈中剩余元素依次弹出
*/
	char c;
	string tmp, houzhui;
	stack<char>st;
	int len = zhongzhui.length();
	for (int i = 0; i < len; i++)
	{
		c = zhongzhui[i];
		if (c == '(')//遇到左括号，入栈
		{
			st.push(c);
		}
		else if (c == ')')//遇到右括号，弹出栈中元素，直到弹出的是左括号为止
		{
			while (st.top() != '(') {
				tmp = st.top();
				houzhui.append(tmp);
				st.pop();
			}
			st.pop();
		}
		else if (st.empty() && yx[c] >= 1)//遇到运算符，如果栈为空，运算符直接入栈
		{
			st.push(c);
		}
		else if (yx[c] >= 1) //遇到运算符，栈非空，栈中优先级大于等于该运算符的出栈，该运算符入栈
		{
			while (!st.empty() && yx[st.top()] >= yx[c]) {
				tmp = st.top();
				houzhui.append(tmp);
				st.pop();
			}
			st.push(c);
		}
		else//遇到数字，直接输出
		{
			tmp = c;
			houzhui.append(tmp);
		}
	}
	while (!st.empty())//最后把栈中剩余元素依次弹出
	{
		tmp = st.top();
		houzhui.append(tmp);
		st.pop();
	}
	return houzhui;
}

struct Node {
	char data;
	Node* lchild, * rchild;
	Node() {
		data = 0;
		lchild = NULL;
		rchild = NULL;
	}
};

Node* build_Tree(string s)
{
	char c;
	int len = s.length();
	Node* p = nullptr;
	if (len == 0)
	{
		cout << "空" << endl;
		return p;
	}
	stack<Node*>st;
	for (int i = 0; i < len; i++) {
		c = s[i];
		if (yx[c] >= 1) {
			p = new Node;
			Node* tmp = st.top();
			p->rchild = tmp;
			st.pop();
			tmp = st.top();
			p->lchild = tmp;
			st.pop();
			p->data = c;
			st.push(p);
		}
		else {
			p = new Node;
			p->data = c;
			st.push(p);
		}
	}
	return p;
}

void show(Node* x, int d) {
	if (x != NULL) {
		show(x->rchild, d + 1);
		cout.setf(ios::right);
		cout << setw(3 * d) << " ";
		cout << x->data << endl;
		show(x->lchild, d + 1);
	}

}

int main()
{
	memset(yx, 0, sizeof(yx));
	yx['+'] = yx['-'] = 1;
	yx['*'] = yx['/'] = 2;
	string s1, s2;
	cout << "输入中缀表达式" << endl;
	cin >> s1;
	s2 = transform(s1);
	cout <<"该中缀表达式的后缀表达式为"<< s2 << endl;
	Node* root = build_Tree(s2);
	show(root, 1);
	return 0;
}