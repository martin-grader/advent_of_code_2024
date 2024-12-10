#include <iostream>
#include <string>
#include <vector>

#include "puzzle_02/puzzle.hpp"
#include "puzzle_02/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    const int safe_reports = get_safe_reports(puzzle);
    std::cout << "safe_reports = " << safe_reports << std::endl;
    const int safe_reports_with_tolerance = get_safe_reports_with_tolerance(puzzle);
    std::cout << "safe_reports_with_tolerance = " << safe_reports_with_tolerance << std::endl;
    return 0;
}
