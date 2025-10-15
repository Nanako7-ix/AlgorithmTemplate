#include <bits/stdc++.h>

void solve() {
	int n, q, rt;
	std::vector<std::vector<int>> adj(n + 1);

	std::vector<int> dep(n + 1);
	std::vector fa(std::__lg(n) + 1, std::vector<int> (n + 1));

	auto dfs = [&](auto&& dfs, int u) -> void {
		dep[u] = dep[fa[0][u]] + 1;
		for (auto& v : adj[u]) {
			if (v == fa[0][u]) {
				continue;
			}
			fa[0][v] = u;
			dfs(dfs, v);
			
		}
	}; dfs(dfs, rt);

	for (int i = 1; i <= std::__lg(n); ++i) {
		for (int u = 1; u <= n; ++u) {
			fa[i][u] = fa[i - 1][fa[i - 1][u]];
		}
	}

	auto lca = [&](int u, int v) -> int {
		if (dep[u] < dep[v]) std::swap(u, v);
		while (dep[u] != dep[v]) {
			u = fa[std::__lg(dep[u] - dep[v])][u];
		}
		if (u == v) return u;
		for (int i = std::__lg(n); i >= 0; --i) {
			if (fa[i][u] != fa[i][v]) {
				u = fa[i][u], v = fa[i][v];
			}
		}
		return fa[0][u];
	};
}
