#include <bits/stdc++.h>

template<typename T, bool SORT = true>
std::vector<T> divisor(std::vector<std::pair<T, int>> pf) {
	std::vector<T> res = { 1 };
	for (auto& [p, e] : pf) {
		int siz = res.size();
		for (int i = 0; i < siz; ++i) {
			T x = 1;
			for (int j = 0; j < e; ++j) {
				x *= p;
				res.push_back(res[i] * x);
			}
		}
	}
	if (SORT) std::sort(res.begin(), res.end());
	return res;
}
