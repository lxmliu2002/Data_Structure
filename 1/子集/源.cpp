//#include<iostream>
//#include<fstream>
//using namespace std;
//void print(bool* b, int cur, int n)
//{
//	if (cur == n)
//	{
//		for (int i = 0; i < n; i++)
//		{
//			if (b[i])
//			{
//				if (i == n - 1)
//				{
//					cout << char('a' + i);
//				}
//				else
//				{
//					cout << char('a' + i) << " ";
//				}
//			}
//		}
//		cout << endl;
//	}
//	else
//	{
//		b[cur] = true;
//		print(b, cur + 1, n);
//		b[cur] = false;
//		print(b, cur + 1, n);
//	}
//}
//int main()
//{
//	int n;
//	/*ifstream infile("input.txt");
//	infile >> n;
//	infile.close();*/
//	cin >> n;
//	if (n <= 0 || n > 26)
//	{
//		cout << "WRONG" << endl;
//	}
//	else
//	{
//		cout << "―――――――――――" << endl << endl;
//		bool* b = new bool(n);
//		print(b, 0, n);
//		cout << "―――――――――――";
//	}
//	return 0;
//}





//#include<iostream>
//#include<fstream>
//using namespace std;
//void print(int n, char* total, int* now, int& time)
//{
//	//now  数组储存当前子集的状态
//	//time 储存当前进行到了第几位
//	if (time == n + 1)
//	{
//		time--;
//		return;
//	}
//
//	now[time] = 1;
//	for (int m = 1, test = 0; m <= n; m++)  //tset用于调整字母间空格 
//	{
//		if (now[m] == 1)
//		{
//			if (test == 1)
//				cout << ' ';  //test==1说明前面已经有字母出现了
//			cout << total[m];
//			test = 1;
//		}
//	}
//
//	cout << endl;
//	time++;  //进入下一级别的分支
//	print(n, total, now, time);
//	now[time] = 0;
//	time++;
//	print(n, total, now, time);
//	time--;  //当前位为0的状况下，下一级别的分支返回了，说明本分支以下的所有分支都执行完了，返回上一级
//	return;
//}
//
//int main()
//{
//	int time = 1;
//	char* total = new char[27];
//
//	for (int i = 1; i < 27; i++)
//		total[i] = 'a' + i - 1;
//
//	int now[30] = { 0 };  //0表示对应为空
//
//	int n;
//	/*ifstream infile("input.txt");
//	infile >> n;
//	infile.close();*/
//	cin >> n;
//	if (n < 1 || n>26)
//		cout << "WRONG" << endl;
//	else
//	{
//
//		print(n, total, now, time);
//		cout << endl;
//	}
//
//}


#include<iostream>
using namespace std;
int a[26];
void print(int a[]) {
	for (int i = 0; i < 26; i++) {
		if (a[i]) cout << char('a' + i) << " ";
	}
	cout << endl;
}
void findzc(int first, int len, int a[]) {
	if (len == 0) return;
	else {
		a[first] = 1;
		print(a);
		findzc(first + 1, len - 1, a);
		a[first] = 0;
		findzc(first + 1, len - 1, a);
	}
}
int main() {
	int n;
	cin >> n;
	if (n < 1 || n>26) {
		cout << "WRONG" << endl;
		return 0;
	}
	findzc(0, n, a);
	return 0;
}