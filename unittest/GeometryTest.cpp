#include <array>
#include <limits>
#include <memory>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#define private public
#include "Geometry.hpp"
#undef private
#include "doctest.h"

using doctest::Approx;
using namespace acmlib::geometry;

TEST_SUITE("Geometry::Real") {
  constexpr const double doubleEpsilon = std::numeric_limits<double>::epsilon();

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

TEST_SUITE("Geometry::Vector") {
  TEST_CASE("Minimal sizeof") {
#define CHECK_SIZEOF(T) CHECK(sizeof(Vector<T>) == 2 * sizeof(T))
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
    Vector<int32_t> v;
    CHECK(v.coords[0] == 0);
    CHECK(v.coords[1] == 0);
  }

  TEST_CASE("Two parameter constructor") {
    LVector a(1, 2);
    CHECK(a.coords[0] == 1);
    CHECK(a.coords[1] == 2);
    RVector b(-1, 0.5);
    CHECK(b.coords[0] == -1);
    CHECK(b.coords[1] == 0.5);
    Vector<float> c{12, 12.01};
    CHECK(c.coords[0] == Approx(12));
    CHECK(c.coords[1] == Approx(12.01));
    Vector<long double> d({3, -31.1});
    CHECK(d.coords[0] == Approx(3));
    CHECK(d.coords[1] == Approx(-31.1));
    LVector e = {1, 100000};
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
    LVector a(1, 2);
    LVector b(a);
    CHECK(b.coords[0] == 1);
    CHECK(b.coords[1] == 2);
    LVector c = b;
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
    LVector v{3, 4};
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
    Vector<double> a(-11, 0.1);
    CHECK(a[0] == -11);
    CHECK(a[1] == 0.1);
  }

  TEST_CASE("Conversion between different coordinate types") {
    LVector a{-1, 1337};
    Vector<float> b(a);
    CHECK(b.x() == Approx(-1));
    CHECK(b.y() == Approx(1337));
    Vector<double> c{a};
    CHECK(c.x() == Approx(-1));
    CHECK(c.y() == Approx(1337));
    RVector d = a;
    CHECK(d.x() == -1);
    CHECK(d.y() == 1337);
    RVector p{-0.1, 37.3};
    LVector q;
    q = p;
    CHECK(q.x() == 0);
    CHECK(q.y() == 37);
  }

  TEST_CASE("Construct from two endpoints") {
    LPoint A{-9, 6};
    LPoint B{3, 7};
    LVector v(A, B);
    CHECK(v.x() == 12);
    CHECK(v.y() == 1);

    RPoint P{1.2, -0.2};
    RPoint Q{1.2, 0.1};
    RVector u{P, Q};
    CHECK(u.x() == 0);
    CHECK(u.y() == 0.3);
  }

  TEST_CASE("Comparison") {
    CHECK(RVector(1e-12, 34.1) == RVector(0, 34.1));
    CHECK(Vector<float>(4.5, 3.0003) != Vector<float>(4.5, 3));
    CHECK(LVector(1, 2) < LVector(3, -100000));
    CHECK(RVector(0.1, 0) <= RVector(0.1, 0.1));
    CHECK(LVector(4, -1) >= LVector(4, -1));
    CHECK_FALSE(LVector(3, 0) < LVector(3, -1));
  }

  TEST_CASE("LVector addition") {
    CHECK(LVector(1, -1) + LVector(2, 3) == LVector(3, 2));
    CHECK(RVector(99.1, 5) + RVector(10, 0) == RVector(109.1, 5));
    LVector a{4, 1};
    CHECK(a + LVector(-4, -1) == RVector());
    CHECK(a == LVector(4, 1));
    a += {3, -2};
    CHECK(a == LVector(7, -1));
  }

  TEST_CASE("LVector subtraction") {
    CHECK(RVector(0.1, -30) - RVector(0.7, -31) == RVector(-0.6, 1));
    CHECK(RVector(1.3, 0) - RVector(0.3, 0) == RVector(1, 0));
    LVector b{-10, -9};
    CHECK(b - LVector(-10, -8) == LVector(0, -1));
    CHECK(b == LVector(-10, -9));
    b -= {5, 6};
    CHECK(b == LVector(-15, -15));
    b -= {-16, 0};
    CHECK(b == LVector(1, -15));
  }

  TEST_CASE("Multiplication by scalar") {
    CHECK(LVector(1, -2) * 3 == LVector(3, -6));
    CHECK(LVector(77, 98) * 0 == LVector());
    CHECK(10 * RVector(0.1, 3e-6) == RVector(1, 3e-5));
    LVector a{1, -1};
    a *= 2;
    CHECK(a == LVector(2, -2));
    a *= -1;
    CHECK(a == LVector(-2, 2));
  }

  TEST_CASE("Unary operators") {
    CHECK(+LVector(3, 1) == LVector(3, 1));
    RVector a = {4, 0};
    CHECK(+(+a) == RVector(4, 0));
    CHECK(-a == RVector(-4, 0));
    CHECK(-LVector(10, 12) == LVector(-10, -12));
  }

  TEST_CASE("Dot product") {
    CHECK((LVector(4, -2) ^ LVector(1, 1)) == 2);
    CHECK((LVector(6, 7) ^ LVector(1, -1)) == -1);
    CHECK((LVector(1, -1) ^ LVector()) == 0);
    CHECK(LVector(3, 7).perpendicularTo({-7, 3}));
    CHECK_FALSE(LVector(1, 15).perpendicularTo({0, -1}));
  }

  TEST_CASE("Cross product") {
    CHECK(LVector(5, 4) % LVector(3, 2) == -2);
    CHECK(RVector(0, 1) % RVector(1, 0) == -1);
    CHECK(LVector(3, 4).parallelTo(LVector(-6, -8)));
    CHECK_FALSE(LVector(1, -1).parallelTo(LVector(-1, -1)));
  }

  TEST_CASE("Length, distance") {
    CHECK(LVector(7, 2).len2() == 53);
    CHECK(RVector(-10, 0).len2() == 100);
    CHECK(LVector(3, 4).len() == 5);
    CHECK(LVector(1, 1).len() == 1.41421356237);
    CHECK(dist2(LPoint(4, 10), {5, 12}) == 5);
    CHECK(dist(RPoint(3, 7), {0, 0}) == 7.615773105863908);
  }

  TEST_CASE("Simple rotations") {
    CHECK(LVector(3, 4).rotatedClockwise() == LVector(4, -3));
    CHECK(LVector(1, -90).rotatedCounterclockwise() == LVector(90, 1));
    LVector a{0, -1};
    a.rotateClockwise();
    CHECK(a == LVector(-1, 0));
    LVector b{7, 1};
    b.rotateCounterclockwise();
    CHECK(b == LVector(-1, 7));
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
    std::vector<LVector> vectors{{1, 3}, {-1, 7}, {0, 0}, {13, 0}};
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

  TEST_CASE("RVector normalization") {
    CHECK(normalized(RVector{1l, 1l}) ==
          RVector(0.7071067811865475, 0.7071067811865475));
    RVector a{8.10073, 0};
    normalize(a);
    CHECK(a == RVector{1, 0});
  }

  TEST_CASE("LVector division (intergral)") {
    CHECK(LVector(4, 6) / 2 == LVector(2, 3));
    CHECK(LVector(9, 7) / 3 == LVector(3, 2));
    LVector v{50, 24};
    CHECK(v / 2 == LVector(25, 12));
    CHECK(v == LVector(50, 24));
    v /= 2;
    CHECK(v == LVector(25, 12));
    v /= 5;
    CHECK(v == LVector(5, 2));
    v /= 2;
    CHECK(v == LVector(2, 1));
    v /= 1;
    CHECK(v == LVector(2, 1));
    v /= 3;
    CHECK(v == LVector(0, 0));
  }

  TEST_CASE("LVector normalization (integral)") {
    CHECK(normalized(LVector{45, 25}) == LVector{9, 5});
    CHECK(normalized(LVector{11, -10}) == LVector{11, -10});
    CHECK(normalized(LVector{-4, 6}) == LVector{2, -3});
    CHECK(normalized(LVector{0, 10}) == LVector{0, 1});
    CHECK(normalized(LVector{0, -32}) == LVector{0, 1});
    CHECK(normalized(LVector{0, 0}) == LVector{0, 0});
  }

  TEST_CASE("Vector range-based for loop") {
    Vector<int> a{1, 2};
    std::vector<int> ac;
    const Vector<int>& ref_a = a;
    for (const int& x : ref_a) {
      ac.push_back(x);
    }
    CHECK(ac == std::vector<int>{1, 2});
    for (int& x : a) {
      x = 3 - x;
    }
    CHECK(a == Vector<int>{2, 1});
  }

  TEST_CASE("triangleArea (by two vectors)") {
    CHECK(triangleArea<long long>({1, 0}, {0, 1}) == 0.5);
    CHECK(triangleArea<long long>({0, 1}, {1, 0}) == 0.5);
    CHECK(triangleArea<long long>({2, 4}, {3, 6}) == 0);
    CHECK(triangleArea<long long>({3, 4}, {-10, 13}) == 39.5);
  }

  TEST_CASE("triangleArea (by three points)") {
    CHECK(triangleArea<long long>({4, -4}, {5, -3}, {6, -4}) == 1);
    CHECK(triangleArea<Real>({0.5, 6}, {11, 12}, {0.5, 6}) == 0);
    CHECK(triangleArea<Real>({0, 0}, {3, 4}, {4, 3}) == 3.5);
    CHECK(triangleArea<Real>({3, 4}, {0, 0}, {4, 3}) == 3.5);
  }
}

TEST_SUITE("Geometry::Line") {
  TEST_CASE("Constructors") {
    Line<int32_t> l{1, 2, 3};
    CHECK(l.a() == 1);
    CHECK(l.b() == 2);
    CHECK(l.c() == 3);
    Line<Real> k({1, 0}, {0, 1});
    CHECK(k.a() == k.b());
    CHECK(k.a() == k.c());
  }

  TEST_CASE("eval") {
    LLine l{1, -5, 3};
    CHECK(l.eval({3, 4}) == -17);
    CHECK(l.eval({0, 0}) == 0);
    CHECK(l.eval({5, 1}) == 0);
  }

  TEST_CASE("contains") {
    LLine l{4, 3, 1};
    CHECK(l.contains({1, -1}));
    CHECK_FALSE(l.contains({0, 0}));
    CHECK_FALSE(l.contains({-38, 11}));
    CHECK(l.contains({10, -13}));
  }

  TEST_CASE("relativePosition") {
    LLine l{5, 9, 0};
    CHECK(l.relativePosition({0, 0}) == 0);
    CHECK(l.relativePosition({1, -1}) == -1);
    CHECK(l.relativePosition({1, 1}) == 1);
    CHECK(l.relativePosition({9, -5}) == 0);
  }

  TEST_CASE("istream operator") {
    std::istringstream is("56 -7 10 .32 1e11 3e-3");
    std::vector<RLine> values{{56, -7, 10}, {0.32, 1e11, 3e-3}};
    for (auto expected : values) {
      RLine found;
      is >> found;
      CHECK(expected.a() == found.a());
      CHECK(expected.b() == found.b());
      CHECK(expected.c() == found.c());
    }
  }

  TEST_CASE("ostream operator") {
    std::vector<LLine> lines{{0, 0, 1}, {3, 4, -2}};
    std::vector<std::string> answers{"0 0 1", "3 4 -2"};
    for (size_t i = 0; i < lines.size(); ++i) {
      std::ostringstream os;
      os << lines[i];
      CHECK(os.str() == answers[i]);
    }
  }

  TEST_CASE("parallelTo") {
    LLine l{1, 2, 7};
    CHECK(l.parallelTo({2, 4, -3}));
    CHECK(l.parallelTo({-3, -6, 0}));
    CHECK_FALSE(l.parallelTo({1, 1, 1}));
  }
}
