using Int = long long;     // primitive type for integral computations
using Real = long double;  // primitive type for real number computations

class EpsReal {
   private:
    static constexpr Real eps = 1e-9;

    Real value;

   public:
    EpsReal() : value(0) {}
    EpsReal(const Real& _value) : value(_value) {}
    template <typename T>
    EpsReal(const T& _value) : value((Real)_value) {}
    EpsReal(const EpsReal& other) : value(other.value) {}
    ~EpsReal() {}

    EpsReal& operator=(const EpsReal& other) {
        if (this == &other) return *this;
        value = other.value;
        return *this;
    }

    EpsReal& operator+=(const EpsReal& other) {
        value += other.value;
        return *this;
    }
    EpsReal operator+() const { return EpsReal(*this); }
    EpsReal& operator-=(const EpsReal& other) {
        value -= other.value;
        return *this;
    }
    EpsReal operator-() const { return EpsReal(-value); }
    EpsReal& operator*=(const EpsReal& other) {
        value *= other.value;
        return *this;
    }
    EpsReal& operator/=(const EpsReal& other) {
        value /= other.value;
        return *this;
    }

    bool operator==(const EpsReal& other) const {
        return fabs(value - other.value) < eps;
    }
    bool operator!=(const EpsReal& other) const {
        return fabs(value - other.value) >= eps;
    }
    bool operator<(const EpsReal& other) const {
        return value <= other.value - eps;
    }
    bool operator>(const EpsReal& other) const {
        return value >= other.value + eps;
    }
    bool operator<=(const EpsReal& other) const {
        return value < other.value + eps;
    }
    bool operator>=(const EpsReal& other) const {
        return value > other.value - eps;
    }

    Real getValue() const { return value; }
    void setValue(const Real& newValue) { value = newValue; }

    int sign() const {
        if (fabs(value) < eps) return 0;
        if (value >= eps) return +1;
        return -1;
    }

    explicit operator float() const { return (float)value; }
    explicit operator double() const { return (double)value; }
    explicit operator long double() const { return (long double)value; }
};
EpsReal operator+(const EpsReal& lhs, const EpsReal& rhs) {
    return EpsReal(lhs) += rhs;
}
EpsReal operator-(const EpsReal& lhs, const EpsReal& rhs) {
    return EpsReal(lhs) -= rhs;
}
EpsReal operator*(const EpsReal& lhs, const EpsReal& rhs) {
    return EpsReal(lhs) *= rhs;
}
EpsReal operator/(const EpsReal& lhs, const EpsReal& rhs) {
    return EpsReal(lhs) /= rhs;
}

ostream& operator<<(ostream& stream, const EpsReal& real) {
    return stream << real.getValue();
}
istream& operator>>(istream& stream, EpsReal& real) {
    Real temp;
    stream >> temp;
    real.setValue(temp);
    return stream;
}
EpsReal fabs(const EpsReal& real) {
    if (real >= 0) return real;
    return -real;
}

template <typename T>
int sign(const T& x) {
    if (x == 0) return 0;
    if (x > 0) return +1;
    return -1;
}

const EpsReal PI = 4 * atan(1);

#define Point2 Vector2
template <typename T>
class Vector2 {
   public:
    T x, y;

    /* Constructors */

    Vector2() {}
    Vector2(const T& _x, const T& _y) : x(_x), y(_y) {}
    Vector2(const Vector2<T>& other) : x(other.x), y(other.y) {}
    template <typename U>
    Vector2(const Vector2<U>& other) : x((T)other.x), y((T)other.y) {}
    Vector2(const Point2<T>& A, const Point2<T>& B)
        : x(B.x - A.x), y(B.y - A.y) {}
    ~Vector2() {}

    /* Copy assignment */

