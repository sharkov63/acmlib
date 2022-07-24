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
    static constexpr PrimitiveReal eps = 1e-9;

   private:
    PrimitiveReal value;

   public:
    // Default constructor: zero value.
    Real() : value(0) {}

    // Construct from a numeric type.
    template <typename T>
    Real(T x) : value(static_cast<PrimitiveReal>(x)) {}

    // Explicit conversion to primitive types.
    explicit operator float() const { return static_cast<float>(value); }
    explicit operator double() const { return static_cast<double>(value); }
    explicit operator long double() const {
        return static_cast<long double>(value);
    }
    explicit operator int32_t() const { return static_cast<int32_t>(value); }
    explicit operator long() const { return static_cast<long>(value); }
    explicit operator long long() const {
        return static_cast<long long>(value);
    }

    // Arithmetic operators.
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
    Real operator-() const { return -value; }
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

    // Comparison operators with epsilon precision.
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

    // I/O stream operators.
    friend std::istream& operator>>(std::istream& is, Real& x) {
        return is >> x.value;
    }
    friend std::ostream& operator<<(std::ostream& os, Real x) {
        return os << x.value;
    }
};
Real operator+(Real lhs, Real rhs) { return lhs += rhs; }
Real operator-(Real lhs, Real rhs) { return lhs -= rhs; }
Real operator*(Real lhs, Real rhs) { return lhs *= rhs; }
Real operator/(Real lhs, Real rhs) { return lhs /= rhs; }

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

// The sign of a number:
// a value in {-1, 0, +1}.
template <typename T>
int32_t sign(T x) {
    if (x == 0) return 0;
    if (x > 0) return +1;
    return -1;
}

// Forward declaration.
template <typename T>
class Vector;

// Point is a Vector type alias semantically convenient for
// representing points instead of vectors.
template <typename T>
using Point = Vector<T>;

// A 2-dimensional vector
// with coordinates of type T.
//
// Type T is implied to be small
// and is always passed by value.
template <typename T>
class Vector {
   public:
    // Default constructor: zero vector.
    Vector() : coords{0, 0} {}

    // Construct vector by coordinates.
    template <typename P, typename Q = P>
    Vector(P x, Q y) : coords{static_cast<T>(x), static_cast<T>(y)} {}

