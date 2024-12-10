#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

typedef std::vector<std::tuple<long int, std::vector<long int>>> puzzle_type;

enum class MathOp {
    add,
    multiply,
};

class Calculator {
  public:
    Calculator(const std::vector<long int> &calculation_data, std::string &calculation_signs)
        : numbers(calculation_data), signs(calculation_signs) {
        result = numbers[0];
        numbers.erase(numbers.begin());
    };
    long int get_result() {
        do_calculation();
        return result;
    };

  private:
    long int result{};
    std::vector<long int> numbers{};
    std::string signs{};
    void do_calculation() {
        for (size_t i = 0; i < numbers.size(); i++) {
            if (signs[i] == '+') {
                result += numbers[i];
            } else if (signs[i] == '|') {
                std::string combination = std::to_string(result) + std::to_string(numbers[i]);
                result = std::stol(combination);
            } else {
                result *= numbers[i];
            }
        }
    };
};

class Calibrator {
  public:
    Calibrator(const std::vector<long int> &calibration_data) : calibration_data(calibration_data) {
        set_sign_permutations();
        set_calibration();
    };
    std::vector<long int> get_calibration() { return calibration; }

  private:
    std::vector<long int> calibration{};
    std::vector<long int> calibration_data{};
    std::vector<char> signs{'+', '*', '|'};
    std::vector<std::string> sign_permutations{};
    void set_sign_permutations() {
        size_t base_length = calibration_data.size() - 1;
        std::vector<std::string> permutation_bases = get_permutation_base(base_length, signs);

        for (std::string s : permutation_bases)
            do {
                sign_permutations.push_back(s);
            } while (std::next_permutation(s.begin(), s.end()));
    }
    void set_calibration() {
        for (std::string permutation : sign_permutations) {
            Calculator c(calibration_data, permutation);
            calibration.push_back(c.get_result());
        }
    };
    std::vector<std::string> get_permutation_base(size_t len, std::vector<char> signs) {
        std::vector<std::string> bases{};
        std::string s_or(len, signs[2]);
        bases.push_back(s_or);
        for (size_t i = 0; i < len; i++) {
            std::string s_or(i, signs[2]);
            for (size_t j = 0; j <= len - i; j++) {
                std::string s = s_or;
                std::string s_plus(len - i - j, signs[0]);
                std::string s_mul(j, signs[1]);
                s += s_mul + s_plus;
                std::sort(s.begin(), s.end());
                bases.push_back(s);
            }
        }
        return bases;
    }
};

class Device {
  public:
    Device(const std::vector<long int> &calibration_data, long int expected_calibration)
        : calibration_data(calibration_data), expected_calibration(expected_calibration){};
    bool is_calibrated() {
        check_calibration();
        return calibrated;
    };

  private:
    bool calibrated{false};
    std::vector<long int> calibration_data{};
    long int expected_calibration{};
    void check_calibration() {
        Calibrator c(calibration_data);
        for (long int possible_calibration : c.get_calibration()) {

            if (possible_calibration == expected_calibration) {
                calibrated = true;
                break;
            }
        }
    };
};

long int get_calibration_result(const puzzle_type &puzzle) {
    long int calibration_result{0};
    for (auto calibration : puzzle) {
        const long int calibration_expected = std::get<0>(calibration);
        Device d(std::get<1>(calibration), calibration_expected);
        if (d.is_calibrated()) {
            calibration_result += calibration_expected;
        }
    }
    return calibration_result;
}
