#include <bits/stdc++.h>
using i64 = long long;

struct Hashing {
    static int n;
    static std::array<i64, 2> Mod;
    static std::array<std::vector<i64>, 2> f;
    constexpr static std::array<i64, 2> base { 131,13331 };

    static void init (int m) {
        if(m <= n) return;
        f[0].resize(2 * m), f[1].resize(2 * m);

        for (int i = n; i < 2 * m; ++i) {
            f[0][i] = f[0][i - 1] * base[0] % Mod[0];
            f[1][i] = f[1][i - 1] * base[1] % Mod[1];
        }
        n = 2 * m;
    }

    static bool isPrime (i64 n) {
        if (n <= 2) return false;
        for (i64 i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    static i64 findPrime (int n) {
        while (!isPrime(n)) n++;
        return n;
    }
    
    static std::array<i64, 2> findPrime () {
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        return {
            findPrime(rng() % 900'000'000 + 100'000'000),
            findPrime(rng() % 900'000'000 + 100'000'000)
        };
    }
    
    static i64 p (int i, int n) {
        init(n + 1);
        return f[i][n];
    }
    
    std::array<std::vector<i64>, 2> h;
    
    Hashing () = default;
    Hashing (const std::string& s) {
        init(s);
    }
    
    void init (const std::string& s) {
        int n = s.size();
        h[0].assign(n + 1, 0);
        h[1].assign(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            h[0][i] = (h[0][i - 1] * base[0] % Mod[0] + s[i - 1]) % Mod[0];
            h[1][i] = (h[1][i - 1] * base[1] % Mod[1] + s[i - 1]) % Mod[1];
        }
    }
    
    std::array<i64, 2> query (int l, int r) {
        l--;
        assert(l < r);
        return {
            (h[0][r] - h[0][l] * p(0, r - l) % Mod[0] + Mod[0]) % Mod[0],
            (h[1][r] - h[1][l] * p(0, r - l) % Mod[1] + Mod[1]) % Mod[1],
        };
    }
};

int Hashing::n = 1;
std::array<i64, 2> Hashing::Mod = Hashing::findPrime();
std::array<std::vector<i64>, 2> Hashing::f {
    std::vector {1LL}, std::vector {1LL}
};
template<int x> i64 Mod = Hashing::Mod[x];

/**
 * 3E2:  179 191 211 227 251 311 313 347 349 353 379 389 397 419
 * 1E6:  950569 959449 960703 961531 972623 1016681 1063619
 * 1E8:  123634409 224247619 566424149 687587993 775262303 872340281
 * 1E12: 992345236997 995678562787 1023452343671 1045674564469
 * 1E13: 10123412340917 10123412346533 10234523455957 10567856781973
 * 2E13: 19234523459539 19345634567977 20234523454021 20567856785261
 * 1E15: 995678567851157 1045674567457081 1045674567459773
 * 1E17: 101234123412348037 103456345634562587 105678567856789793
 * 5E17: 491234123412346679 493456345634561563 502345234523452883
 * 1E18: 992345234523451717 994567456745676007 1045674567456745241
 * 2E18: 1956785678567854391 1956785678567855843 2056785678567853529
 */