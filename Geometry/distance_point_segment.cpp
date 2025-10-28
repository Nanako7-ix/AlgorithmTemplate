#include "Point.cpp"

template<typename T>
double distancePS(const Point<T> &p, const Point<T> &u, const Point<T>& v) {
	if (dot(p - u, v - u) < 0) return (p - u).length();
	if (dot(p - v, u - v) < 0) return (p - v).length();
	return abs((p - u).cross(p - v)) / (u - v).length();
}