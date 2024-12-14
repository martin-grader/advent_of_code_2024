#include "puzzle_11/utils.hpp"

stones ZeroStone::blink() const {
    std::shared_ptr<OddStone> st = std::make_shared<OddStone>(1);
    stones s{};
    s.push_back(std::make_shared<OddStone>(1));
    return s;
};

stones OddStone::blink() const {
    stones s{};
    add_stone(number * 2024, s);
    return s;
};

stones EvenStone::blink() const {
    stones s{};
    add_stone(number_1, s);
    add_stone(number_2, s);
    return s;
};

void StoneInterface::add_stone(size_t num, stones &stone_list) {
    if (num == 0) {
        std::shared_ptr<ZeroStone> s = std::make_shared<ZeroStone>();
        stone_list.push_back(std::make_shared<ZeroStone>());
    } else if (std::to_string(num).size() % 2 == 0) {
        std::shared_ptr<EvenStone> s = std::make_shared<EvenStone>(num);
        stone_list.push_back(std::make_shared<EvenStone>(num));
    } else {
        std::shared_ptr<OddStone> s = std::make_shared<OddStone>(num);
        stone_list.push_back(std::make_shared<OddStone>(num));
    }
};
