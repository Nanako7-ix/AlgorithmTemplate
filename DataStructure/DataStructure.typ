= DSU

== 

```cpp
struct DSU {
	int n, cnt;
	std::vector<int> f, siz;

	DSU() = default;
	DSU(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if (f[x] == x) return x;
		return f[x] = find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}

	bool same(int x, int y) { return find(x) == find(y); }
	int size(int x) { return siz[find(x)]; }
	int count() const { return cnt; }
};
```

== 

```cpp
template<typename Info> struct WeightedDSU {
	int n, cnt;
	std::vector<int> f, siz;
	std::vector<Info> info;

	WeightedDSU() = default;
	WeightedDSU(int n) { init(n); }

	void init(int n, Info e = {}) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		info.assign(n + 1, e);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if (f[x] == x) return x;
		int p = find(f[x]);
		info[x] = info[x] + info[f[x]];
		return f[x] = p;
	}

	bool merge(int x, int y, Info w) {
		w = w + info[x] - info[y];
		x = find(x), y = find(y);
		if (x == y) return false;
		info[y] = w;
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}

	bool same(int x, int y) { return find(x) == find(y); }
	int size(int x) { return siz[find(x)]; }
	int count() const { return cnt; }
	Info query(int x) const { return info[x]; }
};
```

== 

```cpp
struct DrawbackDSU {
	int n, cnt;
	std::vector<int> f, siz, dep;
	std::vector<std::pair<int&, int>> his;

	DrawbackDSU() = default;

	DrawbackDSU(int n) { init(n); }
	
	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		dep.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find (int x) const {
		if (f[x] == x) return x;
		return find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (dep[x] < dep[y]) std::swap(x, y);
		his.push_back({f[y], f[y]});
		his.push_back({cnt, cnt});
		his.push_back({dep[x], dep[x]});
		his.push_back({siz[x], siz[x]});
		if (x == y) return false;
		dep[x] += dep[x] == dep[y];
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}
	
	void roll() {
		assert(his.size() >= 4);
		for (int i = 1; i <= 4; ++i) {
			auto [x, y] = his.back();
			x = y, his.pop_back();
		}
	}

	bool same(int x, int y) const { return find(x) == find(y); }
	int size(int x) const { return siz[find(x)]; }
	int count() const { return cnt; }
};
```

= SparseTanle

== 

```cpp
template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;

	SparseTable () = default;

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	SparseTable (const Iter& l, const Iter& r, Func&& f) : n(r - l), op(f) {
		st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = l[i - 1];
		}
		for (int i = 1; i <= std::__lg(n); ++i) {
			for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
				st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	template<typename Array>
	SparseTable (int n, Array&& a, Func&& f) : n(n), op(f) {
		st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = a(i);
		}
		for (int i = 1; i <= std::__lg(n); ++i) {
			for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
				st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	T operator () (int l, int r) {
		assert(l <= r);
		int k = std::__lg(r - l + 1);
		return op(st[k][l], st[k][r - (1 << k) + 1]);
	}
};

template<typename Iter, typename Func>
SparseTable (const Iter&, const Iter&, Func&&) ->
SparseTable<typename std::iterator_traits<Iter>::value_type, Func>;

template<typename Array, typename Func>
SparseTable (int, Array&&, Func&&) ->
SparseTable<std::invoke_result_t<Array, int>, Func>;
```

==

```cpp
template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;
	SparseTable () = default;

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	SparseTable (const Iter& l, const Iter& r, Func&& f) : n(r - l), op(f) {
		st.assign(std::__lg(n) / 2 + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = l[i - 1];
		}
		for (int i = 1; i <= std::__lg(n) / 2; ++i) {
			for (int j = 1; j + (1 << (i << 1)) - 1 <= n; ++j) {
				st[i][j] = op(
					op(
						st[i - 1][j + (0 << ((i - 1) << 1))],
						st[i - 1][j + (1 << ((i - 1) << 1))]
					),
					op(
						st[i - 1][j + (2 << ((i - 1) << 1))],
						st[i - 1][j + (3 << ((i - 1) << 1))]
					)
				);
			}
		}
	}

	T operator () (int l, int r) {
		assert(l <= r);
		int k = std::__lg(r - l + 1) / 2;
		if ((2 << (k << 1)) >= r - l + 1) {
			return op(st[k][l], st[k][r - (1 << (k << 1)) + 1]);
		} else {
			return op(st[k][l], operator()(l + (1 << (k << 1)), r));
		}
	}
};
template<typename Iter, typename Func>
SparseTable (const Iter&, const Iter&, Func&&) ->
SparseTable<typename std::iterator_traits<Iter>::value_type, Func>;
```

