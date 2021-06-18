#include <iostream>
#include <vector>
#include <stack>
#define MAX 0x0fffffff
using namespace std;
vector<pair<int, int>> dijkstra(int begin, int n, vector<vector<int>> &map) {
	vector<bool> S(n, false);								// ���㼯��S 
	vector<pair<int, int>> Q(n, pair<int, int>(MAX, 0));	// �����ڵ�����ģ������ڵ��ǰһ���ڵ��� 
	
	Q[begin].first = 0;
	
	bool isAll = false;
	while(!isAll) {
		// �ҵ�����S����뼯����С�Ľڵ��ţ�������S 
		int minidx, mindis = MAX;
		for(int i = 0; i < n; i++) {
			if(S[i] == false && Q[i].first < mindis) {
				minidx = i;
				mindis = Q[i].first;
			}
		}
		S[minidx] = true;
		// ���¾�������ǰ�ڵ� 
		for(int i = 0; i < n; i++) {
			if(S[i] == false && Q[minidx].first + map[minidx][i] < Q[i].first) {
				Q[i].first = Q[minidx].first + map[minidx][i];
				Q[i].second = minidx;
			}
		}
		// �жϽڵ��Ƿ�ȫ������S��ȫ������S������ѭ�� 
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
	
	cout << "��ʼ��ţ�" << begin+1 << "   ������ţ�" << end+1 << endl;
	cout << "·����";
	while(!point.empty()) {
		cout << point.top()+1 << " ";
		point.pop();
	}
	cout << endl << "���ģ�" << Q[end].first << endl; 
}
int main() {
	int n, m, begin, end = 4;				// ����ڵ�������������ʼ���ţ��������� 
	cin >> n >> m >> begin;
	vector<vector<int>> map(n, vector<int>(n, MAX));
	for(int i = 0, u, v, w; i < m; i++) {	 
		cin >> u >> v >> w;					// �ߣ�uָ��vȨ��Ϊw
		if(u != v && map[u-1][v-1] > w) 	// ȥ���Ի����Լ����ڵ����·����̵�һ�� 
			map[u-1][v-1] = w;
	}	

	vector<pair<int, int>> Q = dijkstra(begin-1, n, map);
	
	print(begin-1, end-1, Q);				// ����ʱ�ڵ�Ϊ[1, n]��ʵ�ʴ���ʱ��[0, n-1]
	cout << "�������ڵ����ģ�";
	for(int i = 0; i < n; i++)
		cout << Q[i].first << " ";
	cout << endl;
	
	system("pause");
	return 0;
}