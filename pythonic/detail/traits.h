#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

namespace pythonic {
namespace detail {

template<typename Container>
struct traits
{
	typedef typename Container::size_type size_type;

	typedef typename std::conditional<
		std::is_const<Container>::value,
		typename Container::const_reference,
		typename Container::reference
	>::type reference;

	typedef typename std::conditional<
		std::is_const<Container>::value,
		typename Container::const_iterator,
		typename Container::iterator
	>::type iterator;
};

} // detail
} // pythonic
