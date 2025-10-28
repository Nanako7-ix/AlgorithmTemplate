#include <bits/stdc++.h>
#include "Point.cpp"

template<typename T, typename Iter>
bool point_in_polygon(const Point<T>& p, const Iter& l, const Iter& r) {
	int n = r - l;
	for (int i = 0; i < n; ++i) {
		Point<T> u = l[i], v = l[(i + 1) % n];
		if (
			(p - u).cross(p - v) == 0 &&
			std::min(u.x, v.x) <= p.x && p.x <= std::max(u.x, v.x) &&
			std::min(u.y, v.y) <= p.y && p.y <= std::max(u.y, v.y)
		) return true;
	}

	bool ret = false;
	for (int i = 0; i < n; ++i) {
		Point<T> u = l[i], v = l[(i + 1) % n];
		if (u.x < p.x && p.x <= v.x && (p - v).corss(u - v) > 0) {
			ret ^= 1;
		}
		if (v.x < p.x && p.x <= u.x && (p - u).cross(v - u) > 0) {
			ret ^= 1;
		}
	}

	return ret;
}
