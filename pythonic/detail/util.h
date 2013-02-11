#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <cstdlib>

namespace pythonic {
namespace detail {

template<size_t ... N>
struct pack {};


template<typename ... T>
inline
void noop(T&& ...)
{}


template<typename Return>
inline
Return sum()
{
	return 0;
}

template<typename Return, typename T, typename ... Ts>
inline
Return sum(T const& t, Ts const& ... ts)
{
	return t + sum<Return>(ts...);
}

} // detail
} // pythonic
