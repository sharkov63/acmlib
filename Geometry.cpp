
#define Point Vector
struct Vector {
    ll x, y;

    Vector(ll _x = 0, ll _y = 0): x(_x), y(_y) {} // create by coordinates (default (0, 0))
    Vector(const Vector& oth): x(oth.x), y(oth.y) {} // clone vector
    Vector(const Point& A, const Point& B): x(B.x - A.x), y(B.y - A.y) {} // create by two endpoints

    // addition
    inline Vector& operator += (const Vector& oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    // subtraction
    Vector& operator -= (const Vector& oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    // multiplication by a scalar
    Vector& operator *= (ll k) {
        x *= k;
        y *= k;
        return *this;
    }

    // opposite vector
    Vector operator - () const {
        return Vector(-x, -y);
    }

    // dot product
    ll operator * (const Vector& oth) const {
        return x * oth.x + y * oth.y;
    }

    // cross product
    ll operator % (const Vector& oth) const {
        return x * oth.y - y * oth.x;
    }

    // length squared
    ll len2() {
        return x * x + y * y;
    }

    ld len() {
        return sqrt(x * x + y * y);
    }

    bool operator == (const Vector& oth) const {
        return x == oth.x && y == oth.y;
    }

    bool operator != (const Vector& oth) const {
        return x != oth.x || y != oth.y;
    }

    bool parallel_to(const Vector& oth) const {
        return (*this) % oth == 0;
    }
};
Vector operator + (const Vector& lhs, const Vector& rhs) { return Vector(lhs) += rhs; }
Vector operator - (const Vector& lhs, const Vector& rhs) { return Vector(lhs) -= rhs; }
Vector operator * (const Vector& lhs, ll rhs) { return Vector(lhs) *= rhs; }
Vector operator * (ll lhs, const Vector& rhs) { return Vector(rhs) *= lhs; }
ostream& operator << (ostream& stream, const Vector& v) {
    return stream << v.x << ' ' << v.y;
}
istream& operator >> (istream& stream, Vector& v) {
    return stream >> v.x >> v.y;
}

ld cos_vec_angle(Vector a, Vector b) {
    return a * b / a.len() / b.len();
}

ld sin_vec_angle(Vector a, Vector b) {
    return a % b / a.len() / b.len();
}