= BIT

```cpp
template<typename T>
struct BIT {
	int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return ; }

	BIT () = default;
	BIT (int n, const T& e = T()) { init(n, e); }

	template<typename Array> BIT (int n, Array&& a) { init(n, a); }

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	BIT (const Iter& l, const Iter& r) { init(l, r); }

	void init (int n, const T& e = T()) {
		init(n, [&](int) { return e; });
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init (const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return l[p - 1]; });
	}

	template<typename Array>
	void init (int n, Array&& a) {
		this -> n = n;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += a(i);
			if(i + (i & -i) <= n) {
				tr[i + (i & -i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		for(; p <= n; p += p & -p) tr[p] += v;
	}

	T query (int p) {
		T res = T();
		for(; p; p -= p & -p) res += tr[p];
		return res;
	}

	T query (int l, int r) {
		return query(r) - query(l - 1);
	}


	int lower_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] < k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}

	int upper_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] <= k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}
};
```

= CartesionTree

```cpp
// f(a[fa], a[son]) = true
// return: 1-based [rt, ls, rs, fa]
template<typename Iter, typename Func, typename = std::_RequireInputIter<Iter>>
auto CartesianTree(const Iter& l, const Iter& r, Func&& f) {
	int n = r - l;
	std::vector<int> ls(n + 1), rs(n + 1), fa(n + 1);
	std::vector<int> stk;

	auto a = [&](int p) {
		return *(l + p - 1);
	};

	for(int i = 1; i <= n; ++i) {
		while(!stk.empty() && f(a(i), a(stk.back()))) {
			ls[i] = stk.back();
			stk.pop_back();
		}
		fa[ls[i]] = i;
		if(!stk.empty()) {
			rs[stk.back()] = i;
			fa[i] = stk.back();
		}
		stk.push_back(i);
	}

	return std::tuple { stk[0], std::move(ls), std::move(rs), std::move(fa) };
}



```

= MooreVote

```cpp
#define v first
#define c second
template<typename T, int _N>
struct MooreVote {
	using Vote = pair<T, i64>;
	constexpr static int N = _N - 1;
	
	array<Vote, N> d;
	
	MooreVote () { d.fill(Vote { T(), 0 }); }
	MooreVote (const T& e, i64 cnt = 1) {
		d.fill(Vote { T(), 0 });
		d[0] = Vote { e, cnt };
	}
	
	void merge(const Vote& vote) {
		for (auto& [v, c] : d) {
			if (v == vote.v) {
				c += vote.c;
				return;
			}
		}

		auto p = min_element(d.begin(), d.end(), [](const Vote& x, const Vote& y) {
			return x.c < y.c;
		}) - d.begin();

		int del = min(d[p].c, vote.c);
		if (d[p].c < vote.c) {
			d[p] = vote;
		}
		for(auto& [v, c] : d) {
			if (c > 0) c -= del;
		}
	}
	
	friend MooreVote operator+(MooreVote x, MooreVote y) {
		for (Vote& vote : y.d) x.merge(vote);
		return x;
	}
};
#undef v
#undef c

template<typename T>
struct MooreVote<T, 2> {
	T v; i64 c;
	
	MooreVote () { v = T(), c = 0; }
	MooreVote (const T& e, i64 cnt = 1) {
		v = e, c = cnt;
	}


	friend MooreVote operator+(MooreVote x, MooreVote y) {
		if (x.v == y.v) {
			return { x.v, x.c + y.c };
		} else if (x.c <= y.c) {
			return { y.v, y.c - x.c };			
		} else {
			return { x.v, x.c - y.c };
		}
	}
};
```

= ChthollyTree

