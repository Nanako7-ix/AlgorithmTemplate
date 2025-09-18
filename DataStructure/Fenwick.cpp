#include <bits/stdc++.h>

template<typename T>
struct BIT {
    int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return x & -x; }

	BIT () = default;
	BIT (int n, T e = {}) { init(n, e); }

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	BIT (const Iter& l, const Iter& r) { init(l, r); }

	void init (int n, T e = {}) {
		std::vector<T> _(n, e);
		init(_.begin(), _.end());
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init (const Iter& l, const Iter& r) {
		n = r - l;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += l[i - 1];
			if(i + lowbit(i) <= n) {
				tr[i + lowbit(i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		for(; p <= n; p += lowbit(p)) {
			tr[p] += v;
		}
	}

	T query (int p) {
        T res {};
		for(; p; p -= lowbit(p)) {
			res += tr[p];
		}
		return res;
	}

	T query (int l, int r) {
		assert(l <= r && l != 0);
		return query(r) - query(l - 1);
	}

	int lower_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] < k)
				k -= tr[x += i];
		return x + 1;
	}

	int upper_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] <= k)
				k -= tr[x += i];
		return x + 1;
	}
};

int main () {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    BIT<int> tr(a.begin() + 1, a.end());
    for (int i = 1; i <= m; ++i) {
        int op, x, y;
        std::cin >> op >> x >> y;
        if (op == 1) {
            tr.modify(x, y);
        } else {
            std::cout << tr.query(x, y) << "\n";
        }
    }
    return 0;
}
