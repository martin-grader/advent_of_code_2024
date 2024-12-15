#include "array"
#include <gtest/gtest.h>

#include "puzzle_06/utils.hpp"

TEST(puzzle_06, test_starting_position) {
    std::vector<std::string> puzzle = {
        "....#.....", ".........#", "..........", "..#.......", ".......#..",
        "..........", ".#..^.....", "........#.", "#.........", "......#...",
    };
    const Position sp = get_starting_position(puzzle);
    EXPECT_EQ(sp[0], 6);
    EXPECT_EQ(sp[1], 4);
}
TEST(puzzle_06, test_calculation) {
    std::vector<std::string> puzzle = {
        "....#.....", ".........#", "..........", "..#.......", ".......#..",
        "..........", ".#..^.....", "........#.", "#.........", "......#...",
    };
    const int points_visited = get_points_visited(puzzle);
    EXPECT_EQ(points_visited, 41);
}
TEST(puzzle_06, test_obstructions) {
    std::vector<std::string> puzzle = {
        "....#.....", ".........#", "..........", "..#.......", ".......#..",
        "..........", ".#..^.....", "........#.", "#.........", "......#...",
    };
    const int obstructions = get_possible_obstructions(puzzle);
    EXPECT_EQ(obstructions, 6);
}