```cpp
// Requires: Fn.offset(int)
template<typename Fn>
struct ChthollyTree {
	struct Node {
		i64 l, r;
		mutable Fn v;
		Node (i64 l, i64 r, Fn v) {
			this -> l = l;
			this -> r = r;
			this -> v = v;
		}
		bool operator< (const Node& o) const {
			return l < o.l;
		}
	};
	
	i64 n;
	std::set<Node> odt;
	
	ChthollyTree (i64 n) { init(n); }

	void init (i64 n) {
		this -> n = n;
		odt.clear();
		odt.emplace(1, n, Fn());
	}

	std::set<Node>::iterator split(i64 p) {
		if (p == n + 1) return odt.end();
		auto it = odt.lower_bound(Node {p, 0, Fn()});
		if (it != odt.end() && it -> l == p) return it;
		--it;
		auto [l, r, v] = *it;
		odt.erase(it);

		odt.emplace(l, p - 1, v);
		v.offset(r - l + 1);
		return odt.emplace(p, r, v).first;
	}




	void assign(int l, int r, const Fn& val) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		odt.erase(x, y);
		odt.emplace(l, r, val);
	}

	template<typename F>
	void perform(int l, int r, F&& f) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		for (auto it = x; it != y; ++it) {
			auto& [l, r, v] = *it;
			f(l, r, v);
		}
	}
};
```

= HLD
*
$
"ds"("dfn"(\*)) &= a(\*)\
"ds"(\*) &= a("idfn"(\*))
$
*
```cpp
struct HLD {
	int n = 0, tot = 0;
	std::vector<std::vector<int>> adj;
	std::vector<int> dfn, idfn, siz, fa, top, dep;

	HLD() = default;
	HLD(int n) { init(n); }
	void init(int n) {
		this -> n = n;
		tot = 0;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, 0);
		idfn.assign(n + 1, 0);
		siz.assign(n + 1, 0);
		fa.assign(n + 1, 0);
		top.assign(n + 1, 0);
		dep.assign(n + 1, 0);
	}

	void add(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void work(int root = 1) {
		dfs1(root);
		top[root] = root;
		dfs2(root);
	}

	void dfs1(int u) {
		if (fa[u] != 0) {
			adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
		}
		siz[u] = 1;
		for (auto& v : adj[u]) {
			dep[v] = dep[fa[v] = u] + 1;
			dfs1(v);
			siz[u] += siz[v];
			if (siz[v] > siz[adj[u][0]]) {
				std::swap(v, adj[u][0]);
			}
		}
	}

	void dfs2(int u) {
		dfn[u] = ++tot;
		idfn[tot] = u;
		for (auto v : adj[u]) {
			top[v] = v == adj[u][0] ? top[u] : v;
			dfs2(v);
		}
	}

	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				u = fa[top[u]];
			} else {
				v = fa[top[v]];
			}
		}
		return dep[u] < dep[v] ? u : v;
	}

	int jump(int u, int k) {
		assert(dep[u] >= k);
		int d = dep[u] - k;
		while (dep[top[u]] > d) {
			u = fa[top[u]];
		}
		return idfn[dfn[u] - dep[u] + d];
	}

	template<typename Func>
	void modify(int u, int v, Func modify) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				modify(dfn[top[u]], dfn[u]);
				u = fa[top[u]];
			} else {
				modify(dfn[top[v]], dfn[v]);
				v = fa[top[v]];
			}
		}
		if (dep[u] < dep[v]) {
			modify(dfn[u], dfn[v]);
		} else {
			modify(dfn[v], dfn[u]);
		}
	}

	template<typename Func>
	void modify(int u, Func modify) {
		modify(dfn[u], dfn[u] + siz[u] - 1);
	}

	template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
	T query(int u, int v, Func query) {
		T res = T();
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				res = query(dfn[top[u]], dfn[u]) + res;
				u = fa[top[u]];
			} else {
				res = query(dfn[top[v]], dfn[v]) + res;
				v = fa[top[v]];
			}
		}
		if (dep[u] < dep[v]) {  
			return query(dfn[u], dfn[v]) + res;
		} else {
			return query(dfn[v], dfn[u]) + res;
		}
	}

	template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
	T query (int u, Func query) {
		return query(dfn[u], dfn[u] + siz[u] - 1);
	}
};
```

= SegmentTree ALL

可能包含：

- 普通线段树
- 区间修改线段树
- 动态开点线段树 & 主席树 & 线段树合并

== 

```cpp
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
		info.assign(4 << std::__lg(n), Info {});
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
```

== 

```cpp
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
```

== 

