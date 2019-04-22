//#define BOOST_TEST_MODULE Ess Point Test
//#include <boost/test/unit_test.hpp>
//
//BOOST_AUTO_TEST_CASE(Foo)  // NOLINT
//{
//  BOOST_CHECK_EQUAL(0, 0);
//}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Dummy test")
{
  REQUIRE(1 == 0);
}
