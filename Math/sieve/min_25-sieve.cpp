#include <bits/stdc++.h>
using i64 = long long;

template<typename T, typename F_Tp, typename sum_Tp>
struct Min_25 {
public:
	vector<i64> minp, P;
	Min_25(i64 n, F_Tp&& F, sum_Tp&& sum) {
		this -> F = F;
		this -> sum = sum;
		init(n);
	}	
	T operator()(i64 n) { return g(n); }
private:
	F_Tp F;
	sum_Tp sum;
	
	i64 n, sq, m;
	vector<T> pre;
	vector<T> g1, g2;
	
	T& g(i64 k) { return k <= sq ? g1[k] : g2[n / k]; }
	
	void sieve(i64 n) {
		minp.assign(n + 1, 0);
		P.clear();
		for (i64 i = 2; i <= n; ++i) {
			if (minp[i] == 0) {
				P.push_back(minp[i] = i);
			}
			for (i64& p : P) {
				if(i * p > n) break;
				minp[i * p] = p;
				if(i % p == 0) break;
			}
		}
	}
	
	
	void init(i64 n) {
		this -> n = n;
		this -> sq = [n]() {
			i64 t = std::sqrt(n);
			while (t * t > n) --t;
			while ((t + 1) * (t + 1) < n) ++t;
			return t;
		} ();
		
		g1.assign(sq + 1, T());
		g2.assign(sq + 1, T());

		sieve(sq);
		m = P.size();

		pre.assign(m + 1, T());
		for (int i = 0; i < m; ++i) {
			pre[i + 1] = pre[i] + F(P[i]);
		}

		vector<i64> x;
		for (i64 k = 1; k <= n; ++k) {
			g(n / k) = sum(n / k) - F(1);
			x.push_back(n / k);
			k = n / (n / k);
		}
		
		for (i64 j = 0; j < m; ++j) {
			i64 p = P[j];
			for (i64 x : x) {
				if (p * p > x) break;
				g(x) -= F(p) * (g(x / p) - pre[j]);
			}
		}
	}
};

template<typename F_Tp, typename sum_Tp>
Min_25(int, F_Tp, sum_Tp) -> Min_25<std::invoke_result_t<F_Tp, i64>, F_Tp, sum_Tp>;
