#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::map<char, size_t> reg_type;

class Computer {
  public:
    Computer(const reg_type &reg) : reg(reg){};
    size_t get_reg(char reg_adr) { return reg[reg_adr]; };
    void set_reg_a(size_t input) { reg['A'] = input; };
    void execute(const std::vector<size_t> &program) {
        assert(program.size() % 2 == 0);
        for (size_t ip = 0; ip < program.size(); ip += 2) {
            const size_t opcode = program[ip];
            const size_t literal_operand = program[ip + 1];
            const size_t combo_operand = get_combo_operand(literal_operand);
            switch (opcode) {
            case 0:
                dv(combo_operand, 'A');
                break;
            case 1:
                bxl(literal_operand);
                break;
            case 2:
                bst(combo_operand);
                break;
            case 3:
                jnz(literal_operand, ip);
                break;
            case 4:
                bxc(combo_operand);
                break;
            case 5:
                out(combo_operand);
                break;
            case 6:
                dv(combo_operand, 'B');
                break;
            case 7:
                dv(combo_operand, 'C');
                break;
            }
        }
    }
    std::string get_output() const {
        std::ostringstream oss;

        if (!output.empty()) {
            std::copy(output.begin(), output.end() - 1, std::ostream_iterator<size_t>(oss, ","));

            oss << output.back();
        }
        return oss.str();
    };
    std::vector<size_t> get_result() const { return output; };
    void print(const std::vector<size_t> res) {
        std::ostringstream oss;

        if (!res.empty()) {
            std::copy(res.begin(), res.end(), std::ostream_iterator<size_t>(oss, ","));
        }
        std::cout << oss.str() << std::endl;
    };
    void reset() {
        reg = {{'A', 0}, {'B', 0}, {'C', 0}};
        output.clear();
    }

  private:
    reg_type reg;
    std::vector<size_t> output{};
    size_t get_combo_operand(size_t combo_operand) {
        if (combo_operand < 4) {
            return combo_operand;
        } else if (combo_operand == 4) {
            return reg['A'];
        } else if (combo_operand == 5) {
            return reg['B'];
        } else {
            return reg['C'];
        }
    }
    void dv(size_t input, char reg_adr) { reg[reg_adr] = reg['A'] >> input; }
    void bxl(size_t input) { reg['B'] = input xor reg['B']; };
    void bxc(size_t input) { reg['B'] = reg['B'] xor reg['C']; };
    void bst(size_t input) { reg['B'] = input & 7; };
    void jnz(size_t input, size_t &p) {
        if (reg['A'] == 0) {
            return;
        } else {
            p = input - 2;
        }
    };
    void out(size_t input) { output.push_back(input & 7); };
};

class InputFinderBruteForce {
  public:
    InputFinderBruteForce(const Computer &c, const std::vector<size_t> program) : c(c), program(program){};

    void execute() {
        std::vector<size_t> solutions{};
        auto t1 = std::chrono::high_resolution_clock::now();
        assert(program.size() == 16);
        const size_t start = std::pow(8, 15);
        size_t reg_a = 0;
        size_t reg_b = 0;
        size_t reg_c = 0;
        for (size_t i = 1; i < 8; i++) {
            const size_t this_start = start * i;
            const size_t this_end = start * (i + 1);

            // #pragma omp parallel for private(reg_a, reg_b, reg_c) firstprivate(program)
            for (size_t j = this_start; j < this_end; j++) {
                reg_a = j;
                reg_b = 0;
                reg_c = 0;
                for (const size_t &p : program) {
                    reg_b = reg_a & 7;
                    reg_b = 1 xor reg_b;
                    reg_c = reg_a >> reg_b;
                    reg_b = 5 xor reg_b;
                    reg_b = reg_b xor reg_c;
                    reg_a = reg_a >> 3;
                    if ((reg_b & 7) xor p) {
                        break;
                    }
                    if (&p == &program.back()) {
                        std::cout << j << std::endl;
                    }
                }
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto s_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << "duration [ms] = " << s_int.count() << std::endl;
    };

  private:
    Computer c;
    std::vector<size_t> program;
};

class InputFinderPrototype {
  public:
    InputFinderPrototype(const Computer &c, const std::vector<size_t> program) : c(c), program(program){};
    void execute() {
        std::vector<std::vector<size_t>> possible_solutions = get_possible_solutions_each_entry();
        assert(program.size() == possible_solutions.size());
        std::vector<size_t> current_solutions(possible_solutions[0]);
        std::vector<size_t> new_solutions{};
        for (size_t i = 1; i <= program.size() - 14; i++) {
            std::vector<size_t> program_to_compare(program.begin(), program.begin() + 1 + i);
            for (size_t lhs : current_solutions) {
                for (size_t rhs : possible_solutions[i]) {
                    const size_t rhs_shifted = rhs << (3 * i);
                    const size_t reg_a = lhs + rhs_shifted;
                    if (is_part_of_program(reg_a, program_to_compare)) {
                        new_solutions.push_back(reg_a);
                    }
                }
            }
            current_solutions = new_solutions;
            new_solutions.clear();
        }
    };

  private:
    Computer c;
    std::vector<size_t> program;
    size_t length{16};
    void print_bit(size_t to_print) {
        std::bitset<3 * 16> a{to_print};
        std::cout << a.to_string() << std::endl;
    }
    std::vector<size_t> output_finder(std::vector<size_t> out, size_t offset = 0, size_t base = 0) {
        std::vector<size_t> solutions{};
        for (size_t i = 0; i < 8; i++) {
            const size_t constant_part = i;
            for (size_t j = 0; j < 8; j++) {
                for (size_t k = 0; k < length - 1 - offset; k++) {
                    const size_t moving_part = j << 3 * (k + 1);
                    const size_t reg_a_raw = constant_part + moving_part;
                    const size_t reg_a = base xor (reg_a_raw);
                    if (is_part_of_program(reg_a, out)) {
                        solutions.push_back(reg_a);
                    }
                }
            }
        }
        return solutions;
    }
    std::vector<std::vector<size_t>> get_possible_solutions_each_entry() {
        std::vector<std::vector<size_t>> possible_solutions{};
        for (size_t i = 0; i < program.size(); i++) {
            std::cout << program[i] << std::endl;
            std::vector<size_t> this_solutions = output_finder({program[i]}, i);

            std::cout << this_solutions.size() << std::endl;
            possible_solutions.push_back(this_solutions);
        }
        return possible_solutions;
    };
    bool is_part_of_program(size_t reg_a, std::vector<size_t> out_expected) {
        bool is_part{false};
        c.reset();
        c.set_reg_a(reg_a);
        c.execute(program);
        std::vector<size_t> result = c.get_result();
        if (result.size() >= out_expected.size()) {
            if (std::equal(out_expected.begin(), out_expected.end(), result.begin())) {
                is_part = true;
            }
        }
        return is_part;
    }
};
