#include <bits/stdc++.h>

template<typename Info, typename Tag>
struct LazySegmentTreePool {
	int x, y;
	std::vector<Info> info;
	std::vector<Tag> tag;
	std::vector<int> ls, rs;

	LazySegmentTreePool(int x, int y, Info e = {}) {
		init(x, y, e);
	}

	void init(int x, int y, Info e = {}) {
		this -> x = x, this -> y = y;
		info.assign(1, e);
		tag.assign(1, Tag {});
		ls.assign(1, 0);
		rs.assign(1, 0);
	}

	void pull(int u) {
		info[u] = (info[ls[u]] + info[rs[u]]).apply(tag[u]);
	}

	int Node(int u) {
		assert(u == 0);
		info.push_back(info[u]);
		tag.push_back(tag[u]);
		ls.push_back(ls[u]);
		rs.push_back(rs[u]);
		return info.size() - 1;
	}

	template<typename Func>
	int modify(int p, Func&& op, Tag v, int u, int l, int r) {
		if (u == 0) u = Node(0);
		if (l == r) {
			info[u] = op(info[u], v);
			return u;
		}
		int m = (l + r) >> 1;
		v.apply(tag[u]);
		if (p <= m) ls[u] = modify(p, op, v, ls[u], l, m);
		else rs[u] = modify(p, op, v, rs[u], m + 1, r);
		pull(u);
		return u;
	}

	template<typename Func>
	[[nodiscard]] int modify(int u, int p, Func&& op) {
		return modify(p, op, Tag(), u, x, y);
	}

	int modify(int L, int R, const Tag& v, int u, int l, int r) {
		if (u == 0) u = Node(0);
		if (L <= l && r <= R) {
			info[u].apply(v);
			tag[u].apply(v);
			return u;
		}
		int m = (l + r) >> 1;
		if (L <= m) ls[u] = modify(L, R, v, ls[u], l, m);
		if (R  > m) rs[u] = modify(L, R, v, rs[u], m + 1, r);
		pull(u);
		return u;
	}

	[[nodiscard]] int modify(int u, int l, int r, const Tag& v) {
		return modify(l, r, v, u, x, y);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		Info ans;
		if (R <= m) {
			ans = query(L, R, ls[u], l, m);
		} else if (L > m) {
			ans = query(L, R, rs[u], m + 1, r);
		} else {
			ans = query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
		}
		ans.apply(tag[u]);
		return ans;
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, x, y);
	}

	int findL(int u, int l, int r, Func&& f) {
		
	}
};