```cpp
template<typename Info>
struct SegmentTreePool {
	int x, y;
	std::vector<Info> info;
	std::vector<int> ls, rs;

	void reserve(int n) {
		info.reserve(n);
		ls.reserve(n);
		rs.reserve(n);
	}

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
```

= FHQ-Treap

这个是没有封装的，瞎写，仅供参考。没加懒标记，自己加吧（

```cpp
namespace treap {
	constexpr int maxn = 2e6;
	struct Info {
		ll val;
		Info(ll x = 0) { val = x; }
	};

	auto operator<=>(Info x, Info y) {
		return x.val <=> y.val;
	}
	Info operator+(Info x, Info y) {
		return Info(min(x.val, y.val));
	}

	mt19937 sj(time(0));
	Info val[maxn];
	Info info[maxn];
	int siz[maxn], key[maxn], ls[maxn], rs[maxn], fa[maxn];
	int rev[maxn];
	int cnt = 1;

	void init() {
		cnt = 1;
		val[0] = info[0] = Info(INF);
	}
	int add(Info x) {
		info[cnt] = val[cnt] = x;
		key[cnt] = (int) sj();
		siz[cnt] = 1, ls[cnt] = 0, rs[cnt] = 0, fa[cnt] = 0;
		rev[cnt] = 0;
		return cnt++;
	}
	void pull(int u) {
		siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
		info[u] = info[ls[u]] + val[u] + info[rs[u]];
	}
	void push(int u) {
		if(rev[u]) {
			swap(ls[u], rs[u]);
			rev[ls[u]] ^= 1, rev[rs[u]] ^= 1;
			rev[u] = 0;
		}
	}
	void split_val(int u, Info k, int& x, int& y, int fx = 0, int fy = 0) {
		if(!(x = y = u)) return;
		push(u);
		if(val[u] <= k) {
			fa[u] = fx;
			split_val(rs[u], k, rs[u], y, u, fy);
		} else {
			fa[u] = fy;
			split_val(ls[u], k, x, ls[u], fx, u);
		}
		pull(u);
	}
	void split_rnk(int u, int k, int& x, int& y, int fx = 0, int fy = 0) {
		if(!(x = y = u)) return;
		push(u);
		if(siz[ls[u]] + 1 <= k) {
			fa[u] = fx;
			split_rnk(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
		} else {
			fa[u] = fy;
			split_rnk(ls[u], k, x, ls[u], fx, u);
		}
		pull(u);
	}
	int merge(int x, int y) {
		if(!x || !y) return x | y;
		push(x), push(y);
		if(key[x] < key[y]) {
			rs[x] = merge(rs[x], y);
			if(rs[x]) fa[rs[x]] = x;
			pull(x);
			return x;
		} else {
			ls[y] = merge(x, ls[y]);
			if(ls[y]) fa[ls[y]] = y;
			pull(y);
			return y;
		}
	}
	template<class... Args>
	[[nodiscard]] int mergeall(Args... args) {
		int rt = 0;
		((rt = merge(rt, args)), ...);
		return rt;
	}
	template<class T>
	int findleft(int rt, T&& f) {
		if(!f(info[rt])) return inf;
		int u = rt, k = 0;
		while(1) {
			push(u);
			if (ls[u] && f(info[ls[u]])) {
				u = ls[u];
			} else if(f(val[u])) {
				return k + siz[ls[u]] + 1;
			} else {
				k += siz[ls[u]] + 1, u = rs[u];
			}
		}
	}
	template<class T>
	int findright(int rt, T&& f) {
		if(!f(info[rt])) return -inf;
		int u = rt, k = 0;
		while(1) {
			push(u);
			if (rs[u] && f(info[rs[u]])) {
				k += siz[ls[u]] + 1, u = rs[u];
			} else if(f(val[u])) {
				return k + siz[ls[u]] + 1;
			} else {
				u = ls[u];
			}
		}
	}
	int rank(int x) {
		auto dfs = [&](auto dfs, int u) -> void {
			if(fa[u]) dfs(dfs, fa[u]);
			push(u);
		};
		dfs(dfs, x);
		int res = siz[ls[x]] + 1;
		for(int u = x; fa[u]; u = fa[u])
			if(u == rs[fa[u]])
				res += siz[ls[fa[u]]] + 1;
		return res;
	}
	int find(int x) {
		while(fa[x]) x = fa[x];
		return x;
	}
}
```

= Link-Cut-Tree

```cpp

```
