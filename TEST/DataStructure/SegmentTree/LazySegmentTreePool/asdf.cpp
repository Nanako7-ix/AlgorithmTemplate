#include <bits/stdc++.h>
using namespace std;

auto Manacher(std::string& t) {
	std::string s = "$";
	for (auto ch : t) {
		s += ch, s += '$';
	}
	int n = s.size();
	std::vector<int> d(n);
	for (int i = 0, j = 0; i < n; ++i) {
		d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
		while (i + d[i] < n && i - d[i] >= 0 && s[i + d[i]] == s[i - d[i]]) ++d[i];
		if (i + d[i] > j + d[j]) j = i;
	}
	return d;
}

int main () {
	string s;
	cin >> s;
	auto d = Manacher(s);
	for (int i = 1; i < (int) d.size() - 1; ++i) {
		cout << d[i] - 1 << " \n"[i == (int) d.size()];
	}
}
