#include "ess/basic_geometry.h"
#include <catch2/catch.hpp>

template <typename T>
constexpr bool is_regular(T p, T q)
{
  // clang-format off
  return std::is_copy_constructible_v<T>
    && std::is_move_constructible_v<T>
    && std::is_default_constructible_v<T>
    && std::is_copy_assignable_v<T>
    && std::is_move_assignable_v<T>
    && std::is_destructible_v<T>
    && p == q;
  // clang-format on
}

SCENARIO("A point must be a regular type.")
{
  GIVEN("A 2D point p,")
  {
    constexpr ess::basic_2d_point<int> p;
    constexpr ess::basic_2d_point<int> q;
    WHEN("the point is passed a function requiring a regular type,")
    {
      THEN("the code compiles.") { CHECK(is_regular(p, q)); }
    }
  }
  GIVEN("A 3D point p,")
  {
    constexpr ess::basic_3d_point<int> p;
    constexpr ess::basic_3d_point<int> q;
    WHEN("the point is passed a function requiring a regular type,")
    {
      THEN("the code compiles.") { CHECK(is_regular(p, q)); }
    }
  }
}

SCENARIO("A point can be constructed.")
{
  WHEN("A 2D point is default constructed,")
  {
    constexpr ess::basic_2d_point<int> p;
    THEN("the point is (0, 0).")
    {
      CHECK(p.x == 0);
      CHECK(p.y == 0);
    }
  }
  WHEN("A 2D point is user constructed,")
  {
    constexpr ess::basic_2d_point<int> p {2, 4};
    THEN("the point matches the input data.")
    {
      CHECK(p.x == 2);
      CHECK(p.y == 4);
    }
  }
  WHEN("A 2D point is copy constructed,")
  {
    constexpr ess::basic_2d_point<int> p {2, 4};
    constexpr ess::basic_2d_point<int> q {p};
    THEN("the two points are equal.")
    {
      CHECK(p.x == q.x);
      CHECK(p.y == q.y);
    }
  }
  WHEN("A 2D point is move constructed,")
  {
    ess::basic_2d_point<int> p {2, 4};
    const ess::basic_2d_point<int> q {p};
    THEN("the new point has the original point's coordinates.")
    {
      CHECK(q.x == 2);
      CHECK(q.y == 4);
    }
  }
  WHEN("A 3D point is default constructed,")
  {
    constexpr ess::basic_3d_point<int> p {};
    THEN("the point is (0, 0, 0).")
    {
      CHECK(p.x == 0);
      CHECK(p.y == 0);
      CHECK(p.z == 0);
    }
  }
  WHEN("A 3D point is user constructed,")
  {
    constexpr ess::basic_3d_point<int> p {2, 4, 6};
    THEN("the point matches the input data.")
    {
      CHECK(p.x == 2);
      CHECK(p.y == 4);
      CHECK(p.z == 6);
    }
  }
  WHEN("A 3D point is copy constructed,")
  {
    constexpr ess::basic_3d_point<int> p {2, 4, 6};
    constexpr ess::basic_3d_point<int> q {p};
    THEN("the two points are equal.")
    {
      CHECK(p.x == q.x);
      CHECK(p.y == q.y);
      CHECK(p.z == q.z);
    }
  }
  WHEN("A 3D point is move constructed,")
  {
    ess::basic_3d_point<int> p {2, 4, 6};
    const ess::basic_3d_point<int> q {p};
    THEN("the new point has the original point's coordinates.")
    {
      CHECK(q.x == 2);
      CHECK(q.y == 4);
      CHECK(q.z == 6);
    }
  }
}

