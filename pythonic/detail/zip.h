#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>
#include <tuple>

#include <boost/iterator/iterator_facade.hpp>

#include "pythonic/detail/util.h"
#include "pythonic/detail/sequence.h"
#include "pythonic/detail/traits.h"

namespace pythonic {
namespace detail {

template<typename ... Containers>
struct zip_tuple_iter :
	public boost::iterator_facade<
		zip_tuple_iter<Containers...>,
		std::tuple<typename traits<Containers>::reference ...>,
		boost::incrementable_traversal_tag,
		std::tuple<typename traits<Containers>::reference ...>
	>
{
public:
	zip_tuple_iter(typename traits<Containers>::iterator ... its)
		: its(its...)
	{}

private:
	friend class boost::iterator_core_access;

	typedef std::tuple<typename
		traits<Containers>::reference ...> reference;

	bool equal(zip_tuple_iter<Containers...> const& rhs) const
	{
#ifdef PYTHONIC_SAFE_ZIP // safe_zip expects containers of equal length
		return its == rhs.its;
#else // unsafe zip, truncate to length of shortest container
		return equal_helper(rhs, typename sequence<Containers...>::type ());
#endif
	}

	void increment()
	{
		increment_helper(typename sequence<Containers...>::type ());
	}

	reference dereference() const
	{
		return dereference_helper(typename sequence<Containers...>::type ());
	}

	template<size_t ... Ns>
	reference dereference_helper(pack<Ns...> const&) const
	{
		return reference(*std::get<Ns>(its)...);
	}

	template<size_t ... Ns>
	void increment_helper(pack<Ns...> const&)
	{
		noop(++std::get<Ns>(its)...);
	}

	template<size_t ... Ns>
	bool equal_helper(
		zip_tuple_iter<Containers...> const& rhs,
		pack<Ns...> const&) const
	{
		return sum<size_t>(std::get<Ns>(its) == std::get<Ns>(rhs.its)...);
	}

	std::tuple<typename traits<Containers>::iterator ...> its;
};


template<typename ... Containers>
class zip_proxy
{
private:
	typedef zip_tuple_iter<typename
		std::remove_reference<Containers>::type...> iterator;

public:
	template<typename ... Ts>
	zip_proxy(Ts&& ... ts) :
		containers(std::forward<Ts>(ts)...)
	{}

	iterator begin()
	{
		return begin_helper(typename sequence<Containers...>::type ());
	};

	iterator end()
	{
		return end_helper(typename sequence<Containers...>::type ());
	};

private:
	template<size_t ... Ns>
	iterator begin_helper(pack<Ns...> const&)
	{
		return iterator(std::begin(std::get<Ns>(containers))...);
	}

	template<size_t ... Ns>
	iterator end_helper(pack<Ns...> const&)
	{
		return iterator(std::end(std::get<Ns>(containers))...);
	}

	// if Container is passed by rvalue, move it here.
	// Otherwise, use the lvalue reference.
	typename std::tuple<
		typename std::conditional<
			std::is_rvalue_reference<Containers&&>::value,
			typename std::remove_reference<Containers>::type,
			typename std::remove_reference<Containers>::type&
		>::type ...
	> containers;
};

// specialization for empty zip with always begin() == end()
template<>
struct zip_proxy<>
{
public:
	char const* begin() const { return nullptr; };
	char const* end() const { return nullptr; };
};

} // detail
} // pythonic
