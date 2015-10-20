///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for the trigonometric arctangent function of (fixed_point) for a tiny digit range.

#include <cmath>

#define BOOST_TEST_MODULE test_negatable_func_arctangent_tiny
#define BOOST_LIB_DIAGNOSTIC

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_negatable_func_arctangent_tiny)
{
  typedef boost::fixed_point::negatable<4, -11> fixed_point_type;
  typedef fixed_point_type::float_type          float_point_type;

  const fixed_point_type tol = ldexp(fixed_point_type(1), fixed_point_type::resolution + 4);

  // Check positive arguments.
  for(int i = 1; i < 16; ++i)
  {
    const fixed_point_type x = atan(fixed_point_type(i) / 10);

    using std::atan;
    const float_point_type y = atan(float_point_type(i) / 10);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }

  // Check negative arguments.
  for(int i = 1; i < 16; ++i)
  {
    const fixed_point_type x = atan(fixed_point_type(-i) / 10);

    using std::atan;
    const float_point_type y = atan(float_point_type(-i) / 10);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }

  BOOST_CHECK_EQUAL(atan(fixed_point_type(0)), fixed_point_type(0));
}
