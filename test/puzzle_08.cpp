#include <gtest/gtest.h>

#include "puzzle_08/utils.hpp"

TEST(puzzle_08, test_antinodes) {
    std::vector<std::string> puzzle = {
        {"............"}, {"........0..."}, {".....0......"}, {".......0...."}, {"....0......."}, {"......A....."},
        {"............"}, {"............"}, {"........A..."}, {".........A.."}, {"............"}, {"............"},
    };
    const int antinodes = get_antinodes(puzzle);
    EXPECT_EQ(antinodes, 14);
}

TEST(puzzle_06, test_advanced_antinodes) {
    std::vector<std::string> puzzle = {
        {"............"}, {"........0..."}, {".....0......"}, {".......0...."}, {"....0......."}, {"......A....."},
        {"............"}, {"............"}, {"........A..."}, {".........A.."}, {"............"}, {"............"},
    };
    const int antinodes = get_advanced_antinodes(puzzle);
    EXPECT_EQ(antinodes, 34);
}
