#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

class Landscape {
  public:
    Landscape(const std::vector<std::string> puzzle) : map(puzzle){};
    void go_hiking() {
        trailheads = map.get_all_occurances('0');
        for (const Position &start : trailheads) {
            TargetMoverManager m(start, map, '9');
            while (!m.all_finished()) {
                m.advance();
            }
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{0};
        for (const TargetMoverManager &m : managers) {
            score += get_score(m.get_succeeded_movers());
        }
        return score;
    };
    size_t get_rating() {
        size_t rating{0};
        for (const TargetMoverManager &m : managers) {
            rating += m.get_number_of_succeeded_movers();
        }
        return rating;
    };

  private:
    Map<char> map;
    std::vector<Position> trailheads{};
    std::vector<TargetMoverManager> managers{};
    size_t get_score(const std::vector<TargetMover> &succeeded_hikers) const {
        size_t score{0};
        std::vector<Position> destinations;
        for (const TargetMover &h : succeeded_hikers) {
            Position des = h.get_position();
            if (std::find(destinations.begin(), destinations.end(), des) == destinations.end()) {
                score++;
                destinations.push_back(des);
            }
        }
        return score;
    }
};
