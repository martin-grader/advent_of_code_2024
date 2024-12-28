#include <gtest/gtest.h>

#include "utils/map.hpp"

class MapTest : public testing::Test

{
  public:
    void SetUp() override { map = std::make_unique<Map<char>>(rows, columns); }
    std::unique_ptr<Map<char>> map;
    size_t rows = 10;
    size_t columns = 20;
};
TEST_F(MapTest, test_rows) { EXPECT_EQ(map->rows, rows); }
TEST_F(MapTest, test_columns) { EXPECT_EQ(map->columns, columns); }
