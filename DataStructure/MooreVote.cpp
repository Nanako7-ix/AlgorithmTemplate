#include <bits/stdc++.h>

#define v first
#define c second
template<typename T, int _N>
struct MooreVote {
	using Vote = pair<T, i64>;
	constexpr static int N = _N - 1;
	
	array<Vote, N> d;
	
	MooreVote () {
		d.fill(Vote { T(), 0 });
	}
	
	MooreVote (const T& e, i64 cnt = 1) {
		d.fill(Vote { T(), 0 });
		d[0] = Vote { e, cnt };
	}
	
	void merge(const Vote& vote) {
		for (auto& [v, c] : d) {
			if (v == vote.v) {
				c += vote.c;
				return;
			}
		}

		auto p = min_element(d.begin(), d.end(), [](const Vote& x, const Vote& y) {
			return x.c < y.c;
		}) - d.begin();

		int del = min(d[p].c, vote.c);
		if (d[p].c < vote.c) {
			d[p] = vote;
		}
		for(auto& [v, c] : d) {
			if (c > 0) c -= del;
		}
	}
	
	friend MooreVote operator+(MooreVote x, MooreVote y) {
		for (Vote& vote : y.d) x.merge(vote);
		return x;
	}
};
#undef v
#undef c

template<typename T>
struct MooreVote<T, 2> {
	T v; i64 c;
	
	MooreVote () { v = T(), c = 0; }
	
	MooreVote (const T& e, i64 cnt = 1) {
		v = e, c = cnt;
	}
	
	friend MooreVote operator+(MooreVote x, MooreVote y) {
		if (x.v == y.v) {
			return { x.v, x.c + y.c };
		} else if (x.c <= y.c) {
			return { y.v, y.c - x.c };			
		} else {
			return { x.v, x.c - y.c };
		}
	}
};
