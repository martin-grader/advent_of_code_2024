#include <iostream>
#include <string>
#include <vector>

#include "puzzle_18/puzzle.hpp"
#include "puzzle_18/utils.hpp"

int main() {
    const std::vector<std::vector<size_t>> puzzle = get_puzzle();
    Maze maze(71, 71, puzzle, 1024);
    maze.go();
    std::cout << "minimum_number_of_steps = " << maze.get_score() << std::endl;
    std::cout << "first unpassable tile (row, col) = " << std::endl;
    Position blocking_tile = maze.find_blocking_tile();
    blocking_tile.print();
    return 0;
}
