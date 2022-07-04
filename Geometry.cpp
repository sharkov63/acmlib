#include <cmath>
#include <iostream>

/// A helper class for real number computation,
/// which overrides comparison operators
/// to compare reals with epsilon precision.
class Real {
   public:
    using PrimitiveReal = long double;

    static constexpr const PrimitiveReal eps = 1e-9;

   private:
    PrimitiveReal value;

   public:
    Real() : value(0) {}
    template <typename T>
    Real(T x) : value(static_cast<PrimitiveReal>(x)) {}

    explicit operator float() const { return static_cast<float>(value); }
    explicit operator double() const { return static_cast<double>(value); }
    explicit operator long double() const {
        return static_cast<long double>(value);
    }

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
    Real& operator--() {
        --value;
        return *this;
    }
    Real operator--(int32_t) {
        Real copy = *this;
        --value;
        return copy;
    }

    friend bool operator==(Real lhs, Real rhs) {
        return std::fabs(lhs.value - rhs.value) < eps;
    }
    friend bool operator!=(Real lhs, Real rhs) {
        return std::fabs(lhs.value - rhs.value) >= eps;
    }
    friend bool operator<(Real lhs, Real rhs) {
        return lhs.value <= rhs.value - eps;
    }
    friend bool operator>(Real lhs, Real rhs) {
        return lhs.value >= rhs.value + eps;
    }
    friend bool operator<=(Real lhs, Real rhs) {
        return lhs.value < rhs.value + eps;
    }
    friend bool operator>=(Real lhs, Real rhs) {
        return lhs.value > rhs.value - eps;
    }

    friend std::istream& operator>>(std::istream& is, Real& x) {
        return is >> x.value;
    }
    friend std::ostream& operator<<(std::ostream& os, Real x) {
        return os << x.value;
    }
};
Real operator+(Real lhs, Real rhs) { return Real(lhs) += rhs; }
Real operator-(Real lhs, Real rhs) { return Real(lhs) -= rhs; }
Real operator*(Real lhs, Real rhs) { return Real(lhs) *= rhs; }
Real operator/(Real lhs, Real rhs) { return Real(lhs) /= rhs; }

Real acos(Real x) { return std::acos((Real::PrimitiveReal)x); }
Real asin(Real x) { return std::asin((Real::PrimitiveReal)x); }
Real atan(Real x) { return std::atan((Real::PrimitiveReal)x); }
Real atan2(Real y, Real x) {
    return std::atan2((Real::PrimitiveReal)y, (Real::PrimitiveReal)x);
}
Real ceil(Real x) { return std::ceil((Real::PrimitiveReal)x); }
Real cos(Real x) { return std::cos((Real::PrimitiveReal)x); }
Real cosh(Real x) { return std::cosh((Real::PrimitiveReal)x); }
Real exp(Real x) { return std::exp((Real::PrimitiveReal)x); }
Real fabs(Real x) { return std::fabs((Real::PrimitiveReal)x); }
Real floor(Real x) { return std::floor((Real::PrimitiveReal)x); }
Real log(Real x) { return std::log((Real::PrimitiveReal)x); }
Real log10(Real x) { return std::log10((Real::PrimitiveReal)x); }
Real pow(Real x, Real y) {
    return std::pow((Real::PrimitiveReal)x, (Real::PrimitiveReal)y);
}
Real sin(Real x) { return std::sin((Real::PrimitiveReal)x); }
Real sinh(Real x) { return std::sinh((Real::PrimitiveReal)x); }
Real sqrt(Real x) { return std::sqrt((Real::PrimitiveReal)x); }
Real tan(Real x) { return std::tan((Real::PrimitiveReal)x); }
Real tanh(Real x) { return std::tanh((Real::PrimitiveReal)x); }

template <typename T>
int32_t sign(T x) {
    if (x == 0) return 0;
    if (x > 0) return +1;
    return -1;
}
