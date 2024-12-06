#include "array"
#include "puzzle_02/utils.hpp"
#include "vector"
#include <gtest/gtest.h>

TEST(puzzle_02, test_safe_reports) {
    std::vector<std::string> puzzle = {
        "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1", "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9",
    };
    const int safe_reports = get_safe_reports(puzzle);
    EXPECT_EQ(safe_reports, 2);
}

TEST(puzzle_02, test_safe_reports_with_tolerance) {
    std::vector<std::string> puzzle = {
        "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1", "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9",
    };
    const int safe_reports_with_tolerance = get_safe_reports_with_tolerance(puzzle);
    EXPECT_EQ(safe_reports_with_tolerance, 4);
}
