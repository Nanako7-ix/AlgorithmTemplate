#include <bits/stdc++.h>

template<typename T>
struct Flow {
	struct edge {
		int v; T cap;
		edge(int v, T cap) : v(v), cap(cap) {}
	};

	int n;
	std::vector<edge> e;
	std::vector<std::vector<int>> g;
	std::vector<int> cur, h;

	Flow() = default;
	Flow(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		g.assign(n + 1, {});
	}

	void add(int u, int v, T cap) {
		g[u].push_back(e.size());
		e.emplace_back(v, cap);
		g[v].push_back(e.size());
		e.emplace_back(u, 0);
	}

	bool bfs(int s, int t) {
		std::queue<int> que;
		h.assign(n + 1, 0);
		h[s] = 1;
		que.push(s);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (auto i : g[u]) {
				auto [v, cap] = e[i];
				if (cap > 0 && h[v] == 0) {
					h[v] = h[u] + 1;
					if (v == t) return true;
					que.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, int t, T f) {
		if (u == t) return f;
		T r = f;
		for (int& i = cur[u]; i < (int) g[u].size(); ++i) {
			int j = g[u][i];
			auto& [v, cap] = e[j];
			if (cap > 0 && h[v] == h[u] + 1) {
				T aug = dfs(v, t, std::min(r, cap));
				r -= aug;
				e[j].cap -= aug;
				e[j ^ 1].cap += aug;
				if (r == 0) break;
			}
		}
		return f - r;
	}

	T flow(int s, int t) {
		T ans = 0;
		while (bfs(s, t)) {
			cur.assign(n + 1, 0);
			ans += dfs(s, t, std::numeric_limits<T>::max());
		}
		return ans;
	}

	std::vector<int> cut() {
		std::vector<int> x(n + 1);
		for (int i = 1; i <= n; ++i) {
			x[i] = h[i] != 0;
		}
		return x;
	}

	using Edge = std::tuple<int, int, T, T>;
	auto edges() -> std::vector<Edge> {
		std::vector<Edge> E;
		for (int i = 0; i < (int) e.size(); i += 2) {
			E.emplace_back(
				e[i + 1].v,
				e[i].v,
				e[i].cap + e[i + 1].cap,
				e[i + 1].cap
			);
		}
		return E;
	}
};
