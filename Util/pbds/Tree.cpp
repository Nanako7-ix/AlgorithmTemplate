#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using __gnu_pbds::tree, __gnu_pbds::null_type, __gnu_pbds::rb_tree_tag;

template<typename T>
struct NodeUpdate {
	template<typename Node_CItr,typename Node_Itr,typename Cmp_Fn,typename _Alloc>
	struct X {
		using metadata_type = T;
		void operator()(Node_Itr u, Node_CItr end) {
			Node_Itr l = u.get_l_child();
			Node_Itr r = u.get_r_child();
			const_cast<T&> (u.get_metadata()) = (
				(l == end ? T() : l.get_metadata()) +
				**u +
				(r == end ? T() : r.get_metadata())
			);
		}
		virtual Node_CItr node_begin() const = 0;
		virtual Node_CItr node_end() const = 0;
	};
};

using std::cin, std::cout, std::less, std::pair;

using i64 = long long;
std::mt19937_64 rng((std::random_device())());

constexpr int N = 1E6 + 5;
int val[N], siz[N], ls[N], rs[N], tot = 0;
i64 phi[N];

int Node(int x) {
	tot++;
	val[tot] = x, siz[tot] = 1;
	ls[tot] = rs[tot] = 0;
	phi[tot] = rng();
	return tot;
}

void pull(int u) {
	siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
}

void split_val(int u, int k, int& x, int& y) {
	if (!(x = y = u)) return;
	if (val[u] <= k) {
		split_val(rs[u], k, rs[u], y);
	} else {
		split_val(ls[u], k, x, ls[u]);
	}
	pull(u);
}

void split_rnk(int u, int k, int& x, int& y) {
	if (!(x = y = u)) return;
	if (siz[ls[u]] + 1 <= k) {
		split_rnk(rs[u], k - siz[ls[u]] - 1, rs[u], y);
	} else {
		split_rnk(ls[u], k, x, ls[u]);
	}
	pull(u);
}

[[nodiscard]] int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (phi[x] < phi[y]) {
		rs[x] = merge(rs[x], y);
		pull(x);
		return x;
	} else {
		ls[y] = merge(x, ls[y]);
		pull(y);
		return y;
	}
}

int main() {
	// tree<int, null_type, less<int>, rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr;
	
	// int n, q;
	// cin >> n >> q;

	// for (int i = 1; i <= n; ++i) {
	// 	int x;
	// 	cin >> x;
	// 	tr.insert(x);
	// }

	// for (int i = 1; i <= q; ++i) {
	// 	int op, x;
	// 	cin >> op >> x;
	// 	if (op == 0) {
	// 		tr.insert(x);
	// 	} else if (op == 1) {
	// 		if (auto it = tr.find(x); it != tr.end()) {
	// 			tr.erase(it);
	// 		}
	// 	} else if (op == 2) {
	// 		if ((int) tr.size() >= x) {
	// 			cout << *tr.find_by_order(x - 1) << "\n";
	// 		} else cout << "-1\n";
	// 	} else if (op == 3) {
	// 		cout << tr.order_of_key(x) + (tr.find(x) != tr.end()) << "\n";
	// 	} else if (op == 4) {
	// 		if (auto it = tr.upper_bound(x); it != tr.begin()) {
	// 			cout << *prev(it) << "\n";
	// 		} else cout << "-1\n";
	// 	} else if (op == 5) {
	// 		if (auto it = tr.lower_bound(x); it != tr.end()) {
	// 			cout << *it << "\n";
	// 		} else cout << "-1\n";
	// 	} else {
	// 		__builtin_unreachable();
	// 	}
	// }

	
	int n, q, rt = 0;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		int x, t1, t2;
		cin >> x;
		split_val(rt, x, t1, t2);
		rt = merge(merge(t1, Node(x)), t2);
	}

	for (int i = 1; i <= q; ++i) {
		int op, x;
		cin >> op >> x;
		if (op == 0) {
			int t1, t2, t3;
			split_val(rt, x - 1, t1, t2);
			split_val(t2, x, t2, t3);

			if (t2 == 0) t2 = Node(x);
			rt = merge(merge(t1, t2), t3);
		} else if (op == 1) {
			int t1, t2, t3;
			split_val(rt, x - 1, t1, t2);
			split_val(t2, x, t2, t3);
			rt = merge(t1, t3);
		} else if (op == 2) {
			if (siz[rt] < x) {
				cout << "-1\n";
			} else {
				int t1, t2, t3;
				split_rnk(rt, x - 1, t1, t2);
				split_rnk(t2, 1, t2, t3);
				cout << val[t2] << "\n";
				rt = merge(merge(t1, t2), t3);
			}
		} else if (op == 3) {
			int t1, t2;
			split_val(rt, x, t1, t2);
			cout << siz[t1] << "\n";
			rt = merge(t1, t2);
		} else if (op == 4) {
			int t1, t2, t3;
			split_val(rt, x, t1, t3);
			if (siz[t1] == 0) {
				cout << "-1\n";
			} else {
				split_rnk(t1, siz[t1] - 1, t1, t2);
				cout << val[t2] << "\n";
				t1 = merge(t1, t2);
			}
			rt = merge(t1, t3);
		} else if (op == 5) {
			int t1, t2, t3;
			split_val(rt, x - 1, t1, t2);
			if (siz[t2] == 0) {
				cout << "-1\n";
			} else {
				split_rnk(t2, 1, t2, t3);
				cout << val[t2] << "\n";
				t2 = merge(t2, t3);
			}
			rt = merge(t1, t2);
		}
	}
}
