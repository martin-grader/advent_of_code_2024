#include <iostream>
#include <string>

#include "puzzle_09/puzzle.hpp"
#include "puzzle_09/utils.hpp"

int main() {
    const std::string puzzle = get_puzzle();
    const size_t checksum = get_checksum(puzzle);
    std::cout << "checksum = " << checksum << std::endl;
    const size_t updated_checksum = get_updated_checksum(puzzle);
    std::cout << "updated checksum = " << updated_checksum << std::endl;
    return 0;
}
