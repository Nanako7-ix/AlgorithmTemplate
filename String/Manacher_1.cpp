// validated by: https://judge.yosupo.jp/submission/320606
#include <bits/stdc++.h>

// input: 0-based, idx(s[i]) = 2i
std::vector<int> Manacher(const std::string& t) {
	std::string s = "#";
	for (auto& ch : t) {
		s += '$', s += ch;
	} s += '$';

	int n = s.size() - 1;
	std::vector<int> d(n + 1);
	for (int i = 1, j = 1; i <= n; ++i) {
		d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
		while (i + d[i] <= n && i - d[i] >= 1 && s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (i + d[i] > j + d[j]) j = i;
	}

	return d;
}
