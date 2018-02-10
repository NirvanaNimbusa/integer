/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#define BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#include <tuple>
#include <limits>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7.
// Should the tuple be a named tuple? Is that possible?
// Solves mx + ny = gcd(m,n). Returns tuple with (gcd(m,n), x, y).
// Is this the natural ordering?, or must people simply have to read the docs?
template<class Z>
std::tuple<Z, Z, Z> extended_euclidean(Z m, Z n)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                  "The extended Euclidean algorithm works on integral types.\n");

    static_assert(numeric_limits<Z>::is_signed,
                  "The extended Euclidean algorithm only works on signed integer types.\n");

    if (m < 1 || n < 1)
    {
        throw std::domain_error("Arguments must be strictly positive.\n");
    }
    bool swapped = false;
    if (m < n)
    {
        swapped = true;
        std::swap(m, n);
    }
    Z u0 = m;
    Z u1 = 1;
    Z u2 = 0;
    Z v0 = n;
    Z v1 = 0;
    Z v2 = 1;
    Z w0;
    Z w1;
    Z w2;
    while(v0 > 0)
    {
        Z q = u0/v0;
        w0 = u0 - q*v0;
        w1 = u1 - q*v1;
        w2 = u2 - q*v2;
        u0 = v0;
        u1 = v1;
        u2 = v2;
        v0 = w0;
        v1 = w1;
        v2 = w2;
    }
    if (swapped)
    {
        std::swap(u1, u2);
        BOOST_ASSERT(u2*m+u1*n==u0);
    }
    else
    {
        BOOST_ASSERT(u1*m+u2*n==u0);
    }

    return std::make_tuple(u0, u1, u2);
}

}}
#endif
