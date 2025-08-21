#include <bits/stdc++.h>

struct DrawbackDSU {
	int n, cnt;
	std::vector<int> f, siz, dep;
	std::vector<std::pair<int&, int>> his;

	DrawbackDSU() = default;

	DrawbackDSU(int n) { init(n); }
	
	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		dep.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find (int x) const {
		if (f[x] == x) return x;
		return find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (dep[x] < dep[y]) std::swap(x, y);
		his.push_back({f[y], f[y]});
		his.push_back({cnt, cnt});
		his.push_back({dep[x], dep[x]});
		his.push_back({siz[x], siz[x]});
		if (x == y) return false;
		dep[x] += dep[x] == dep[y];
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}
	
	void roll() {
		assert(his.size() >= 4);
		for (int i = 1; i <= 4; ++i) {
			auto [x, y] = his.back();
			x = y, his.pop_back();
		}
	}

	bool same(int x, int y) const {
		return find(x) == find(y);
	}

	int size(int x) const {
		return siz[find(x)];
	}

	int count() const {
		return cnt;
	}
};
