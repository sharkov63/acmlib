const long double PI = 4 * atan(1);

#define Point2 Vector2
template<typename T>
class Vector2 {
public:

    T x, y;


    /* Constructors */

    Vector2() {}                                                              
    Vector2(const T& _x, const T& _y): x(_x), y(_y) {}                         
    Vector2(const Vector2<T>& other): x(other.x), y(other.y) {}                    
    template<typename U> Vector2(const Vector2<U>& other): x((T)other.x), y((T)other.y) {}                    
    Vector2(const Point2<T>& A, const Point2<T>& B): x(B.x - A.x), y(B.y - A.y) {}     
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
    Vector2<T> operator+() const {
        return Vector2<T>(*this);
    }
    Vector2<T>& operator-=(const Vector2<T>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2<T> operator-(const Vector2<T>& other) const {
        return Vector2<T>(*this) -= other;
    }
    Vector2<T> operator-() const {
        return Vector2<T>(-x, -y);
    }
    template<typename U> Vector2<T>& operator*=(const U& k) {
        T f = (T)k;
        x *= f;
        y *= f;
        return *this;
    }
    template<typename U> Vector2<T> operator*(const U& k) const {
        return Vector2<T>(*this) *= k;
    }
    template<typename U> Vector2<T>& operator/=(const U& k) {
        T f = (T)k;
        x /= f;
        y /= f;
        return *this;
    }
    template<typename U> Vector2<T> operator/(const U& k) const {
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

    /* vector[0] and vector[1] access */

    T operator[](const int& i) const {
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        throw;
    }
    T& operator[](const int& i) {
        if (i == 0)
            return x;
        if (i == 1)
            return y;
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
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator<=(const Vector2<T>& other) const {
        if (x != other.x)
            return x <= other.x;
        return y <= other.y;
    }
    bool operator>(const Vector2<T>& other) const {
        if (x != other.x)
            return x > other.x;
        return y > other.y;
    }
    bool operator>=(const Vector2<T>& other) const {
        if (x != other.x)
            return x >= other.x;
        return y >= other.y;
    }
    

    /* Length */

    T length2() const {
        return x * x + y * y;
    }
    long double length() const {
        long double cx = (long double)x;
        long double cy = (long double)y;
        return sqrt(cx * cx + cy * cy);
    }
    template<typename R> Vector2<R> normalized() const {
        return Vector2<R>(*this) /= length();
    }
    void normalize() {
        (*this) /= length();
    }

    
    /* Angles */

    /**
     * Returns angle in [-PI; PI].
     */
    long double polar() const {
        return atan2((long double)y, (long double)x);
    }
};
template<typename T, typename U> Vector2<T> operator*(const U& k, const Vector2<T>& v) {
    return v * k;
}

template<typename T> ostream& operator<<(ostream& stream, const Vector2<T>& v) {
    return stream << v.x << ' ' << v.y;
}
template<typename T> istream& operator>>(istream& stream, Vector2<T>& v) {
    return stream >> v.x >> v.y;
}

template<typename T> T distance2(const Point2<T>& A, const Point2<T>& B) {
    return (B - A).length2();
}
template<typename T> long double distance(const Point2<T>& A, const Point2<T>& B) {
    return (B - A).length();
}

/**
 * Returns angle in [-PI; PI].
 */
template<typename T> long double polar(const Vector2<T>& u, const Vector2<T>& v) {
    return atan2((long double)(u % v), (long double)(u * v));
}



template<typename R>
class EpsReal {
private:
    static constexpr R eps = 1e-9;

    R value;

public:

    EpsReal(): value(0) {}
    EpsReal(const R& _value): value(_value) {}
    template<typename S> EpsReal(const S& _value): value((R)_value) {}
    EpsReal(const EpsReal<R>& other): value(other.value) {}
    template<typename S> EpsReal(const EpsReal<S>& other): value((R)other.value) {}

    EpsReal<R>& operator=(const EpsReal<R>& other) {
        if (this == &other) return *this;
        value = other.value;
        return *this;
    }

    EpsReal<R>& operator+=(const EpsReal<R>& other) {
        value += other.value;
        return *this;
    }
    EpsReal<R> operator+(const EpsReal<R>& other) const {
        return EpsReal<R>(*this) += other;
    }
    EpsReal<R> operator+() const {
        return EpsReal<R>(*this);
    }
    EpsReal<R>& operator-=(const EpsReal<R>& other) {
        value -= other.value;
        return *this;
    }
    EpsReal<R> operator-(const EpsReal<R>& other) const {
        return EpsReal<R>(*this) -= other;
    }
    EpsReal<R> operator-() const {
        return EpsReal<R>(-value);
    }
    EpsReal<R>& operator*=(const EpsReal<R>& other) {
        value *= other.value;
        return *this;
    }
    EpsReal<R> operator*(const EpsReal<R>& other) const {
        return EpsReal<R>(*this) *= other;
    }
    EpsReal<R>& operator/=(const EpsReal<R>& other) {
        value /= other.value;
        return *this;
    }
    EpsReal<R> operator/(const EpsReal<R>& other) const {
        return EpsReal<R>(*this) /= other;
    }

    bool operator==(const EpsReal<R>& other) const {
        return fabs(value - other.value) < eps;
    }
    bool operator!=(const EpsReal<R>& other) const {
        return fabs(value - other.value) >= eps;
    }
    bool operator<(const EpsReal<R>& other) const {
        return value <= other.value - eps;
    }
    bool operator>(const EpsReal<R>& other) const {
        return value >= other.value + eps;
    }
    bool operator<=(const EpsReal<R>& other) const {
        return value < other.value + eps;
    }
    bool operator>=(const EpsReal<R>& other) const {
        return value > other.value - eps;
    }

    R getValue() const {
        return value; 
    }
    void setValue(const R& newValue) {
        value = newValue;
    }

    operator float() const {
        return (float)value;
    }
    operator double() const {
        return (double)value;
    }
    operator long double() const {
        return (long double)value;
    }

    int sign() const {
        if (fabs(value) < eps)
            return 0;
        if (value >= eps)
            return +1;
        return -1;
    }
};
template<typename R> ostream& operator<<(ostream& stream, const EpsReal<R>& real) {
    return stream << real.getValue();
}
template<typename R> istream& operator>>(istream& stream, EpsReal<R>& real) {
    R temp;
    stream >> temp;
    real.setValue(temp);
    return stream;
}

typedef EpsReal<float> EpsFloat;
typedef EpsReal<double> EpsDouble;
typedef EpsReal<long double> EpsLongDouble;

typedef Vector2<long long> Vector;
typedef Point2<long long> Point;
typedef Vector2<EpsFloat> FVector;
typedef Vector2<EpsDouble> DVector;
typedef Vector2<EpsLongDouble> LDVector;
