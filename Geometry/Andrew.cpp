#include <bits/stdc++.h>
#include "Point.cpp"

template<typename Iter, typename point = std::iterator_traits<Iter>::value_type>
auto Andrew(Iter l, Iter r) {
	std::vector p(l, r);
	std::sort(p.begin(), p.end());

	int n = r - l, x = 0, y = 0;
	std::vector<point> u(n), d(n);
	for (auto p : p) {
		while (x > 1 && (u[x - 1] - u[x - 2]).cross(p - u[x - 1]) >= 0) x--;
		while (x && p.x == u[x - 1].x) x--;
		u[x++] = p;
		while (y > 1 && (d[y - 1] - d[y - 2]).cross(p - d[y - 1]) <= 0) y--;
		if (y == 0 || d[y - 1].x < p.x) d[y++] = p;
	}
	u.resize(x), d.resize(y);

	return std::pair { u, d };

	// if (u.back() == d[0]) u.pop_back();
	// if (d.back() == u[0]) d.pop_back();
	// d.insert(d.end(), u.rbegin(), u.rend());	
	// return d;
}
