#include <bits/stdc++.h>

using u64 = unsigned long long;

template<int N>
struct Basis {
	std::array<u64, N + 1> a;
	Basis() : a {} ();
	void insert(int x) {
		for (int i = N; i >= 0; --i) {
			if (x >> i & 1) {
				if (a[i] == 0) {
					a[i] = x;
					break;
				}
				x ^= a[i];
			}
		}
	}
};
