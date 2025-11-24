#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

template<typename T>
struct Kruskal {
	struct Edge {
		int u, v; T w;
		Edge(int u, int v, T w) {
			this -> u = u;
			this -> v = v;
			this -> w = w;
		}
		bool operator<(const Edge& o) const {
			return w < o.w;
		}
	};

	int n;
	vector<Edge> edges;
	
	void add(int u, int v, T w) {
		edges.emplace_back(u, v, w);
	}
	
	auto work() {
		int tot = n;
		vector<int> val(2 * n);
		vector<vector<int>> adj(2 * n);
		sort(edges.begin(), edges.end());
		for (auto [u, v, w] : edges) {
			if (same(u, v)) continue;
			merge(u, v);
			++tot;
			val[tot] = w;
			adj[tot].push_back(u);
			adj[tot].push_back(v);
		}
		return pair { std::move(val), std::move(adj) }
	}

	vector<int> fa;
	
	int find(int u) {
		if (fa[u] == u) return u;
		return fa[u] = find(fa[u]);
	}

	int merge(int u, int v) {
		u = find(u), v = find(v);
		if (u != v) fa[v] = u;
	}
};

void Thephix() {
	
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
