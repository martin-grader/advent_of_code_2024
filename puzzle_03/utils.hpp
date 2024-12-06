#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> get_regex_matches(const std::string &s, const std::regex &expr) {
    std::vector<std::string> matches{};
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), expr);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        matches.push_back(match_str);
    }
    return matches;
}

int get_calculation_result(const std::string &puzzle) {
    int sum{0};
    std::regex word_regex("(mul\\(\\d+,\\d+\\))");
    std::vector<std::string> matches = get_regex_matches(puzzle, word_regex);
    for (std::string s : matches) {
        std::regex digits("(\\d+)");
        std::vector<std::string> digit_matches = get_regex_matches(s, digits);
        sum += std::stoi(digit_matches[0]) * std::stoi(digit_matches[1]);
    }
    return sum;
}

int get_accurate_calculation_results(const std::string &puzzle) {
    std::string s(puzzle);
    std::string::size_type dont_pos{0};
    while ((dont_pos = s.find("don't()")) != std::string::npos) {
        auto next_do_pos = s.find("do()", dont_pos);
        s.erase(dont_pos, next_do_pos - dont_pos + 4);
    }
    const int sum = get_calculation_result(s);
    return sum;
}
