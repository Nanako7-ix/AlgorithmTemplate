#include <bits/stdc++.h>

struct LCA {
	int n, tot;
	std::vector<std::vector<int>> adj, st;
	std::vector<int> fa, dep, dfn, siz;
	
	LCA (int n) { init(n); }
	
	void init (int n) {
		this -> n = n;
		tot = 0;
		adj.assign(n + 1, {});
		st.assign(std::__lg(n) + 1, std::vector<int> (n + 1));
		fa.assign(n + 1, 0);
		dep.assign(n + 1, 0);
		dfn.assign(n + 1, 0);
		siz.assign(n + 1, 0);
	}
	
	void add (int u, int v) {
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	
	void dfs (int u) {
		if(fa[u] != 0) adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
		siz[u] = 1;
		st[0][dfn[u] = ++tot] = u;
		for(auto v : adj[u]) {
			dep[v] = dep[fa[v] = u] + 1;
			dfs(v);
			siz[u] += siz[v];
		}
	}
	
	int merge (int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	
	void work (int rt = 1) {
		dep[rt] = 1;
		dfs(rt);
		for(int i = 1; i <= std::__lg(n); ++i) {
			for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
				st[i][j] = merge(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	
	int operator() (int u, int v) {
		if(u == v) return u;
		u = dfn[u], v = dfn[v];
		if(u > v) std::swap(u, v);
		int len = std::__lg(v - u);
		return fa[merge(st[len][u + 1], st[len][v - (1 << len) + 1])];
	}
	
	// 下面是辅助性函数
	bool isAncester(int f, int u) {
		return operator()(f, u) == f;
	}
	
	int rootedParent(int rt, int u) {
		if(rt == u) return rt;
		if (!isAncester(u, rt)) return fa[u];
		auto it = upper_bound(adj[u].begin(), adj[u].end(), rt, [&](int x, int y) {
			return dfn[x] < dfn[y];
		}) - 1;
		return *it;
	}
	
	int rootedSize(int rt, int u) {
		if (rt == u) return n;
		if (!isAncester(u, rt)) return siz[u];
		return n - siz[rootedParent(rt, u)];
	}
	
	int rootedLca(int rt, int u, int v) {
		return operator()(rt, u) ^ operator()(u, v) ^ operator()(v, rt);
	}
};
