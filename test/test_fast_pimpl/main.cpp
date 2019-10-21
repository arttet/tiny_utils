#include "example.h"

#include <gtest/gtest.h>

struct test_suite_t : testing::TestWithParam<int>
{
};

TEST_P(test_suite_t, Init)
{
   int x = GetParam();
   example_t example(x);
   EXPECT_EQ(example.x(), x);
}

TEST_P(test_suite_t, Copy)
{
   int x = GetParam();
   example_t example(x);

   example_t copy(example);
   EXPECT_EQ(example.x(), copy.x());
}

// clang-format off

INSTANTIATE_TEST_CASE_P(Test, test_suite_t,
   testing::Range(0, 10)
);

// clang-format on

int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
