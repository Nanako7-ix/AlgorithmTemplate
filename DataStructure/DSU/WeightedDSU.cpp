#include <bits/stdc++.h>

template<typename Info>
struct WeightedDSU {
	int n, cnt;
	std::vector<int> f, siz;
	std::vector<Info> info;

	WeightedDSU() = default;

	WeightedDSU(int n) { init(n); }

	void init(int n, Info e = {}) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		info.assign(n + 1, e);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if(f[x] == x) return x;
		int p = find(f[x]);
		info[x] = info[x] + info[f[x]];
		return f[x] = p;
	}

	bool merge(int x, int y, Info w) {
		w = w + info[x] - info[y];
		x = find(x), y = find(y);
		if (x == y) return false;
		info[y] = w;
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

	Info query(int x) {
		return info[x];
	}
};