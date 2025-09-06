#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

	int modify(int L, int R, const Tag& v, int u, int l, int r) {
		if (u == 0) u = Node(0);
		if (L <= l && r <= R) {
			apply(u, v);
			return u;
		}
		int m = (l + r) >> 1;
		if (L <= m) modify(L, R, v, ls[u], l, m);
		if (R  > m) modify(L, R, v, rs[u], m + 1, r);
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
		if (R <= m) return query(L, R, ls[u], l, m).apply(tag[u]);
		if (L > m)  return query(L, R, rs[u], m + 1, r).apply(tag[u]);
		return (query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r)).apply(tag[u]);
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, x, y);
	}

	// template<typename Func>
	// int findL(int L, int R, Func&& f, int u, int l, int r) {
	// 	if (l > R || r < L || !f(info[u])) {
	// 		return y + 1;
	// 	}
	// 	if (l == r) return l;
	// 	int m = (l + r) >> 1;
	// 	int p = findL(L, R, f, ls[u], l, m);
	// 	if (p > y) {
	// 		p = findL(L, R, f, rs[u], m + 1, r);
	// 	}
	// 	return p;
	// }

	// template<typename Func>
	// int findL(int u, int l, int r, Func&& f) {
	// 	assert(l <= r);
	// 	return findL(l, r, f, u, x, y);
	// }

	// template<typename Func>
	// int findR(int L, int R, Func&& f, int u, int l, int r) {
	// 	if (l > R || r < L || !f(info[u])) {
	// 		return x - 1;
	// 	}
	// 	if (l == r) return l;
	// 	int m = (l + r) >> 1;
	// 	int p = findR(L, R, f, rs[u], m + 1, r);
	// 	if (p < x) {
	// 		p = findR(L, R, f, ls[u], l, m);
	// 	}
	// 	return p;
	// }

	// template<typename Func>
	// auto findR(int u, int l, int r, Func&& f) {
	// 	assert(l <= r);
	// 	return findR(l, r, f, u, x, y);
	// }
};

void Thephix() {
	constexpr int inf = 1E9;
	
	int n;
	cin >> n;
	vector<vector<array<int, 3>>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		int l, r, c;
		cin >> l >> r >> c;
		a[c].push_back({l, r, i});
	}

	LazysegmentTreePool<Info, Tag> seg(1, inf);
	vector<int> ans(n + 1);

	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " \n"[i == n];
	}
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
