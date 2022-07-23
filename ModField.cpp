#include <iostream>

class ModField {
   public:
    static constexpr const int32_t MOD = 998244353;

   private:
    int32_t r;

    static int64_t calcInverse(int64_t a) {
        int64_t m = MOD;
        int64_t ua = 1, um = 0;
        while (a) {
            int64_t t = m / a;
            m -= t * a, std::swap(a, m);
            um -= t * ua, std::swap(ua, um);
        }
        return um;
    }

   public:
    ModField() : r(0) {}
    ModField(int64_t x) {
        r = x % MOD;
        if (r < 0) r += MOD;
    }

    ModField& operator+=(ModField other) {
        if ((r += other.r) >= MOD) r -= MOD;
        return *this;
    }
    ModField operator+(ModField other) const {
        return ModField(*this) += other;
    }
    ModField operator+() const { return *this; }
    ModField& operator++() { return *this += 1; }
    ModField& operator++(int32_t) { return ++ModField(*this); }

    ModField& operator-=(ModField other) {
        if ((r -= other.r) < 0) r += MOD;
        return *this;
    }
    ModField operator-(ModField other) const {
        return ModField(*this) -= other;
    }
    ModField operator-() const {
        ModField copy(*this);
        copy.r *= -1;
        if (copy.r) copy.r += MOD;
        return copy;
    }
    ModField& operator--() { return *this -= 1; }
    ModField& operator--(int32_t) { return --ModField(*this); }

    ModField& operator*=(ModField other) {
        r = r * static_cast<int64_t>(other.r) % MOD;
        return *this;
    }
    ModField operator*(ModField other) const {
        return ModField(*this) *= other;
    }

    ModField bpow(int64_t power) const {
        ModField res = 1;
        ModField base = *this;
        for (; power; power >>= 1, base *= base)
            if (power & 1) res *= base;
        return res;
    }

    ModField inv() const { return ModField(calcInverse(r)); }
    ModField& operator/=(ModField other) { return *this *= other.inv(); }
    ModField operator/(ModField other) const { return *this * other.inv(); }

    bool operator==(ModField other) const { return r == other.r; }
    bool operator!=(ModField other) const { return r != other.r; }
    bool operator<(ModField other) const { return r < other.r; }
    bool operator<=(ModField other) const { return r <= other.r; }
    bool operator>(ModField other) const { return r > other.r; }
    bool operator>=(ModField other) const { return r >= other.r; }

    friend std::istream& operator>>(std::istream& is, ModField& x) {
        int64_t y;
        is >> y;
        x = ModField(y);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, ModField x) {
        return os << x.r;
    }
};
