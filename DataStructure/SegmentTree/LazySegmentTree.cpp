#include <bits/stat.h>

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info, typename Tag, int Base = 1>
class LazySegmentTree {
public:
	LazySegmentTree() = default;
	
	LazySegmentTree(int n) { init(n); }
	
	template<typename Func>
	LazySegmentTree(int n, Func&& f) { init(n, f); }
	
	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	LazySegmentTree(const Iter& l, const Iter& r) { init(l, r); }
	
	template<typename Func>
	void modify(int p, Func&& op) {
		p += offset;
		assert(1 <= p && p <= n);
		modify(p, op, 1, x, y);
	}
	
	void modify(int l, int r, const Tag& v) {
		l += offset, r += offset;
		assert(1 <= l && l <= r && r <= n);
		modify(l, r, v, 1, x, y);
	}
	
	Info query(int p) {
		p += offset;
		assert(1 <= p && p <= n);
		return query(p, 1, x, y);
	}
	
	Info query(int l, int r) {
		l += offset, r += offset;
		assert(1 <= l && l <= r && r <= n);
		return query(l, r, 1, x, y);
	}
	
	template<typename Func>
	std::optional<int> findL(int l, int r, Func&& f) {
		l += offset, r += offset;
		assert(1 <= l && l <= r && r <= n);
		return findL(l, r, f, 1, x, y);
	}
	
	template<typename Func>
	std::optional<int> findR(int l, int r, Func&& f) {
		l += offset, r += offset;
		assert(1 <= l && l <= r && r <= n);
		return findR(l, r, f, 1, x, y);
	}
private:
	constexpr static int offset = 1 - Base;
	
	int n, x, y;
	std::vector<Info> info;
	std::vector<Tag>  tag;

	void init(int n) {
		init(n, [](int) { return Info {}; });
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init(const Iter& l, const Iter& r) {
		init(r - l, [](int p) { return l[p - 1]; });
	}

	template<typename Func>
	void init(int n, Func&& f) {
		this -> n = n;
		x = 1 + offset;
		y = n + offset;
		info.assign(4 << __lg(n), Info {});
		tag.assign(4 << __lg(n), Tag {});
		build(1, 1, n, f);
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

	template<typename Func>
	void build(int u, int l, int r, Func&& f) {
		if (l == r) {
			info[u] = f(l);
			return;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, f);
		build(rs, m + 1, r, f);
		pull(u);
	}

	template<typename Func>
	void modify(int p, Func&& op, int u, int l, int r) {
		if (l == r) {
			op(info[u]);
			return;
		}
		int m = (l + r) >> 1;
		if (p <= m) modify(p, op, ls, l, m);
		else modify(p, op, rs, m + 1, r);
	}

	void modify(int L, int R, const Tag& v, int u, int l, int r) {
		if (L <= l && r <= R) {
			apply(u, v);
			return;
		}
		push(u);
		int m = (l + r) >> 1;
		if (L <= m) modify(L, R, v, ls, l, m);
		if (R > m) modify(L, R, v, rs, m + 1, r);
		pull(u);
	}

	Info query(int p, int u, int l, int r) {
		if (l == r) return info[u];
		push(u);
		int m = (l + r) >> 1;
		if (L <= m) return query(p, ls, l, m);
		if (R > m) return query(p, rs, m + 1, r);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		push(u);
		int m = (l + r) >> 1;

		if (R <= m) return query(L, R, ls, l, m);
		if (L > m) return query(L, R, rs, m + 1, r);

		return query(L, R, ls, l, m) + query(L, R, rs, m + 1, r);
	}

	template<typename Func>
	std::optional<int> findL(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) {
			return n + 1;
		}
		if(l == r) return l;
		push(u);
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls, l, m);
		if(p > n) {
			p = findL(L, R, f, rs, m + 1, r);
		}
		return p;
	}

	template<typename Func>
	std::optional<int> findR(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) {
			return x - 1;
		}
		if(l == r) return l;
		push(u);
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs, m + 1, r);
		if(p < x) p = findR(L, R, f, ls, l, m);
		return p;
	}
};
#undef ls
#undef rs