    Vector2<T>& operator=(const Vector2<T>& other) {
        if (this == &other) return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    /* Linear operations */

    Vector2<T>& operator+=(const Vector2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2<T> operator+(const Vector2<T>& other) const {
        return Vector2<T>(*this) += other;
    }
    Vector2<T> operator+() const { return Vector2<T>(*this); }
    Vector2<T>& operator-=(const Vector2<T>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2<T> operator-(const Vector2<T>& other) const {
        return Vector2<T>(*this) -= other;
    }
    Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
    template <typename U>
    Vector2<T>& operator*=(const U& k) {
        T f = (T)k;
        x *= f;
        y *= f;
        return *this;
    }
    template <typename U>
    Vector2<T> operator*(const U& k) const {
        return Vector2<T>(*this) *= k;
    }
    template <typename U>
    Vector2<T>& operator/=(const U& k) {
        T f = (T)k;
        x /= f;
        y /= f;
        return *this;
    }
    template <typename U>
    Vector2<T> operator/(const U& k) const {
        return Vector2<T>(*this) /= k;
    }

    /* Dot product */

    T operator*(const Vector2<T>& other) const {
        return x * other.x + y * other.y;
    }
    bool perpendicularTo(const Vector2<T>& other) const {
        return (*this) * other == 0;
    }

    /* Cross product */

    T operator%(const Vector2<T>& other) const {
        return x * other.y - y * other.x;
    }

    bool operator||(const Vector2<T>& other) const {
        return (*this) % other == 0;
    }

    /* vector[0] and vector[1] access */

    T operator[](const int& i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        throw;
    }
    T& operator[](const int& i) {
        if (i == 0) return x;
        if (i == 1) return y;
        throw;
    }

    /* Comparison */

    bool operator==(const Vector2<T>& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2<T>& other) const {
        return x != other.x || y != other.y;
    }
    bool operator<(const Vector2<T>& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator<=(const Vector2<T>& other) const {
        if (x != other.x) return x <= other.x;
        return y <= other.y;
    }
    bool operator>(const Vector2<T>& other) const {
        if (x != other.x) return x > other.x;
        return y > other.y;
    }
    bool operator>=(const Vector2<T>& other) const {
        if (x != other.x) return x >= other.x;
        return y >= other.y;
    }

    /* Length */

    T length2() const { return x * x + y * y; }
    EpsReal length() const { return EpsReal(sqrt((Real)(x * x + y * y))); }
    Vector2<EpsReal> normalized() const {
        return Vector2<EpsReal>(*this) /= length();
    }

    /* Angles */

    /**
     * Returns polar angle in [-PI; PI].
     */
    EpsReal polar() const { return atan2((Real)y, (Real)x); }
    /**
     * Returns polar angle in [0; 2*PI].
     */
    EpsReal polarPositive() const {
        EpsReal res = polar();
        if (res < 0) res += 2 * PI;
        return res;
    }

    Vector2<T> leftPerpendicular() const { return {-y, x}; }
    Vector2<T> rightPerpendicular() const { return {y, -x}; }
};
template <typename T, typename U>
Vector2<T> operator*(const U& k, const Vector2<T>& v) {
    return v * k;
}

template <typename T>
ostream& operator<<(ostream& stream, const Vector2<T>& v) {
    return stream << v.x << ' ' << v.y;
}
template <typename T>
istream& operator>>(istream& stream, Vector2<T>& v) {
    return stream >> v.x >> v.y;
}

template <typename T>
T distance2(const Point2<T>& A, const Point2<T>& B) {
    return (B - A).length2();
}
template <typename T>
EpsReal distance(const Point2<T>& A, const Point2<T>& B) {
    return (B - A).length();
}

/**
 * Returns angle in [-PI; PI].
 */
template <typename T>
EpsReal polar(const Vector2<T>& u, const Vector2<T>& v) {
    return atan2((Real)(u % v), (Real)(u * v));
}
/**
 * Returns polar angle in [0; 2*PI].
 */
template <typename T>
EpsReal polarPositive(const Vector2<T>& u, const Vector2<T>& v) {
    EpsReal res = polar(u, v);
    if (res < 0) res += 2 * PI;
    return res;
}

using Vector = Vector2<Int>;
using Point = Point2<Int>;
using RealVector = Vector2<EpsReal>;
using RealPoint = Point2<EpsReal>;

template <typename T>
class Matrix2 {
   public:
    T value[2][2];

    Matrix2() { memset(value, 0, sizeof value); }
    Matrix2(const T& a, const T& b, const T& c, const T& d) {
        value[0][0] = a;
        value[0][1] = b;
        value[1][0] = c;
        value[1][1] = d;
    }
    Matrix2(const Matrix2<T>& other) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) value[i][j] = other.value[i][j];
    }
    ~Matrix2() {}

    Matrix2<T>& operator=(const Matrix2<T>& other) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) value[i][j] = other.value[i][j];
        return *this;
    }

