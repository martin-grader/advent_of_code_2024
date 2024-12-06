#include "puzzle_03/puzzle.hpp"
#include "puzzle_03/utils.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::string puzzle = get_puzzle();
    const int sum = get_calculation_result(puzzle);
    std::cout << "sum = " << sum << std::endl;
    const int accurate_sum = get_accurate_calculation_results(puzzle);
    std::cout << "accurate_sum = " << accurate_sum << std::endl;
    return 0;
}
