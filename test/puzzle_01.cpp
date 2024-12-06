#include "array"
#include "puzzle_01/utils.hpp"
#include "vector"
#include <gtest/gtest.h>

TEST(puzzle_01, test_distance) {
    std::vector<std::array<int, 2>> puzzle = {
        std::array<int, 2>{3, 4}, std::array<int, 2>{4, 3}, std::array<int, 2>{2, 5},
        std::array<int, 2>{1, 3}, std::array<int, 2>{3, 9}, std::array<int, 2>{3, 3},
    };
    int distance = get_distance(puzzle);
    EXPECT_EQ(distance, 11);
}

TEST(puzzle_01, test_similarity) {
    std::vector<std::array<int, 2>> puzzle = {
        std::array<int, 2>{3, 4}, std::array<int, 2>{4, 3}, std::array<int, 2>{2, 5},
        std::array<int, 2>{1, 3}, std::array<int, 2>{3, 9}, std::array<int, 2>{3, 3},
    };
    int similarity_score = get_similarity_score(puzzle);
    EXPECT_EQ(similarity_score, 31);
}
