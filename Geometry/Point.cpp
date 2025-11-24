#include <bits/stdc++.h>

template<typename T, typename F>
struct Point {
	using value_type = T;
	using float_type = F;
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
	
	friend std::istream& operator>> (std::istream& is, Point& p) { return is >> p.x >> p.y; }
	friend std::ostream& operator<< (std::ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

	T square() const { return dot(*this); }
	F length() const { return std::sqrt<F>(dot(*this)); }
	F angle() const { return std::atan2<F>(y, x); }

	Point<F> rotate(F k) const {
		return Point<F>(
			x * std::cos<F>(k) - y * std::sin<F>(k),
			x * std::sin<F>(k) + y * std::cos<F>(k)
		);
	}

	template<typename _T, typename _F = F> operator Point<_T, _F>() const { return Point<_T, _F> (_T(x), _T(y)); }
};
