#include <bits/stdc++.h>

template<typename Iter, typename point = std::iterator_traits<Iter>::value_type>
auto Area(Iter l, Iter r) {
	using T = point::value_type;
	T ans = 0;
	int n = r - l;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		ans += l[i].cross(l[j]);
	}
	return std::abs(ans);
}
