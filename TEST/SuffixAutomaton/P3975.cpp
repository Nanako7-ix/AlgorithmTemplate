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
	static constexpr int N = 26;
	struct Node {
		int len;
		int link;
		std::array<int, N> next;
		Node() : len(), link(), next() {}
	};

	i64 substr;
	std::vector<Node> t;

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
};

void Thephix() {
	string s;
	int t, k;
	cin >> s >> t >> k;
	
	int n = s.size();
	SAM sam(n);
	vector<int> p(n + 1);
	p[0] = 1;
	for (int i = 0; i < n; ++i) {
		p[i + 1] = sam.extend(p[i], s[i] - 'a');
	}

	int m = sam.size() - 1;
	vector<vector<int>> adj(m + 1);
	for (int i = 2; i <= m; ++i) {
		adj[sam.link(i)].push_back(i);
	}

	vector<i64> siz(m + 1);
	if (t == 1) { // 考虑 endpos.size()
		for (int i = 1; i <= n; ++i) {
			siz[p[i]]++;
		}
		auto dfs = [&](auto &&dfs, int u) -> void {
			for (auto v : adj[u]) {
				dfs(dfs, v);
				siz[u] += siz[v];
			}
		}; dfs(dfs, 1);
	} else { // 否则一个集合只算一次
		for (int i = 1; i <= m; ++i) {
			siz[i] = 1;
		}
	} siz[1] = 0; // 空串不算串

	i64 substr = 0;
	for (int u = 2; u <= m; ++u) {
		substr += (sam.len(u) - sam.len(sam.link(u))) * siz[u];
	}
	if (substr < k) {
		cout << "-1\n";
		return;
	}
	
	vector<int> vis(m + 1);
	vector<i64> dp = siz;
	auto dfs2 = [&](auto&& dfs2, int u) -> void {
		for (int ch = 0; ch < 26; ++ch) {
			int v = sam.next(u, ch);
			if (v == 0) continue;
			if (vis[v] == 0) {
				vis[v] = 1;
				dfs2(dfs2, v);
			}
			dp[u] += dp[v];
		}
	}; dfs2(dfs2, 1);

	int u = 1;
	string ans;
	while (k > siz[u]) {
		ans.push_back('$');
		k -= siz[u];
		for (int ch = 0; ch < 26; ++ch) {
			int v = sam.next(u, ch);
			if (v == 0) continue;
			ans.back() = 'a' + ch;
			if (k > dp[v]) {
				k -= dp[v];
			} else break;
		}
		u = sam.next(u, ans.back() - 'a');
	}
	cout << ans << "\n";
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