#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>

#include "puzzle_19/utils.hpp"

TEST(ProgramTest, test_execution) {
    std::vector<std::string> patterns{"r", "wr", "b", "g", "bwu", "rb", "gb", "br"};
    std::vector<std::string> designs{
        "brwrr", "bggr", "gbbr", "rrbgbr", "ubwu", "bwurrg", "brgr", "bbrgwb",
        //"brwrr",
    };
    Onsen o(patterns);
    EXPECT_EQ(o.get_number_of_possible_designs(designs), 6);
}
