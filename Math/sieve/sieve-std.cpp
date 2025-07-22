#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> minp, P;

void sieve(int N) {
    minp.assign(N + 1, 0);
    P.clear();
    for (int i = 2; i <= N; ++i) {
        if (minp[i] == 0) {
            P.push_back(minp[i] = i);
        }
        for (i64 p : P) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}