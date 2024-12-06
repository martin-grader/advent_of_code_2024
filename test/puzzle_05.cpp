#include "puzzle_05/utils.hpp"
#include <gtest/gtest.h>

TEST(puzzle_05, test_example) {
    std::vector<std::vector<int>> numbers = {{75, 47, 61, 53, 29}, {97, 61, 53, 29, 13}, {75, 29, 13},
                                             {75, 97, 47, 61, 53}, {61, 13, 29},         {97, 13, 75, 29, 47}};
    std::vector<std::tuple<int, int>> order_rules = {
        {47, 53}, {97, 13}, {97, 61}, {97, 47}, {75, 29}, {61, 13}, {75, 53}, {29, 13}, {97, 29}, {53, 29}, {61, 53},
        {97, 53}, {61, 29}, {47, 13}, {75, 47}, {97, 75}, {47, 61}, {75, 61}, {47, 29}, {75, 13}, {53, 13},
    };
    std::tuple<int, int> results = get_result(numbers, order_rules);
    EXPECT_EQ(std::get<0>(results), 143);
    EXPECT_EQ(std::get<1>(results), 123);
}
