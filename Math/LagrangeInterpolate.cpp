#include <bits/stdc++.h>

template<typename Z>
auto f = []() {
	constexpr int N = 100000;
	std::vector<Z> f(N + 1);
	f[0] = 1;
	for (int i = 1; i <= N; ++i) {
		f[i] = f[i - 1] * i;
	}
	return f;
} ();

template<typename Z>
auto g = []() {
	constexpr int N = 100000;
	std::vector<Z> g(N + 1);
	g[N] = f<Z>[N].inv();
	for (int i = N; i >= 1; --i) { // 这里不要复制前面的 f，别写成正序遍历了
		g[i - 1] = g[i] * i;
	}
	return g;
} ();

template<typename T>
T lagrangeIota(T x, const std::vector<T>& y) {
	int n = y.size();
	if (x < n) return y[x.val()];

	std::vector<T> lp(n + 1), rp(n + 1);
	lp[0] = rp[n] = 1;
	for (int i = 0; i < n; ++i) {
		lp[i + 1] = lp[i] * (x - i);
	}
	for (int i = n - 1; i >= 0; --i) {
		rp[i] = rp[i + 1] * (x - i);
	}

	T ans = 0;
	for (int i = 0; i < n; ++i) {
		if ((n - 1 - i) & 1) {
			ans -= y[i] * lp[i] * rp[i + 1] * g<T>[i] * g<T>[n - 1 - i];
		} else {
			ans += y[i] * lp[i] * rp[i + 1] * g<T>[i] * g<T>[n - 1 - i];
		}
	}
	return ans;
}

template<typename T>
T lagrangeAny(T x, const std::vector<std::pair<T, T>>& f) {
	T ans = 0; int n = f.size();
	for (int i = 0; i < n; ++i) {
		Z u = 1, d = 1;
		auto& [xi, yi] = f[i];
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			auto& [xj, yj] = f[j];
			if (x == xj) return yj;
			u *=  x - xj;
			d *= xi - xj;
		}
		ans += yi * u / d;
	}
	return ans;
}
