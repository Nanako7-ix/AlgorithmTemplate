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
		if (R <= m) return query(L, R, ls[u], l, m).apply(tag[u]);
		if (L > m)  return query(L, R, rs[u], m + 1, r).apply(tag[u]);
		return (query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r)).apply(tag[u]);
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, x, y);
	}
};

struct Tag {
	i64 add;
	Tag (int x = 0) {
		add = x;
	}
	void apply(const Tag& v) {
		add += v.add;
	}
};

struct Info {
	i64 sum, len;
	Info () { sum = len = 1; }
	Info (i64 x) {
		sum = x, len = 1;
	}
	Info apply(const Tag& v) {
		sum += v.add * len;
		return *this;
	}
};

Info operator+ (Info x, Info y) {
	Info res;
	res.sum = x.sum + y.sum;
	res.len = x.len + y.len;
	return res;
}

void Thephix() {
	int n, m, rt = 0;
	cin >> n >> m;

	LazySegmentTreePool<Info, Tag> seg(1, n);
	for (int i = 1; i <= n; ++i) {
		i64 x; cin >> x;
		rt = seg.modify(rt, i, i, x);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			cout << seg.query(rt, i, j).sum << "\n";
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
