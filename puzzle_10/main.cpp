#include <iostream>
#include <string>
#include <vector>

#include "puzzle_10/puzzle.hpp"
#include "puzzle_10/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    const int sum_of_scores = get_sum_of_scores(puzzle);
    std::cout << "sum_of_scores = " << sum_of_scores << std::endl;
    return 0;
}
