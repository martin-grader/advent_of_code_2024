#include <gtest/gtest.h>
#include <memory>

#include "puzzle_16/utils.hpp"

class MazeTestSmall : public testing::Test

{
  public:
    void SetUp() override {
        maze = std::make_unique<Maze>(puzzle);
        maze->go_raindeers();
    }
    std::vector<std::string> puzzle = {

        "###############", "#.......#....E#", "#.#.###.#.###.#", "#.....#.#...#.#", "#.###.#####.#.#",
        "#.#.#.......#.#", "#.#.#####.###.#", "#...........#.#", "###.#.#####.#.#", "#...#.....#.#.#",
        "#.#.#.###.#.#.#", "#.....#...#.#.#", "#.###.#.#.#.#.#", "#S..#.....#...#", "###############",
    };
    std::unique_ptr<Maze> maze;
};
TEST_F(MazeTestSmall, test_score) { EXPECT_EQ(maze->get_score(), 7036); }

class MazeTestBig : public testing::Test

{
  public:
    void SetUp() override {
        maze = std::make_unique<Maze>(puzzle);
        maze->go_raindeers();
    }
    std::vector<std::string> puzzle = {
        "#################", "#...#...#...#..E#", "#.#.#.#.#.#.#.#.#", "#.#.#.#...#...#.#", "#.#.#.#.###.#.#.#",
        "#...#.#.#.....#.#", "#.#.#.#.#.#####.#", "#.#...#.#.#.....#", "#.#.#####.#.###.#", "#.#.#.......#...#",
        "#.#.###.#####.###", "#.#.#...#.....#.#", "#.#.#.#####.###.#", "#.#.#.........#.#", "#.#.#.#########.#",
        "#S#.............#", "#################",
    };
    std::unique_ptr<Maze> maze;
};
TEST_F(MazeTestBig, test_score) { EXPECT_EQ(maze->get_score(), 11048); }
