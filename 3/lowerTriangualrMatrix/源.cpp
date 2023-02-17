#include<iostream>
using namespace std;

template <typename T>
class lowerTriangularMatrix
{
public:
	template<typename T>
	friend ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x);//重载输入运算符
	template<typename T>
	friend istream& operator>>(istream& in, lowerTriangularMatrix<T>& x);//重载输出运算符
	lowerTriangularMatrix(int size);//构造函数，生成大小为size的n阶方阵，并生成保存下三角的值的一维数组
	lowerTriangularMatrix();//构造函数，生成大小为size的n阶方阵，并生成保存下三角的值的一维数组
	~lowerTriangularMatrix();//析构函数，释放一维数组的空间
	void Outpuut1(ostream& out)const;//行主打印输出该矩阵
	void Outpuut2(ostream& out)const;//列主打印输出该矩阵
	void transpose(lowerTriangularMatrix<T>& x)const;//将矩阵x转置
	lowerTriangularMatrix<T>operator+(const lowerTriangularMatrix<T>& x)const;//重载+运算符
	lowerTriangularMatrix<T>operator-(const lowerTriangularMatrix<T>& x)const;//重载-运算符
	lowerTriangularMatrix<T>& Store(const T& x, int i, int j);//修改矩阵值
	T Retrieve(int i, int j)const;//读取矩阵的值
private:
	int n;
	T* t;
};

template<typename T>//重载输入运算符
istream& operator>>(istream& in, lowerTriangularMatrix<T>& x)
{
	for (int i = 0; i < x.n * (x.n + 1) / 2; i++)
	{
		in >> x.t[i];
	}
	return in;
}

template<typename T>//重载输出运算符
ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x)
{
	x.Outpuut1(out);
	return out;
}

template <typename T>//构造函数，生成大小为size的n阶方阵，并生成保存下三角的值的一维数组
lowerTriangularMatrix<T>::lowerTriangularMatrix(int size)
{
	n = size;
	t = new T[n * (n + 1) / 2];
}

template <typename T>//构造函数，生成大小为size的n阶方阵，并生成保存下三角的值的一维数组
lowerTriangularMatrix<T>::lowerTriangularMatrix()
{

}

template<typename T>//析构函数，释放一维数组的空间
lowerTriangularMatrix<T>::~lowerTriangularMatrix()
{
	delete[]t;
}

template<typename T>//行主打印输出该矩阵
void lowerTriangularMatrix<T>::Outpuut1(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			cout << t[i * (i - 1) / 2 + j] << " ";
		}
		for (int j = 0; j < n - i; j++)
		{
			cout << 0 << " ";
		}
		cout << endl;
	}
}

template<typename T>//列主打印输出该矩阵
void lowerTriangularMatrix<T>::Outpuut2(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			cout << 0 << " ";
		}
		for (int j = 0; j <= n - i; j++)
		{
			cout << t[(2 * n - i + 2) * (i - 1) / 2 + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>//将矩阵x转置
void lowerTriangularMatrix<T>::transpose(lowerTriangularMatrix<T>& x)const
{
	int count1 = 0, count2 = 0, position = 0, temp = 0;
	for (int i = 1; i <= n; i++)
	{
		temp = i;//temp是一个中间量，表示原矩阵同列元素在数组中的位置差值
		count1 = i * (i + 1) / 2;//count表示原矩阵前i行的元素个数
		position = count1;
		for (int j = 0; j <= n - i; j++)
		{
			//ij表示原矩阵第i行第j个元素在数组中的位置
			x.t[count2 + j] = t[position - 1];
			position += temp;
			temp++;
		}
		count2 += (n - i + 1);//temp2是新矩阵前n-1行元素个数
	}
}

template<typename T>//重载+运算符
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator+(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] + x.t[i];
	}
	return y;
}

template<typename T>//重载-运算符
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator-(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] - x.t[i];
	}
	return y;
}

template<typename T>//修改矩阵值
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::Store(const T& x, int i, int j)
{
	t[i * (i - 1) / 2 + j - 1] = x;
	return *this;
}

template<typename T>//读取矩阵的值
T lowerTriangularMatrix<T>::Retrieve(int i, int j)const
{
	if (i >= j)
	{
		return t[i * (i - 1) / 2 + j - 1];
	}
	else
	{
		return 0;
	}
}

int main()
{
	cout << "请选择实验数据类型：" << endl;
	cout << "A.整数   B.小数   C.字符" << endl;
	char m;
L:cin >> m;
	if (m == 'A')
	{
		int size;
		cout << endl << "请输入原下三角矩阵的行数：";
		cin >> size;
		lowerTriangularMatrix<int>x(size), y(size);
		cout << endl << "请输入原始数组：" << endl;
		cin >> x;
		cout << endl << "转置前的下三角矩阵为：" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "转置后的上三角矩阵为：" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'B')
	{
		int size;
		cout << endl << "请输入原下三角矩阵的行数：";
		cin >> size;
		lowerTriangularMatrix<float>x(size), y(size);
		cout << endl << "请输入原始数组：" << endl;
		cin >> x;
		cout << endl << "转置前的下三角矩阵为：" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "转置后的上三角矩阵为：" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'C')
	{
		int size;
		cout << endl << "请输入原下三角矩阵的行数：";
		cin >> size;
		lowerTriangularMatrix<char>x(size), y(size);
		cout << endl << "请输入原始数组：" << endl;
		cin >> x;
		cout << endl << "转置前的下三角矩阵为：" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "转置后的上三角矩阵为：" << endl;
		y.Outpuut2(cout);
	}
	if (m != 'A' && m != 'B' && m != 'C')
	{
		cout << "输入错误，请重新输入：" << endl;
		goto L;
	}
	return 0;
}