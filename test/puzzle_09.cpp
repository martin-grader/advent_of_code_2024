#include <gtest/gtest.h>

#include "puzzle_09/utils.hpp"

TEST(puzzle_09, test_checksum) {
    std::string puzzle = "2333133121414131402";
    const long int checksum = get_checksum(puzzle);
    EXPECT_EQ(checksum, 1928);
}
TEST(puzzle_09, test_updated_checksum) {
    std::string puzzle = "2333133121414131402";
    const long int checksum = get_updated_checksum(puzzle);
    EXPECT_EQ(checksum, 2858);
}
