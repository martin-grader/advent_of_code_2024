#include <gtest/gtest.h>

#include "puzzle_10/utils.hpp"

TEST(puzzle_10, test_sum_of_scores) {
    std::vector<std::string> puzzle = {
        {"89010123"}, {"78121874"}, {"87430965"}, {"96549874"}, {"45678903"}, {"32019012"}, {"01329801"}, {"10456732"},
    };
    const int sum_of_scores = get_sum_of_scores(puzzle);
    EXPECT_EQ(sum_of_scores, 36);
}