SCENARIO("A point can be assigned new values.")
{
  GIVEN("Two different 2D points, p and q,")
  {
    ess::basic_2d_point<int> p;
    constexpr ess::basic_2d_point<int> q {2, 4};
    WHEN("q is assigned to p,")
    {
      p = q;
      THEN("p now has the values of q")
      {
        CHECK(p.x == 2);
        CHECK(p.y == 4);
      }
    }
  }
  GIVEN("Two different 2D points, p and q,")
  {
    ess::basic_2d_point<int> p;
    ess::basic_2d_point<int> q {2, 4};
    WHEN("q is move assigned to p,")
    {
      p = q;
      THEN("p now has the values of q")
      {
        CHECK(p.x == 2);
        CHECK(p.y == 4);
      }
    }
  }
  GIVEN("Two different 3D points, p and q,")
  {
    ess::basic_3d_point<int> p {};
    constexpr ess::basic_3d_point<int> q {2, 4, 6};
    WHEN("q is assigned to p,")
    {
      p = q;
      THEN("p now has the values of q")
      {
        CHECK(p.x == 2);
        CHECK(p.y == 4);
        CHECK(p.z == 6);
      }
    }
  }
  GIVEN("Two different 3D points, p and q,")
  {
    ess::basic_3d_point<int> p {};
    constexpr ess::basic_3d_point<int> q {2, 4, 6};
    WHEN("q is move assigned to p,")
    {
      p = q;
      THEN("p now has the values of q")
      {
        CHECK(p.x == 2);
        CHECK(p.y == 4);
        CHECK(p.z == 6);
      }
    }
  }
}

SCENARIO("Two points can be compared for equality and inequality.")
{
  GIVEN("Two equal 2D points, p and q,")
  {
    constexpr ess::basic_2d_point<int> p {2, 4};
    constexpr ess::basic_2d_point<int> q {2, 4};
    WHEN("they are compared for equality,")
    {
      THEN("the result is true.") { CHECK(p == q); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is false.") { CHECK(!(p != q)); }
    }
  }
  GIVEN("Two 2D points, which only differ in x,")
  {
    constexpr ess::basic_2d_point<int> p {1, 4};
    constexpr ess::basic_2d_point<int> q {2, 4};
    WHEN("they are compared for equality,")
    {
      THEN("the result is false.") { CHECK(!(p == q)); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is true.") { CHECK(p != q); }
    }
  }
  GIVEN("Two 2D points, which only differ in y,")
  {
    constexpr ess::basic_2d_point<int> p {2, 4};
    constexpr ess::basic_2d_point<int> q {2, 5};
    WHEN("they are compared for equality,")
    {
      THEN("the result is false.") { CHECK(!(p == q)); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is true.") { CHECK(p != q); }
    }
  }
  GIVEN("Two equal 3D points, p and q,")
  {
    constexpr ess::basic_3d_point<int> p {2, 4, 6};
    constexpr ess::basic_3d_point<int> q {2, 4, 6};
    WHEN("they are compared for equality,")
    {
      THEN("the result is true.") { CHECK(p == q); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is false.") { CHECK(!(p != q)); }
    }
  }
  GIVEN("Two 3D points, which only differ in x,")
  {
    constexpr ess::basic_3d_point<int> p {1, 4, 6};
    constexpr ess::basic_3d_point<int> q {2, 4, 6};
    WHEN("they are compared for equality,")
    {
      THEN("the result is false.") { CHECK(!(p == q)); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is true.") { CHECK(p != q); }
    }
  }
  GIVEN("Two 3D points, which only differ in y,")
  {
    constexpr ess::basic_3d_point<int> p {2, 4, 6};
    constexpr ess::basic_3d_point<int> q {2, 5, 6};
    WHEN("they are compared for equality,")
    {
      THEN("the result is false.") { CHECK(!(p == q)); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is true.") { CHECK(p != q); }
    }
  }
  GIVEN("Two 3D points, which only differ in z,")
  {
    constexpr ess::basic_3d_point<int> p {2, 4, 6};
    constexpr ess::basic_3d_point<int> q {2, 4, 7};
    WHEN("they are compared for equality,")
    {
      THEN("the result is false.") { CHECK(!(p == q)); }
    }
    AND_WHEN("they are compared for inequality,")
    {
      THEN("the result is true.") { CHECK(p != q); }
    }
  }
}
