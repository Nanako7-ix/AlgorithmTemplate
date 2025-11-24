#include <bits/stdc++.h>

template< typename T, typename F>
struct CostFlow {
	struct edge {
		int v; T cap; F cost;
		edge(int v, T cap, F cost) : v(v), cap(cap), cost(cost) {}
	};

	int n;
	std::vector<edge> e;
	std::vector<std::vector<int>> g;
	std::vector<F> h, dp;
	std::vector<int> pre;

	CostFlow() = default;
	CostFlow(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		g.assign(n + 1, {});
		h.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}

	void add(int u, int v, T cap, F cost) {
		g[u].push_back(e.size());
		e.emplace_back(v, cap, cost);
		g[v].push_back(e.size());
		e.emplace_back(u, 0,  -cost);
	}

	bool dijkstra(int s, int t) {
		fill( dp.begin(),  dp.end(), std::numeric_limits<F>::max());
		fill(pre.begin(), pre.end(), -1);

		std::priority_queue<std::pair<F, int>, std::vector<std::pair<F, int>>, std::greater<std::pair<F, int>>> q;
		dp[s] = 0;
		q.emplace(dp[s], s);
		while (!q.empty()) {
			auto [w, u] = q.top();
			q.pop();
			if (dp[u] != w) continue;
			for (auto i : g[u]) {
				auto [v, cap, cost] = e[i];
				if (cap > 0 && dp[u] + h[u] - h[v] + cost < dp[v]) {
					dp[v] = dp[u] + h[u] - h[v] + cost;
					pre[v] = i;
					q.emplace(dp[v], v);
				}
			}
		}
		return dp[t] != std::numeric_limits<F>::max();
	}

	std::pair<T, F> flow(int s, int t) {
		T flow = 0;
		F cost = 0;
		while (dijkstra(s, t)) {
			for (int i = 1; i <= n; ++i) {
				h[i] += dp[i];
			}
			// 最小费用可行流：if (g[t] >= 0) break;
			T aug = std::numeric_limits<T>::max();
			for (int u = t; u != s; u = e[pre[u] ^ 1].v) {
				aug = std::min(aug, e[pre[u]].cap);
			}
			for (int u = t; u != s; u = e[pre[u] ^ 1].v) {
				e[pre[u]].cap -= aug;
				e[pre[u] ^ 1].cap += aug;
			}
			flow += aug;
			cost += aug * h[t];
		}

		return std::pair(flow, cost);
	}

	using Edge = std::tuple<int, int, T, T, F>;
	auto edges() -> std::vector<Edge> {
		std::vector<Edge> E;
		for(int i = 0; i < (int)e.size(); i += 2) {
			E.emplace(
				e[i + 1].v,
				e[i].v,
				e[i].cap + e[i + 1].cap,
				e[i + 1].cap,
				e[i].cost
			);
		}
		return E;
	}
};
