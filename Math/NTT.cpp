#include <bits/stdc++.h>

using u64 = unsigned long long;

template<typename T>
std::vector<T> NTT(std::vector<T> a, std::vector<T> b) {
	static constexpr u64 P = T::mod();
	static constexpr  T  g = 3;
	static std::vector<T> rt { 0, 1 };

	int tot = a.size() + b.size() - 1;
	int k = std::__lg(tot), n = 1 << (k + 1);

	std::vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
	}

	if ((int) rt.size() < n) {
		int k = std::countr_zero(rt.size());
		rt.resize(n);
		for (; (1 << k) < n; ++k) {
			auto e = g.pow((P - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); ++i) {
				rt[i << 1] = rt[i];
				rt[i << 1 | 1] = rt[i] * e;
			}
		}
	}

	auto dft = [&](std::vector<T>& f) {
		for (int i = 0; i < n; ++i) {
			if (i < rev[i]) {
				std::swap(f[i], f[rev[i]]);
			}
		}
		for (int i = 1; i < n; i <<= 1) {
			for (int j = 0; j < n; j += 2 * i) {
				for (int k = 0; k < i; ++k) {
					T fx = f[j + k], fy = f[i + j + k] * rt[i + k];
					f[j + k] = fx + fy;
					f[i + j + k] = fx - fy;
				}
			}
		}
	};

	a.resize(n), b.resize(n);
	dft(a), dft(b);

	for (int i = 0; i < n; ++i) {
		a[i] *= b[i];
	}

	std::reverse(a.begin() + 1, a.end());
	dft(a);
	a.resize(tot);
	T inv = T(n).inv();
	for (int i = 0; i < tot; ++i) {
		a[i] *= inv;
	}
	return a;
}
