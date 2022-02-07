/**
 * Field modulo a constant prime number.
 */
struct ModField {
    static const int mod = 998244353;

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

    ModField(): r(0) {}
    ModField(ll x) {
        r = x % mod;
        if (r < 0)
            r += mod;
    }
    ModField(const ModField& oth): r(oth.r) {}

    ModField& operator = (const ModField& oth) {
        r = oth.r;
        return *this;
    }

    ModField& operator += (const ModField& oth) {
        if ((r += oth.r) >= mod)
            r -= mod;
        return *this;
    }
    ModField& operator -= (const ModField& oth) {
        if ((r -= oth.r) < 0)
            r += mod;
        return *this;
    }
    ModField operator - () const {
        return ModField(-r);
    }
    ModField& operator ++ () {
        return *this += 1;
    }
    ModField& operator -- () {
        return *this -= 1;
    }
    ModField operator ++ (int32_t) const {
        return ++ModField(*this);
    }
    ModField operator -- (int32_t) const {
        return --ModField(*this);
    }

    bool operator == (const ModField& oth) const {
        return r == oth.r;
    }
    bool operator != (const ModField& oth) const {
        return r != oth.r;
    }
    bool operator < (const ModField& oth) const {
        return r < oth.r;
    }

    ModField& operator *= (const ModField& oth) {
        r = r * (ll)oth.r % mod;
        return *this;
    }
    ModField& operator /= (const ModField& oth) {
        return *this *= ModField(inverse(oth.r));
    }
};
ostream& operator << (ostream& stream, const ModField& a) {
    return stream << a.r;
}
istream& operator >> (istream& stream, ModField& a) {
    ll x;
    stream >> x;
    a = ModField(x);
    return stream;
}
ModField operator + (const ModField& lhs, const ModField& rhs) { return ModField(lhs) += rhs; }
ModField operator - (const ModField& lhs, const ModField& rhs) { return ModField(lhs) -= rhs; }
ModField operator * (const ModField& lhs, const ModField& rhs) { return ModField(lhs) *= rhs; }
ModField operator / (const ModField& lhs, const ModField& rhs) { return ModField(lhs) /= rhs; }
ModField bpow(ModField a, ll b) {
    ModField res = 1;
    for (; b; b >>= 1, a *= a)
        if (b & 1)
            res *= a;
    return res;
}

