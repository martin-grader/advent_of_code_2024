#include <iostream>

#include "puzzle_07/puzzle.hpp"
#include "puzzle_07/utils.hpp"

int main() {
    const puzzle_type puzzle = get_puzzle();
    const long int calibration_result = get_calibration_result(puzzle);
    std::cout << "calibration_result = " << calibration_result << std::endl;
    return 0;
}
