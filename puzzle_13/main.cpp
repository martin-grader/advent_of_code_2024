#include <iostream>
#include <vector>

#include "puzzle_13/puzzle.hpp"
#include "puzzle_13/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    const size_t tokens_spent = solve_puzzle_brute_force(puzzle);
    std::cout << "number of tokens spent = " << tokens_spent << std::endl;
    const size_t tokens_spent_costly = solve_puzzle_clever(puzzle, 10000000000000);
    std::cout << "number of costly tokens spent = " << tokens_spent_costly << std::endl;
    return 0;
}
