#include <gtest/gtest.h>

#include "puzzle_14/utils.hpp"

TEST(RobotTest, test_safety_factor) {
    std::vector<std::string> puzzle = {
        "p=0,4 v=3,-3",  "p=6,3 v=-1,-3", "p=10,3 v=-1,2", "p=2,0 v=2,-1", "p=0,0 v=1,3",  "p=3,0 v=-2,-2",
        "p=7,6 v=-1,-3", "p=3,0 v=-1,-2", "p=9,3 v=2,3",   "p=7,3 v=-1,2", "p=2,4 v=2,-3", "p=9,5 v=-3,-3",
    };
    Headquarter h(puzzle, 7, 11);
    h.calc_safety_factor(100);
    EXPECT_EQ(h.get_safety_factor(), 12);
}
