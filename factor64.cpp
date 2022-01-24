namespace factor64 {
    const int SIEVE_MAX = 1e7;
    const int SQRT_MAX = 1e12;

#ifdef LOCAL
    #define RAND_SEED 1337
#else
    #define RAND_SEED time(0)
#endif
    mt19937_64 rand64(RAND_SEED);

    int sieve[SIEVE_MAX];
    void build_sieve() {
        iota(sieve, sieve + SIEVE_MAX, 0);
        for (int p = 2; p < SIEVE_MAX; ++p)
            for (ll q = p * (ll)p; q < SIEVE_MAX; q += p)
                chkmin(sieve[q], p);
    }

    vector<ull> factorize_sieve(ull n) {
        assert(n < SIEVE_MAX);
        vector<ull> primes;
        while (n > 1) {
            int d = sieve[n];
            primes.push_back(d);
            n /= d;
        }
        return primes;
    }

    vector<ull> factorize_sqrt(ull n) {
        assert(n < SQRT_MAX);
        vector<ull> primes;
        for (int p = 2; p * (ull)p <= n; ++p)
            for (; n % p == 0; n /= p)
                primes.push_back(p);
        if (n > 1)
            primes.push_back(n);
        return primes;
    }

    static inline ull add_mod(ull a, ull b, ull m) {
        return (a + b) % m;
    }

    static inline ull mul_mod(ull a, ull b, ull m) {
        static const ull E9 = 1e9;
        static const ull E12 = 1e12;
        if (m < E9)
            return a * b % m;
        if (m < E12)
            return add_mod(((a >> 20) * b % m) << 20, (a & ((1 << 20) - 1)) * b, m);
        return a * (__uint128_t)b % m;
    }

    ull bpow(ull a, ull b, ull m) {
        ull res = 1;
        for (; b; b >>= 1, a = mul_mod(a, a, m))
            if (b & 1)
                res = mul_mod(res, a, m);
        return res;
    }

    bool miller_rabin(ull n) {
        static const int MILLER_RABIN_ITERATIONS = 10;

        assert(n > 9);
        if (n % 2 == 0) return false;

        ull m = n - 1;
        int k = 0;
        for (; ~m & 1; m >>= 1)
            ++k;

        uniform_int_distribution<ull> random_candidate(2, n - 2);
        for (int iteration = 0; iteration < MILLER_RABIN_ITERATIONS; ++iteration) {
            ull a = random_candidate(rand64);
            a = bpow(a, m, n);
            if (a == 1) continue;
            bool ok = false;
            for (int i = 0; i < k; ++i) {
                if (a == n - 1) {
                    ok = true;
                    break;
                }
                a = mul_mod(a, a, n);
            }
            if (!ok) return false;
        }
        return true;
    }

    ull rho_pollard(ull n) {
        static int RHO_POLLARD_ITERATIONS = 10;

        uniform_int_distribution<ull> random_x0(0, n - 1);
        auto f = [&](ull x) {
            return (mul_mod(x, x, n) + 1) % n;
        };

        for (int iteration = 0; iteration < RHO_POLLARD_ITERATIONS; ++iteration) {
            ull x = random_x0(rand64);
            ull y = x;
            ull g = 1;
            while (g == 1) {
                x = f(x);
                y = f(f(y));
                g = gcd(y - x, n);
            }
            if (g < n) {
                return g;
            }
        }
        throw;
    }

    vector<ull> factorize64(ull n) {
        if (n < SIEVE_MAX)
            return factorize_sieve(n);
        if (n < SQRT_MAX)
            return factorize_sqrt(n);
        if (miller_rabin(n))
            return {n};
        auto d = rho_pollard(n);
        auto res = factorize64(d);
        auto res1 = factorize64(n / d);
        res.insert(res.end(), ALL(res1));
        sort(ALL(res));
        return res;
    }
}
