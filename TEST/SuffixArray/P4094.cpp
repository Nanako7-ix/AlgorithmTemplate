#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

auto SuffixArray(const string& s) {
	int n = s.size();
	std::vector<int> sa(n + 1), rk(n + 1);
	std::iota(sa.begin() + 1, sa.end(), 1);
	std::sort(sa.begin() + 1, sa.end(), [&](int x, int y) {
		return s[x - 1] < s[y - 1];
	});

	rk[sa[1]] = 1;
	for (int i = 1; i < n; ++i) {
		rk[sa[i + 1]] = rk[sa[i]] + (s[sa[i + 1] - 1] != s[sa[i] - 1]);
	}
			
	vector<int> tmp(n + 1), cnt(n + 1);
	for (int k = 1; rk[sa[n]] != n; k <<= 1) {
		for (int i = n - k + 1, j = 1; i <= n; ++i, ++j) {
			tmp[j] = i;
		}
		for (int i = 1, j = k; i <= n; ++i) {
			if (sa[i] <= k) continue;
			tmp[++j] = sa[i] - k;
		}

		for (int i = 1; i <= n; ++i) {
			cnt[rk[i]]++;
		}
		for (int i = 1; i < rk[sa[n]]; ++i) {
			cnt[i + 1] += cnt[i];
		}
		for (int i = n; i >= 1; --i) {
			sa[cnt[rk[tmp[i]]]--] = tmp[i];
		}

		std::swap(rk, tmp);
		rk[sa[1]] = 1, cnt[tmp[sa[n]]] = 0;
		for (int i = 1; i < n; ++i) {
			cnt[tmp[sa[i]]] = 0;
			rk[sa[i + 1]] = rk[sa[i]] + (
				tmp[sa[i + 1]] != tmp[sa[i]] ||
				sa[i] + k - 1 == n ||
				tmp[sa[i + 1] + k] != tmp[sa[i] + k]
			);
		}
	}

	std::vector<int> height(n + 1);
	for (int i = 1, lcp = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (lcp != 0) lcp--;
		while (
			i + lcp <= n && 
			sa[rk[i] - 1] + lcp <= n &&
			s[i + lcp - 1] == s[sa[rk[i] - 1] + lcp - 1]
		) ++lcp;
		height[rk[i]] = lcp;
	}

	return std::tuple {
		std::move(sa), 
		std::move(rk), 
		std::move(height)
	};
}

template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;

	SparseTable () = default;

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	SparseTable (const Iterator& l, const Iterator& r, Func&& f) : op(f) {
		init(l, r);
	}

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	void init (const Iterator& l, const Iterator& r) {
		n = r - l;
		st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = *(l + i - 1);
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

template<typename Info>
struct SegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<int> ls, rs;

	SegmentTree() = default;

	SegmentTree(int n, int m) {
		init(n, m);
	}

	void init(int n, int m) {
		this -> n = n;
		info.assign(1, Info {});
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
		} else {
			int m = (l + r) >> 1;
			ls[u] = build(l, m, f);
			rs[u] = build(m + 1, r, f);
			pull(u);
		}
		return u;
	}

	template<typename Func>
	int build(Func&& f) {
		return build(1, n, f);
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
	void modify(int& u, int v, int p, Func&& op) {
		u = modify(p, op, v, 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if (R <= m) {
			return query(L, R, ls[u], l, m);
		} else if (L > m) {
			return query(L, R, rs[u], m + 1, r);
		} else {
			return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
		}
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, 1, n);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int v, int l, int r) {
		if (l > R || r < L || !f(info[u] - info[v])) {
			return n + 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls[u], ls[v], l, m);
		if (p > n) {
			p = findL(L, R, f, rs[u], rs[v], m + 1, r);
		}
		return p;
	}

	template<typename Func>
	int findL(int u, int v, int l, int r, Func&& f) {
		if(!(l <= r)) return n + 1;
		return findL(l, r, f, u, v, 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int v, int l, int r) {
		if (l > R || r < L || !f(info[u] - info[v])) {
			return 0;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs[u], rs[v], m + 1, r);
		if (p < 1) {
			p = findR(L, R, f, ls[u], ls[v], l, m);
		}
		return p;
	}

	template<typename Func>
	auto findR(int u, int v, int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, u, v, 1, n);
	}
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;

void Thephix() {
	int n, q;
	string s;
	cin >> n >> q >> s;

	auto [sa, rk, height] = SuffixArray(s);
	SparseTable Min(height.begin() + 1, height.end(), [&](int x, int y) {
		return min(x, y);
	});

	SegmentTree<int> seg(n, n);
	vector<int> ver(n + 1);
	for (int i = 1; i <= n; ++i) {
		seg.modify(ver[i], ver[i - 1], rk[i], [&](int& cnt) { cnt = 1; });
	}

	for (int i = 1; i <= q; ++i) {
		int l1, r1, l2, r2;
		cin >> l1 >> r1 >> l2 >> r2;
		auto check = [&](int len) -> bool {
			int u = ver[r1 - len + 1], v = ver[l1 - 1], p;
			p = seg.findR(u, v, 1, rk[l2] - 1, [](const int& cnt) {
				return cnt > 0;
			});
			if (p != 0 && Min(p + 1, rk[l2]) >= len) {
				return true;
			}
			p = seg.findL(u, v, rk[l2] + 1, n, [&](const int& cnt) {
				return cnt > 0;
			});
			if (p != n + 1 && Min(rk[l2] + 1, p) >= len) {
				return true;
			}
			return false;
		};

		// 哦 我没考虑同起点的情况，加上就好了
		int l = 1, r = min(r1 - l1 + 1, r2 - l2 + 1);
		int res = l1 <= l2 && l2 <= r1 ? min(r1, r2) - l2 + 1 : 0;
		while (l <= r) {
			int m = (l + r) >> 1;
			if (check(m)) {
				res = m, l = m + 1;
			} else r = m - 1;
		}
		cout << res << "\n";
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