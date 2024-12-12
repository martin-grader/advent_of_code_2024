#include <iostream>
#include <string>
#include <vector>

#include "puzzle_10/puzzle.hpp"
#include "puzzle_10/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    Landscape land(puzzle);
    land.go_hiking();
    std::cout << "sum_of_scores = " << land.get_score() << std::endl;
    std::cout << "ratin  = " << land.get_rating() << std::endl;
    return 0;
}
