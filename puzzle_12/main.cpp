#include <iostream>
#include <string>
#include <vector>

#include "puzzle_12/puzzle.hpp"
#include "puzzle_12/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    Garden garden(puzzle);
    std::cout << "sum_of_scores = " << garden.get_fence_costs() << std::endl;
    std::cout << "sum_of_bilk_fence_scores = " << garden.get_fence_bulk_discount_costs() << std::endl;
    return 0;
}
