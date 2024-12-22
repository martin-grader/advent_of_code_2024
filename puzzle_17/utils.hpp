#include <cassert>
#include <cmath>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::map<char, size_t> reg_type;

class Computer {
  public:
    Computer(const reg_type &reg) : reg(reg){};
    size_t get_reg(char reg_adr) { return reg[reg_adr]; };
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
    void dv(size_t input, char reg_adr) {
        reg[reg_adr] = trunc(static_cast<double>(reg['A']) / static_cast<double>(std::pow(2, input)));
    }
    void bxl(size_t input) { reg['B'] = input xor reg['B']; };
    void bxc(size_t input) { reg['B'] = reg['B'] xor reg['C']; };
    void bst(size_t input) { reg['B'] = input % 8; };
    void jnz(size_t input, size_t &p) {
        if (reg['A'] == 0) {
            return;
        } else {
            p = input - 2;
            // p = input;
        }
    };
    void out(size_t input) { output.push_back(input % 8); };
};
