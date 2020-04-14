//https://leetcode-cn.com/problems/number-of-ways-to-paint-n-x-3-grid/

#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;


class Solution {
private:
	LL mod = 1e9 + 7;
	LL m[2][2] = { 3, 2, 2, 2 };
	LL tmp[2][2] = { 0, 0, 0, 0 };
	LL ans[2][2] = { 1, 0, 0, 1 };

public:
	// 矩阵快速幂：积的模等于取模的积 (a * b) % mod = ( (a % mod) * (b % mod) ) % mod	
	void matrixFastPow(int n, LL mod) {
		while (n) {
			if (n % 2) {
				memcpy(tmp, ans, sizeof(ans));
				for (int i = 0; i < 2; i++) {
					ans[i][0] = ((tmp[i][0] * m[0][0]) % mod + (tmp[i][1] * m[1][0]) % mod) % mod;
					ans[i][1] = ((tmp[i][0] * m[0][1]) % mod + (tmp[i][1] * m[1][1]) % mod) % mod;
				}
			}
			memcpy(tmp, m, sizeof(m));
			for (int i = 0; i < 2; i++) {
				// cout << tmp[0][0] << ' ' << tmp[0][1] << ' ' << tmp[1][0] << ' ' << tmp[1][1] << endl;
				m[i][0] = ((tmp[i][0] * tmp[0][0]) % mod + (tmp[i][1] * tmp[1][0]) % mod) % mod;
				m[i][1] = ((tmp[i][0] * tmp[0][1]) % mod + (tmp[i][1] * tmp[1][1]) % mod) % mod;
			}
			n /= 2;
		}

	}

	int numOfWays(int n) {
		if (n == 1) 
			return 12;
		matrixFastPow(n - 1, mod);
		int x = ((ans[0][0] * 6) % mod + (ans[0][1] * 6) % mod) % mod;
		int y = ((ans[1][0] * 6) % mod + (ans[1][1] * 6) % mod) % mod;
		return (LL)((x + y) % mod);
	}
};


int main()
{
	Solution S;
	cout<<S.numOfWays(7);
	return 0;
}