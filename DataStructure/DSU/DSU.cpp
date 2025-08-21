#include <bits/stdc++.h>

struct DSU {
	int n, cnt;
	std::vector<int> f, siz;

	DSU() = default;

	DSU(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if(f[x] == x) return x;
		return f[x] = find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	int size(int x) {
		return siz[find(x)];
	}

	int count() const {
		return cnt;
	}
};
