
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Paul A. Bristow 2015.
// Copyright Christopher Kormanyos 2015.
// Copyright Nikhar Agrawal 2015.

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

// This file also includes Doxygen-style documentation about the function of the code.
// See http://www.doxygen.org for details.

//! \file

// Below are snippets of code that can be included into a Quickbook file.

#include <iostream>
#include <iomanip>
#include <exception>
#include <typeinfo>
#include <limits>

//[fixed_point_include_1
#include <boost/fixed_point/fixed_point.hpp>
//] [/fixed_point_include_1]

//[fixed_point_typedef_1
typedef boost::fixed_point::negatable<15, -16> fixed_point_type;
//] [/fixed_point_typedef_1]

//typedef boost::fixed_point::negatable<87, -2> fixed_point_type_fastest_round;


//typedef boost::fixed_point::negatable<5, -2> fixed_point_type;
//typedef boost::fixed_point::negatable<15, -15> fixed_point_type;

/*
! Show numeric_limits values for a type.
\tparam T floating-point, fixed-point type.

*/
template <typename T>
void show_fixed_point()
{
  using boost::fixed_point::negatable;

  std::cout.precision(std::numeric_limits<T>::digits10);

  std::cout << "Numeric_limits of type:"
    << typeid(fixed_point_type).name()

    << "\n range " << T::range
    << "  resolution " << T::resolution
    << "\n radix = " << std::numeric_limits<T>::radix // Always 2 for fixed-point.
    << "\n digits = " << std::numeric_limits<T>::digits // Does not include any sign bit.
    << "\n total bits = " << T::all_bits // DOES include sign bit.
    << "\n epsilon = " << std::numeric_limits<T>::epsilon()
    << "\n lowest = " << std::numeric_limits<fixed_point_type>::lowest()
    << " min = " << std::numeric_limits<T>::min()
    << " max = " << std::numeric_limits<T>::max()
    << "\n max_exponent = " << std::numeric_limits<fixed_point_type>::max_exponent
    << " min_exponent = " << std::numeric_limits<fixed_point_type>::min_exponent

    << "\n digits10 = " << std::numeric_limits<T>::digits10
    //<< "\n max_digits10 = " << std::numeric_limits<T>::max_digits10
    << std::endl;
  // TODO add resolution and range to report.
  std::cout << std::endl;

} // template <typename T> void show_fixed_point


using namespace boost::fixed_point;

typedef boost::fixed_point::negatable<11, -20> fixed_point_type_11m20;

negatable<11, -20> x = 0;


typedef boost::fixed_point::negatable<0, -30> fixed_point_type_0m30;

typedef boost::fixed_point::negatable<29, -2> fixed_point_type_29m2;

int main()
{
  try
  {
    std::cout.setf(std::ios_base::boolalpha | std::ios_base::showpoint); // Show any trailing zeros.
    std::cout << std::endl;

    using boost::fixed_point::negatable;

    int r = negatable<11, -20>::range;
    

//[fixed_example_1


    // Show all the significant digits for this particular floating-point type.

    //show_fixed_point<float>();
    // digits 24 (leaving 8 for decimal exponent).
    // epsilon 1.2e-7 


    show_fixed_point<negatable<15, -16> >();
    show_fixed_point<negatable<11, -20> >();
    show_fixed_point<negatable<29, -2> >();

    //std::cout << "fixed_point_type(123) / 100 = "
    //  << x // 1.22999573 is the nearest representation of decimal digit string 1.23.
    //  << std::endl;


//] [/fixed_example_1]

  }
  catch (std::exception ex)
  {
    std::cout << ex.what() << std::endl;
  }
}



/*
//[fixed_point_type_examples_output_1


//] [/fixed_point_type_examples_output_1]


*/