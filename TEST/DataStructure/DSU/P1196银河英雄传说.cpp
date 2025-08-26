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

constexpr int N = 30000;

void Thephix() {
	WeightedDSU<int> dsu(N);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		char op;
		int u, v;
		cin >> op >> u >> v;
		if (op == 'M') {
			int fu = dsu.find(u);
			int fv = dsu.find(v);
			dsu.merge(fv, fu, dsu.size(fv));
		} else if (!dsu.same(u, v)) {
			cout << "-1\n";
		} else {
			int fu = dsu.query(u);
			int fv = dsu.query(v);
			cout << abs(fu - fv) - 1 << "\n";
		}
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