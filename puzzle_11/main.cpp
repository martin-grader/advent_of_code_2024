#include <iostream>
#include <vector>

#include "puzzle_11/puzzle.hpp"
#include "puzzle_11/utils.hpp"

int main() {
    const std::vector<size_t> puzzle = get_puzzle();
    StoneLine stone_line(puzzle);
    stone_line.blinks(25);
    std::cout << "number of stones after 25 blinks = " << stone_line.get_number_of_stones() << std::endl;
    StoneLineFast stone_line_fast(puzzle);
    stone_line_fast.blinks(75);
    std::cout << "number of stones after 75 blinks = " << stone_line_fast.get_number_of_stones() << std::endl;
    return 0;
}
