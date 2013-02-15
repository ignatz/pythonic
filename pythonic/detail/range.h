#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

#include <boost/iterator/iterator_facade.hpp>
#include "pythonic/detail/util.h"

namespace pythonic {
namespace detail {

template<typename T>
struct const_range_iterator :
	public boost::iterator_facade<
		const_range_iterator<T>,
		T const,
		boost::incrementable_traversal_tag>
{
public:
	const_range_iterator(T const current, T const step)
		: current(current), step(step)
	{}

private:
	friend class boost::iterator_core_access;

	bool equal(const_range_iterator<T> const& other) const
	{
		return current == other.current;
	}

	void increment()
	{
		current += step;
	}

	T const&
	dereference() const
	{
		return current;
	}

	T current;
	T const step;
};


template<typename T>
class range_proxy
{
public:
	typedef size_t size_type;
	typedef const_range_iterator<T> iterator;
	typedef const_range_iterator<T> const_iterator;
	typedef typename std::add_const<T>::type& reference;
	typedef typename std::add_const<T>::type& const_reference;

	range_proxy(T start, T end, T step) :
		m_start(start), m_end(end), m_step(step)
	{}

	const_range_iterator<T> begin()
	{
		return const_range_iterator<T>(m_start, m_step);
	};

	const_range_iterator<T> end()
	{
		T last (m_end-sign(m_step));
		return const_range_iterator<T>(last - (last-m_start)%m_step, 0);
	};

private:
	T const m_start;
	T const m_end;
	T const m_step;
};

} // detail
} // pythonic