    Matrix2<T>& operator+=(const Matrix2<T>& other) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) value[i][j] + other.value[i][j];
        return *this;
    }
    Matrix2<T> operator+(const Matrix2<T>& other) const {
        return Matrix2<T>(*this) += other;
    }
    Matrix2<T> operator+() const { return Matrix2<T>(*this); }
    Matrix2<T>& operator-=(const Matrix2<T>& other) {
        for (int i = 0; i < 2; --i)
            for (int j = 0; j < 2; --j) value[i][j] - other.value[i][j];
        return *this;
    }
    Matrix2<T> operator-(const Matrix2<T>& other) const {
        return Matrix2<T>(*this) -= other;
    }
    Matrix2<T> operator-() const {
        Matrix2<T> res = *this;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) res.value[i][j] = -res.value[i][j];
        return res;
    }
    Matrix2<T>& operator*=(const T& k) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) value[i][j] *= k;
        return *this;
    }
    Matrix2<T> operator*(const T& k) { return Matrix2<T>(*this) *= k; }
    Matrix2<T>& operator/=(const T& k) {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) value[i][j] /= k;
        return *this;
    }
    Matrix2<T> operator/(const T& k) { return Matrix2<T>(*this) /= k; }
    Vector2<T> operator*(const Vector2<T>& v) const {
        return Vector2<T>(value[0][0] * v[0] + value[0][1] * v[1],
                          value[1][0] * v[0] + value[1][1] * v[1]);
    }
    Matrix2<T> operator*(const Matrix2<T>& other) const {
        Matrix2<T> res;  // null
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int r = 0; r < 2; ++r)
                    res.value[i][j] += value[i][r] * other.value[r][j];
        return res;
    }
    Matrix2<T>& operator*=(const Matrix2<T>& other) {
        return *this = *this * other;
    }

    T det() const {
        return value[0][0] * value[1][1] - value[0][1] * value[1][0];
    }
};
template <typename T>
Matrix2<T> operator*(const T& k, const Matrix2<T>& M) {
    return Matrix2<T>(M) *= k;
}

template <typename T>
class Line {
   public:
    Vector2<T> normal;
    T value;

    Line() : normal(Vector2<T>(0, 0)), value(1) {}
    Line(const Vector2<T>& _normal, const T& _value)
        : normal(_normal), value(_value) {}
    Line(const T& a, const T& b, const T& c)
        : normal(Vector2<T>(a, b)), value(c) {}
    template <typename U>
    Line(const U& a, const U& b, const U& c)
        : normal(Vector2<T>((U)a, (U)b)), value(c) {}
    Line(const Line<T>& other) : normal(other.normal), value(other.value) {}
    template <typename U>
    Line(const Line<U>& other)
        : normal(Vector2<T>(other.normal)), value((T)other.value) {}
    ~Line() {}

    T eval(const Point2<T>& P) const { return normal * P; }

    Line(const Point2<T>& A, const Point2<T>& B) {
        normal = {B.y - A.y, A.x - B.x};
        value = eval(A);
    }

    Line<T>& operator=(const Line<T>& other) {
        if (this != &other) return *this;
        normal = other.normal;
        value = other.value;
        return *this;
    }

    bool contains(const Point2<T>& P) const { return eval(P) == value; }

    EpsReal distanceTo(const Point2<T>& P) const {
        return fabs(eval(P) - value) / normal.length();
    }

