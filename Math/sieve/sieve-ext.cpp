#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> minp, P;
std::vector<i64> mu;

void sieve(int n) {
	minp.assign(n + 1, 0);
	P.clear();
	mu.assign(n + 1, 0); mu[1] = 1;

	std::vector<int> h(n + 1, 0);
	for(int i = 2; i <= n; ++i) {
		if(minp[i] == 0) {
			P.push_back(h[i] = minp[i] = i);
			mu[i] = -1;
		}
		for(i64 p : P) {
			i64 x = i * p;
			if(x > n) break;
			h[x] = (minp[x] = p) * (i % p ? 1 : h[i]);
			if(x == h[x]) {
				mu[x] = 0;
			} else {
				mu[x] = mu[h[x]] * mu[x / h[x]];
			}
			if(i % p == 0) break;
		}
	}
}

/**
 *    d   |   2   | f(i) + 1 |  因子个数
 *  sigma | x + 1 | f(i) + x |  因子和
 *   phi  | x - 1 | f(i) * p |  欧拉函数 (与 n 互素的数字个数)
 *   mu   |   -1  |     0    |  莫比乌斯函数 (莫比乌斯反演用)
 */
