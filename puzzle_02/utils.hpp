#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> string_to_int_vector(const std::string &s) {
    std::vector<int> int_vector{};
    std::istringstream iss(s);
    int num{};
    while (iss >> num) {
        int_vector.push_back(num);
    }
    return int_vector;
}

bool all_greater_zero(const std::vector<int> &v) {
    auto iter = std::find_if(v.begin(), v.end(), [&](int elem) { return elem <= 0; });
    const bool all_greater_zero = iter == v.end();
    return all_greater_zero;
}
bool all_less_zero(const std::vector<int> &v) {
    auto iter = std::find_if(v.begin(), v.end(), [&](int elem) { return elem >= 0; });
    const bool all_greater_zero = iter == v.end();
    return all_greater_zero;
}

bool max_difference_within_limits(const std::vector<int> &v) {
    int max_diff{0};
    for (int i : v) {
        max_diff = std::max(max_diff, std::abs(i));
    }
    return max_diff < 4;
}

bool is_safe(const std::vector<int> &r) {
    std::vector<int> report(r);
    std::adjacent_difference(report.begin(), report.end(), report.begin());
    report.erase(report.begin());
    const bool increasing = all_greater_zero(report);
    const bool decreasing = all_less_zero(report);
    const bool limits_met = max_difference_within_limits(report);
    const bool is_safe = (increasing || decreasing) && limits_met;
    return is_safe;
}

int get_safe_reports(const std::vector<std::string> &puzzle) {
    int safe_reports{};
    for (std::string report : puzzle) {
        std::vector<int> numeric_report = string_to_int_vector(report);
        if (is_safe(numeric_report)) {
            safe_reports++;
        }
    }
    return safe_reports;
}

int get_safe_reports_with_tolerance(const std::vector<std::string> &puzzle) {
    int safe_reports{};
    for (std::string report : puzzle) {
        std::vector<int> numeric_report = string_to_int_vector(report);
        if (is_safe(numeric_report)) {
            safe_reports++;
        } else {
            for (long unsigned int i = 0; i < numeric_report.size(); i++) {
                std::vector<int> numeric_report_one_less(numeric_report);
                numeric_report_one_less.erase(numeric_report_one_less.begin() + i);
                if (is_safe(numeric_report_one_less)) {
                    safe_reports++;
                    break;
                }
            }
        }
    }
    return safe_reports;
}
