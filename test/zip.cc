#include <gtest/gtest.h>

#include "pythonic/zip.h"

#define UNUSED(x) static_cast<void>(x)

using namespace pythonic;

TEST(Zip, Simple)
{
	std::vector<int> vec0(10, 42);
	std::vector<int> vec1(10, 5);

	for(auto v : zip(vec0, vec1)) {
		ASSERT_EQ(42, std::get<0>(v));
		ASSERT_EQ(42, v.first);  // special case for 2 containers
		ASSERT_EQ( 5, std::get<1>(v));
		ASSERT_EQ( 5, v.second); // special case for 2 containers
	}
}

TEST(Zip, Const)
{
	std::vector<int> vec0(10, 42);
	std::vector<int> const& ref = vec0;
	for(auto v : zip(vec0, ref)) {
		ASSERT_EQ(42, std::get<0>(v));
		ASSERT_EQ(42, std::get<1>(v));
	}
}

TEST(Zip, Empty)
{
	for(auto v : zip()) {
		UNUSED(v);
		ASSERT_TRUE(false);
	}
}

#ifndef PYTHONIC_SAFE_ZIP
TEST(Zip, VariableLength)
{
	std::vector<int> vec0(10, 42);
	std::vector<int> vec_long(100, 5);
	size_t cnt = 0;
	for(auto v : zip(vec0, vec_long)) {
		ASSERT_EQ(42, std::get<0>(v));
		ASSERT_EQ( 5, std::get<1>(v));
		cnt++;
	}
	ASSERT_EQ(vec0.size(), cnt);
}
#endif
