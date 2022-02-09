
/**
 * It's possible to create many ModRing's,
 * to handle arithmetic under several modules at once.
 */

/**
 * An integer wrapper modulo M
 */
struct ModInt {
    ll r;

    ModInt(): r(0) {}
    ModInt(ll x) {
        r = x;
    }
    ModInt(const ModInt& oth): r(oth.r) {}

    /* comparison */

    bool operator == (const ModInt& oth) const {
        return r == oth.r;
    }
    bool operator != (const ModInt& oth) const {
        return r != oth.r;
    }
    bool operator < (const ModInt& oth) const {
        return r < oth.r;
    }
};
ostream& operator << (ostream& stream, const ModInt& x) {
    return stream << x.r;
}

/*
 * A ring of integers modulo 64-bit integer M.
 */
struct ModRing {
    ll M;

    ModRing(ll _M) {
        assert(_M >= 2);
        M = _M;
    }

    inline ModInt toModInt(ll x) {
        x %= M;
        if (x < 0)
            x += M;
        return ModInt(x);
    }

    /* arithmetic */

    inline ModInt& add(ModInt& lhs, const ModInt& rhs) {
        if ((lhs.r += rhs.r) >= M)
            lhs.r -= M;
        return lhs;
    }
    inline ModInt sum(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        return add(res, rhs);
    }
    inline ModInt& sub(ModInt& lhs, const ModInt& rhs) {
        if ((lhs.r -= rhs.r) < 0)
            lhs.r += M;
        return lhs;
    }
    inline ModInt opp(const ModInt& x) {
        if (x == 0)
            return 0;
        return ModInt(-x.r);
    }
    inline ModInt diff(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        return sub(res, rhs);
    }
    inline ModInt& mul(ModInt& lhs, const ModInt& rhs) {
        static const ll E9 = 1e9;
        static const ll E12 = 1e12;
        if (M < E9)
            lhs.r = lhs.r * rhs.r % M;
        if (M < E12)
            lhs.r = ((((lhs.r >> 20) * rhs.r % M) << 20) + (lhs.r & ((1 << 20) - 1)) * rhs.r) % M;
        lhs.r = lhs.r * (__uint128_t)rhs.r % M;
        return lhs;
    }
    inline ModInt prod(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        return mul(res, rhs);
    }
    ModInt bpow(ModInt a, ll b) {
        ModInt res = 1;
        for (; b; mul(a, a), b >>= 1)
            if (b & 1)
                mul(res, a);
        return res;
    }
    ModInt inverse(const ModInt& x) {
        ll a = x.r;
        ll m = M;
        ll ua = 1;
        ll um = 0;
        while (a) {
            ll t = m / a;
            m -= t * a; swap(a, m);
            um -= t * ua; swap(ua, um);
        }
        assert(m == 1);
        return toModInt(ua);
    }
    ModInt divide(ModInt& lhs, const ModInt& rhs) {
        return mul(lhs, inverse(rhs));
    }
    ModInt quotient(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        return divide(res, rhs);
    }
};

