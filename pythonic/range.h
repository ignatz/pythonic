#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

#include "pythonic/detail/range.h"

namespace pythonic {

detail::range_proxy<int>
range(int const end, int const step = 1)
{
	return detail::range_proxy<int>(0, end, step);
}

detail::range_proxy<int>
range(int const start, int const end, int const step = 1)
{
	return detail::range_proxy<int>(start, end, step);
}

} // pythonic
