#include <bits/stdc++.h>

struct VDCC {
	int n, cur;
	std::vector<std::vector<int>> adj, vdcc;
	std::vector<int> dfn, low, stk, cut;

	VDCC() = default;
	VDCC (int n) { init(n); }

	void init(int n) {
		this -> n = n;
		cur = 0;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, 0);
		low.assign(n + 1, 0);
		cut.assign(n + 1, 0);
		vdcc.clear();
		stk.clear();
	}

	void add(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int u, int fa) {
		int son = 0;
		stk.push_back(u);
		low[u] = dfn[u] = ++cur;
		for (auto v : adj[u]) {
			if (dfn[v] == 0) {
				son += 1;
				dfs(v, u);
				low[u] = std::min(low[u], low[v]);
				if(low[v] >= dfn[u]) {
					if (fa != 0) cut[u] = 1;
					std::vector<int> cc { u };
					int x;
					do {
						cc.push_back(x = stk.back());
						stk.pop_back();
					} while(x != v);
					vdcc.push_back(cc);
				}
			} else if (v != fa) {
				low[u] = std::min(low[u], dfn[v]);
			}
		}

		if (fa == 0 && son == 0) {
			vdcc.push_back({u});
		}

		if (fa == 0 && son >= 2) {
			cut[u] = 1;
		}
	}

	void work() {
		for (int i = 1; i <= n; ++i) {
			if (dfn[i] == 0) dfs(i, 0);
		}
	}

	auto getTree() {
		work();
		int m = vdcc.size();
		std::vector<std::vector<int>> adj(n + m + 1);
		for (int i = 1; i <= m; ++i) {
			for (auto x : vdcc[i - 1]) {
				adj[x].push_back(i + n);
				adj[i + n].push_back(x);
			}
		}
		return std::pair { m, std::move(adj) };
	}
};
