#include <bits/stdc++.h>

static std::vector<int> rev;

template<typename Z>
struct Poly : public std::vector<Z> {
    Poly() : std::vector<Z> () {}
    explicit constexpr Poly(int n) : std::vector<Z> (n) {}
    explicit constexpr Poly(const std::vector<Z>& a) : std::vector<Z> (a) {}
    explicit Poly(const std::initializer_list<Z>& a) : std::vector<Z> (a) {}

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    explicit constexpr Poly(Iterator l, Iterator r) : std::vector<Z> (l, r) {}
    
    template<typename Func>
    explicit constexpr Poly(int n, Func&& f) : std::vector<Z> (n) {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }

    constexpr friend Poly operator<<(const Poly& p, int k) {
        assert(k >= 0);
        if (k < (int) p.size()) {
            return Poly(p.begin() + k, p.end());
        }
        return Poly();
    }
    constexpr Poly& operator<<= (int k) {
        *this = *this << k;
        return *this;
    }

    constexpr friend Poly operator>>(const Poly& p, int k) {
        assert(k >= 0);
        Poly f(p);
        f.insert(f.begin(), k, 0);
        return f;
    }
    constexpr Poly& operator>>=(int k) {
        *this = *this >> k;
        return *this;
    }

    constexpr Poly trunc(int k) const {
        assert(k >= 0);
        Poly f(*this);
        f.reserve(k);
        return f;
    }

    constexpr friend Poly operator+(const Poly& f, const Poly& g) {
        int n = f.size(), m = g.size();
        Poly h(std::max(n, m));
        for (int i = 0; i < n; i++) {
            h[i] += f[i];
        }
        for (int i = 0; i < m; ++i) {
            h[i] += g[i];
        }
        return h;
    }

    constexpr friend Poly operator-(const Poly& f, const Poly& g) {
        int n = f.size(), m = g.size();
        Poly h(std::max(n, m));
        for (int i = 0; i < n; i++) {
            h[i] += f[i];
        }
        for (int i = 0; i < m; ++i) {
            h[i] -= g[i];
        }
        return h;
    }

    constexpr Poly operator-() const {
        Poly f(*this);
        for (auto& x : f) x = -x;
        return f;
    }

    constexpr Poly derivative() const {
        int n = this->size();
        if (n <= 1) return Poly();
        Poly f(n - 1);
        for (int i = 1; i < n; ++i) {
            f[i - 1] = i * (*this)[i];
        }
        return f;
    }

    constexpr Poly integral() const {
        int n = this->size();
        Poly f(n + 1);
        for (int i = 0; i < n; ++i) {
            f[i + 1] = (*this)[i] / (i + 1);
        }
        return f;
    }

private:
    static std::vector<Z> roots;
    void dft(std::vector<Z>& f) const {
        int n = f.size();
        if (rev.size() != n) {
            
        }
    }
};

template<typename Z> std::vector<Z> Poly<Z>::roots {0, 1};

int main () {
    Poly<int> p ({1, 2, 3, 4, 5});
    Poly<int> q = p << 2;
    for (auto x : q) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
