#include <bits/stdc++.h>

using u64 = unsigned long long;

template<typename T>
std::vector<T> NTT(std::vector<T> a, std::vector<T> b) {
	static constexpr u64 P = T::mod();

	int tot = a.size() + b.size() - 1;
	int k = std::__lg(tot), n = 1 << (k + 1);

	std::vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
	}

	auto dft = [&](std::vector<T>& f, const T& g) {
		for (int i = 0; i < n; ++i) {
			if (i < rev[i]) std::swap(f[i], f[rev[i]]);
		}
		for (int i = 1; i < n; i <<= 1) {
			T wn = g.pow((P - 1) / (i << 1));
			for (int j = 0; j < n; j += 2 * i) {
				T w = 1;
				for (int k = 0; k < i; ++k, w *= wn) {
					T fx = f[j + k], fy = f[i + j + k] * w;
					f[j + k] = fx + fy;
					f[i + j + k] = fx - fy;
				}
			}
		}
	};

	a.resize(n), b.resize(n);
	dft(a, 3), dft(b, 3);

	for (int i = 0; i < n; ++i) {
		a[i] *= b[i];
	}
	
	dft(a, 332748118);
	const T inv = T(n).inv();
	for (int i = 0; i < tot; ++i) {
		a[i] *= inv;
	}
	
	return a;
}
