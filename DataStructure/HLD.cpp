#include <bits/stdc++.h>

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

	template<typename Callback>
	void subtree(int u, Callback&& fn) {
		fn(dfn[u], dfn[u] + siz[u] - 1);
	}

	template<typename Callback>
	void path(int u, int v, Callback&& fn) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				fn(dfn[top[u]], dfn[u]);
				u = fa[top[u]];
			} else {
				fn(dfn[top[v]], dfn[v]);
				v = fa[top[v]];
			}
		}
		if (dep[u] < dep[v]) {
			fn(dfn[u], dfn[v]);
		} else {
			fn(dfn[v], dfn[u]);
		}
	}
};
