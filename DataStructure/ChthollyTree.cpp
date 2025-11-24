#include <bits/stdc++.h>

// Requires: Fn.offset(int)
template<typename Fn>
struct ChthollyTree {
	struct Node {
		i64 l, r;
		mutable Fn v;
		Node (i64 l, i64 r, Fn v) {
			this -> l = l;
			this -> r = r;
			this -> v = v;
		}
		bool operator< (const Node& o) const {
			return l < o.l;
		}
	};
	
	i64 n;
	std::set<Node> odt;
	
	ChthollyTree (i64 n) { init(n); }

	void init (i64 n) {
		this -> n = n;
		odt.clear();
		odt.emplace(1, n, Fn());
	}

	std::set<Node>::iterator split(i64 p) {
		if (p == n + 1) return odt.end();
		auto it = odt.lower_bound(Node {p, 0, Fn()});
		if (it != odt.end() && it -> l == p) return it;
		--it;
		auto [l, r, v] = *it;
		odt.erase(it);

		odt.emplace(l, p - 1, v);
		v.offset(r - l + 1);
		return odt.emplace(p, r, v).first;
	}

	void assign(int l, int r, const Fn& val) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		odt.erase(x, y);
		odt.emplace(l, r, val);
	}

	template<typename F>
	void perform(int l, int r, F&& f) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		for (auto it = x; it != y; ++it) {
			auto& [l, r, v] = *it;
			f(l, r, v);
		}
	}
};
