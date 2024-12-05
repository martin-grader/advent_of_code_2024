#include <iostream>
#include "puzzle_05/utils.hpp"

int main()
{
    std::vector<std::vector<int>> numbers = get_input_numbers();
    std::vector<std::tuple<int,int>> order_rules = get_order_rules();
    const int result_sum = get_result(numbers, order_rules);
    std::cout << "result is " << result_sum << std::endl;
    return 0;
}
