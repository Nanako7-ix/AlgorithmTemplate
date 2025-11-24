#include <bits/stat.h>

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<Tag>  tag;

	LazySegmentTree() = default;

	LazySegmentTree(int n) { init(n); }
	
	template<typename Array>
	LazySegmentTree(int n, Array&& a) { init(n, a); }
	
	template<typename Iter>
	LazySegmentTree(const Iter& l, const Iter& r) { init(l, r); }

	void init(int n) {
		init(n, [](int) { return Info(); });
	}

	template<typename Array>
	void init(int n, Array&& a) {
		this -> n = n;
		info.assign(4 << __lg(n), Info());
		 tag.assign(4 << __lg(n),  Tag());
		build(1, 1, n, a);
	}

	template<typename Iter>
	void init(const Iter& l, const Iter& r) {
		init(r - l, [](int p) { return l[p - 1]; });
	}

	void pull(int u) {
		info[u] = info[ls] + info[rs];
	}

	void apply(int u, const Tag& v) {
		info[u].apply(v);
		 tag[u].apply(v);
	}

	void push(int u) {
		apply(ls, tag[u]);
		apply(rs, tag[u]);
		tag[u] = Tag();
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
		push(u);
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

	void modify(int L, int R, const Tag& v, int u, int l, int r) {
		if (L <= l && r <= R) {
			apply(u, v);
			return;
		}
		push(u);
		int m = (l + r) >> 1;
		if (L <= m) {
			modify(L, R, v, ls, l, m);
		}
		if (R > m) {
			modify(L, R, v, rs, m + 1, r);
		}
		pull(u);
	}
	
	void modify(int l, int r, const Tag& v) {
		assert(l <= r)
		modify(l, r, v, 1, 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		push(u);
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
		push(u);
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
		push(u);
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
