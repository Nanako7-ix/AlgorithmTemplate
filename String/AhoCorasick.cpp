#include <bits/stdc++.h>

struct AhoCorasick {
public:
	AhoCorasick(int n = 0) {
		t.reserve(n);
		t.assign(2, Node());
		t[0].next.fill(1);
		t[0].len = -1;
		t[0].adj.push_back(1);
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int insert(const std::string& s) {
		int p = 1;
		for (auto c : s) {
			int x = c - 'a';
			if (t[p].next[x] == 0) {
				t[p].next[x] = newNode();
				t[t[p].next[x]].len = t[p].len + 1;
			}
			p = t[p].next[x];
		}
		return p;
	}

	void work() {
		std::queue<int> q;
		q.push(1);
		
		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int i = 0; i < N; i++) {
				if (t[u].next[i] == 0) {
					t[u].next[i] = t[t[u].fail].next[i];
				} else {
					t[t[u].next[i]].fail = t[t[u].fail].next[i];
					t[t[t[u].fail].next[i]].adj.push_back(t[u].next[i]);
					q.push(t[u].next[i]);
				}
			}
		}
	}

	int len(int p) {
		return t[p].len;
	}

	int fail(int p) {
		return t[p].fail;
	}

	const std::vector<int>& adj(int p) {
		return t[p].adj;
	}

	int next(int p, int x) {
		return t[p].next[x];
	}

	int size() {
		return t.size();
	}

private:
	static constexpr int N = 26;
	struct Node {
		int len, fail;
		std::vector<int> adj;
		std::array<int, N> next;
		Node() : len(0), fail(0), adj{}, next{} {}
	};

	std::vector<Node> t;
};
