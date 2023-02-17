#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 100;
vector<int> g[N];
int start, theEnd;
int reach[N], vis[N];
int m, n;
int len;


bool bfs(int v, int label)
{// 广度优先搜索， reach[i] 用来标记从顶点v可到达的所有顶点
	len = 1;
	queue<int>q;
	reach[v] = label;
	q.push(v);
	while (!q.empty())
	{
		// 从队列中删除一个标记过的顶点
		int w = q.front();
		q.pop();
		if (w == theEnd)
			break;
		// 标记所有没有到达的邻接于顶点w的顶点
		int u;
		for (int i = 0; i < g[w].size(); i++)
		{
			u = g[w][i];
			if (!vis[u])
			{
				len++;
				reach[u] = w;
				vis[u] = 1;
				q.push(u);
			}
		}
	}
	if (len == 1)
		return false;
	return true;
}
//从新使用bfs编写findpath函数
bool findpath_bfs(int Start, int End) {
	reach[1] = Start;
	len = 1;
	theEnd = End;
	fill(vis, vis + n, 0);
	if (Start == End || bfs(Start, 1)) {
		reach[0] = 0;
		return true;
	}
	return false;
}
//输出路径上的节点号
void show_bfs(int x) {
	if (x == start) {
		cout << x << " ";
		return;
	}
	show_bfs(reach[x]);
	cout << x << " ";
	reach[0]++;
}
int main() {
	cout << "请输入节点数和边数" << endl;
	cin >> n >> m;
	int u, v;
	cout << "请输入每条边两个节点编号" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cout << "请输入起始节点和终止节点" << endl;
	cin >> start >> theEnd;
	if (findpath_bfs(start, theEnd))
	{
		cout << "bfs路径:";
		show_bfs(theEnd);
		cout << endl;
		cout << "bfs路径长度:" << reach[0] << endl;
	}
	return 0;
}