#include <bits/stdc++.h>

struct EDCC {
	int n;
	int cur, cnt, edges;
	std::vector<int> stk, dfn, low, bel;
	std::vector<std::array<int, 2>> cut;
	std::vector<std::vector<std::array<int, 2>>> adj;

	EDCC(int n = 0) { init(n); }

	void init(int n) {
		this -> n = n;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, 0);
		low.assign(n + 1, 0);
		bel.assign(n + 1, 0);
		stk.clear();
		cut.clear();
		cur = cnt = edges = 0;
	}

	void add(int u, int v) {
		++edges;
		adj[u].push_back({ v, edges });
		adj[v].push_back({ u, edges });
	}

	void dfs(int u, int fa) {
		dfn[u] = low[u] = ++cur;
		stk.push_back(u);
		for (auto [v, w] : adj[u]) {
			if (w == fa) continue;
			if (dfn[v] == 0) {
				dfs(v, w);
				low[u] = std::min(low[u], low[v]);
				if (dfn[u] < low[v]) {
					cut.push_back({ u, v });
				}
			} else {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			int x = ++cnt;
			do {
				bel[x = stk.back()] = cnt;
				stk.pop_back();
			} while (x != u);
		}
	}

	void work() {
		for (int i = 1; i <= n; ++i) {
			if (dfn[i] == 0) dfs(i, 0);
		}
	}

	auto getTree() {
		work();
		std::vector<std::vector<int>> adj(cnt + 1);
		for (auto [u, v] : cut) {
			adj[bel[u]].push_back(bel[v]);
			adj[bel[v]].push_back(bel[u]);
		}
		return std::pair { cnt, std::move(adj) };
	}
};
