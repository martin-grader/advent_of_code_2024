#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

class RaindeerNavigator : public Navigator<char> {
  public:
    RaindeerNavigator(const std::shared_ptr<Map<char>> map) : Navigator(map){};

  private:
    bool is_possible_position(const Position &pos, const Position &next_pos) const override {
        bool is_possible{false};
        if (map->is_inside(next_pos)) {
            const char elevation = map->get_entry(pos);
            const char next_elevation = map->get_entry(next_pos);
            const bool height_difference_ok = next_elevation == elevation + 1;
            is_possible = height_difference_ok;
        }
        return is_possible;
    }
};

class Landscape {
  public:
    Landscape(const std::vector<std::string> puzzle) : map(std::make_shared<Map<char>>(puzzle)){};
    void go_hiking() {
        trailheads = map->get_all_occurances('0');
        std::shared_ptr<Navigator<char>> navi = std::make_shared<RaindeerNavigator>(map);
        for (const Position &start : trailheads) {
            TargetMoverManager<char> m(start, map, '9', navi);
            while (!m.all_finished()) {
                m.advance();
            }
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{0};
        for (const TargetMoverManager<char> &m : managers) {
            score += get_score(m.get_succeeded_movers());
        }
        return score;
    };
    size_t get_rating() {
        size_t rating{0};
        for (const TargetMoverManager<char> &m : managers) {
            rating += m.get_number_of_succeeded_movers();
        }
        return rating;
    };

  private:
    std::shared_ptr<Map<char>> map;
    std::vector<Position> trailheads{};
    std::vector<TargetMoverManager<char>> managers{};
    size_t get_score(const std::vector<TargetMover<char>> &succeeded_hikers) const {
        size_t score{0};
        std::vector<Position> destinations;
        for (const TargetMover<char> &h : succeeded_hikers) {
            Position des = h.get_position();
            if (std::find(destinations.begin(), destinations.end(), des) == destinations.end()) {
                score++;
                destinations.push_back(des);
            }
        }
        return score;
    }
};
