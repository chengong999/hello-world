#include <iostream>
#include <vector>
#include <stack>
#define MAX 0x0fffffff
using namespace std;
vector<pair<int, int>> dijkstra(int begin, int n, vector<vector<int>> &map) {
	vector<bool> S(n, false);								// 顶点集合S 
	vector<pair<int, int>> Q(n, pair<int, int>(MAX, 0));	// 各个节点的消耗，各个节点的前一个节点编号 
	
	Q[begin].first = 0;
	
	bool isAll = false;
	while(!isAll) {
		// 找到集合S外距离集合最小的节点编号，并加入S 
		int minidx, mindis = MAX;
		for(int i = 0; i < n; i++) {
			if(S[i] == false && Q[i].first < mindis) {
				minidx = i;
				mindis = Q[i].first;
			}
		}
		S[minidx] = true;
		// 更新距离与先前节点 
		for(int i = 0; i < n; i++) {
			if(S[i] == false && Q[minidx].first + map[minidx][i] < Q[i].first) {
				Q[i].first = Q[minidx].first + map[minidx][i];
				Q[i].second = minidx;
			}
		}
		// 判断节点是否全部加入S，全部加入S，跳出循环 
		isAll = true;
		for(int i = 0; i < n; i++) {
			if(S[i] == false)
				isAll = false;
		}
	} 
	
	return Q;
}
void print(int begin, int end, vector<pair<int, int>> &Q) {
	stack<int> point;
	int point_temp = end;
	while(point_temp != begin) {
		point.push(point_temp);
		point_temp = Q[point_temp].second;
	}
	point.push(point_temp);
	
	cout << "开始编号：" << begin+1 << "   结束编号：" << end+1 << endl;
	cout << "路径：";
	while(!point.empty()) {
		cout << point.top()+1 << " ";
		point.pop();
	}
	cout << endl << "消耗：" << Q[end].first << endl; 
}
int main() {
	int n, m, begin, end = 4;				// 输入节点数，边数，起始点编号，结束点编号 
	cin >> n >> m >> begin;
	vector<vector<int>> map(n, vector<int>(n, MAX));
	for(int i = 0, u, v, w; i < m; i++) {	 
		cin >> u >> v >> w;					// 边：u指向v权重为w
		if(u != v && map[u-1][v-1] > w) 	// 去掉自环，以及两节点多条路径最短的一条 
			map[u-1][v-1] = w;
	}	

	vector<pair<int, int>> Q = dijkstra(begin-1, n, map);
	
	print(begin-1, end-1, Q);				// 输入时节点为[1, n]，实际处理时是[0, n-1]
	cout << "到各个节点消耗：";
	for(int i = 0; i < n; i++)
		cout << Q[i].first << " ";
	cout << endl;
	
	system("pause");
	return 0;
}