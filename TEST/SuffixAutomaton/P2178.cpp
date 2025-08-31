#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct SAM {
public:
	SAM (int n = 0) {
		t.reserve(n);
		t.assign(2, Node {});
		t[0].next.fill(1);
		t[0].len = -1;
		substr = 0;
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int extend(int p, int c) {
		if (t[p].next[c]) {
			int q = t[p].next[c];
			if (t[q].len == t[p].len + 1) {
				return q;
			}
			int r = newNode();
			t[r].len = t[p].len + 1;
			t[r].link = t[q].link;
			t[r].next = t[q].next;
			t[q].link = r;
			while (t[p].next[c] == q) {
				t[p].next[c] = r;
				p = t[p].link;
			}
			return r;
		}

		int cur = newNode();
		t[cur].len = t[p].len + 1;
		while (!t[p].next[c]) {
			t[p].next[c] = cur;
			p = t[p].link;
		}

		t[cur].link = extend(p, c);
		substr += t[cur].len - t[t[cur].link].len;
		return cur;
	}

	int len(int p) {
		return t[p].len;
	}

	int link(int p) {
		return t[p].link;
	}

	int next(int p, int x) {
		return t[p].next[x];
	}
			
	int size() {
		return t.size();
	}

	i64 count () {
		return substr;
	}

	auto getTree() -> std::vector<std::vector<int>> {
		int n = t.size();
		std::vector<std::vector<int>> adj(n);
		for (int i = 2; i < n; ++i) {
			adj[t[i].link].push_back(i);
		}
		return adj;
	}

private:
	static constexpr int N = 26;
	struct Node {
		int len;
		int link;
		std::array<int, N> next;
		Node() : len(), link(), next() {}
	};

	i64 substr;
	std::vector<Node> t;
};

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<Tag>  tag;

	LazySegmentTree() = default;

	LazySegmentTree(int n) { init(n); }

	template<typename Func>
	LazySegmentTree(int n, Func&& f) { init(n, f); }

	void init(int n) {
		init(n, [](int p) { return Info {}; });
	}

	template<typename Func>
	void init(int n, Func&& f) {
		this -> n = n;
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
		tag[u] = Tag {};
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
		if (L <= m) modify(L, R, v, ls, l, m);
		if (R > m)  modify(L, R, v, rs, m + 1, r);
		pull(u);
	}

	void modify(int l, int r, const Tag& v) {
		assert(l <= r);
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
	int findL(int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, 1, 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) {
			return -0;
		}
		if(l == r) return l;
		push(u);
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs, m + 1, r);
		if(p < 1) {
			p = findR(L, R, f, ls, l, m);
		}
		return p;
	}

	template<typename Func>
	int findR(int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, 1, 1, n);
	}
};
#undef ls
#undef rs

constexpr i64 inf = 2E9;
constexpr i64 INF = 4E18;

struct Info {
	i64 cnt, Max;
	Info () {
		cnt = 0, Max = -INF;
	}
	Info (i64 x, i64 y) {
		cnt = x, Max = y;
	}
	void apply (const Info& v) {
		cnt += v.cnt;
		Max = max(Max, v.Max);
	}
};

Info operator+ (const Info& x, const Info y) {
	return Info { x.cnt + y.cnt, max(x.Max, y.Max) };
}

void Thephix() {
	int n;
	string s;
	cin >> n >> s;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	reverse(s.begin(), s.end());
	reverse(a.begin() + 1, a.end());

	SAM sam(n);
	vector<int> p(n + 1);
	p[0] = 1;
	for (int i = 0; i < n; ++i) {
		p[i + 1] = sam.extend(p[i], s[i] - 'a');
	}

	int m = sam.size() - 1;
	vector<i64> cnt(m + 1);
	vector<array<i64, 2>> Max(m + 1, { -inf, -inf });
	vector<array<i64, 2>> Min(m + 1, {  inf,  inf });
	for (int i = 1; i <= n; ++i) {
		cnt[p[i]] = 1;
		Max[p[i]] = { a[i], -inf };
		Min[p[i]] = { a[i],  inf };
	}
	
	LazySegmentTree<Info, Info> seg(n);
	auto adj = sam.getTree();
	auto dfs = [&](auto&& dfs, int u) -> void {
		for (int v : adj[u]) {
			dfs(dfs, v);
			cnt[u] += cnt[v];
			array<i64, 4> tmp;
			tmp = { Max[u][0], Max[u][1], Max[v][0], Max[v][1] };
			sort(tmp.begin(), tmp.end(), greater {});
			Max[u] = { tmp[0], tmp[1] };

			tmp = { Min[u][0], Min[u][1], Min[v][0], Min[v][1] };
			sort(tmp.begin(), tmp.end(), less {});
			Min[u] = { tmp[0], tmp[1] };
		}
		int l = sam.len(sam.link(u)) + 1;
		int r = sam.len(u);
		if (r == n) return;
		if (Max[u][1] != -inf) {
			seg.modify(l + 1, r + 1, {
				cnt[u] * (cnt[u] - 1) / 2,
				Max[u][0] * Max[u][1]
			});
		}
		if (Min[u][1] !=  inf) {
			seg.modify(l + 1, r + 1, {
				cnt[u] * (cnt[u] - 1) / 2,
				Min[u][0] * Min[u][1]
			});
		}
	}; dfs(dfs, 1);

	for (int i = 1; i <= n; ++i) {
		auto [x, y] = seg.query(i, i);
		if (x == 0) y = 0;
		cout << x / 2 << ' ' << y << "\n";
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