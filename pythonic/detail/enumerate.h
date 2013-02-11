#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>
#include <tuple>

#include <boost/iterator/iterator_facade.hpp>

#include "pythonic/detail/traits.h"

namespace pythonic {
namespace detail {

template<typename Container>
struct enum_pair_iter :
	public boost::iterator_facade<
		enum_pair_iter<Container>,
		std::pair<int, typename traits<Container>::reference>,
		boost::incrementable_traversal_tag,
		std::pair<int, typename traits<Container>::reference>
	>
{
public:
	enum_pair_iter(typename traits<Container>::iterator it, int const start = 0)
		: it(it), cnt(start)
	{}

private:
	friend class boost::iterator_core_access;

	typedef std::pair<int, typename traits<Container>::reference
		> reference;

	bool equal(enum_pair_iter<Container> const& other) const
	{
		return it == other.it;
	}

	void increment()
	{
		++it;
		++cnt;
	}

	reference
	dereference() const
	{
		return reference(cnt, *it);
	}

	typename traits<Container>::iterator  it;
	int cnt;
};


template<typename Container>
struct enumerate_proxy
{
private:
	typedef typename std::remove_reference<Container>::type type;

public:
	template<typename T>
	enumerate_proxy(T&& data, int const start = 0) :
		container(std::forward<T>(data)), start(start)
	{}

	typename type::size_type size() const
	{
		return container.size();
	}

	enum_pair_iter<type> begin()
	{
		return enum_pair_iter<type>(container.begin(), start);
	};

	enum_pair_iter<type> end()
	{
		return enum_pair_iter<type>(container.end(), -1);
	};

private:
	// if Container is passed by rvalue, move it here.
	// Otherwise, use the lvalue reference.
	typename std::conditional<
		std::is_rvalue_reference<Container&&>::value,
		type, type&>::type container;
	int const start;
};

} // detail
} // pythonic
