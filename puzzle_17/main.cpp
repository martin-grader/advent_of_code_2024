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
    c.print(program);
    InputFinderBruteForce i(c, program);
    // i.execute(); // duration 4.8h
    Computer com(reg);
    com.set_reg_a(164540892147389);
    // com.set_reg_a(164540892147645);
    // com.set_reg_a(164545992421053);
    // com.set_reg_a(164545992421309);
    // com.set_reg_a(164546059529917);
    // com.set_reg_a(164546059530173);
    com.execute(program);
    std::cout << "program = " << std::endl;
    com.print(program);
    std::cout << "program output = " << com.get_output() << std::endl;
    return 0;
}
