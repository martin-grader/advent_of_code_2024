#include <iostream>
#include <string>
#include <vector>

#include "puzzle_16/puzzle.hpp"
#include "puzzle_16/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    Maze maze(puzzle);
    maze.go_raindeers();
    std::cout << "sum_of_scores = " << maze.get_score() << std::endl;
    std::cout << "sum_of_best_tiles = " << maze.get_best_tiles() << std::endl;
    return 0;
}
