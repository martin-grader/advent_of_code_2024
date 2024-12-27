#include <gtest/gtest.h>
#include <vector>

#include "puzzle_18/utils.hpp"

class MazeTestSmall : public testing::Test

{
  public:
    void SetUp() override {
        maze = std::make_unique<Maze>(7, 7, puzzle, 12);
        maze->go();
    }
    std::vector<std::vector<size_t>> puzzle = {
        {5, 4}, {4, 2}, {4, 5}, {3, 0}, {2, 1}, {6, 3}, {2, 4}, {1, 5}, {0, 6}, {3, 3}, {2, 6}, {5, 1}, {1, 2},
        {5, 5}, {2, 5}, {6, 5}, {1, 4}, {0, 4}, {6, 4}, {1, 1}, {6, 1}, {1, 0}, {0, 5}, {1, 6}, {2, 0},
    };
    std::unique_ptr<Maze> maze;
};
TEST_F(MazeTestSmall, test_score) { EXPECT_EQ(maze->get_score(), 22); }
TEST_F(MazeTestSmall, test_blocking_tile) {
    Position blocking_tile_expected(1, 6);
    Position blocking_tile = maze->find_blocking_tile();
    blocking_tile.print();
    blocking_tile_expected.print();
    EXPECT_TRUE(blocking_tile == blocking_tile_expected);
}
