#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> minp, P;

void sieve(int n) {
	minp.assign(n + 1, 0);
	P.clear();
	for (int i = 2; i <= n; ++i) {
		if (minp[i] == 0) {
			P.push_back(minp[i] = i);
		}
		for (i64 p : P) {
			if(i * p > n) break;
			minp[i * p] = p;
			if(i % p == 0) break;
		}
	}
}