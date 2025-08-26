#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<array<int, 3>> a(m + 1);
	for (int i = 1; i <= m; ++i) {
		auto& [u, v, w] = a[i];
		cin >> u >> v >> w;
	}
	sort(a.begin() + 1, a.end(), [](const array<int, 3>& x, const array<int, 3>& y) {
		return x[2] > y[2];
	});

	WeightedDSU<int> dsu(n);
	for (int i = 1; i <= m; ++i) {
		auto [u, v, w] = a[i];
		if (!dsu.same(u, v)) {
			dsu.merge(u, v, 1);
		} else {
			int fu = dsu.query(u);
			int fv = dsu.query(v);
			if ((fu - fv) % 2 == 0) {
				cout << w << "\n";
				return;
			}
		}
	}
	cout << "0\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}