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

// allow access via first & second if two containers are zipped
template<typename ... T>
struct zip_tuple
{
	typedef std::tuple<T...> type;
};

template<typename T0, typename T1>
struct zip_tuple<T0, T1>
{
	typedef std::pair<T0, T1> type;
};


template<typename ... Containers>
struct zip_iterator :
	public boost::iterator_facade<
		zip_iterator<Containers...>,
		typename zip_tuple<typename traits<Containers>::reference ...>::type,
		boost::incrementable_traversal_tag,
		typename zip_tuple<typename traits<Containers>::reference ...>::type
	>
{
public:
	typedef typename zip_tuple<typename
		traits<Containers>::reference ...>::type reference;
	typedef typename zip_tuple<typename std::add_const<typename
		traits<Containers>::reference>::type ...>::type const_reference;

	zip_iterator(typename traits<Containers>::iterator ... its)
		: its(its...)
	{}

private:
	friend class boost::iterator_core_access;

	bool equal(zip_iterator<Containers...> const& rhs) const
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
		zip_iterator<Containers...> const& rhs,
		pack<Ns...> const&) const
	{
		return sum<size_t>(std::get<Ns>(its) == std::get<Ns>(rhs.its)...);
	}

	typename zip_tuple<typename traits<Containers>::iterator ...>::type its;
};


template<typename ... Containers>
class zip_proxy
{
public:
	typedef size_t size_type;
	typedef zip_iterator<typename
		std::remove_reference<Containers>::type...> iterator;
	typedef zip_iterator<typename std::add_const<typename
		std::remove_reference<Containers>::type>::type ...> const_iterator;
	typedef typename iterator::reference reference;
	typedef typename iterator::const_reference const_reference;

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
