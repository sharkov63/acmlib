
const int MOD = 998244353;
struct PrimeField {
    int r;

    PrimeField(): r(0) {}
    PrimeField(ll x) {
        r = x % MOD;
        if (r < 0)
            r += MOD;
    }
    PrimeField(const PrimeField& oth): r(oth.r) {}

    PrimeField operator - () {
        return PrimeField(-r);
    }
    PrimeField& operator += (const PrimeField& oth) {
        if ((r += oth.r) >= MOD)
            r -= MOD;
        return *this;
    }
    PrimeField& operator -= (const PrimeField& oth) {
        if ((r -= oth.r) < 0)
            r += MOD;
        return *this;
    }
    PrimeField& operator *= (const PrimeField& oth) {
        r = r * (ll)oth.r % MOD;
        return *this;
    }
};
ostream& operator << (ostream& stream, const PrimeField& a) {
    return stream << a.r;
}
PrimeField operator + (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) += rhs; }
PrimeField operator - (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) -= rhs; }
PrimeField operator * (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) *= rhs; }
bool operator == (const PrimeField& lhs, const PrimeField& rhs) { return lhs.r == rhs.r; }
bool operator != (const PrimeField& lhs, const PrimeField& rhs) { return lhs.r != rhs.r; }
PrimeField bpow(PrimeField a, ll b) {
    PrimeField res = 1;
    for (; b; b >>= 1, a *= a)
        if (b & 1)
            res *= a;
    return res;
}
PrimeField inv(PrimeField a) {
    return bpow(a, MOD - 2);
}

