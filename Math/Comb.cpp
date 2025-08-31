#include <bits/stdc++.h>

template<typename Z>
struct Comb {
	int n;
	std::vector<Z> f, g;
	Comb() : n(0), f{1}, g{1} {}
	void init(int m) {
		if (m <= n) return;
		f.resize(m + 1);
		g.resize(m + 1);
		for (int i = n + 1; i <= m; ++i) {
			f[i] = f[i - 1] * i;
		}
		g[m] = f[m].inv();
		for (int i = m; i >= n + 1; --i) {
			g[i - 1] = g[i] * i;
		}
		n = m;
	}
	Z fac(int m) {
		if (n < m) init(2 * m);
		return f[m];
	}
	Z invfac(int m) {
		if (n < m) init(2 * m);
		return g[m];
	}
	Z inv(int m) {
		return invfac(m) * fac(m - 1);
	}
	Z C(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(m) * invfac(n - m);
	}
	Z A(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(n - m);
	}
};
