#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "puzzle_19/puzzle.hpp"
#include "puzzle_19/utils.hpp"

int main() {
    const std::vector<std::string> patterns = get_patterns();
    const std::vector<std::string> designs = get_designs();

    Onsen o(patterns);
    std::cout << "possible designs = " << o.get_number_of_possible_designs(designs) << std::endl;
    // 260 too low
    return 0;
}
