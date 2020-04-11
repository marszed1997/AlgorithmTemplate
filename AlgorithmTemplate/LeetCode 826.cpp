// https://leetcode-cn.com/problems/most-profit-assigning-work/

#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define mid (left + right)/2
using namespace std;

const int maxn = 1e4 + 10;

vector<int> difficulty = { 2,4,6,8,10 }, profit = { 10,20,30,40,50 }, worker = { 4,5,6,7 };


class SegmentTree {
public:
	struct Node {
		int d, p;

		bool operator <(const Node& b) {
			return this->d < b.d;
		}
	}nod[maxn];

	int cover[maxn<<2];

public:
	void build(int root, int left, int right) {
		if (left == right) {
			cover[root] = nod[left].p; 
			return;
		}
		build(root << 1, left, mid);
		build(root << 1 | 1, mid + 1, right);
		cover[root] = max(cover[root << 1], cover[root << 1 | 1]);
	}

	int query(int root, int left, int right, int qstart, int qend) {
		if (qstart <= left && right <= qend)
			return cover[root];
		int ans = 0;
		if (qstart <= mid)
			ans = query(root << 1, left, mid, qstart, qend);
		if (mid < qend)
			ans = max(ans, query(root << 1 | 1, mid + 1, right, qstart, qend));
		return ans;
	}

	int Qquery(int left, int right, int w, int n) {
		if (nod[left].d > w) 
			return 0;
		if (nod[right].d <= w) 
			return query(1, 1, n, left, right);
		if (left == right)
			return nod[left].p;
		if (nod[mid].d <= w) 
			return max(query(1, 1, n, left, mid), Qquery(mid + 1, right, w, n));
		return Qquery(left, mid - 1, w, n);
	}
};


class Solution {
public:

	int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
		SegmentTree T;
		int ans = 0;
		for (int i = 0; i < difficulty.size(); i++) {
			T.nod[i + 1].d = difficulty[i];
			T.nod[i + 1].p = profit[i];
		}
		sort(T.nod + 1, T.nod + difficulty.size() + 1);
		T.build(1, 1, difficulty.size());
		for (int i = 0; i < worker.size(); i++) 
			ans += T.Qquery(1, difficulty.size(), worker[i], difficulty.size());
		return ans;
	}
};


int main()
{
	return 0;
}