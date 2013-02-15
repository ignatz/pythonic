#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

#include "pythonic/detail/enumerate.h"

namespace pythonic {

template<typename Container>
detail::enumerate_proxy<Container>
enumerate(Container&& a, int const start = 0)
{
	return detail::enumerate_proxy<Container>(
		std::forward<Container>(a), start);
}

template<typename ... Ts>
char enumerate(Ts&& ...)
{
	static_assert(sizeof...(Ts) != 1,
		"enumerate(T t) expects one instance t of container type T");
	return char();
}

} // pythonic
