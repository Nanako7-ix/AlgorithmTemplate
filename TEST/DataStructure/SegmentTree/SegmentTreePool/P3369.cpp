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
	int merge(int u, int v, Func&& op) {
		return merge(u, v, x, y, op);
	}

	// int split(int p, int u, int l, int r) {

	// }
};

void Thephix() {
	int n;
	cin >> n;
	vector<int> dis;
	vector<array<i64, 2>> query(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [op, x] = query[i];
		cin >> op >> x;
		if (op != 4) dis.push_back(x);
	}
	sort(dis.begin(), dis.end());
	dis.erase(unique(dis.begin(), dis.end()), dis.end());

	int m = dis.size(), root = 0;
	SegmentTreePool<int> seg(1, m, 0);
	for (int i = 1; i <= n; ++i) {
		auto [op, x] = query[i];
		if (op != 4) {
			x = lower_bound(dis.begin(), dis.end(), x) - dis.begin() + 1;
		}
		if (op == 1) {
			root = seg.modify(root, x, [](int& cnt) { cnt++; });
		} else if (op == 2) {
			root = seg.modify(root, x, [](int& cnt) { cnt--; });
		} else if (op == 3) {
			cout << (x == 1 ? 0 : seg.query(root, 1, x - 1)) + 1 << "\n";
		} else if (op == 4) {
			cout << dis[seg.findL(root, 1, m, [&](int cnt) {
				if (cnt >= x) return true;
				x -= cnt;
				return false;
			}) - 1] << "\n";
		} else if (op == 5) {
			cout << dis[seg.findR(root, 1, x - 1, [&](int cnt) { return cnt > 0; }) - 1] << "\n";
		} else {
			cout << dis[seg.findL(root, x + 1, m, [&](int cnt) { return cnt > 0; }) - 1] << "\n";
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