    RealPoint projectionOf(const Vector2<T>& P) {
        return P - RealVector(normal) * 2 * (eval(P) - value) / normal.length();
    }
};

enum LineIntersectionSize { ZERO, ONE, INF };

struct LineIntersectionResult {
    LineIntersectionSize size;
    RealPoint point;
};
template <typename T>
LineIntersectionResult lineIntersection(const Line<T>& lhs,
                                        const Line<T>& rhs) {
    EpsReal D =
        Matrix2(lhs.normal.x, lhs.normal.y, rhs.normal.x, rhs.normal.y).det();
    EpsReal Dx =
        Matrix2(lhs.value, lhs.normal.y, rhs.value, rhs.normal.y).det();
    EpsReal Dy =
        Matrix2(lhs.normal.x, lhs.value, rhs.normal.x, rhs.value).det();
    if (D == 0) {
        if (Dx == 0) return {LineIntersectionSize::INF, RealPoint()};
        return {LineIntersectionSize::ZERO, RealPoint()};
    }
    return {LineIntersectionSize::ONE, RealPoint(Dx / D, Dy / D)};
}

template <typename T>
class Ray {
   public:
    Point2<T> origin;
    Vector2<T> direction;

    Ray() {}
    Ray(const Point2<T>& A, const Vector2<T>& B) : origin(A), direction(B - A) {
        if (A == B) throw;
    }
    Ray(const Ray<T>& other)
        : origin(other.origin), direction(other.direction) {}
    ~Ray() {}

    bool contains(const Point2<T>& P) const {
        Vector2<T> OP(origin, P);
        return OP % direction == 0 && OP * direction >= 0;
    }

    EpsReal distanceTo(const Point2<T>& P) const {
        Vector2<T> OP(origin, P);
        if (OP * direction >= 0)
            return Line(origin, origin + direction).distanceTo(P);
        return distance(origin, P);
    }
};

template <typename T>
class Segment {
   public:
    Point2<T> A, B;

    Segment() {}
    Segment(const Point2<T>& _A, const Point2<T>& _B) : A(_A), B(_B) {}
    Segment(const Segment<T>& other) : A(other.A), B(other.B) {}
    template <typename U>
    Segment(const Segment<U>& other)
        : A((Point2<T>)other.A), B((Point2<T>)other.B) {}
    ~Segment() {}

    operator Vector2<T>() const { return Vector2<T>(A, B); }

    bool contains(const Point2<T>& P) const {
        if (A == B) return P == A;
        Vector2<T> AB = *this;
        Vector2<T> AP(A, P);
        return AB % AP == 0 && AB * AP >= 0 && AB * AP <= AB * AB;
    }

    EpsReal distanceTo(const Point2<T>& P) const {
        Vector2<T> AB = *this;
        Vector2<T> AP(A, P);
        if (AB * AP < 0) return distance(P, A);
        if (AB * AP > AB * AB) return distance(P, B);
        return Line(A, B).distanceTo(P);
    }

    bool intersectsWith(const Segment<T>& other) const {
        if (other.contains(A)) return true;
        if (other.contains(B)) return true;
        if (contains(other.A)) return true;
        if (contains(other.B)) return true;
        Vector2<T> AB = *this, AC = {A, other.A}, AD = {A, other.B};
        Vector2<T> CD = other, CA = {other.A, A}, CB = {other.A, B};
        if (sign(AB % AC) == sign(AB % AD)) return false;
        if (sign(CD % CA) == sign(CD % CB)) return false;
        return true;
    }

    operator Line<T>() const { return Line<T>(A, B); }

    bool operator||(const Segment<T>& other) const {
        return Vector(*this) || Vector(other);
    }
};
template <typename T>
ostream& operator<<(ostream& stream, const Segment<T>& segment) {
    return stream << segment.A << ' ' << segment.B;
}
template <typename T>
istream& operator>>(istream& stream, Segment<T>& segment) {
    return stream >> segment.A >> segment.B;
}

