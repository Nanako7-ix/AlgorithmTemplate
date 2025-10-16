#include <bits/stdc++.h>

// validated by: https://qoj.ac/submission/1516951
// validated by: https://www.luogu.com.cn/record/240699257
// validated by: https://www.luogu.com.cn/record/240699932

// input: 0-based, output: 1-based
auto getFail (const std::string& s) {
	int n = s.size();
	std::vector<int> fail(n + 1);
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && s[i] != s[j]) j = fail[j];
		fail[i + 1] = j += (s[i] == s[j]);
	}
	return fail;
}

// validated by: https://www.luogu.com.cn/record/240699257

// input: 0-based, output: 1-based
auto getTrans(const std::string& s) {
	int n = s.size();
	auto fail = getFail(s);

	std::vector<int> trans(n + 1);
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && s[i] != s[j]) j = fail[j];
		j += s[i] == s[j];
		while (2 * j > i + 1) j = fail[j];
		trans[i + 1] = j;
	}
	return trans;
}

// validated by: https://www.luogu.com.cn/record/240699932

// input: 0-based, output: 0-based
auto occurrence(const std::string& s, const std::string& t) {
	int n = s.size(), m = t.size();
	auto fail = getFail(t);

	std::vector<int> occur;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j && s[i] != t[j]) j = fail[j];
		j += s[i] == t[j];
		if (j == m) {
			occur.push_back(i - m + 1);
			j = fail[j];
		}
	}
	return occur;
}
