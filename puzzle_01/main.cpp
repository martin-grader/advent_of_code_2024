#include "puzzle_01/puzzle.hpp"
#include "puzzle_01/utils.hpp"
#include <array>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::array<int, 2>> puzzle = get_puzzle();
    const int distance = get_distance(puzzle);
    std::cout << "distance = " << distance << std::endl;
    const int similarity_score = get_similarity_score(puzzle);
    std::cout << "similarity_score = " << similarity_score << std::endl;
    return 0;
}
