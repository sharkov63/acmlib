#include <cmath>
#include <iostream>

using namespace std;

/**
 * A helper class for real number computation,
 * which overrides comparison operators
 * to compare reals with epsilon precision.
 */
class Real {
   private:
    using PrimitiveReal = long double;

    static constexpr PrimitiveReal eps = 1e-9;

    PrimitiveReal value;

   public:
    Real() : value(0) {}
    Real(PrimitiveReal real) : value(real) {}
    template <typename T>
    Real(const T& x) : value(static_cast<PrimitiveReal>(x)) {}

    explicit operator float() const { return static_cast<float>(value); }
    explicit operator double() const { return static_cast<float>(value); }
    explicit operator long double() const { return static_cast<float>(value); }

    Real& operator+=(Real other) {
        value += other.value;
        return *this;
    }
    Real& operator-=(Real other) {
        value -= other.value;
        return *this;
    }
    Real& operator*=(Real other) {
        value *= other.value;
        return *this;
    }
    Real& operator/=(Real other) {
        value /= other.value;
        return *this;
    }

    Real operator+() const { return *this; }
    Real operator-() const { return Real(-value); }
    Real& operator++() {
        ++value;
        return *this;
    }
    Real operator++(int32_t) {
        Real copy = *this;
        ++value;
        return copy;
    }

    bool operator==(Real other) const {
        return fabs(value - other.value) < eps;
    }
    bool operator!=(Real other) const {
        return fabs(value - other.value) >= eps;
    }
    bool operator<(Real other) const { return value <= other.value - eps; }
    bool operator>(Real other) const { return value >= other.value + eps; }
    bool operator<=(Real other) const { return value < other.value + eps; }
    bool operator>=(Real other) const { return value > other.value - eps; }

    friend istream& operator>>(istream& is, Real& x) { return is >> x.value; }
    friend ostream& operator<<(ostream& os, Real x) { return os << x.value; }
};
Real operator+(Real lhs, Real rhs) { return Real(lhs) += rhs; }
Real operator-(Real lhs, Real rhs) { return Real(lhs) -= rhs; }
Real operator*(Real lhs, Real rhs) { return Real(lhs) *= rhs; }
Real operator/(Real lhs, Real rhs) { return Real(lhs) /= rhs; }

Real fabs(Real x) {
    if (x >= 0) return x;
    return -x;
}

template <typename T>
int sign(const T& x) {
    if (x == 0) return 0;
    if (x > 0) return +1;
    return -1;
}
