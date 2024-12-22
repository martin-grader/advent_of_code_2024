#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>

#include "puzzle_17/utils.hpp"

TEST(ProgramTest, test_execution) {
    std::map<char, size_t> reg{{'A', 729}, {'B', 0}, {'C', 0}};
    std::vector<size_t> program{0, 1, 5, 4, 3, 0};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_output(), "4,6,3,5,6,3,5,2,1,0");
}

TEST(ProgramTest, example1) {
    std::map<char, size_t> reg{{'A', 0}, {'B', 0}, {'C', 9}};
    std::vector<size_t> program{2, 6};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_reg('B'), 1);
}

TEST(ProgramTest, example2) {
    std::map<char, size_t> reg{{'A', 10}, {'B', 0}, {'C', 9}};
    std::vector<size_t> program{5, 0, 5, 1, 5, 4};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_output(), "0,1,2");
}

TEST(ProgramTest, example3) {
    std::map<char, size_t> reg{{'A', 2024}, {'B', 0}, {'C', 9}};
    std::vector<size_t> program{0, 1, 5, 4, 3, 0};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_output(), "4,2,5,6,7,7,7,7,3,1,0");
    EXPECT_EQ(c.get_reg('A'), 0);
}
TEST(ProgramTest, example4) {
    std::map<char, size_t> reg{{'A', 0}, {'B', 29}, {'C', 9}};
    std::vector<size_t> program{1, 7};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_reg('B'), 26);
}
TEST(ProgramTest, example5) {
    std::map<char, size_t> reg{{'A', 0}, {'B', 2024}, {'C', 43690}};
    std::vector<size_t> program{4, 0};
    Computer c(reg);
    c.execute(program);
    EXPECT_EQ(c.get_reg('B'), 44354);
}
