#include <bits/stdc++.h>

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info>
struct SegmentTree {
	int n;
	std::vector<Info> info;

	SegmentTree() = default;

	SegmentTree(int n) { init(n); }

	template<typename Array>
	SegmentTree(int n, Array&& a) { init(n, a); }

	template<typename Iter>
	SegmentTree(const Iter& l, const Iter& r) { init(l, r); }

	void init(int n) {
		init(n, [](int) { return Info(); });
	}

	template<typename Array>
	void init(int n, Array&& a) {
		this -> n = n;
		info.assign(4 << std::__lg(n), Info());
		build(1, 1, n, a);
	}

	template<typename Iter>
	void init(const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return l[p - 1]; });
	}

	void pull(int u) {
		info[u] = info[ls] + info[rs];
	}

	template<typename Array>
	void build(int u, int l, int r, Array&& a) {
		if (l == r) {
			info[u] = a(l);
			return;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a);
		build(rs, m + 1, r, a);
		pull(u);
	}

	template<typename Func>
	void modify(int p, Func&& op, int u, int l, int r) {
		if (l == r) {
			op(info[u]);
			return;
		}
		int m = (l + r) >> 1;
		if (p <= m) {
			modify(p, op, ls, l, m);
		} else {
			modify(p, op, rs, m + 1, r);
		}
		pull(u);
	}

	template<typename Func>
	void modify(int p, Func&& op) {
		modify(p, op, 1, 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if (R <= m) {
			return query(L, R, ls, l, m);
		} else if (L > m) {
			return query(L, R, rs, m + 1, r);
		} else {
			return query(L, R, ls, l, m) + query(L, R, rs, m + 1, r);
		}
	}

	Info query(int l, int r) {
		assert(l <= r);
		return query(l, r, 1, 1, n);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) return n + 1;
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls, l, m);
		if (p > n) p = findL(L, R, f, rs, m + 1, r);
		return p;
	}

	template<typename Func>
	int findL(int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, 1, 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) return 0;
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs, m + 1, r);
		if (p < 1) p = findR(L, R, f, ls, l, m);
		return p;
	}

	template<typename Func>
	auto findR(int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, 1, 1, n);
	}
};
#undef ls
#undef rs
