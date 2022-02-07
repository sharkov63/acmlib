/**
 * Ring modulo a static int.
 */
struct ModRing {
    static int mod;

    static ll inverse(ll a) {
        ll m = mod;
        ll ua = 1;
        ll um = 0;
        while (a) {
            ll t = m / a;
            m -= t * a; swap(a, m);
            um -= t * ua; swap(ua, um);
        }
        return um;
    }

    int r;

    ModRing(): r(0) {}
    ModRing(ll x) {
        r = x % mod;
        if (r < 0)
            r += mod;
    }
    ModRing(const ModRing& oth): r(oth.r) {}

    ModRing& operator = (const ModRing& oth) {
        r = oth.r;
        return *this;
    }

    ModRing& operator += (const ModRing& oth) {
        if ((r += oth.r) >= mod)
            r -= mod;
        return *this;
    }
    ModRing& operator -= (const ModRing& oth) {
        if ((r -= oth.r) < 0)
            r += mod;
        return *this;
    }
    ModRing operator - () const {
        return ModRing(-r);
    }
    ModRing& operator ++ () {
        return *this += 1;
    }
    ModRing& operator -- () {
        return *this -= 1;
    }
    ModRing operator ++ (int32_t) const {
        return ++ModRing(*this);
    }
    ModRing operator -- (int32_t) const {
        return --ModRing(*this);
    }

    bool operator == (const ModRing& oth) const {
        return r == oth.r;
    }
    bool operator != (const ModRing& oth) const {
        return r != oth.r;
    }
    bool operator < (const ModRing& oth) const {
        return r < oth.r;
    }

    ModRing& operator *= (const ModRing& oth) {
        r = r * (ll)oth.r % mod;
        return *this;
    }
    ModRing& operator /= (const ModRing& oth) {
        return *this *= ModRing(inverse(oth.r));
    }
};
int ModRing::mod;
ostream& operator << (ostream& stream, const ModRing& a) {
    return stream << a.r;
}
istream& operator >> (istream& stream, ModRing& a) {
    ll x;
    stream >> x;
    a = ModRing(x);
    return stream;
}
ModRing operator + (const ModRing& lhs, const ModRing& rhs) { return ModRing(lhs) += rhs; }
ModRing operator - (const ModRing& lhs, const ModRing& rhs) { return ModRing(lhs) -= rhs; }
ModRing operator * (const ModRing& lhs, const ModRing& rhs) { return ModRing(lhs) *= rhs; }
ModRing operator / (const ModRing& lhs, const ModRing& rhs) { return ModRing(lhs) /= rhs; }
ModRing bpow(ModRing a, ll b) {
    ModRing res = 1;
    for (; b; b >>= 1, a *= a)
        if (b & 1)
            res *= a;
    return res;
}

