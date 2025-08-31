#include <bits/stdc++.h>

template<typename Info>
struct Fenwick {
public:
	Fenwick () = default;

	Fenwick (int n, Info e = {}) { init(n, e); }

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	Fenwick (const Iterator& l, const Iterator& r) { init(l, r); }

	void init (int n, Info e = {}) {
		vector<Info> _(n, e);
		init(_.begin(), _.end());
	}

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	void init (const Iterator& l, const Iterator& r) {
		n = r - l;
		tr.assign(n + 1, Info {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += *(l + i - 1);
			if(i + lowbit(i) <= n) {
				tr[i + lowbit(i)] += tr[i];
			}
		}
	}

	void modify (int p, const Info& v) {
		for(; p <= n; p += lowbit(p)) {
			tr[p] += v;
		}
	}

	Info query (int p) {
		Info res{};
		for(; p; p -= lowbit(p)) {
			res += tr[p];
		}
		return res;
	}

	Info query (int l, int r) {
		assert(l <= r && l != 0);
		return query(r) - query(l - 1);
	}

	int lower_bound (Info k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] < k)
				k -= tr[x += i];
		return x + 1;
	}

	int upper_bound (Info k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] <= k)
				k -= tr[x += i];
		return x + 1;
	}

private:
	int n;
	std::vector<Info> tr;
	constexpr int lowbit(int x) { return x & -x; }
};