    // Conversion between vectors with different coordinate types.
    template <typename P>
    Vector(Vector<P> v)
        : coords{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

    // Construct vector by two endpoints.
    explicit Vector(Point<T> A, Point<T> B)
        : coords{B.x() - A.x(), B.y() - A.y()} {}

    // Access to x and y coordinates.
    T& x() { return coords[0]; }
    T x() const { return coords[0]; }
    T& y() { return coords[1]; }
    T y() const { return coords[1]; }

    // Access to coordinates by [] operator.
    T& operator[](int i) { return coords[i]; }
    T operator[](int i) const { return coords[i]; }

    // Comparison operators.
    bool operator==(Vector<T> other) const { return coords == other.coords; }
    bool operator!=(Vector<T> other) const { return coords != other.coords; }
    bool operator<(Vector<T> other) const { return coords < other.coords; }
    bool operator<=(Vector<T> other) const { return coords <= other.coords; }
    bool operator>(Vector<T> other) const { return coords > other.coords; }
    bool operator>=(Vector<T> other) const { return coords >= other.coords; }

    // Vector addition operators.
    Vector<T> operator+(Vector<T> other) const {
        return {x() + other.x(), y() + other.y()};
    }
    Vector<T>& operator+=(Vector<T> other) {
        x() += other.x();
        y() += other.y();
        return *this;
    }
    Vector<T> operator+() const { return *this; }
    Vector<T> operator-(Vector<T> other) const {
        return {x() - other.x(), y() - other.y()};
    }
    Vector<T>& operator-=(Vector<T> other) {
        x() -= other.x();
        y() -= other.y();
        return *this;
    }
    Vector<T> operator-() const { return {-x(), -y()}; }

    // Scalar multiplication operators.
    Vector<T> operator*(T rhs) const { return {x() * rhs, y() * rhs}; }
    friend Vector<T> operator*(T lhs, Vector<T> rhs) { return rhs * lhs; }
    Vector<T>& operator*=(T k) {
        x() *= k;
        y() *= k;
        return *this;
    }
    Vector<T> operator/(T rhs) const { return {x() / rhs, y() / rhs}; }
    Vector<T>& operator/=(T rhs) {
        x() /= rhs;
        y() /= rhs;
        return *this;
    }

    // Dot product.
    T operator^(Vector<T> other) const {
        return x() * other.x() + y() * other.y();
    }

    // Returns true iff vectors are perpendicular.
    bool perpendicularTo(Vector<T> other) { return (*this ^ other) == 0; }

    // Cross product.
    T operator%(Vector<T> other) const {
        return x() * other.y() - y() * other.x();
    }

    // Returns true iff vectors are parallel.
    bool parallelTo(Vector<T> other) const { return *this % other == 0; }

    // Squared length of the vector.
    T len2() const { return x() * x() + y() * y(); }

    // Length of the vector.
    Real len() const { return sqrt(len2()); }

    // Simple rotations.
    Vector<T>& rotateCounterclockwise() {
        std::swap(x(), y());
        x() *= -1;
        return *this;
    }
    Vector<T> rotatedCounterclockwise() const { return {-y(), x()}; }
    Vector<T>& rotateClockwise() {
        std::swap(x(), y());
        y() *= -1;
        return *this;
    }
    Vector<T> rotatedClockwise() const { return {y(), -x()}; }

    // I/O stream operators.
    //
    // In the stream a vector is represented by
    // two space-separated numbers:
    // x and y coordinates respectively.
    friend std::istream& operator>>(std::istream& is, Vector<T>& v) {
        return is >> v.x() >> v.y();
    }
    friend std::ostream& operator<<(std::ostream& os, Vector<T> v) {
        return os << v.x() << ' ' << v.y();
    }

    // Iterator methods for range-based for loops over Vector.
    //
    // They are delegated to iterators over coords array.
    auto begin() { return coords.begin(); }
    auto begin() const { return coords.begin(); }
    auto end() { return coords.end(); }
    auto end() const { return coords.end(); }

   private:
    std::array<T, 2> coords;
};

// Squared euclidean distance between two points.
template <typename T>
T dist2(Point<T> A, Point<T> B) {
    return (B - A).len2();
}

// Euclidean distance between two points.
template <typename T>
Real dist(Point<T> A, Point<T> B) {
    return (B - A).len();
}

// Type alias for vectors with real coordinates.
using RVector = Vector<Real>;
using RPoint = RVector;

// Scales a vector so it has length 1.
void normalize(RVector& v) {
    Real l = v.len();
    v /= l;
}

// Returns the same vector, but scaled to length 1.
RVector normalized(RVector v) { return v / v.len(); }

// Type alias for vectors with integral coordinates.
using LVector = Vector<int64_t>;
using LPoint = LVector;

// Scales an integral vector down so it's coordinates
// are coprime.
//
// Out of two possible choices, the one
// where the first non-null coordinate is positive
// is returned.
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type normalize(
    Vector<T>& v) {
    auto g = std::gcd(v.x(), v.y());
    if (!g) return;
    if (v.x() < 0 || (v.x() == 0 && v.y() < 0)) g *= -1;
    v.x() /= g;
    v.y() /= g;
}
template <typename T>
typename std::enable_if<std::is_integral<T>::value, Vector<T>>::type normalized(
    Vector<T> v) {
    normalize(v);
    return v;
}

// Area of the triangle formed by two vectors.
template <typename T>
Real triangleArea(Vector<T> a, Vector<T> b) {
    return fabs(a % b) * 0.5l;
}

// Area of the triangle formed by three points.
template <typename T>
Real triangleArea(Point<T> A, Point<T> B, Point<T> C) {
    return triangleArea(Vector<T>(A, B), Vector<T>(A, C));
}

// A line formed by equation ax + by = c.
//
// We assume that in all initialized Line objects
// coefficients form a correct line equation,
// i.e. at least one of coefficients a, b
// is non-zero.
template <typename T>
class Line {
    Vector<T> normal;
    T constant;

   public:
    // Evaluate left-hand side ax + by
    // on a given Point.
    T eval(Point<T> P) const { return normal ^ P; }

    Line() = default;

    // Construct a line given all coefficients.
    Line(T a, T b, T c) : normal{a, b}, constant{c} {}

    // Construct a line by two points.
    Line(Point<T> A, Point<T> B)
        : normal{B.y() - A.y(), A.x() - B.x()}, constant{eval(A)} {}

    // Access to coefficients of the line equation.
    T& a() { return normal.x(); }
    T a() const { return normal.x(); }
    T& b() { return normal.y(); }
    T b() const { return normal.y(); }
    T& c() { return constant; }
    T c() const { return constant; }

    // Returns true iff the line contains given Point.
    bool contains(Point<T> P) const { return eval(P) == constant; }

    // Returns +1 or -1 depending on which half-plane
    // the given point lies in, or 0 is the point
    // lies in the line.
    int32_t relativePosition(Point<T> P) const {
        return sign(eval(P) - constant);
    }

    // I/O stream operators.
    //
    // In the stream a line is represented by
    // three space-separated numbers: the coefficients
    // of the line equation.
    //
    // TODO allow R/W in form ax + by + c = 0
    // using #ifdef.
    friend std::istream& operator>>(std::istream& is, Line& l) {
        return is >> l.normal >> l.constant;
    }
    friend std::ostream& operator<<(std::ostream& os, Line l) {
        return os << l.normal << ' ' << l.constant;
    }

    // Returns true iff lines are parallel.
    bool parallelTo(Line other) const {
        return normal.parallelTo(other.normal);
    }
};

// Type alias for lines with integral coefficients.
using LLine = Line<int64_t>;
// Type alias for lines with real coefficients.
using RLine = Line<Real>;
