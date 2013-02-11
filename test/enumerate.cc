#include <gtest/gtest.h>

#include "pythonic/enumerate.h"

using namespace pythonic;

TEST(Enumerate, Simple)
{
	std::vector<int> vec(10, 42);

	for (int probe : std::vector<int> {0, -1337, 42}) {
		for (auto v : enumerate(vec, probe)) {
			ASSERT_EQ(probe++, v.first);
			ASSERT_EQ(42, v.second);
		}
	}
}

TEST(Enumerate, Const)
{
	std::vector<int> vec(10, 42);
	auto const& ref = vec;
	int probe;

	probe = 0;
	for (auto v : enumerate(ref)) {
		ASSERT_EQ(probe++, v.first);
		ASSERT_EQ(42, v.second);
	}

	probe = 0;
	for (auto const& v : enumerate(ref)) {
		ASSERT_EQ(probe++, v.first);
		ASSERT_EQ(42, v.second);
	}
}

TEST(Enumerate, RValue)
{
	int probe = 0;
	for (auto const& v : enumerate(std::vector<int> (10, 42))) {
		ASSERT_EQ(probe++, v.first);
		ASSERT_EQ(42, v.second);
	}
}
