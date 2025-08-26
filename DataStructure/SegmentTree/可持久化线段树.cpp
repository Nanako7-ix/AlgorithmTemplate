#include <bits/stdc++.h>

template<typename Info>
struct PersistentSegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<int> ls, rs, ver;

	PersistentSegmentTree() = default;

	PersistentSegmentTree(int n, int m) {
		init(n, m);
	}

	template<typename Func>
	PersistentSegmentTree(int n, int m, Func&& f) {
		init(n, m, f);
	}

	void init(int n, int m) {
		init(n, m, [](int p) { return Info {}; });
	}

	template<typename Func>
	void init(int n, int m, Func&& f) {
		this -> n = n;
		info.assign(1, Info {});
		ls.assign(1, 0);
		rs.assign(1, 0);
		ver.assign(m + 1, 0);
		build(ver[0], 1, n, f);
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
		u = Node(0);
		if (l == r) {
			info[u] = f(l);
		} else {
			int m = (l + r) >> 1;
			ls[u] = build(l, m, f);
			rs[u] = build(m + 1, r, f);
			pull(u);
		}
		return u;
	}

	template<typename Func>
	int modify(int p, Func&& op, int u, int l, int r) {
		u = Node(u);
		if (l == r) {
			op(info[u]);
		} else {
			int m = (l + r) >> 1;
			if (p <= m) {
				ls[u] = modify(p, op, ls[u], l, m);
			} else {
				rs[u] = modify(p, op, rs[u], m + 1, r);
			}
			pull(u);
		}
		return u;
	}

	template<typename Func>
	void modify(int u, int v, int p, Func&& op) {
		modify(p, op, ver[u], ver[v], 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if (R <= m) return query(L, R, ls[u], l, m);
		if (L > m) return query(L, R, rs[u], m + 1, r);
		return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, ver[u], 1, n);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return n + 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls[u], l, m);
		if (p > n) {
			p = findL(L, R, f, rs[u], m + 1, r);
		}
		return p;
	}

	template<typename Func>
	int findL(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, ver[u], 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return 0;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs[u], m + 1, r);
		if (p < 1) {
			p = findR(L, R, f, ls[u], l, m);
		}
		return p;
	}

	template<typename Func>
	auto findR(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, ver[u], 1, n);
	}
};
