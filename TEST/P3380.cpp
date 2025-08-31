/**
 * Author:  Thephix
 * Created: 2025/08/31 21:25:44
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;
using namespace std;

template<typename Info>
struct SegmentTreePool {
	int x, y;
	std::vector<Info> info;
	std::vector<int> ls, rs;

	SegmentTreePool(int x, int y, Info e = {}) {
		init(x, y, e);
	}

	void init(int x, int y, Info e = {}) {
		this -> x = x, this -> y = y;
		info.assign(1, e);
		ls.assign(1, 0);
		rs.assign(1, 0);
	}

	void pull(int u) {
		info[u] = info[ls[u]] + info[rs[u]];
	}

	int Node(int u) {
		info.push_back(info[u]);
		ls.push_back(ls[u]);
		rs.push_back(rs[u]);
		return info.size() - 1;
	}

	template<typename Func>
	int build(int l, int r, Func&& f) {
		int u = Node(0);
		if (l == r) {
			info[u] = f(l);
			return u;
		}
		int m = (l + r) >> 1;
		ls[u] = build(l, m, f);
		rs[u] = build(m + 1, r, f);
		pull(u);
		return u;
	}

	template<typename Func>
	[[nodiscard]] int build(Func&& f) {
		return build(x, y, f);
	}

	template<typename Func>
	int modify(int p, Func&& op, int u, int l, int r) {
		if (u == 0) u = Node(0);
		if (l == r) {
			op(info[u]);
			return u;
		}
		int m = (l + r) >> 1;
		if (p <= m) ls[u] = modify(p, op, ls[u], l, m);
		else rs[u] = modify(p, op, rs[u], m + 1, r);
		pull(u);
		return u;
	}

	template<typename Func>
	[[nodiscard]] int modify(int u, int p, Func&& op) {
		return modify(p, op, u, x, y);
	}

	template<typename Func>
	int extend(int p, Func&& op, int u, int l, int r) {
		u = Node(u);
		if (l == r) {
			op(info[u]);
			return u;
		}
		int m = (l + r) >> 1;
		if (p <= m) {
			ls[u] = extend(p, op, ls[u], l, m);
		} else {
			rs[u] = extend(p, op, rs[u], m + 1, r);
		}
		pull(u);
		return u;
	}

	template<typename Func>
	[[nodiscard]] int extend(int u, int p, Func&& op) {
		return extend(p, op, u, x, y);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if (R <= m) return query(L, R, ls[u], l, m);
		if (L > m)  return query(L, R, rs[u], m + 1, r);
		return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, x, y);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return y + 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls[u], l, m);
		if (p > y) {
			p = findL(L, R, f, rs[u], m + 1, r);
		}
		return p;
	}

	template<typename Func>
	int findL(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, u, x, y);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return x - 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs[u], m + 1, r);
		if (p < x) {
			p = findR(L, R, f, ls[u], l, m);
		}
		return p;
	}

	template<typename Func>
	auto findR(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, u, x, y);
	}

	template<typename Func>
	int merge(int u, int v, int l, int r, Func&& op) {
		if (u == 0 || v == 0) return u | v;
		if (l == r) {
			info[u] = op(info[u], info[v]);
			return u;
		}
		int m = (l + r) >> 1;
		ls[u] = merge(ls[u], ls[v], l, m, op);
		rs[u] = merge(rs[u], rs[v], m + 1, r, op);
		pull(u);
		return u;
	}

	template<typename Func>
	[[nodiscard]] int merge(int u, int v, Func&& op) {
		return merge(u, v, x, y, op);
	}
};

inline int lowbit(int x) { return x & -x; }

void solve() {
	int n, m;
	cin >> n >> m;
	SegmentTreePool<int> seg(0, 1E8);

	vector<int> a(n + 1);
	vector<int> rt(n + 1);

	auto rank = [&](int l, int r, int k) -> int {
		if (k == 0) return 1;
		l--;
		int ans = 0;
		for (int u = r; u; u -= lowbit(u)) {
			ans += seg.query(rt[u], 0, k - 1);
		}
		for (int u = l; u; u -= lowbit(u)) {
			ans -= seg.query(rt[u], 0, k - 1);
		}
		return ans + 1;
	};

	auto kth = [&](int l, int r, int k) -> int {
		assert(1 <= k && k <= r - l + 1);
		l--;
		vector<int> add, del;
		for (int u = r; u; u -= lowbit(u)) {
			add.push_back(rt[u]);
		}
		for (int u = l; u; u -= lowbit(u)) {
			del.push_back(rt[u]);
		}
		auto dfs = [&](auto&& dfs, int l, int r) -> int {
			if (l == r) return l;
			int cnt = 0;
			for (auto x : add) cnt += seg.info[seg.ls[x]];
			for (auto x : del) cnt -= seg.info[seg.ls[x]];
			int m = (l + r) >> 1;
			if (cnt >= k) {
				for (auto& x : add) x = seg.ls[x];
				for (auto& x : del) x = seg.ls[x];
				return dfs(dfs, l, m);
			} else {
				k -= cnt;
				for (auto& x : add) x = seg.rs[x];
				for (auto& x : del) x = seg.rs[x];
				return dfs(dfs, m + 1, r);
			}
		};
		return dfs(dfs, 0, 1E8);
	};

	auto modify = [&](int p, int x) -> void {
		for (int u = p; u <= n; u += lowbit(u)) {
			rt[u] = seg.modify(rt[u], a[p], [](int& cnt) { cnt--; });
		}
		a[p] = x;
		for (int u = p; u <= n; u += lowbit(u)) {
			rt[u] = seg.modify(rt[u], a[p], [](int& cnt) { cnt++; });
		}
	};

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		for (int u = i; u <= n; u += lowbit(u)) {
			rt[u] = seg.modify(rt[u], a[i], [&](int& cnt) { cnt++; });
		}
	}

	for (int i = 1; i <= m; ++i) {
		int op; cin >> op;
		if (op == 1) {
			int l, r, k;
			cin >> l >> r >> k;
			cout << rank(l, r, k) << "\n";
		} else if (op == 2) {
			int l, r, k;
			cin >> l >> r >> k;
			cout << kth(l, r, k) << "\n";
		} else if (op == 3) {
			int p, x;
			cin >> p >> x;
			modify(p, x);
		} else if (op == 4) {
			int l, r, k;
			cin >> l >> r >> k;
			int rk = rank(l, r, k) - 1;
			if (rk == 0) {
				cout << "-2147483647\n";
			} else {
				cout << kth(l, r, rk) << "\n";
			}
		} else {
			int l, r, k;
			cin >> l >> r >> k;
			int rk = rank(l, r, k + 1);
			if (rk == r - l + 2) {
				cout << "2147483647\n";
			} else {
				cout << kth(l, r, rk) << "\n";
			}
		}
	}
}

signed main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		solve ();
	}

	return 0;
}