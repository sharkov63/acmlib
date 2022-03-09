class ModInt {
public:
    static int64_t mod;
private:
    int64_t value;

    int64_t inverse(int64_t a) {
        int64_t m = mod;
        int64_t ua = 1;
        int64_t um = 0;
        while (a) {
            int64_t t = m / a;
            m -= t * a; swap(a, m);
            um -= t * ua; swap(ua, um);
        }
        assert(m == 1);
        return ua;
    }

public:
    ModInt(): value(0) {}
    ModInt(const int64_t& x) {
        value = x % mod;
        if (value < 0) value += mod;

    }
    ModInt(const ModInt& other): value(other.value) {}

    explicit operator int64_t() const {
        return value;
    }

    ModInt& operator=(const ModInt& other) {
        value = other.value;
        return *this;
    }

    ModInt& operator+=(const ModInt& other) {
        if ((value += other.value) >= mod) value -= mod;
        return *this;
    }
    ModInt operator+() const {
        return ModInt(*this);
    }
    ModInt& operator-=(const ModInt& other) {
        if ((value -= other.value) < 0) value += mod;
        return *this;
    }
    ModInt operator-() const {
        return ModInt(-value);
    }

    ModInt& operator*=(const ModInt& other) {
        static const int64_t E9 = 1e9;
        static const int64_t E12 = 1e12;
        if (mod < E9)
            (value *= other.value) %= mod;
        else if (mod < E12)
            value = ((((value >> 20) * other.value % mod) << 20) + (value & ((1 << 20) - 1)) * other.value) % mod;
        else
            value = (int64_t)(value * (__uint128_t)other.value % mod);
        return *this;
    }

    ModInt& operator/=(const ModInt& other) {
        return (*this) *= ModInt(inverse(other.value));
    }

    bool operator==(const ModInt& other) const {
        return value == other.value;
    }
    bool operator!=(const ModInt& other) const {
        return value != other.value;
    }
    bool operator<(const ModInt& other) const {
        return value < other.value;
    }
    bool operator<=(const ModInt& other) const {
        return value <= other.value;
    }
    bool operator>(const ModInt& other) const {
        return value > other.value;
    }
    bool operator>=(const ModInt& other) const {
        return value >= other.value;
    }
};
int64_t ModInt::mod = 1;
ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
ModInt bpow(ModInt a, int64_t b) {
    ModInt res = 1;
    for (; b > 0; a *= a, b >>= 1)
        if (b & 1)
            res *= a;
    return res;
}
ostream& operator<<(ostream& stream, const ModInt& x) {
    return stream << (int64_t)x;
}
istream& operator>>(istream& stream, ModInt& x) {
    int64_t y;
    stream >> y;
    x = ModInt(y);
    return stream;
}
