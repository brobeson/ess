#include "point.h"
#include <catch2/catch.hpp>

TEST_CASE("Equality")
{
  const ess::point2<int> a {1, 3};
  const ess::point2<int> b {1, 3};
  const ess::point2<int> c {1, 2};
  const ess::point2<int> d {0, 3};
  REQUIRE(a == b);
  REQUIRE(a != c);
  REQUIRE(a != d);
}
