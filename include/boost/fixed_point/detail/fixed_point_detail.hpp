///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file contains fixed_point details.

#ifndef FIXED_POINT_DETAIL_2015_05_23_HPP_
  #define FIXED_POINT_DETAIL_2015_05_23_HPP_

  // Do not produce Doxygen indexing of items in namespace detail unless specifically required.
  // The section between \cond and \endcond can be included by adding its section label DETAIL
  // to the ENABLED_SECTIONS configuration option. 
  // If the section label is omitted, the section will be excluded from processing unconditionally.

  //! \cond DETAIL

  namespace boost { namespace fixed_point { namespace detail {

  template<typename UnsignedIntegralType>
  UnsignedIntegralType left_shift_helper(UnsignedIntegralType& u, const int shift_count)
  {
    static_assert(    (std::numeric_limits<UnsignedIntegralType>::is_integer == true)
                   && (std::numeric_limits<UnsignedIntegralType>::is_signed  == false),
                   "the UnsignedIntegralType for left shift must be an unsigned integral type");

    return ((shift_count > 0) ? UnsignedIntegralType(u << +shift_count)
                              : UnsignedIntegralType(u >> -shift_count));
  }

  template<typename UnsignedIntegralType>
  UnsignedIntegralType right_shift_helper(UnsignedIntegralType& u, const int shift_count)
  {
    static_assert(    (std::numeric_limits<UnsignedIntegralType>::is_integer == true)
                   && (std::numeric_limits<UnsignedIntegralType>::is_signed  == false),
                   "the UnsignedIntegralType for right shift must be an unsigned integral type");

    return ((shift_count > 0) ? UnsignedIntegralType(u >> +shift_count)
                              : UnsignedIntegralType(u << -shift_count));
  }

  template<typename UnsignedIntegralType,
           const unsigned BitPosition,
           const unsigned BitCount,
           typename EnableType = void>
  struct bit_mask_helper
  {
    // Ensure that the requested bit mask is in range.
    static_assert((BitPosition + BitCount) <= unsigned(std::numeric_limits<UnsignedIntegralType>::digits),
                  "the requested bit_mask value exceeds the maximum value of the UnsignedIntegralType");

    static const UnsignedIntegralType& value()
    {
      static const UnsignedIntegralType the_bit_mask =
        static_cast<UnsignedIntegralType>(static_cast<UnsignedIntegralType>(static_cast<UnsignedIntegralType>(~static_cast<UnsignedIntegralType>(0U)) >> (std::numeric_limits<UnsignedIntegralType>::digits - BitCount)) << BitPosition);

      return the_bit_mask;
    }
  };

  template<typename UnsignedIntegralType,
           const unsigned BitPosition,
           const unsigned BitCount>
  struct bit_mask_helper<UnsignedIntegralType,
                         BitPosition,
                         BitCount,
                         typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                 && std::is_unsigned<UnsignedIntegralType>::value>::type>
  {
    // Ensure that the requested bit mask is in range.
    static_assert((BitPosition + BitCount) <= unsigned(std::numeric_limits<UnsignedIntegralType>::digits),
                  "the requested bit_mask value exceeds the maximum value of the UnsignedIntegralType");

    static UnsignedIntegralType value() BOOST_NOEXCEPT
    {
      return static_cast<UnsignedIntegralType>(static_cast<UnsignedIntegralType>(static_cast<UnsignedIntegralType>(~static_cast<UnsignedIntegralType>(0U)) >> (std::numeric_limits<UnsignedIntegralType>::digits - BitCount)) << BitPosition);
    }
  };

  #if !defined(BOOST_FIXED_POINT_DISABLE_MULTIPRECISION)
    template<const unsigned BitCount,
             typename EnableType = void>
    struct integer_type_helper
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<BitCount,
                                                     BitCount,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<BitCount,
                                                     BitCount,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };
  #else
    template<const unsigned BitCount,
             typename EnableType = void>
    struct integer_type_helper
    {
      typedef signed long long   exact_signed_type;
      typedef unsigned long long exact_unsigned_type;
    };
  #endif

  template<const unsigned BitCount>
  struct integer_type_helper<BitCount,
                             typename std::enable_if<(BitCount <= 8U)>::type>
  {
    typedef boost::int8_t  exact_signed_type;
    typedef boost::uint8_t exact_unsigned_type;
  };

  template<const unsigned BitCount>
  struct integer_type_helper<BitCount,
                             typename std::enable_if<   (BitCount >   8U)
                                                     && (BitCount <= 16U)>::type>
  {
    typedef boost::int16_t  exact_signed_type;
    typedef boost::uint16_t exact_unsigned_type;
  };

  template<const unsigned BitCount>
  struct integer_type_helper<BitCount,
                             typename std::enable_if<   (BitCount >  16U)
                                                     && (BitCount <= 32U)>::type>
  {
    typedef boost::int32_t  exact_signed_type;
    typedef boost::uint32_t exact_unsigned_type;
  };

  template<const unsigned BitCount>
  struct integer_type_helper<BitCount,
                             typename std::enable_if<   (BitCount >  32U)
                                                     && (BitCount <= 64U)>::type>
  {
    typedef boost::int64_t  exact_signed_type;
    typedef boost::uint64_t exact_unsigned_type;
  };

  #if !defined(BOOST_FIXED_POINT_DISABLE_MULTIPRECISION)

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                                typename std::enable_if<   (BitCount >   64U)
                                                        && (BitCount <= 128U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<128U,
                                                     128U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<128U,
                                                     128U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >  128U)
                                                       && (BitCount <= 256U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<256U,
                                                     256U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<256U,
                                                     256U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >  256U)
                                                       && (BitCount <= 512U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<512U,
                                                     512U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<512U,
                                                     512U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >   512U)
                                                       && (BitCount <= 1024U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<1024U,
                                                     1024U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<1024U,
                                                     1024U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                                typename std::enable_if<   (BitCount >  1024U)
                                                        && (BitCount <= 2048U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<2048U,
                                                     2048U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<2048U,
                                                     2048U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >  2048U)
                                                       && (BitCount <= 4096U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<4096U,
                                                     4096U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<4096U,
                                                     4096U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >  4096U)
                                                       && (BitCount <= 8192U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<8192U,
                                                     8192U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<8192U,
                                                     8192U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >   8192U)
                                                       && (BitCount <= 16384U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<16384U,
                                                     16384U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<16384U,
                                                     16384U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    template<const unsigned BitCount>
    struct integer_type_helper<BitCount,
                               typename std::enable_if<   (BitCount >  16384U)
                                                       && (BitCount <= 32768U)>::type>
    {
    private:
      typedef boost::multiprecision::cpp_int_backend<32768U,
                                                     32768U,
                                                     boost::multiprecision::signed_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      signed_integral_backend_type;

      typedef boost::multiprecision::cpp_int_backend<32768U,
                                                     32768U,
                                                     boost::multiprecision::unsigned_magnitude,
                                                     boost::multiprecision::unchecked,
                                                     void>
      unsigned_integral_backend_type;

    public:
      typedef boost::multiprecision::number<signed_integral_backend_type,
                                            boost::multiprecision::et_off> exact_signed_type;

      typedef boost::multiprecision::number<unsigned_integral_backend_type,
                                            boost::multiprecision::et_off> exact_unsigned_type;
    };

    #endif // !BOOST_FIXED_POINT_DISABLE_MULTIPRECISION


    #if !defined(BOOST_FIXED_POINT_DISABLE_MULTIPRECISION)

      template<const unsigned BitCount,
                typename EnableType = void>
      struct float_type_helper
      {
        typedef boost::multiprecision::number<
                  boost::multiprecision::backends::cpp_bin_float<BitCount,
                                                                 boost::multiprecision::backends::digit_base_2>,
                boost::multiprecision::et_off>
        exact_float_type;
      };

    #else

      template<const unsigned BitCount,
                typename EnableType = void>
      struct float_type_helper
      {
        typedef boost::floatmax_t exact_float_type;
      };

  #endif // !BOOST_FIXED_POINT_DISABLE_MULTIPRECISION

  template<const unsigned BitCount>
  struct float_type_helper<BitCount,
                           typename std::enable_if<(BitCount <= 24U)>::type>
  {
    typedef boost::float32_t exact_float_type;
  };

  #if defined(BOOST_FLOAT64_C)
    template<const unsigned BitCount>
    struct float_type_helper<BitCount,
                             typename std::enable_if<   (BitCount >  24U)
                                                     && (BitCount <= 53U)>::type>
    {
      typedef boost::float64_t exact_float_type;
    };
  #endif // BOOST_FLOAT64_C

  #if defined(BOOST_FLOAT80_C)
    template<const unsigned BitCount>
    struct float_type_helper<BitCount,
    #if defined(BOOST_FLOAT64_C)
                             typename std::enable_if<   (BitCount >  53U)
                                                     && (BitCount <= 64U)>::type>
    #else
                             typename std::enable_if<   (BitCount >  24U)
                                                     && (BitCount <= 64U)>::type>
    #endif
    {
      typedef boost::float64_t exact_float_type;
    };
  #endif // BOOST_FLOAT80_C

  #if defined(BOOST_FLOAT128_C)
    template<const unsigned BitCount>
    struct float_type_helper<BitCount,
    #if defined(BOOST_FLOAT80_C)
                             typename std::enable_if<   (BitCount >   64U)
                                                     && (BitCount <= 113U)>::type>
    #else
                             typename std::enable_if<   (BitCount >   53U)
                                                     && (BitCount <= 113U)>::type>
    #endif
    {
      typedef boost::float128_t exact_float_type;
    };
  #endif // BOOST_FLOAT128_C

  #if !defined(BOOST_FIXED_POINT_DISABLE_MULTIPRECISION)
    template<typename UnsignedIntegralType,
             typename FloatingPointType,
             typename EnableType = void>
    struct conversion_helper
    {
      static void convert_floating_point_to_unsigned_integer(const FloatingPointType& floating_point_source,
                                                             UnsignedIntegralType& unsigned_destination)
      {
        unsigned_destination = floating_point_source.template convert_to<UnsignedIntegralType>();
      }
    };

    #if defined(BOOST_FLOAT80_C)
    template<>
    struct conversion_helper<boost::uint64_t,
                             boost::float80_t,
                             typename std::enable_if<true>::type>
    {
      static void convert_floating_point_to_unsigned_integer(const boost::float80_t& floating_point_source,
                                                             boost::uint64_t& unsigned_destination)
      {
        unsigned_destination = static_cast<boost::uint64_t>(floating_point_source);
      }
    };
    #endif

    template<typename FloatingPointType>
    struct conversion_helper<boost::uint64_t,
                             FloatingPointType,
                             typename std::enable_if<std::is_floating_point<FloatingPointType>::value == false>::type>
    {
      static void convert_floating_point_to_unsigned_integer(const FloatingPointType& floating_point_source,
                                                             boost::uint64_t& unsigned_destination)
      {
        // Here is a somewhat significant workaround for the conversion of
        // cpp_bin_float to uint64_t. It is used for cases when the digits
        // in cpp_bin_float are fewer than the digits in uint64_t,
        // but larger than the digits in float64_t.

        // TBD: See the TODO in the comment at line 1113 of cpp_bin_float.hpp.

        std::stringstream ss;

        ss << std::fixed << floating_point_source;

        std::string str(ss.str());

        const std::string::size_type position_of_dot = str.find(".");

        if(position_of_dot != std::string::npos)
        {
          str = str.substr(std::string::size_type(0U), position_of_dot);
        }

        unsigned_destination = boost::lexical_cast<boost::uint64_t>(str);
      }
    };

    template<typename UnsignedIntegralType,
             typename FloatingPointType>
    struct conversion_helper<UnsignedIntegralType,
                             FloatingPointType,
                             typename std::enable_if<std::is_floating_point<FloatingPointType>::value>::type>
    {
      static void convert_floating_point_to_unsigned_integer(const FloatingPointType& floating_point_source,
                                                             UnsignedIntegralType& unsigned_destination)
      {
        unsigned_destination = static_cast<UnsignedIntegralType>(floating_point_source);
      }
    };

  #else

    template<typename UnsignedIntegralType,
             typename FloatingPointType,
             typename EnableType = void>
    struct conversion_helper
    {
      static void convert_floating_point_to_unsigned_integer(const FloatingPointType& floating_point_source,
                                                             UnsignedIntegralType& unsigned_destination)
      {
        unsigned_destination = static_cast<UnsignedIntegralType>(floating_point_source);
      }
    };

    #if defined(BOOST_FLOAT80_C)
    template<>
    struct conversion_helper<boost::uint64_t,
                             boost::float80_t,
                             typename std::enable_if<true>::type>
    {
      static void convert_floating_point_to_unsigned_integer(const boost::float80_t& floating_point_source,
                                                             boost::uint64_t& unsigned_destination)
      {
        unsigned_destination = static_cast<boost::uint64_t>(floating_point_source);
      }
    };
    #endif

  #endif // !BOOST_FIXED_POINT_DISABLE_MULTIPRECISION

  } } } // namespace boost::fixed_point::detail
  //! \endcond // DETAIL

#endif // FIXED_POINT_DETAIL_2015_05_23_HPP_