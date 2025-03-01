#include <gtest/gtest.h>

#include "puzzle_12/utils.hpp"

TEST(GardenTest, test_fence_costs_1) {
    std::vector<std::string> puzzle = {
        {"AAAA"},
        {"BBCD"},
        {"BBCC"},
        {"EEEC"},
    };
    Garden garden(puzzle);
    garden.print();
    EXPECT_EQ(garden.get_fence_costs(), 140);
    EXPECT_EQ(garden.get_fence_bulk_discount_costs(), 80);
}
TEST(GardenTest, test_fence_costs_2) {
    std::vector<std::string> puzzle = {
        {"OOOOO"}, {"OXOXO"}, {"OOOOO"}, {"OXOXO"}, {"OOOOO"},
    };
    Garden garden(puzzle);
    garden.print();
    EXPECT_EQ(garden.get_fence_costs(), 772);
    EXPECT_EQ(garden.get_fence_bulk_discount_costs(), 436);
}
TEST(GardenTest, test_fence_costs_3) {
    std::vector<std::string> puzzle = {
        {"RRRRIICCFF"}, {"RRRRIICCCF"}, {"VVRRRCCFFF"}, {"VVRCCCJFFF"}, {"VVVVCJJCFE"},
        {"VVIVCCJJEE"}, {"VVIIICJJEE"}, {"MIIIIIJJEE"}, {"MIIISIJEEE"}, {"MMMISSJEEE"},

    };
    Garden garden(puzzle);
    garden.print();
    EXPECT_EQ(garden.get_fence_costs(), 1930);
    EXPECT_EQ(garden.get_fence_bulk_discount_costs(), 1206);
}
TEST(GardenTest, test_fence_costs_4) {
    std::vector<std::string> puzzle = {
        {"EEEEE"}, {"EXXXX"}, {"EEEEE"}, {"EXXXX"}, {"EEEEE"},
    };
    Garden garden(puzzle);
    garden.print();
    EXPECT_EQ(garden.get_fence_bulk_discount_costs(), 236);
}
TEST(GardenTest, test_fence_costs_5) {
    std::vector<std::string> puzzle = {
        {"AAAAAA"}, {"AAABBA"}, {"AAABBA"}, {"ABBAAA"}, {"ABBAAA"}, {"AAAAAA"},
    };
    Garden garden(puzzle);
    garden.print();
    EXPECT_EQ(garden.get_fence_bulk_discount_costs(), 368);
}
