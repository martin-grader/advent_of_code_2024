#include "puzzle_04/utils.hpp"
#include <gtest/gtest.h>

TEST(puzzle_04, test_all_occurances) {
    std::vector<std::string> puzzle = {
        "MMMSXXMASM", "MSAMXMSMSA", "AMXSXMAAMM", "MSAMASMSMX", "XMASAMXAMM",
        "XXAMMXXAMA", "SMSMSASXSS", "SAXAMASAAA", "MAMMMXMMMM", "MXMXAXMASX",
    };
    int results = get_all_occurances(puzzle, "XMAS");
    EXPECT_EQ(results, 18);
}

TEST(puzzle_04, test_star_shaped_occurances) {
    std::vector<std::string> puzzle = {
        "MMMSXXMASM", "MSAMXMSMSA", "AMXSXMAAMM", "MSAMASMSMX", "XMASAMXAMM",
        "XXAMMXXAMA", "SMSMSASXSS", "SAXAMASAAA", "MAMMMXMMMM", "MXMXAXMASX",
    };
    int results = get_star_shaped_occurances(puzzle, "MAS");
    EXPECT_EQ(results, 9);
}
