#include <gtest/gtest.h>
#include <memory>

#include "puzzle_11/utils.hpp"

class StoneLineTest : public testing::Test

{
  public:
    void SetUp() override {
        stone_line = std::make_unique<StoneLine>(puzzle);
        stone_line->blinks(25);
        stone_line_fast = std::make_unique<StoneLineFast>(puzzle);
        stone_line_fast->blinks(25);
    }
    std::vector<size_t> puzzle = {125, 17};
    std::unique_ptr<StoneLine> stone_line;
    std::unique_ptr<StoneLineFast> stone_line_fast;
};
TEST_F(StoneLineTest, test_number_of_stones) { EXPECT_EQ(stone_line->get_number_of_stones(), 55312); }
TEST_F(StoneLineTest, test_number_of_stones_simple) { EXPECT_EQ(stone_line_fast->get_number_of_stones(), 55312); }
