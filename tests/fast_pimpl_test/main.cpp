#include "book.h"
#include "example.h"

#include <gtest/gtest.h>

namespace
{

int constexpr lhs = 10;
int constexpr rhs = 10;
static_assert(tiny_utils::is_same_number_v<lhs, rhs>, "");

int constexpr n = 999;
static_assert(tiny_utils::strings_equal(tiny_utils::numeric_string_t<n>().data(), "999"), "");

struct TestSuite : testing::TestWithParam<int>
{
};

struct TestCharSuite : testing::TestWithParam<char>
{
};

} // namespace

TEST_P(TestSuite, Init) // NOLINT
{
    int const x = GetParam();
    example_t const example(x);

    EXPECT_EQ(example.x(), x);
}

TEST_P(TestCharSuite, Init) // NOLINT
{
    std::string const ch(1, GetParam());
    book_t const book(ch);
    EXPECT_EQ(book.contents(), ch);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(Test, TestSuite,
   testing::Range(95, 105)
);

INSTANTIATE_TEST_SUITE_P(Test, TestCharSuite,
   testing::Range('a', 'z')
);
// clang-format on

auto main(int argc, char ** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
