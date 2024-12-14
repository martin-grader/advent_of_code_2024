#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class StoneInterface;
class ZeroStone;
class EvenStone;
class OddStone;

typedef std::vector<std::shared_ptr<StoneInterface>> stones;
typedef std::map<size_t, size_t> stone_map;

class StoneInterface {
  public:
    StoneInterface(size_t number) : number(number){};
    virtual stones blink() const = 0;
    virtual size_t get_size_after_blink() const = 0;
    static void add_stone(size_t number, stones &stone_list);

  protected:
    size_t number;
};

class ZeroStone : public StoneInterface {
  public:
    ZeroStone() : StoneInterface(0) {}
    stones blink() const override;
    size_t get_size_after_blink() const override { return 1; };
};

class EvenStone : public StoneInterface {
  public:
    EvenStone(size_t number) : StoneInterface(number) {
        std::string num = std::to_string(number);
        size_t half_length = num.size() / 2;
        std::string num_1 = num.substr(0, half_length);
        std::string num_2 = num.substr(half_length);
        number_1 = std::stoi(num_1);
        number_2 = std::stoi(num_2);
    }
    stones blink() const override;
    size_t get_size_after_blink() const override { return 2; };

  private:
    size_t number_1{};
    size_t number_2{};
};

class OddStone : public StoneInterface {
  public:
    OddStone(size_t number) : StoneInterface(number) {}
    stones blink() const override;
    size_t get_size_after_blink() const override { return 1; };
};

class StoneLine {
  public:
    StoneLine(const std::vector<size_t> &initial_line) {
        for (size_t number : initial_line) {
            StoneInterface::add_stone(number, line);
        }
    }
    void blinks(size_t n_of_blinks) {
        for (size_t i = 0; i < n_of_blinks; i++) {
            blink();
        }
    };
    size_t get_number_of_stones() { return line.size(); };

  private:
    void blink() {

        stones new_line;
        size_t n_new_stones = get_next_number_of_stones();
        new_line.reserve(n_new_stones);
        for (const std::shared_ptr<StoneInterface> &s : line) {
            for (std::shared_ptr<StoneInterface> new_stone : s->blink()) {
                new_line.push_back(new_stone);
            }
        }
        line = new_line;
    };
    stones line{};
    size_t get_next_number_of_stones() {
        size_t next_number_of_stones{0};
        for (const std::shared_ptr<StoneInterface> &s : line) {
            next_number_of_stones += s->get_size_after_blink();
        }
        return next_number_of_stones;
    };
};
class StoneLineFast {
  public:
    StoneLineFast(const std::vector<size_t> &initial_line) {
        for (size_t s : initial_line) {
            line[s] += 1;
        }
    }
    void blinks(size_t n_of_blinks) {
        for (size_t i = 0; i < n_of_blinks; i++) {
            blink();
        }
    };
    size_t get_number_of_stones() {
        size_t n_stones{0};
        for (const auto &[s, num] : line) {
            n_stones += num;
        }

        return n_stones;
    };

  private:
    void blink() {
        stone_map new_line;

        for (const auto &[s, num] : line) {
            if (s == 0) {
                new_line[1] += num;
            } else {
                const float log_10 = std::log10(s);
                const int digits = static_cast<int>(std::trunc(log_10)) + 1;
                if (digits % 2 == 0) {
                    const int helper = std::pow(10, digits / 2);
                    const int first_part = static_cast<int>(std::trunc(s / helper));
                    const int second_part = s - first_part * helper;
                    new_line[first_part] += num;
                    new_line[second_part] += num;
                } else {
                    new_line[s * 2024] += num;
                }
            }
        }
        line = new_line;
    };
    stone_map line{};
};
