/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/06/19 00:19:44
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct SuffixAutomaton {
	static constexpr int N = 26;
	struct Node {
		int len;
		int link;
		std::array<int, N> next;
		Node() : len(), link(), next() {}
	};

	i64 substr;
	std::vector<Node> t;

	SuffixAutomaton () { init(); }

	void init() {
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
};

#define ls(u) ls[u]
#define rs(u) rs[u]
template<typename Info>
struct DynamicSegmentTree {
  using i64 = long long;
  int lo, hi, cnt;
  std::vector<Info> info;
  std::vector<int> ls, rs;

  DynamicSegmentTree () = default;

  DynamicSegmentTree (int N, int lo, int hi) { init(N, lo, hi); }

  void init (int N, int lo, int hi) {
	this -> lo = lo;
	this -> hi = hi;
	cnt = 0;
	info.assign(N, Info {});
	ls.assign(N, 0);
	rs.assign(N, 0);
  }

  void pull(int u) {
	info[u] = info[ls(u)] + info[rs(u)];
  }

  template<typename Func>
  void modify(int p, Func&& op, int& u, int l, int r) {
	if(u == 0) u = ++cnt;
	if(l == r) {
	  op(info[u]);
	  return;
	}
	int m = (l + r) >> 1;
	if(p <= m) modify(p, op, ls(u), l, m);
	else modify(p, op, rs(u), m + 1, r);
	pull(u);
  }

  template<typename Func>
  void modify(int& u, int p, Func&& op) {
	modify(p, op, u, lo, hi);
  }

  Info query(int L, int R, int u, int l, int r) {
	if(u == 0) return Info {};
	if(L <= l && r <= R) {
	  return info[u];
	}
	int m = (l + r) >> 1;
	if(R <= m) return query(L, R, ls(u), l, m);
	if(L > m) return query(L, R, rs(u), m + 1, r);
	return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
  }

  Info query(int u, int l, int r) {
	return query(l, r, u, lo, hi);
  }

	template<typename Func>
	int merge(int x, int y, int l, int r, Func&& op) {
		if(!x || !y) return x | y;
		if(l == r) {
			info[x] = op(info[x], info[y]);
		} else {
			int m = (l + r) >> 1;
			ls[x] = merge(ls[x], ls[y], l, m, op);
			rs[x] = merge(rs[x], rs[y], m + 1, r, op);
			pull(x);
		}
		return x;
	}

	template<typename Func>
	void merge(int& x, int y, Func&& op) {
		x = merge(x, y, lo, hi, op);
	}

	template<typename Func>
	int FindFirst(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) return inf;
		if(l == r) return l;
		int m = (l + r) >> 1;
		int res = FindFirst(L, R, f, ls(u), l, m);
		if(res == inf) res = FindFirst(L, R, f, rs(u), m + 1, r);
		return res;
	}
			
	template<typename Func>
	int FindLast(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) return -inf;
		if(l == r) return l;
		int m = (l + r) >> 1;
		int res = FindLast(L, R, f, rs(u), m + 1, r);
		if(res == -inf) res = FindLast(L, R, f, ls(u), l, m);
		return res;
	}
};
#undef ls
#undef rs

void solve() {
	int n, p = 1;
	string s;
	cin >> n >> s;
	SuffixAutomaton sam;
	vector<int> node(n + 1);
	for (int i = 0; i < n; ++i) {
		p = sam.extend(p, s[i] - 'a');
		node[i + 1] = p;
	}

	int m = sam.size() - 1;
	vector<vector<int>> adj(m + 1);
	for (int i = 2; i <= m; ++i) {
		adj[sam.link(i)].push_back(i);
	}

	DynamicSegmentTree<int> seg(m << 4, 1, n);
	vector<int> root(m + 1);
	for (int i = 1; i <= n; ++i) {
		seg.modify(root[node[i]], i, [](int& cnt) {
			cnt++;
		});
	}

	int ans = 0;

	[&](this auto&& dfs, int u) -> void {
		for (auto v : adj[u]) {
			dfs(v);
			seg.merge(root[u], root[v], [](int x, int y) {
				return x + y;
			});
		}
		int x = seg.FindFirst(seg.lo, seg.hi, [](int cnt) {
			return cnt > 0;
		}, root[u], seg.lo, seg.hi);
		int y = seg.FindLast(seg.lo, seg.hi, [](int cnt) {
			return cnt > 0;
		}, root[u], seg.lo, seg.hi);
		int l = sam.len(sam.link(u)) + 1;
		int r = min(sam.len(u), (y - x) / 2 - 1);
		int res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (seg.query(root[u], x + mid + 1, y - mid - 1)) {
				res = mid, l = mid + 1;
			} else r = mid - 1;
		}
		if (res > 0) {
			ans = max(ans, y - x + res);
		}
	} (1);

	cout << ans << "\n";
}

signed main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		solve();
	}

	return 0;
}
