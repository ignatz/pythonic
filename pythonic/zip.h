#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

#include "pythonic/detail/zip.h"

namespace pythonic {

template<typename ... Containers>
detail::zip_proxy<Containers ...> zip(Containers&& ... cs)
{
	return detail::zip_proxy<Containers...>(
		std::forward<Containers>(cs)...);
}

} // pythonic
