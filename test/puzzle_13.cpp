#include <gtest/gtest.h>

#include "puzzle_13/utils.hpp"

TEST(ClawContraptionTest, test_tokens_spent_brute_force) {
    std::vector<std::string> puzzle = {
        "Button A: X+94, Y+34", "Button B: X+22, Y+67", "Prize: X=8400, Y=5400",   "",
        "Button A: X+26, Y+66", "Button B: X+67, Y+21", "Prize: X=12748, Y=12176", "",
        "Button A: X+17, Y+86", "Button B: X+84, Y+37", "Prize: X=7870, Y=6450",   "",
        "Button A: X+69, Y+23", "Button B: X+27, Y+71", "Prize: X=18641, Y=10279",
    };
    const size_t tokens_spent = solve_puzzle_brute_force(puzzle);
    EXPECT_EQ(tokens_spent, 480);
}

TEST(ClawContraptionTest, test_tokens_spent_clever) {
    std::vector<std::string> puzzle = {
        "Button A: X+94, Y+34", "Button B: X+22, Y+67", "Prize: X=8400, Y=5400",   "",
        "Button A: X+26, Y+66", "Button B: X+67, Y+21", "Prize: X=12748, Y=12176", "",
        "Button A: X+17, Y+86", "Button B: X+84, Y+37", "Prize: X=7870, Y=6450",   "",
        "Button A: X+69, Y+23", "Button B: X+27, Y+71", "Prize: X=18641, Y=10279",
    };
    const size_t tokens_spent = solve_puzzle_clever(puzzle);
    EXPECT_EQ(tokens_spent, 480);
}
