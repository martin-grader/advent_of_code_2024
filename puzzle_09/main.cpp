#include <iostream>
#include <string>

#include "puzzle_09/puzzle.hpp"
#include "puzzle_09/utils.hpp"

int main() {
    const std::string puzzle = get_puzzle();
    const long int checksum = get_checksum(puzzle);
    std::cout << "checksum = " << checksum << std::endl;
    // 6323903789307 is wrong
    return 0;
}
