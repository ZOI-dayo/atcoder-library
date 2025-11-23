#pragma once

#if __has_include(<boost/multiprecision/gmp.hpp>)

#define EXIST_BOOST

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
using namespace boost::multiprecision;

using bint = mpz_int;

#endif
