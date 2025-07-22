#include <bits/stdc++.h>

/**
 * 线性筛求解常见积性函数
 *    d   |   2   | f(i) + 1  |  因子个数
 *  sigma | 1 + i | f(i) + ip |  因子和
 *   phi  | i - 1 | f(i) * p  |  欧拉函数 (与 n 互素的数字个数)
 *   mu   |   -1  |     0     |  莫比乌斯函数 (莫比乌斯反演用)
 */

using i64 = long long;

std::vector<int> minp, P;
std::vector<i64> mu;

void sieve(int n) {
    minp.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    mu[1] = 1, P.clear();

    std::vector<i64> g(n + 1, 0);
    for(int i = 2; i <= n; ++i) {
        if(minp[i] == 0) {
            minp[i] = i;
            g[i] = i, mu[i] = -1;
            P.push_back(i);
        }
        for(auto p : P) {
            if(i * p > n) break;
            minp[i * p] = p;
            g[i * p] = p * (i % p ? 1 : g[i]);
            if(i * p == g[i * p]) mu[i * p] = 0;
            else mu[i * p] = mu[g[i * p]] * mu[i * p / g[i * p]];
            if(i % p == 0) break;
        }
    }
}