///////////////////////////////////////////////////////////////////////////////
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file does round-trip testing for
// "C++ binary fixed-point arithmetic" as specified in N3352.
// See: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3352.html


#define BOOST_TEST_MODULE round_trip_decimal_digits_003
#define BOOST_LIB_DIAGNOSTIC

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/cstdfloat.hpp>
#include <boost/fixed_point/fixed_point.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/test/included/unit_test.hpp>

namespace local
{
  // Define a binary fixed-point type with 3 decimal digits of precision.
  typedef
  boost::fixed_point::negatable<0,
                                -11,
                                boost::fixed_point::round::nearest_even>
  fixed_point_type_decimal_digits_003;

  bool round_trip(const fixed_point_type_decimal_digits_003& x);
}

bool local::round_trip(const local::fixed_point_type_decimal_digits_003& x)
{
  typedef local::fixed_point_type_decimal_digits_003 fixed_point_type;

  std::stringstream ss1;

  ss1 << std::setprecision(std::numeric_limits<fixed_point_type>::digits10)
      << std::fixed
      << x;

  std::stringstream ss2(ss1.str());

  fixed_point_type y;
  ss2 >> y;

  const bool b(x == y);

  return b;
}

BOOST_AUTO_TEST_CASE(round_trip_decimal_digits_003)
{
  typedef local::fixed_point_type_decimal_digits_003 fixed_point_type;
  typedef fixed_point_type::float_type floating_point_type;

  uint_fast32_t count;

  bool b = true;

  // Test every single value with 3 decimal digits of precision
  // The values range from 0.001, 0.002, 0.003, ... 0.500.
  for(count = UINT32_C(1); ((count < UINT32_C(500)) && b); ++count)
  {
    std::stringstream ss1;

    ss1 << count;

    std::string str(ss1.str());

    str.insert(0U, 3U - str.length(), '0');

    str = ("0." + str);

    const floating_point_type x = boost::lexical_cast<floating_point_type>(str);

    const fixed_point_type fx(x);

    const bool next_test_result =
      local::round_trip(local::fixed_point_type_decimal_digits_003(fx));

    b = (b && next_test_result);
  }

  BOOST_CHECK_EQUAL(count, UINT32_C(500));

  BOOST_CHECK_EQUAL(b, true);
}
