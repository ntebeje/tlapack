
// Copyright (c) 2021-2022, University of Colorado Denver. All rights reserved.
//
// This file is part of <T>LAPACK.
// <T>LAPACK is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#ifndef __TLAPACK_MPREAL_HH__
#define __TLAPACK_MPREAL_HH__

#include <mpreal.h>
#include <complex>

namespace tlapack {

    // Forward declarations
    template< typename T > auto abs ( const T& x );
    template< typename T > bool isnan( const std::complex<T>& x );
    template< typename T > bool isinf( const std::complex<T>& x );

    /// Absolute value
    template<>
    inline auto abs( const mpfr::mpreal& x ) {
        return mpfr::abs( x );
    }
    
    /// 2-norm absolute value, sqrt( |Re(x)|^2 + |Im(x)|^2 )
    ///
    /// Note that std::abs< std::complex > does not overflow or underflow at
    /// intermediate stages of the computation.
    /// @see https://en.cppreference.com/w/cpp/numeric/complex/abs
    /// but it may not propagate NaNs.
    ///
    /// Also, std::abs< mpfr::mpreal > may not propagate Infs.
    ///
    template<>
    inline auto abs( const std::complex<mpfr::mpreal>& x ) {
        if( isnan(x) )
            return std::numeric_limits< mpfr::mpreal >::quiet_NaN();
        else if( isinf(x) )
            return std::numeric_limits< mpfr::mpreal >::infinity();
        else
            return std::abs( x );
    }

    // Argument-dependent lookup (ADL) will include the remaining functions,
    // e.g., mpfr::sin, mpfr::cos.
    // Including them here may cause ambiguous call of overloaded function.
    // See: https://en.cppreference.com/w/cpp/language/adl

    #ifdef MPREAL_HAVE_DYNAMIC_STD_NUMERIC_LIMITS
        
        // Forward declaration
        template< typename real_t > const real_t digits();

        /** Digits for the mpfr::mpreal datatype
         * @ingroup utils
         */
        template<>
        inline const mpfr::mpreal digits() {
            return std::numeric_limits< mpfr::mpreal >::digits(); 
        }
    #endif

} // namespace tlapack

#endif // __TLAPACK_MPREAL_HH__
