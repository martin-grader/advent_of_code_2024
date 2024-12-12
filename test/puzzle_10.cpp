#include <gtest/gtest.h>
#include <memory>

#include "puzzle_10/utils.hpp"

class LandscapeTest : public testing::Test

{
  public:
    void SetUp() override {
        land = std::make_unique<Landscape>(puzzle);
        land->go_hiking();
    }
    std::vector<std::string> puzzle = {
        {"89010123"}, {"78121874"}, {"87430965"}, {"96549874"}, {"45678903"}, {"32019012"}, {"01329801"}, {"10456732"},
    };
    std::unique_ptr<Landscape> land;
};
TEST_F(LandscapeTest, test_sum_of_scores) { EXPECT_EQ(land->get_score(), 36); }
TEST_F(LandscapeTest, test_rating) { EXPECT_EQ(land->get_rating(), 81); }
