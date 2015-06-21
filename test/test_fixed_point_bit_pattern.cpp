// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


//! \file
//!\ This is used to test the underlying bit representation of our negatable class. If these tests fail, something's wrong at
//!\ the very basic level.

#define BOOST_TEST_MODULE fixed_point_basic
#define BOOST_LIB_DIAGNOSTIC
//  Linking to lib file: libboost_unit_test_framework-vc120-mt-gd-1_59.lib

#include <boost/test/included/unit_test.hpp> // No Boost.Test library.
//#include <boost/test/unit_test.hpp> // USe Boost.Test library.

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "boost/fixed_point/fixed_point.hpp"

typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<100>, boost::multiprecision::et_off> cpp_dec_float_100_noet;

BOOST_AUTO_TEST_CASE(fixed_point_construct_nearest_even_round)
{
  //! small range and resolution
  {
  	typedef boost::fixed_point::negatable<4, -2, boost::fixed_point::round::nearest_even> fixed_point_type_nearest_even_round;
    fixed_point_type_nearest_even_round x = fixed_point_type_nearest_even_round (-15.375);
    fixed_point_type_nearest_even_round y = fixed_point_type_nearest_even_round(-15.5);    
    
    std::string bit_pattern = "1000010";

    BOOST_CHECK_EQUAL(x.bit_pattern (), bit_pattern);
    BOOST_CHECK_EQUAL(y.bit_pattern (), bit_pattern);

    x = fixed_point_type_nearest_even_round (15.375);
    y = fixed_point_type_nearest_even_round (15.5);

    bit_pattern = "0111110";

    BOOST_CHECK_EQUAL(x.bit_pattern (), bit_pattern);
    BOOST_CHECK_EQUAL(y.bit_pattern (), bit_pattern);
  }

  //! larger range and larger resolution
  {
  	typedef boost::fixed_point::negatable<87, -4, boost::fixed_point::round::nearest_even> fixed_point_type_nearest_even_round;
    fixed_point_type_nearest_even_round x = fixed_point_type_nearest_even_round (cpp_dec_float_100_noet("154742504910672534362390527.375"));
    fixed_point_type_nearest_even_round y = fixed_point_type_nearest_even_round (cpp_dec_float_100_noet("154742504910672534362390527.34375"));

    std::string bit_pattern = "01111111111111111111111111111111111111111111111111111111111111111111111111111111111111110110";

    BOOST_CHECK_EQUAL(x.bit_pattern (), bit_pattern);
    BOOST_CHECK_EQUAL(y.bit_pattern (), bit_pattern);

    x = fixed_point_type_nearest_even_round (cpp_dec_float_100_noet("-154742504910672534362390527.375"));
    y = fixed_point_type_nearest_even_round (cpp_dec_float_100_noet("-154742504910672534362390527.34375"));

    bit_pattern = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010";

    BOOST_CHECK_EQUAL(x.bit_pattern (), bit_pattern);
    BOOST_CHECK_EQUAL(y.bit_pattern (), bit_pattern);

  }  
}
