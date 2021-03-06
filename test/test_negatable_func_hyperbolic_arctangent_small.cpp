///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for the hyperbolic arctangent function of (fixed_point) for a small digit range.

#include <cmath>

#define BOOST_TEST_MODULE test_negatable_func_hyperbolic_arctangent_small
#define BOOST_LIB_DIAGNOSTIC

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_negatable_func_hyperbolic_arctangent_small)
{
  typedef boost::fixed_point::negatable<7, -24> fixed_point_type;
  typedef fixed_point_type::float_type          float_point_type;

  const fixed_point_type tol = ldexp(fixed_point_type(1), fixed_point_type::resolution + 4);

  BOOST_CONSTEXPR int i_max = 32;

  // Check positive arguments.
  for(int i = 0; i < i_max; ++i)
  {
    const fixed_point_type x = atanh(fixed_point_type(i) / i_max);

    using std::atanh;
    const float_point_type y = atanh(float_point_type(i) / i_max);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }

  // Check negative arguments.
  for(int i = 0; i < 9; ++i)
  {
    const fixed_point_type x = atanh(fixed_point_type(-i) / i_max);

    using std::atanh;
    const float_point_type y = atanh(float_point_type(-i) / i_max);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }
}
