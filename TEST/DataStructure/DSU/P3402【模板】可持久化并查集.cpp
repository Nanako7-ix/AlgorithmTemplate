#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<vector<array<int, 4>>> adj(m + 1);

	for (int i = 1; i <= m; ++i) {
		int op;
		cin >> op;
		if (op == 2) {
			int k;
			cin >> k;
			adj[k].push_back({i, op, k, 0});
		} else {
			int u, v;
			cin >> u >> v;
			adj[i - 1].push_back({i, op, u, v});
		}
	}

	DrawbackDSU dsu(n);
	vector<int> ans(m + 1, -1);
	auto jxt = [&](auto&& jxt, int u) -> void {
		for (auto [v, op, x, y] : adj[u]) {
			if (op == 1) {
				dsu.merge(x, y);
			} else if (op == 3) {
				ans[v] = dsu.same(x, y);
			}
			jxt(jxt, v);
			if (op == 1) dsu.roll();
		}
	}; jxt(jxt, 0);

	for (int i = 1; i <= m; ++i) {
		if (ans[i] == -1) continue;
		cout << ans[i] << "\n";
	}
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