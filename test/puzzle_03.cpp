#include "array"
#include "puzzle_03/utils.hpp"
#include "vector"
#include <gtest/gtest.h>

TEST(puzzle_02, test_calculation) {
    std::string puzzle = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
    const int sum = get_calculation_result(puzzle);
    EXPECT_EQ(sum, 161);
}

TEST(puzzle_02, test_accurate_calculation) {
    std::string puzzle = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    const int sum = get_accurate_calculation_results(puzzle);
    EXPECT_EQ(sum, 48);
}
