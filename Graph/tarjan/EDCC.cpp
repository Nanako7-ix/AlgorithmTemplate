#include <bits/stdc++.h>

struct EDCC {
	int n;
	std::vector<std::vector<std::array<int, 2>>> adj;
	std::vector<std::array<int, 2>> bridge;
	std::vector<int> stk;
	std::vector<int> dfn, low, bel;
	int cur, cnt, edges;

	EDCC () = default;

	EDCC (int n) { init(n); }

	void init (int n) {
		this -> n = n;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, 0);
		low.assign(n + 1, 0);
		bel.assign(n + 1, 0);
		stk.clear();
		cur = cnt = edges = 0;
	}

	void add (int u, int v) {
		adj[u].push_back({v, edges++});
		adj[v].push_back({u, edges++});
	}

	void tarjan (int u, int fa) {
		dfn[u] = low[u] = ++cur;
		stk.push_back(u);
		for (auto [v, id] : adj[u]) {
			if ((id ^ fa) == 1) continue;
			if (dfn[v] == 0) {
				tarjan(v, id);
				low[u] = std::min(low[u], low[v]);
				if (dfn[u] < low[v]) {
					bridge.push_back({u, v});
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

	std::vector<int> work() {
		for (int i = 1; i <= n; ++i) {
			if (dfn[i] == 0) tarjan(1, -1);
		}
		return bel;
	}

	auto getTree() {
		int _n = *max_element(bel.begin() + 1, bel.end());
		std::vector<std::vector<int>> _adj(_n + 1);
		for (auto [u, v] : bridge) {
			_adj[bel[u]].push_back(bel[v]);
			_adj[bel[v]].push_back(bel[u]);
		}
		return std::pair {_n, std::move(_adj)};
	}
};
