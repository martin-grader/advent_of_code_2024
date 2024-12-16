#include "utils/position.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>

class Button {
  public:
    Button(){};
    Button(size_t dx, size_t dy, size_t cost) : delta({dx, dy}), cost(cost){};
    void push(Position &pos) {
        tokens_spent += cost;
        pos += delta;
    };
    void push(Position &pos, size_t times) {
        tokens_spent += times * cost;
        Position new_delta(delta);
        new_delta *= times;
        pos += new_delta;
    };
    void reset() { tokens_spent = 0; };
    size_t get_tokens_spent() const { return tokens_spent; };
    size_t get_dx() const { return delta[0]; };
    size_t get_dy() const { return delta[1]; };
    size_t get_cost() const { return cost; };

  private:
    Position delta{};
    size_t cost;
    size_t tokens_spent{0};
};

class Claw {
  public:
    Claw(const Button &a, const Button &b, size_t price_x, size_t prize_y) : a(a), b(b), prize_pos(price_x, prize_y){};
    void push_a() { a.push(current_pos); };
    void push_b() { b.push(current_pos); };
    void push_a(size_t times) { a.push(current_pos, times); };
    void push_b(size_t times) { b.push(current_pos, times); };
    void reset() {
        a.reset();
        b.reset();
        current_pos.set_row(0);
        current_pos.set_column(0);
    }
    bool success() const { return current_pos == prize_pos; };
    bool not_finished() const { return current_pos < prize_pos; };
    size_t get_tokens_spent() const { return a.get_tokens_spent() + b.get_tokens_spent(); }
    size_t get_x() const { return prize_pos[0]; };
    size_t get_y() const { return prize_pos[1]; };
    size_t get_dx_a() const { return a.get_dx(); };
    size_t get_dy_a() const { return a.get_dy(); };
    size_t get_dx_b() const { return b.get_dx(); };
    size_t get_dy_b() const { return b.get_dy(); };
    size_t get_cost_a() const { return a.get_cost(); };
    size_t get_cost_b() const { return b.get_cost(); };

  private:
    Button a;
    Button b;
    Position current_pos;
    Position prize_pos;
};

size_t get_dx(const std::string &s) {
    auto idx1 = s.find("X+") + 2;
    auto idx2 = s.find(",");
    std::string dx = s.substr(idx1, idx2 - idx1);
    return std::stoi(dx);
}

size_t get_dy(const std::string &s) {
    auto idx1 = s.find("Y+") + 2;
    std::string dy = s.substr(idx1);
    return std::stoi(dy);
}
size_t get_prize_x(const std::string &s) {
    auto idx1 = s.find("X=") + 2;
    auto idx2 = s.find(",");
    std::string dx = s.substr(idx1, idx2 - idx1);
    return std::stoi(dx);
}

size_t get_prize_y(const std::string &s) {
    auto idx1 = s.find("Y=") + 2;
    std::string dy = s.substr(idx1);
    return std::stoi(dy);
}

size_t solve_brute_force(Claw &claw) {
    size_t min_tokens_spent = std::numeric_limits<size_t>::max();
    size_t pushes_a{1};
    size_t pushes_b{0};
    while (pushes_a > 0) {
        claw.push_b(pushes_b);
        pushes_a = 0;
        while (claw.not_finished()) {
            claw.push_a();
            pushes_a++;
        }
        if (claw.success() && pushes_a <= 100 && pushes_b <= 100) {
            min_tokens_spent = std::min(min_tokens_spent, claw.get_tokens_spent());
        }
        claw.reset();
        pushes_b++;
    }
    if (min_tokens_spent == std::numeric_limits<size_t>::max()) {
        min_tokens_spent = 0;
    }
    return min_tokens_spent;
}

std::array<size_t, 2> solve_2x2_matrix(const Claw &claw) {
    const double x{static_cast<double>(claw.get_x())};
    const double y = {static_cast<double>(claw.get_y())};
    const double dx_a = {static_cast<double>(claw.get_dx_a())};
    const double dx_b = {static_cast<double>(claw.get_dx_b())};
    const double dy_a = {static_cast<double>(claw.get_dy_a())};
    const double dy_b = {static_cast<double>(claw.get_dy_b())};
    const double pushes_b_f = (x - y * (dx_a / dy_a)) / (dx_b - dy_b * dx_a / dy_a);
    const double pushes_a_f = (x - dx_b * pushes_b_f) / dx_a;
    const size_t pushes_b = static_cast<size_t>(std::round(pushes_b_f));
    const size_t pushes_a = static_cast<size_t>(std::round(pushes_a_f));
    return {pushes_a, pushes_b};
}

size_t solve_clever(Claw &claw) {
    size_t min_tokens_spent{0};
    std::array<size_t, 2> pushes = solve_2x2_matrix(claw);
    claw.push_a(pushes[0]);
    claw.push_b(pushes[1]);
    if (claw.success()) {
        min_tokens_spent = pushes[0] * claw.get_cost_a() + pushes[1] * claw.get_cost_b();
    }
    return min_tokens_spent;
}

std::vector<Claw> get_claws_from_puzzle(const std::vector<std::string> &puzzle, size_t claw_offset) {
    std::vector<Claw> claw_machines{};
    for (size_t i = 0; i < puzzle.size(); i += 4) {
        Button a(get_dx(puzzle[i]), get_dy(puzzle[i]), 3);
        Button b(get_dx(puzzle[i + 1]), get_dy(puzzle[i + 1]), 1);
        Claw c(a, b, get_prize_x(puzzle[i + 2]) + claw_offset, get_prize_y(puzzle[i + 2]) + claw_offset);
        claw_machines.push_back(c);
    }
    return claw_machines;
}

size_t solve_puzzle_brute_force(const std::vector<std::string> &puzzle, size_t claw_offset = 0) {
    size_t tokens_spent = 0;
    std::vector<Claw> claw_machines = get_claws_from_puzzle(puzzle, claw_offset);
    for (size_t i = 0; i < claw_machines.size(); i++) {
        tokens_spent += solve_brute_force(claw_machines[i]);
    }

    return tokens_spent;
}

size_t solve_puzzle_clever(const std::vector<std::string> &puzzle, size_t claw_offset = 0) {
    size_t tokens_spent = 0;
    std::vector<Claw> claw_machines = get_claws_from_puzzle(puzzle, claw_offset);

    for (size_t i = 0; i < claw_machines.size(); i++) {
        tokens_spent += solve_clever(claw_machines[i]);
    }
    return tokens_spent;
}
