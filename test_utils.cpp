#include "gtest/gtest.h"
#include "utils.h"

using namespace stl;

#define EXPECT_EQ_PAIR(a, b, c) \
            EXPECT_EQ((a), (c).first_val); \
            EXPECT_EQ((b), (c).second_val);

class test_utils : public testing::Test
{
};

TEST_F(test_utils, TestDefaultConstructor)
{
	int a = 1;
	int b = 2;
	pair<int, int> p1;
	EXPECT_EQ_PAIR(0, 0, p1);

	pair<int, int> p2 (1, 2);
	EXPECT_EQ_PAIR(1, 2, p2);

	pair<int, int> p3 (a, b);
	EXPECT_EQ_PAIR(a, b, p3);

	pair<std::string, std::string> p4 ("hello", "world");
	EXPECT_EQ_PAIR("hello", "world", p4);

	pair<std::string, int> p5 ("hello", 1);
	EXPECT_EQ_PAIR("hello", 1, p5);

	pair<int, double> p6{ 42, 3.1415 };
	EXPECT_EQ_PAIR(42, 3.1415, p6);
}

TEST_F(test_utils, TestCopyConstructor)
{
	pair<int, int> p1 (1, 2);
	pair<int, int> p2 (p1);
	EXPECT_EQ_PAIR(1, 2, p2);

	pair<int, int> p3 = p1;
	EXPECT_EQ_PAIR(1, 2, p3);
}

TEST_F(test_utils, TestOperator)
{
	pair<int, int> p1 (1, 2);
	std::stringstream os;
	os << p1;
	EXPECT_EQ("1, 2\n", os.str ());

	pair<int, int> p2 (1, 2);
	EXPECT_EQ(p1, p2);

	pair<int, int> p3 (1, 3);
	EXPECT_NE(p1, p3);

	pair<int, int> p4 (2, 2);
	EXPECT_NE(p3, p4);

	EXPECT_GE(p4, p3);
	EXPECT_GE(p4, p4);

	EXPECT_GT(p4, p3);

	EXPECT_LE(p2, p3);
	EXPECT_LE(p2, p2);

	EXPECT_LE(p3, p4);
}

TEST_F(test_utils, TestMoveAndForward)
{
	std::string str = "Hello";
	std::vector<std::string> v;

	v.push_back (str);
	EXPECT_EQ("Hello", str);

	v.push_back (stl::move (str));
	EXPECT_EQ("", str);

	EXPECT_EQ("Hello", v[0]);
	EXPECT_EQ("Hello", v[1]);
	EXPECT_EQ(2, v.size ());
}