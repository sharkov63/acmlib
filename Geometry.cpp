#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

// A helper class for real number computation,
// which overrides comparison operators
// to compare reals with epsilon-precision.
class Real {
   public:
    // Underlying primitive floating-point type.
    // Feel free to change it to double/float
    // for better performance.
    using PrimitiveReal = long double;

    // Allowed approximation error.
    // Feel free to tweak it.
    static constexpr const PrimitiveReal eps = 1e-9;

   private:
    PrimitiveReal value;

   public:
    Real() : value(0) {}
    template <typename T>
    Real(T x) : value(static_cast<PrimitiveReal>(x)) {}

    // Conversion to primitive types

    explicit operator float() const { return static_cast<float>(value); }
    explicit operator double() const { return static_cast<double>(value); }
    explicit operator long double() const {
        return static_cast<long double>(value);
    }
    explicit operator int() const { return static_cast<int>(value); }
    explicit operator long() const { return static_cast<long>(value); }
    explicit operator long long() const {
        return static_cast<long long>(value);
    }

    // Arithmetic

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

    // Comparison

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

    // iostream operators

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

// Overloads of some functions from <cmath> for Real type.

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

template <typename T, typename Enable = void>
class Vector2;
template <typename T>
using Point2 = Vector2<T>;

// Encapsulates common functionality
// of Vector2 class specializations.
template <typename T>
class Vector2Common {
   public:
    // Default constructor.
    Vector2Common() : coords{0, 0} {}

    // Construct vector by coordinates.
    template <typename P, typename Q = P>
    Vector2Common(P x, Q y = 0)
        : coords{static_cast<T>(x), static_cast<T>(y)} {}

    // Conversion between vectors with different coordinate types.
    template <typename P>
    Vector2Common(Vector2<P> v)
        : coords{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

    // Construct vector by two endpoints.
    explicit Vector2Common(Point2<T> A, Point2<T> B)
        : coords{B.x() - A.x(), B.y() - A.y()} {}

    // Access to x and y coordinates
    T& x() { return coords[0]; }
    T x() const { return coords[0]; }
    T& y() { return coords[1]; }
    T y() const { return coords[1]; }

    // Access to coordinates via [] operator
    T& operator[](int i) { return coords[i]; }
    T operator[](int i) const { return coords[i]; }

    // Comparison

    bool operator==(Vector2<T> other) const { return coords == other.coords; }
    bool operator!=(Vector2<T> other) const { return coords != other.coords; }
    bool operator<(Vector2<T> other) const { return coords < other.coords; }
    bool operator<=(Vector2<T> other) const { return coords <= other.coords; }
    bool operator>(Vector2<T> other) const { return coords > other.coords; }
    bool operator>=(Vector2<T> other) const { return coords >= other.coords; }

    // Arithmetic operators

    Vector2<T> operator+(Vector2<T> other) const {
        return {x() + other.x(), y() + other.y()};
    }
    void operator+=(Vector2<T> other) {
        x() += other.x();
        y() += other.y();
    }
    Vector2<T> operator+() const { return *this; }

    Vector2<T> operator-(Vector2<T> other) const {
        return {x() - other.x(), y() - other.y()};
    }
    void operator-=(Vector2<T> other) {
        x() -= other.x();
        y() -= other.y();
    }
    Vector2<T> operator-() const { return {-x(), -y()}; }

    Vector2<T> operator*(T rhs) const { return {x() * rhs, y() * rhs}; }
    friend Vector2<T> operator*(T lhs, Vector2<T> rhs) { return rhs * lhs; }
    void operator*=(T k) {
        x() *= k;
        y() *= k;
    }

    // Dot product
    T operator^(Vector2<T> other) const {
        return x() * other.x() + y() * other.y();
    }

    bool perpendicularTo(Vector2<T> other) { return (*this ^ other) == 0; }

    // Cross product
    T operator%(Vector2<T> other) const {
        return x() * other.y() - y() * other.x();
    }

    bool parallelTo(Vector2<T> other) const { return *this % other == 0; }

    // Length

    T len2() const { return x() * x() + y() * y(); }
    Real len() const { return sqrt(len2()); }

    // Simple rotations

    void rotateCounterclockwise() {
        std::swap(x(), y());
        x() *= -1;
    }

    Vector2<T> rotatedCounterclockwise() const { return {-y(), x()}; }

    void rotateClockwise() {
        std::swap(x(), y());
        y() *= -1;
    }

    Vector2<T> rotatedClockwise() const { return {y(), -x()}; }

    // iostream operators

    friend std::istream& operator>>(std::istream& is, Vector2<T>& v) {
        return is >> v.x() >> v.y();
    }
    friend std::ostream& operator<<(std::ostream& os, Vector2<T> v) {
        return os << v.x() << ' ' << v.y();
    }

   private:
    std::array<T, 2> coords;

    operator Vector2<T>() const { return {x(), y()}; }
};

// A vector in euclidan space R^2
// with coordinates of type T.
template <typename T, typename Enable>
class Vector2 : public Vector2Common<T> {
   public:
    using Vector2Common<T>::Vector2Common;
};

// Distance between points

template <typename T>
T dist2(Point2<T> A, Point2<T> B) {
    return (B - A).len2();
}

template <typename T>
Real dist(Point2<T> A, Point2<T> B) {
    return (B - A).len();
}

template <typename T>
class Vector2<T, typename std::enable_if<std::is_integral<T>::value>::type>
    : public Vector2Common<T> {
   public:
    using Vector2Common<T>::Vector2Common;

    // Normalization

    void normalize() {
        auto g = std::gcd(this->x(), this->y());
        if (!g) return;
        if (this->x() < 0 || (this->x() == 0 && this->y() < 0)) g *= -1;
        this->x /= g;
        this->y /= g;
    }

    Vector2<T> normalized() const {
        Vector2<T> copy(*this);
        copy.normalize();
        return copy;
    }
};
using Vector = Vector2<int64_t>;
using Point = Vector;

template <typename Enable>
class Vector2<Real, Enable> : public Vector2Common<Real> {
   public:
    using Vector2Common<Real>::Vector2Common;

    // Scalar division

    Vector2<Real> operator/(Real rhs) const { return {x() / rhs, y() / rhs}; }
    void operator/=(Real k) {
        x() /= k;
        y() /= k;
    }

    // Normalization

    void normalize() {
        Real l = len();
        *this /= l;
    }

    Vector2<Real> normalized() const {
        Real l = len();
        return {x() / l, y() / l};
    }
};
using RVector = Vector2<Real>;
using RPoint = RVector;
