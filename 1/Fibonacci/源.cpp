#include<iostream>
#include<fstream>
using namespace std;
long long Fibonacci(long long* F, int n)
{
	if (F[n] != 0)
	{
		return F[n];
	}
	else
	{
		F[n] = Fibonacci(F, n - 1) + Fibonacci(F, n - 2);
	}
	return F[n];
}
int main()
{
	ifstream infile("input.txt");
	int n;
	infile >> n;
	/*int n;
	cin >> n;*/
	long long* F = new long long[91];
	F[1] = F[2] = 1;
	for (int i = 3; i < 91; i++)
	{
		F[i] = 0;
	}
	if (n < 0 || n > 90)
	{
		cout << "WRONG" << endl;
	}
	else
	{
		/*cout << F[1] << endl << F[2] << endl;
		for (int i = 3; i < 91; i++)
		{
			F[i] = Fibonacci(F, i);
			cout << F[i] << endl;
		}*/
		F[n] = Fibonacci(F, n);
		cout << F[n] << endl;
	}
}