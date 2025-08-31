#include <bits/stdc++.h>

using i64 = long long;

template<typename Info, typename Tag>
struct LazyFhqTreapPool {
	static std::mt19937_64 rng;
	std::vector<Info> val, sum;
	std::vector<Tag> tag;
	std::vector<int> ls, rs, fa, siz, rev;
	std::vector<i64> phi;
	
	LazyFhqTreapPool(Info e = {}) { init(e); }

	void init(Info e = {}) {
		val.assign(1, e);
		sum.assign(1, e);
		tag.assign(1, Tag{});
		ls.assign(1, 0);
		rs.assign(1, 0);
		fa.assign(1, 0);
		siz.assign(1, 0);
		rev.assign(1, 0);
		phi.assign(1, 0);
	}

	void apply(int u, const Tag& v) {
		tag[u].apply(v);
		val[u].apply(tag[u]);
	}
	
	void push(int u) {

	}
	
	void pull(int u) {
		sum[u] = sum[ls[u]] + val[u] + sum[rs[u]];
		siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
	}

	int Node(const Info& x) {
		val.push_back(x);
		sum.push_back(x);
		ls.push_back(0);
		rs.push_back(0);
		fa.push_back(0);
		siz.push_back(0);
		phi.push_back(rng());
		return val.size() - 1;
	}

	void splitByRank(int u, int k, int& x, int& y, int fx, int fy) {
		if (!(x = y = u)) return;
		if (siz[ls[u]] + 1 <= k) {
			fa[u] = fx;
			splitByRank(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
		} else {
			fa[u] = fy;
			splitByRank(ls[u], k, x, ls[u], fx, u);
		}
		pull(u);
	}

	std::pair<int, int> splitByRank(int u, int k) {
		int x, y;
		splitByRank(u, k, x, y, 0, 0);
		return std::pair { x, y };
	}

	void splitByValue(int u, Info k, int& x, int& y, int fx, int fy) {
		if (!(x = y = u)) return;
		if (val[u] <= k) {
			fa[u] = fx;
			splitByValue(rs[u], k, rs[u], y, u, fy);
		} else {
			fa[u] = fy;
			splitByValue(ls[u], k, x, ls[u], fx, u);
		}
		pull(u);
	}

	std::pair<int, int> splitByValue(int u, Info k) {
		int x, y;
		splitByValue(u, k, x, y, 0, 0);
		return std::pair { x, y };
	}

	[[nodiscard]] int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (phi[x] > phi[y]) {
			rs[x] = merge(rs[x], y);
			if (rs[x]) fa[rs[x]] = x;
			pull(x);
			return x;
		} else {
			ls[y] = merge(x, ls[y]);
			if (ls[y]) fa[ls[y]] = y;
			pull(y);
			return y;
		}
	}

	int root(int x) {
		while (fa[x]) x = fa[x];
		return x;
	}

	int rank(int x) {
		int res = siz[ls[x]] + 1;
		for (int u = x; fa[u]; u = fa[u]) {
			if (u == rs[fa[u]]) {
				res += siz[ls[fa[u]]] + 1;
			}
		}
		return res;
	}

	void print(int u) {
		if (u == 0) return;
		print(ls[u]);
		std::cerr << val[u] << " ";
		print(rs[u]);
	}
	
	void debug(int u) {
		print(u);
		std::cerr << "\n";
	}
};

template<typename Info, typename Tag>
std::mt19937_64 LazyFhqTreapPool<Info, Tag>::rng(std::chrono::steady_clock::now().time_since_epoch().count());
