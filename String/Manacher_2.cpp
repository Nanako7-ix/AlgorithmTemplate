// validated by: https://www.luogu.com.cn/record/240609771
#include <bits/stdc++.h>

// input: 0-based
// idx(s[i]) = 2i
int Manacher(const std::string& t) {
	std::string s = "#";
	for (auto& ch : t) {
		s += '$', s += ch;
	} s += '$';

	int n = s.size() - 1, ans = 0;
	std::vector<int> d(n + 1);
	for (int i = 1, j = 1; i <= n; ++i) {
		d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
		while (i + d[i] <= n && i - d[i] >= 1 && s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (i + d[i] > j + d[j]) {
			if (s[i] == '$') {
				for (int k = j + d[j]; k < i + d[i]; ++k) {
					if (s[k] == '$') continue;
					int l = (2 * i - k) >> 1, r = k >> 1;
					if ((r - l + 1) % 4 != 0) continue;
					int x = i >> 1;
					if (d[l + x] - 1 >= (r - l + 1) / 2) {
						ans = std::max(ans, r - l + 1);
					}
				}
			}
			j = i;
		}
	}

	return ans;
}
