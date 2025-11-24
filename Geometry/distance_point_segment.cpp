#include "Point.cpp"

template<typename T, typename F>
double distancePS(const Point<T, F> &p, const Point<T, F> &u, const Point<T, F>& v) {
	if (dot(p - u, v - u) < 0) return (p - u).length();
	if (dot(p - v, u - v) < 0) return (p - v).length();
	return abs((p - u).cross(p - v)) / (u - v).length();
}