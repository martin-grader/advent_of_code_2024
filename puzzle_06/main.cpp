#include <iostream>
#include <string>
#include <vector>

#include "puzzle_06/puzzle.hpp"
#include "puzzle_06/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    const int points_visited = get_points_visited(puzzle);
    std::cout << "points_visited = " << points_visited << std::endl;
    const int possible_obstructions = get_possible_obstructions(puzzle);
    std::cout << "possible_obstructions = " << possible_obstructions << std::endl;
    return 0;
}
