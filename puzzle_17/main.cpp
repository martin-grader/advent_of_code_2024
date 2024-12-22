#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "puzzle_17/puzzle.hpp"
#include "puzzle_17/utils.hpp"

int main() {
    const std::map<char, size_t> reg = get_reg();
    const std::vector<size_t> program = get_program();

    Computer c(reg);
    c.execute(program);
    std::cout << "program output = " << c.get_output() << std::endl;
    // 0,7,2,6,4,2,7,2,5 wrong
    return 0;
}
