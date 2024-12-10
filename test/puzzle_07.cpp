#include "array"
#include "puzzle_07/utils.hpp"
#include "tuple"
#include "vector"
#include <gtest/gtest.h>

TEST(puzzle_07, test_pussle0) {
    std::vector<std::tuple<long int, std::vector<long int>>> puzzle = {
        {190, {10, 19}},    {3267, {81, 40, 27}},    {83, {17, 5}},
        {156, {15, 6}},     {7290, {6, 8, 6, 15}},   {161011, {16, 10, 13}},
        {192, {17, 8, 14}}, {21037, {9, 7, 18, 13}}, {292, {11, 6, 16, 20}},
    };
    const long int result = get_calibration_result(puzzle);
    // EXPECT_EQ(result, 3749);
    EXPECT_EQ(result, 11387);
}
