#include <cmath>
#include <algorithm>
#include "ordering.hpp"
#include "numbers.hpp"


std::vector<std::tuple<int,int>> get_relevant_order_rules(std::vector<int>& unordered_numbers, std::vector<std::tuple<int,int>>& order_rules)
{
    std::vector<std::tuple<int,int>> relevant_order_rules{};
    for (auto [first, second] : order_rules)
    {
        const bool first_found = std::find(unordered_numbers.begin(), unordered_numbers.end(), first) != unordered_numbers.end();
        const bool second_found = std::find(unordered_numbers.begin(), unordered_numbers.end(), second) != unordered_numbers.end();
        if (first_found && second_found)
        {
            relevant_order_rules.push_back({first, second});
        }
    }
    return relevant_order_rules;
}

std::vector<int> get_ordered_numbers(std::vector<int>& unordered_numbers, std::vector<std::tuple<int,int>>& order_rules)
{
    std::vector<int> ordered_numbers(unordered_numbers.size(),0);
    std::vector<std::tuple<int,int>> relevant_order_rules = get_relevant_order_rules(unordered_numbers, order_rules);
    for (int number : unordered_numbers)
    {
        int number_position{0};
        for (auto [first, second] : relevant_order_rules)
        {
            if (second == number)
            {
                number_position++;
            }
        }
        ordered_numbers[number_position] = number;
    }
    return ordered_numbers;
}


int get_result(std::vector<std::vector<int>>& unordered_numbers, std::vector<std::tuple<int,int>>& order_rules)
{
    int result_sum{0};
    for (std::vector<int> number_list : unordered_numbers)
    {
        std::vector<int> ordered_numbers= get_ordered_numbers(number_list, order_rules); 
        if (std::equal(number_list.begin(), number_list.end(), ordered_numbers.begin()))
        {    
            const int idx_mid = std::floor(ordered_numbers.size()/2);
            result_sum += ordered_numbers[idx_mid];
        }
    }
    return result_sum;
}
