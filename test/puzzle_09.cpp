#include <gtest/gtest.h>

#include "puzzle_09/utils.hpp"

TEST(puzzle_09, test_checksum) {
    std::string puzzle = "2333133121414131402";
    const long int checksum = get_checksum(puzzle);
    EXPECT_EQ(checksum, 1928);
}
// TEST(puzzle_09, test_reorder) {
// std::string puzzle = "00...111...2...333.44.5555.6666.777.888899";
// const std::string compressed_disk_content = compress_disk_content(puzzle);
// EXPECT_EQ(compressed_disk_content, "0099811188827773336446555566");
//}
