
#define Point Vector
struct Vector {
    ll x, y;

    Vector(ll _x = 0, ll _y = 0): x(_x), y(_y) {} // create by coordinates (default (0, 0))
    Vector(const Vector& oth): x(oth.x), y(oth.y) {} // clone vector
    Vector(const Point& A, const Point& B): x(B.x - A.x), y(B.y - A.y) {} // create by two endpoints

    // addition
    inline Vector& operator+=(const Vector& oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    // subtraction
    Vector& operator-=(const Vector& oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    // multiplication by a scalar
    Vector& operator*=(ll k) {
        x *= k;
        y *= k;
        return *this;
    }

    // division by a scalar
    Vector& operator/=(ll k) {
        x /= k;
        y /= k;
        return *this;
    }

    // opposite vector
    Vector operator-() const {
        return Vector(-x, -y);
    }

    // dot product
    ll operator*(const Vector& oth) const {
        return x * oth.x + y * oth.y;
    }

    // cross product
    ll operator%(const Vector& oth) const {
        return x * oth.y - y * oth.x;
    }

    // length squared
    ll len2() {
        return x * x + y * y;
    }

    ld len() {
        return sqrt(x * x + y * y);
    }

    bool operator==(const Vector& oth) const {
        return x == oth.x && y == oth.y;
    }

    bool operator!=(const Vector& oth) const {
        return x != oth.x || y != oth.y;
    }

    bool operator<(const Vector& oth) const {
        return x < oth.x || (x == oth.x && y < oth.y);
    }

    bool parallel_to(const Vector& oth) const {
        return (*this) % oth == 0;
    }
};
Vector operator+(const Vector& lhs, const Vector& rhs) { return Vector(lhs) += rhs; }
Vector operator-(const Vector& lhs, const Vector& rhs) { return Vector(lhs) -= rhs; }
Vector operator*(const Vector& lhs, ll rhs) { return Vector(lhs) *= rhs; }
Vector operator*(ll lhs, const Vector& rhs) { return Vector(rhs) *= lhs; }
Vector operator/(const Vector& lhs, ll rhs) { return Vector(lhs) /= rhs; }
ostream& operator<<(ostream& stream, const Vector& v) {
    return stream << v.x << ' ' << v.y;
}
istream& operator>>(istream& stream, Vector& v) {
    return stream >> v.x >> v.y;
}

// double geometry

const double eps = 1e-9;

#define DPoint DVector
struct DVector {
    ld x, y;

    DVector(ld _x = 0, ld _y = 0): x(_x), y(_y) {} // create by coordinates (default (0, 0))
    DVector(const DVector& oth): x(oth.x), y(oth.y) {} // clone vector
    DVector(const Vector& oth): x(oth.x), y(oth.y) {}  // clone integer vector
    DVector(const DPoint& A, const DPoint& B): x(B.x - A.x), y(B.y - A.y) {} // create by two endpoints

    // addition
    inline DVector& operator+=(const DVector& oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    // subtraction
    DVector& operator-=(const DVector& oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    // multiplication by a scalar
    DVector& operator*=(ld k) {
        x *= k;
        y *= k;
        return *this;
    }

    // division by a scalar
    DVector& operator/=(ld k) {
        x /= k;
        y /= k;
        return *this;
    }

    // opposite vector
    DVector operator-() const {
        return DVector(-x, -y);
    }

    // dot product
    ld operator*(const DVector& oth) const {
        return x * oth.x + y * oth.y;
    }

    // cross product
    ld operator%(const DVector& oth) const {
        return x * oth.y - y * oth.x;
    }

    // length squared
    ld len2() {
        return x * x + y * y;
    }

    ld len() {
        return sqrt(x * x + y * y);
    }

    bool operator==(const DVector& oth) const {
        return fabs(x - oth.x) < eps && fabs(y - oth.y) < eps;
    }

    bool operator!=(const DVector& oth) const {
        return fabs(x - oth.x) >= eps || fabs(y - oth.y) > eps;
    }

    bool parallel_to(const DVector& oth) const {
        return fabs((*this) % oth) < eps;
    }
};
DVector operator+(const DVector& lhs, const DVector& rhs) { return DVector(lhs) += rhs; }
DVector operator-(const DVector& lhs, const DVector& rhs) { return DVector(lhs) -= rhs; }
DVector operator*(const DVector& lhs, ld rhs) { return DVector(lhs) *= rhs; }
DVector operator*(ld lhs, const DVector& rhs) { return DVector(rhs) *= lhs; }
DVector operator/(const DVector& lhs, ld rhs) { return DVector(lhs) /= rhs; }
ostream& operator<<(ostream& stream, const DVector& v) {
    return stream << v.x << ' ' << v.y;
}
istream& operator>>(istream& stream, DVector& v) {
    return stream >> v.x >> v.y;
}
