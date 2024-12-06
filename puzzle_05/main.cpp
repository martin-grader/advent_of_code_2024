#include "puzzle_05/utils.hpp"
#include <iostream>

int main() {
    std::vector<std::vector<int>> numbers = get_input_numbers();
    std::vector<std::tuple<int, int>> order_rules = get_order_rules();
    const std::tuple<int, int> result_sum = get_result(numbers, order_rules);
    std::cout << "results correctly ordered is " << std::get<0>(result_sum) << std::endl;
    std::cout << "results wrongly ordered is " << std::get<1>(result_sum) << std::endl;
    return 0;
}
