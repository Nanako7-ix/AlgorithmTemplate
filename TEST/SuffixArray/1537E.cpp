#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

auto SuffixArray(const std::string& s) {
	int n = s.size();
	std::vector<int> sa(n + 1), rk(n + 1);
	std::iota(sa.begin() + 1, sa.end(), 1);
	std::sort(sa.begin() + 1, sa.end(), [&](int x, int y) {
		return s[x - 1] < s[y - 1];
	});

	rk[sa[1]] = 1;
	for (int i = 1; i < n; ++i) {
		rk[sa[i + 1]] = rk[sa[i]] + (s[sa[i + 1] - 1] != s[sa[i] - 1]);
	}
			
	std::vector<int> tmp(n + 1), cnt(n + 1);
	for (int k = 1; rk[sa[n]] != n; k <<= 1) {
		for (int i = n - k + 1, j = 1; i <= n; ++i, ++j) {
			tmp[j] = i;
		}
		for (int i = 1, j = k; i <= n; ++i) {
			if (sa[i] <= k) continue;
			tmp[++j] = sa[i] - k;
		}

		for (int i = 1; i <= n; ++i) {
			cnt[rk[i]]++;
		}
		for (int i = 1; i < rk[sa[n]]; ++i) {
			cnt[i + 1] += cnt[i];
		}
		for (int i = n; i >= 1; --i) {
			sa[cnt[rk[tmp[i]]]--] = tmp[i];
		}

		std::swap(rk, tmp);
		rk[sa[1]] = 1, cnt[tmp[sa[n]]] = 0;
		for (int i = 1; i < n; ++i) {
			cnt[tmp[sa[i]]] = 0;
			rk[sa[i + 1]] = rk[sa[i]] + (
				tmp[sa[i + 1]] != tmp[sa[i]] ||
				sa[i] + k - 1 == n ||
				tmp[sa[i + 1] + k] != tmp[sa[i] + k]
			);
		}
	}

	std::vector<int> height(n + 1);
	for (int i = 1, lcp = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (lcp != 0) lcp--;
		while (
			i + lcp <= n && 
			sa[rk[i] - 1] + lcp <= n &&
			s[i + lcp - 1] == s[sa[rk[i] - 1] + lcp - 1]
		) ++lcp;
		height[rk[i]] = lcp;
	}

	return std::tuple {
		std::move(sa), 
		std::move(rk), 
		std::move(height)
	};
}

void Thephix() {
	int n, k;
	string s;
	cin >> n >> k >> s;
	
	int len = n;
	auto [sa, rk, height] = SuffixArray(s + s);
	for (int i = rk[1] + 1; i <= 2 * n; ++i) {
		len = min(len, sa[i] - 1);
	}
	for (int i = 1, j = 0; i <= k; ++i, j = (j + 1) % len) {
		cout << s[j];
	}
	cout << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
