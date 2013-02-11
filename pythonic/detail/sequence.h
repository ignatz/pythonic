#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <cstdlib>

#include "pythonic/detail/util.h"

namespace pythonic {
namespace detail {

template<typename NoPack, size_t Start, typename ... Args>
struct build_sequence;

template<size_t Start, typename Arg, typename ... Args, size_t ... Enum>
struct build_sequence<pack<Enum...>, Start, Arg, Args...>
{
	typedef typename build_sequence<
		pack<Enum..., Start>,
		Start+1, Args...>::type type;
};

template<size_t Start, size_t ... Enum>
struct build_sequence<pack<Enum...>, Start>
{
	typedef pack<Enum...> type;
};


template<typename ... Args>
struct sequence
{
	typedef typename build_sequence<pack<>, 0, Args...>::type type;
};

} // detail
} // pythonic
