#include <gtest/gtest.h>

#include "pythonic/range.h"
#include "pythonic/zip.h"
#include "pythonic/enumerate.h"

using namespace pythonic;
using namespace std;

int const last = 1337;

TEST(Range, Simple)
{
	vector<vector<int>> ranges {
		{ 0, 11, 1 },
		{ 0, 11, 2 },
		{ 0, 11, 3 },
		{-1, 11, 2 },
		{-1,-20,-1 },
		{-3,-20,-3 }
	};
	vector<vector<int>> expect {
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, last},
		{0, 2, 4, 6, 8, 10, last},
		{0, 3, 6, 9, last},
		{-1, 1, 3, 5, 7, 9, last},
		{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10,
			-11, -12, -13, -14, -15, -16, -17, -18, -19, last},
		{-3, -6, -9, -12, -15, -18, last}
	};

	int s = -10;
	for (auto const& r : range(-10, 20, 3))
	{
		ASSERT_EQ(s, r);
		s += 3;
	}

	for (auto const& v : zip(ranges, expect))
	{
		for (auto const& probe : enumerate(
			range(std::get<0>(v)[0], std::get<0>(v)[1], std::get<0>(v)[2])))
		{
			ASSERT_EQ(std::get<1>(v)[probe.first], probe.second);
		}
	}
}
