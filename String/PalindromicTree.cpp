// validated by: https://qoj.ac/submission/1523333
// validated by: https://judge.yosupo.jp/submission/320953
#include <bits/stdc++.h>

//  odd root: 1
// even root: 0
struct PAM {
	static constexpr int N = 26;
	struct Node {
		int len, fail;
		std::array<int, N> next;
		Node() : len(0), fail(0), next{} {}
	};

	int cur;
	std::vector<int> s;
	std::vector<Node> t;

	PAM(int n = 0) {
		s.reserve(n);
		t.reserve(n + 2);
		t.assign(2, Node());
		t[t[0].fail = 1].len = -1;
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int append(int p, int ch) {
		int n = s.size();
		s.push_back(ch);

		auto get = [&](int p) {
			while (n - t[p].len - 1 < 0 || ch != s[n - t[p].len - 1]) {
				p = t[p].fail;
			}
			return p;
		};

		p = get(p);
		if (t[p].next[ch] == 0) {
			int cur = newNode();
			t[cur].len = t[p].len + 2;
			t[p].next[ch] = cur;
			if (t[cur].len != 1) {
				t[cur].fail = t[get(t[p].fail)].next[ch];
			}
		}

		return t[p].next[ch];
	}

	int len(int p) {
		return t[p].len;
	}

	int fail(int p) {
		return t[p].fail;
	}

	int next(int p, int x) {
		return t[p].next[x];
	}

	int size() {
		return t.size();
	}
};

int main () {
	std::cin.tie(nullptr) -> sync_with_stdio(false);

	std::string s;
	std::cin >> s;

	auto f = [&](int p) {
		if (p == 0) return 0;
		if (p == 1) return -1;
		return p - 1;
	};
	
	int n = s.size();
	PAM pam(n);
	std::vector<int> p(n + 1);
	for (int i = 0; i < n; ++i) {
		p[i + 1] = pam.append(p[i], s[i] - 'a');
	}

	int m = pam.size() - 1;
	std::vector<int> prev(m + 1);
	for (int u = 0; u <= m; ++u) {
		for (int ch = 0; ch < 26; ++ch) {
			if (pam.next(u, ch) != 0) {
				prev[pam.next(u, ch)] = u;
			}
		}
	}

	std::cout << m - 1 << "\n";
	for (int u = 2; u <= m; ++u) {
		std::cout << f(prev[u]) << ' ' << f(pam.fail(u)) << "\n";
	}
	for (int i = 1; i <= n; ++i) {
		std::cout << f(p[i]) << " \n"[i == n];
	}

	return 0;
}
