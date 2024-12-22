#include <map>
#include <vector>

std::map<char, size_t> get_reg() {
    std::map<char, size_t> reg{{'A', 30344604}, {'B', 0}, {'C', 0}};
    return reg;
};
std::vector<size_t> get_program() {
    std::vector<size_t> program = {2, 4, 1, 1, 7, 5, 1, 5, 4, 5, 0, 3, 5, 5, 3, 0};
    return program;
};
