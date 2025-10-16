// validated by: https://qoj.ac/submission/1518734
// validated by: https://qoj.ac/submission/1518792

#include <bits/stdc++.h>
using i64 = long long;

// Node: 1-based "" 为 1 号节点
struct SAM {
	static constexpr int N = 26;
	struct Node {
		int len;
		int link;
		std::array<int, N> next;
		Node() : len(), link(), next() {}
	};

	i64 substr;
	std::vector<Node> t;

	SAM (int n = 0) {
		t.reserve(n);
		t.assign(2, Node());
		t[0].next.fill(1);
		t[0].len = -1;
		substr = 0;
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int extend(int p, int c) {
		int cur = newNode();
		t[cur].len = t[p].len + 1;

		while (t[p].next[c] == 0) {
			t[p].next[c] = cur;
			p = t[p].link;
		}
		
		int q = t[p].next[c];
		if (t[q].len == t[p].len + 1) {
			t[cur].link = q;
		} else {
			int r = newNode();
			t[r].len = t[p].len + 1;
			t[r].link = t[q].link;
			t[r].next = t[q].next;
			t[q].link = r;
			while (t[p].next[c] == q) {
				t[p].next[c] = r;
				p = t[p].link;
			}
			t[cur].link = r;
		}

		substr += t[cur].len - t[t[cur].link].len;
		return cur;
	}

	int len(int p) {
		return t[p].len;
	}

	int link(int p) {
		return t[p].link;
	}

	int next(int p, int x) {
		return t[p].next[x];
	}
			
	int size() {
		return t.size();
	}

	i64 count () {
		return substr;
	}

	// [ SAM 节点的个数 (不含空节点), 后缀树 ]
	auto getTree() {
		int n = t.size();
		std::vector<std::vector<int>> adj(n);
		for (int i = 2; i < n; ++i) {
			adj[t[i].link].push_back(i);
		}
		return std::pair { n - 1, std::move(adj) };
	}
};
