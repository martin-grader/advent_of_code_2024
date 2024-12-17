#include <iostream>
#include <string>
#include <vector>

#include "puzzle_14/puzzle.hpp"
#include "puzzle_14/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();

    Headquarter h(puzzle, 103, 101);
    h.calc_safety_factor(100);
    std::cout << "safety_factor = " << h.get_safety_factor() << std::endl;

    Headquarter ch(puzzle, 103, 101);
    std::cout << "christams_counts = " << ch.get_christms_tree_iterations() << std::endl;
    return 0;
}
