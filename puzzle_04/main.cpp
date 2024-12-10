#include <iostream>
#include <vector>

#include "puzzle_04/puzzle.hpp"
#include "puzzle_04/utils.hpp"

int main() {
    std::vector<std::string> puzzle = get_input_puzzle();
    const int xmas_occurances = get_all_occurances(puzzle, "XMAS");
    std::cout << "xmas occurances: " << xmas_occurances << std::endl;
    const int x_mas_occurances = get_star_shaped_occurances(puzzle, "MAS");
    std::cout << "x_mas occurances: " << x_mas_occurances << std::endl;
    return 0;
}
