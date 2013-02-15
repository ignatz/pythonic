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
struct enumerate_iterator :
	public boost::iterator_facade<
		enumerate_iterator<Container>,
		std::pair<int, typename traits<Container>::reference>,
		boost::incrementable_traversal_tag,
		std::pair<int, typename traits<Container>::reference>
	>
{
public:
	enumerate_iterator(
		typename traits<Container>::iterator it,
		int const start = 0)
			: it(it), cnt(start)
	{}

private:
	friend class boost::iterator_core_access;

	typedef std::pair<
		int, typename traits<Container>::reference> reference;

	bool equal(enumerate_iterator<Container> const& other) const
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
	typedef size_t size_type;
	typedef enumerate_iterator<type> iterator;
	typedef enumerate_iterator<typename
		std::add_const<type>::type> const_iterator;
	typedef type& reference;
	typedef typename std::add_const<type>::type& const_reference;

	template<typename T>
	enumerate_proxy(T&& data, int const start = 0) :
		container(std::forward<T>(data)), start(start)
	{}

	enumerate_iterator<type> begin()
	{
		return enumerate_iterator<type>(container.begin(), start);
	};

	enumerate_iterator<type> end()
	{
		return enumerate_iterator<type>(container.end(), -1);
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
