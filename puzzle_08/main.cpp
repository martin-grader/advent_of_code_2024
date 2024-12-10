#include <iostream>
#include <string>
#include <vector>

#include "puzzle_08/puzzle.hpp"
#include "puzzle_08/utils.hpp"

int main() {
    const std::vector<std::string> puzzle = get_puzzle();
    const int antinodes = get_antinodes(puzzle);
    std::cout << "antinodes = " << antinodes << std::endl;
    const int antinodes_advanced = get_advanced_antinodes(puzzle);
    std::cout << "antinodes_advanced = " << antinodes_advanced << std::endl;
    return 0;
}
