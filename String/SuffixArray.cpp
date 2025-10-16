// validated by: https://judge.yosupo.jp/submission/320707
// validated by: https://judge.yosupo.jp/submission/320708
// validated by: https://judge.yosupo.jp/submission/320713
// validated by: https://qoj.ac/submission/1524299
#include <bits/stdc++.h>

// input: 0-based, output: 1-based
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

int main () {
	std::cin.tie(nullptr) -> sync_with_stdio(false);

	std::string s, t;
	std::cin >> s >> t;

	int n = s.size(), m = t.size();
	auto [sa, rk, height] = SuffixArray(s + '$' + t);

	std::array<int, 3> ans { 0, 0, 0 };
	for (int i = 1; i <= n + m; ++i) {
		int x = sa[i], y = sa[i + 1];
		int len = height[i + 1];
		if (len <= ans[0]) continue;
		if (x <= n && y >= n + 2) {
			ans = { len, x - 1, y - n - 2 };
		}
		if (y <= n && x >= n + 2) {
			ans = { len, y - 1, x - n - 2 };
		}
	}

	std::cout << ans[1] << ' ' << ans[1] + ans[0] << ' ' << ans[2] << ' ' << ans[2] + ans[0] << "\n";
}
