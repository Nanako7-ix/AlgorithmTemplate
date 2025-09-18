#include <bits/stdc++.h>

template<typename T>
struct Point {
	using value_type = T;
	T x, y;
	Point () : x(0), y(0) {}
	Point (const T& x, const T& y) : x(x), y(y) { }
	
	T   dot(const Point& o) const { return x * o.x + y * o.y; }
	T cross(const Point& o) const { return x * o.y - y * o.x; }

	Point  operator- () const { return Point { -x, -y }; }
	Point& operator+=(const Point& o) & { x += o.x, y += o.y; return *this; }
	Point& operator-=(const Point& o) & { x -= o.x, y -= o.y; return *this; }
	Point& operator*=(const T& k) & { x *= k, y *= k; return *this; }
	Point& operator/=(const T& k) & { x /= k, y /= k; return *this; }
	
	friend Point operator+(Point x, const Point& y) { return x += y; }
	friend Point operator-(Point x, const Point& y) { return x -= y; }
	friend Point operator*(Point p, const T& k) { return p *= k; }
	friend Point operator*(const T& k, Point p) { return p *= k; }
	friend Point operator/(Point p, const T& k) { return p /= k; }
	
	friend bool operator== (const Point& x, const Point& y) { return x.x == y.x && x.y == y.y; }
	friend auto operator<=>(const Point& x, const Point& y) = default;
	
	friend istream& operator>> (istream& is, Point& p) { return is >> p.x >> p.y; }
	friend ostream& operator<< (ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

	T square() const { return dot(*this); }
};
