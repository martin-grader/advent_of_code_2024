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
    return 0;
}
