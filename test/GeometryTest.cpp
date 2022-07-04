#include <array>
#include <limits>
#include <memory>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#define private public
#include "Geometry.cpp"
#undef private
#include "doctest.h"

using doctest::Approx;

TEST_SUITE("Geometry::Real") {
    constexpr const double doubleEpsilon =
        std::numeric_limits<double>::epsilon();

    TEST_CASE("Construction/assignment/conversion") {
        Real emptyConstructed;
        CHECK((long double)emptyConstructed == Approx(0));

        Real constructedFromInt(-38);
        CHECK((long double)constructedFromInt == Approx(-38));

        Real constructedFromUInt(13'333u);
        CHECK((long double)constructedFromUInt == Approx(13'333u));

        Real constructedFromLongLong(-2'003'000'010'000'000'079ll);
        CHECK((long double)constructedFromLongLong ==
              Approx(-2'003'000'010'000'000'079ll));

        Real constructedFromULongLong(10'000'000'000'000'003'009ull);
        CHECK((long double)constructedFromULongLong ==
              Approx(10'000'000'000'000'003'009ull));

        Real constructedFromFloat(0.45f);
        CHECK((long double)constructedFromFloat == Approx(0.45f));

        Real constructedFromDouble(-8e6);
        CHECK((long double)constructedFromDouble == Approx(-8e6));

        Real constructedFromLongDouble(7e20l);
        CHECK((long double)constructedFromLongDouble == Approx(7e20l));

        Real constructedEqualsSignInt = 1;
        CHECK((long double)constructedEqualsSignInt == Approx(1));

        Real constructedEqualsSign = -5e-10l;
        CHECK((long double)constructedEqualsSign == Approx(-5e-10l));

        Real initial = 1.8;
        Real constructedByCopy(initial);
        CHECK((long double)constructedByCopy == Approx(1.8));
        Real constructedByCopyEquals = initial;
        CHECK((long double)constructedByCopyEquals == Approx(1.8));
        Real constructedByMove(std::move(initial));
        CHECK((long double)constructedByMove == Approx(1.8));

        Real assignedToInt;
        assignedToInt = 45;
        CHECK((long double)assignedToInt == Approx(45));

        Real assignedToDouble;
        assignedToDouble = -4.4444444;
        CHECK((long double)assignedToDouble == Approx(-4.4444444));

        Real assignedToAnotherReal = 1e11;
        assignedToAnotherReal = emptyConstructed;
        CHECK((long double)assignedToAnotherReal == Approx(0));

        Real initial2 = 3;
        Real moveAssignment;
        moveAssignment = std::move(initial2);
        CHECK(moveAssignment == 3);

        Real convertedToFloat(9.45f);
        CHECK((float)convertedToFloat == Approx(9.45f));

        Real convertedToDouble(-44445.124);
        CHECK((double)convertedToDouble == Approx(-44445.124));

        Real convertedToLongDouble(3e3 + 7);
        CHECK((long double)convertedToLongDouble == Approx(3007));

        Real multiple1 = 1, multiple2 = 2, multiple3 = 3;
        multiple1 = multiple2 = multiple3 = 19;
        CHECK(multiple1 == 19);
        CHECK(multiple2 == 19);
        CHECK(multiple3 == 19);
    }

    TEST_CASE("General comparison") {
        CHECK(Real(11) == Real(11.0));
        CHECK(99.0f == Real(100 - 1));
        Real x = 77;
        CHECK(x == 77.0l);
        x = -1337;
        Real y = x;
        CHECK(x == y);
        CHECK_FALSE(Real(-199) == -200);
        CHECK_FALSE(y == -1337 + 99);

        CHECK(Real(0) != Real(0.101f));
        CHECK_FALSE(10 != Real(10.0f));
        CHECK_FALSE(y != x);

        CHECK(Real(5.5) < Real(5.6));
        CHECK(98 < Real(198));
        CHECK(Real(-1e10) < 1e-10);
        CHECK_FALSE(Real(9e9) < Real(-3e20));

        CHECK(Real(1) > Real(-1));
        CHECK(Real(0) > -0.001f);
        CHECK(1e7 > Real(1e-7));
        CHECK_FALSE(Real(8) > Real(256));

        CHECK(Real(8) <= Real(8.5));
        CHECK(Real(8) <= Real(8));
        CHECK(Real(10.1) <= 10.2);
        CHECK(8.01 <= Real(8.10f));
        CHECK_FALSE(Real(1) <= Real(0));

        CHECK(Real(10) >= Real(9));
    }

    TEST_CASE("Eps comparison") {
        CHECK(Real(10) == Real(10 + 1e-20));
        CHECK(Real(0) == Real(10 * doubleEpsilon));
        CHECK(Real(10) != Real(10 + 1e-7));
        CHECK_FALSE(Real(-8) < Real(-8 + 1e-10));
        CHECK(Real(7) <= Real(7 + 1e-10));
        CHECK(Real(doubleEpsilon) == 0);
        CHECK(Real(-doubleEpsilon) == 0);
    }

    TEST_CASE("istream operator") {
        std::vector<long double> values{89,      -1,   3.05, 0.79,
                                        -150.01, 1e11, 3e3,  2e-9};
        std::istringstream is("89 -1 3.05 .79 -150.01 1e11 3e+3 2E-9");
        for (auto value : values) {
            Real x;
            is >> x;
            CHECK(x == value);
        }
    }

    TEST_CASE("ostream operator") {
        std::vector<Real> values{0, 12, -37, 0.1, 1e7};
        std::vector<std::string> answers{"0", "12", "-37", "0.1", "1e+07"};
        for (size_t i = 0; i < values.size(); ++i) {
            std::ostringstream os;
            os << values[i];
            CHECK(os.str() == answers[i]);
        }
    }

    TEST_CASE("Arithmetic") {
        CHECK(Real(0.1) + Real(0.2) == Real(0.3));
        CHECK(Real(-9.8) + Real(6.66) == -3.14);
        CHECK(Real(0.001) + 103 == 103.001);
        CHECK(1e10 + Real(11) == 10000000011.0);
        Real plusEquals = 97;
        plusEquals += 3;
        CHECK(plusEquals == 100);
        plusEquals += 0.7;
        CHECK(plusEquals == 100.7);
        plusEquals += 1.0f;
        CHECK(plusEquals == 101.7);
        plusEquals += 0.1l;
        CHECK(plusEquals == 101.8);
        plusEquals += Real(0.2);
        CHECK(plusEquals == 102);
        Real increment = 8.3;
        CHECK(++increment == 9.3);
        CHECK(increment == 9.3);
        CHECK(increment++ == 9.3);
        CHECK(increment == 10.3);
        ++increment;
        CHECK(increment == 11.3);
        increment++;
        CHECK(increment == 12.3);
        CHECK(+Real(8) == 8);
        CHECK(+Real(-0.9) == -0.9);

        CHECK(Real(1e10) - Real(1e10 + doubleEpsilon) == Real(0));
        CHECK(Real(16) - Real(16.0000000000000001l) == 0);
        CHECK(7 - Real(9.9) == -2.9);
        CHECK(Real(13.5) - 0.6 == 12.9);
        Real minusEquals = 0.1;
        minusEquals -= 39;
        CHECK(minusEquals == -38.9);
        minusEquals -= (-40);
        CHECK(minusEquals == 1.1);
        minusEquals -= 1.0f;
        CHECK(minusEquals == 0.1);
        minusEquals -= 0.8;
        CHECK(minusEquals == -0.7);
        minusEquals -= 0.91l;
        CHECK(minusEquals == -1.61);
        minusEquals -= Real(0.09);
        CHECK(minusEquals == -1.7);
        Real decrement = 0.98;
        CHECK(--decrement == -0.02);
        CHECK(decrement == -0.02);
        CHECK(decrement-- == -0.02);
        CHECK(decrement == -1.02);
        --decrement;
        CHECK(decrement == -2.02);
        decrement--;
        CHECK(decrement == -3.02);
        CHECK(-Real(11) == -11);
        CHECK(-Real(-12.7) == 12.7);

        CHECK(Real(2) * Real(-3.09) == Real(-6.18));
        CHECK(Real(11.07) * Real(0.0009) == 0.009963);
        CHECK(Real(0.1) * 9 == 0.9);
        CHECK(1.5 * Real(4.6666666666666666666666) == 7);
        CHECK(0 * Real(1e30) == 0);
        Real mulEquals = 1;
        mulEquals *= 3;
        CHECK(mulEquals == 3);
        mulEquals *= 0.3333333333;
        CHECK(mulEquals == 1);

        CHECK(Real(1) / Real(30) == Real(0.0333333333333333));
        CHECK(Real(3.5) / Real(0.5) == 7);
        CHECK(1 / Real(11) == 0.09090909090909090909);
        CHECK(Real(16) / 4 == 4);
        CHECK(0 / Real(1e12) == 0);
        Real divEquals = 30;
        divEquals /= 15;
        CHECK(divEquals == 2);
        divEquals /= 0.2;
        CHECK(divEquals == 10);
    }

    TEST_CASE("Substitution into std functions") {
        Real x = 16;
        CHECK(sqrt(x) == 4);
        CHECK(sqrt(Real(9)) == 3.0000000000001l);
        CHECK(sqrt(Real(889)) == sqrt(889) + doubleEpsilon);
        CHECK(cos(Real(4 * std::atan(1))) == -1);
    }

    TEST_CASE("sign") {
        CHECK(sign(11) == 1);
        CHECK(sign(-3) == -1);
        CHECK(sign(0) == 0);
        CHECK(sign(doubleEpsilon) == 1);
        CHECK(sign(-doubleEpsilon) == -1);
        CHECK(sign(0.1) == 1);
        CHECK(sign(-0.2f) == -1);
        CHECK(sign(0.0003l) == 1);
        CHECK(sign(Real(1.5)) == 1);
        CHECK(sign(Real(-0.0)) == 0);
        CHECK(sign(Real(-doubleEpsilon)) == 0);
    }

    TEST_CASE("Conversion to primitive types") {
        Real a = 89.1;
        CHECK((long long)a == 89);
        CHECK((long)a == 89);
        CHECK((int)a == 89);
        CHECK((float)a == Approx(89.1));
        CHECK((double)a == Approx(89.1));
        CHECK((long double)a == Approx(89.1));
    }
}

TEST_SUITE("Geometry::Vector2") {
    TEST_CASE("Minimal sizeof") {
#define CHECK_SIZEOF(T) CHECK(sizeof(Vector2<T>) == 2 * sizeof(T))
        CHECK_SIZEOF(int8_t);
        CHECK_SIZEOF(int16_t);
        CHECK_SIZEOF(int32_t);
        CHECK_SIZEOF(int64_t);
        CHECK_SIZEOF(__int128);
        CHECK_SIZEOF(float);
        CHECK_SIZEOF(double);
        CHECK_SIZEOF(long double);
        CHECK_SIZEOF(Real);
#undef CHECK_CHECK_SIZEOF
    }

    TEST_CASE("Empty constructor") {
        Vector2<int32_t> v;
        CHECK(v.coords[0] == 0);
        CHECK(v.coords[1] == 0);
    }

    TEST_CASE("One parameter constructor") {
        Vector2<int32_t> a(1);
        CHECK(a.coords[0] == 1);
        CHECK(a.coords[1] == 0);
        RVector b{-3};
        CHECK(b.coords[0] == -3);
        CHECK(b.coords[1] == 0);
        Vector2<float> c({12});
        CHECK(c.coords[0] == Approx(12));
        CHECK(c.coords[1] == Approx(0));
        Vector2<double> d = {-0.2};
        CHECK(d.coords[0] == Approx(-0.2));
        CHECK(d.coords[1] == Approx(0));
        RVector e = -11.1;
        CHECK(e.coords[0] == -11.1);
        CHECK(e.coords[1] == 0);
    }

    TEST_CASE("Two parameter constructor") {
        Vector a(1, 2);
        CHECK(a.coords[0] == 1);
        CHECK(a.coords[1] == 2);
        RVector b(-1, 0.5);
        CHECK(b.coords[0] == -1);
        CHECK(b.coords[1] == 0.5);
        Vector2<float> c{12, 12.01};
        CHECK(c.coords[0] == Approx(12));
        CHECK(c.coords[1] == Approx(12.01));
        Vector2<long double> d({3, -31.1});
        CHECK(d.coords[0] == Approx(3));
        CHECK(d.coords[1] == Approx(-31.1));
        Vector e = {1, 100000};
        CHECK(e.coords[0] == 1);
        CHECK(e.coords[1] == 100000);
        std::vector<RVector> ff{{1, 5}, {-0.1, 0.03}, {8, 33.1}};
        CHECK(ff[0].coords[0] == 1);
        CHECK(ff[0].coords[1] == 5);
        CHECK(ff[1].coords[0] == -0.1);
        CHECK(ff[1].coords[1] == 0.03);
        CHECK(ff[2].coords[0] == 8);
        CHECK(ff[2].coords[1] == 33.1);
    }

    TEST_CASE("Copy constructor") {
        Vector a(1, 2);
        Vector b(a);
        CHECK(b.coords[0] == 1);
        CHECK(b.coords[1] == 2);
        Vector c = b;
        CHECK(c.coords[0] == 1);
        CHECK(c.coords[1] == 2);
    }

    TEST_CASE("Copy assignment") {
        RVector a;
        RVector b(0.1, 3);
        a = b;
        CHECK(a.coords[0] == 0.1);
        CHECK(a.coords[1] == 3);
    }

    TEST_CASE("xy member access") {
        Vector v{3, 4};
        CHECK(v.x() == 3);
        CHECK(v.y() == 4);
        v.x() = 9;
        v.y() = 2 * v.x();
        CHECK(v.x() == 9);
        CHECK(v.y() == 18);
        std::swap(v.x(), v.y());
        CHECK(v.x() == 18);
        CHECK(v.y() == 9);
    }

    TEST_CASE("Indexing operator") {
        Vector2<double> a(-11, 0.1);
        CHECK(a[0] == -11);
        CHECK(a[1] == 0.1);
    }

    TEST_CASE("Conversion between different coordinate types") {
        Vector a{-1, 1337};
        Vector2<float> b(a);
        CHECK(b.x() == Approx(-1));
        CHECK(b.y() == Approx(1337));
        Vector2<double> c{a};
        CHECK(c.x() == Approx(-1));
        CHECK(c.y() == Approx(1337));
        RVector d = a;
        CHECK(d.x() == -1);
        CHECK(d.y() == 1337);
        RVector p{-0.1, 37.3};
        Vector q;
        q = p;
        CHECK(q.x() == 0);
        CHECK(q.y() == 37);
    }

    TEST_CASE("Construct from two endpoints") {
        Point A{-9, 6};
        Point B{3, 7};
        Vector v(A, B);
        CHECK(v.x() == 12);
        CHECK(v.y() == 1);

        RPoint P{1.2, -0.2};
        RPoint Q{1.2, 0.1};
        RVector u{P, Q};
        CHECK(u.x() == 0);
        CHECK(u.y() == 0.3);
    }

    TEST_CASE("Comparison") {
        CHECK(Vector(3, 0) == 3);
        CHECK(RVector(1e-12, 34.1) == Vector2<Real>(0, 34.1));
        CHECK(Vector2<float>(4.5, 3.0003) != Vector2<float>(4.5, 3));
        CHECK(Vector(1, 2) < Vector(3, -100000));
        CHECK(RVector(0.1) <= Vector2<Real>(0.1, 0.1));
        CHECK(Vector(4, -1) >= Vector(4, -1));
        CHECK_FALSE(Vector(3, 0) < Vector(3, -1));
    }

    TEST_CASE("Vector addition") {
        CHECK(Vector(1, -1) + Vector(2, 3) == Vector(3, 2));
        CHECK(RVector(99.1, 5) + 10 == Vector2<Real>(109.1, 5));
        Vector a{4, 1};
        CHECK(a + Vector(-4, -1) == 0);
        CHECK(a == Vector(4, 1));
        a += {3, -2};
        CHECK(a == Vector(7, -1));
    }

    TEST_CASE("Vector subtraction") {
        CHECK(RVector(0.1, -30) - Vector2<Real>(0.7, -31) == RVector(-0.6, 1));
        CHECK(RVector(1.3) - 0.3 == 1);
        Vector b{-10, -9};
        CHECK(b - Vector(-10, -8) == Vector(0, -1));
        CHECK(b == Vector(-10, -9));
        b -= {5, 6};
        CHECK(b == Vector(-15, -15));
        b -= -16;
        CHECK(b == Vector(1, -15));
    }

    TEST_CASE("Multiplication by scalar") {
        CHECK(Vector(1, -2) * 3 == Vector(3, -6));
        CHECK(Vector(77, 98) * 0 == 0);
        CHECK(10 * RVector(0.1, 3e-6) == Vector2<Real>(1, 3e-5));
        Vector a{1, -1};
        a *= 2;
        CHECK(a == Vector(2, -2));
        a *= -1;
        CHECK(a == Vector(-2, 2));
    }

    TEST_CASE("Unary operators") {
        CHECK(+Vector(3, 1) == Vector(3, 1));
        RVector a = 4;
        CHECK(+(+a) == 4.0);
        CHECK(-a == -4);
        CHECK(-Vector(10, 12) == Vector(-10, -12));
    }

    TEST_CASE("Dot product") {
        CHECK((Vector(4, -2) ^ Vector(1, 1)) == 2);
        CHECK((Vector(6, 7) ^ Vector(1, -1)) == -1);
        CHECK((Vector(1, -1) ^ 0) == 0);
        CHECK(Vector(3, 7).perpendicularTo({-7, 3}));
        CHECK_FALSE(Vector(1, 15).perpendicularTo({0, -1}));
    }

    TEST_CASE("Cross product") {
        CHECK(Vector(5, 4) % Vector(3, 2) == -2);
        CHECK(RVector(0, 1) % Vector2<Real>(1, 0) == -1);
        CHECK(Vector(3, 4).parallelTo(Vector(-6, -8)));
        CHECK_FALSE(Vector(1, -1).parallelTo(Vector(-1, -1)));
    }

    TEST_CASE("Length, distance") {
        CHECK(Vector(7, 2).len2() == 53);
        CHECK(RVector(-10, 0).len2() == 100);
        CHECK(Vector(3, 4).len() == 5);
        CHECK(Vector(1, 1).len() == 1.41421356237);
        CHECK(dist2(Point(4, 10), {5, 12}) == 5);
        CHECK(dist(RPoint(3, 7), {0, 0}) == 7.615773105863908);
    }

    TEST_CASE("Simple rotations") {
        CHECK(Vector(3, 4).rotatedClockwise() == Vector(4, -3));
        CHECK(Vector(1, -90).rotatedCounterclockwise() == Vector(90, 1));
        Vector a{0, -1};
        a.rotateClockwise();
        CHECK(a == Vector(-1, 0));
        Vector b{7, 1};
        b.rotateCounterclockwise();
        CHECK(b == Vector(-1, 7));
    }

    TEST_CASE("istream operator") {
        std::istringstream is("89 -1 3.05 .79 -150.01 1e11 3e+3 2E-9");
        std::vector<RVector> values{
            {89, -1}, {3.05, 0.79}, {-150.01, 1e11}, {3e3, 2e-9}};
        for (auto expected : values) {
            RVector found;
            is >> found;
            CHECK(expected == found);
        }
    }

    TEST_CASE("ostream operator") {
        std::vector<Vector> vectors{{1, 3}, {-1, 7}, 0, 13};
        std::vector<std::string> answers{"1 3", "-1 7", "0 0", "13 0"};
        for (size_t i = 0; i < vectors.size(); ++i) {
            std::ostringstream os;
            os << vectors[i];
            CHECK(os.str() == answers[i]);
        }
    }

    TEST_CASE("RVector division") {
        CHECK(RVector(10, 2) / 2 == RVector(5, 1));
        CHECK(RVector(3, 7) / 3 == RVector(1, 2.3333333333333333333333));
        RVector a{4, 10};
        CHECK(a / 2 == RVector(2, 5));
        CHECK(a == RVector(4, 10));
        a /= 2;
        CHECK(a == RVector(2, 5));
        a /= 2;
        CHECK(a == RVector(1, 2.5));
        a /= 2.5;
        CHECK(a == RVector(0.4, 1));
    }

    TEST_CASE("RVector normalization") {}
}
