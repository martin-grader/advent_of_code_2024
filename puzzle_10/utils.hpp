#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

typedef std::vector<std::tuple<Position, Direction>> path;
class Navigator {
  public:
    Navigator(const Map<char> &map) : map(map){};
    std::vector<std::tuple<Position, Direction>> get_next_positions(const Position &pos) const {
        path neighbour_positions = get_neighbour_positions(pos);
        path allowed_next_positions = get_allowed_next_positions(pos, neighbour_positions);
        return allowed_next_positions;
    };

  private:
    Map<char> map;
    std::vector<Direction> neighbour_directions{Direction::left, Direction::top, Direction::right, Direction::bottom};
    path get_neighbour_positions(const Position &pos) const {
        path neighbour_positions{};
        for (Direction neighbour_direction : neighbour_directions) {
            Mover m(neighbour_direction);
            Position neighbour_position = m.get_next_position(pos);
            neighbour_positions.push_back({neighbour_position, neighbour_direction});
        }
        return neighbour_positions;
    }
    path get_allowed_next_positions(const Position &pos, const path &neighbour_positions) const {
        path allowed_next_positions{};
        for (auto [next_pos, d] : neighbour_positions) {
            if (is_possible_position(pos, next_pos)) {
                allowed_next_positions.push_back({pos, d});
            }
        }
        return allowed_next_positions;
    }
    bool is_possible_position(const Position &pos, const Position &next_pos) const {
        bool is_possible{false};
        if (map.is_inside(next_pos)) {
            const char elevation = map.get_entry(pos);
            const char next_elevation = map.get_entry(next_pos);
            const bool height_difference_ok = next_elevation == elevation + 1;
            is_possible = height_difference_ok;
        }
        return is_possible;
    }
};

class HikerManager {

  public:
    HikerManager(const Position &start_position, const Map<char> &map, char target_element)
        : map(map), tmf(map, target_element), navi(map) {
        TargetMover first_hiker = tmf.get_hiker(start_position, Direction::left);
        hikers.push_back(first_hiker);
    }
    void advance() {
        add_new_hikers();
        move_all_hikers();
    }
    bool all_finished() const {
        const bool all_finished = hikers.size() == finished_hikers;
        return all_finished;
    };
    size_t get_succeeded_hikers() const {
        size_t succeeded{0};
        for (const TargetMover &h : hikers) {
            if (h.success()) {
                succeeded++;
            }
        }
        return succeeded;
    }
    size_t get_score() const {
        size_t score{0};
        std::vector<Position> destinations;
        for (const TargetMover &h : hikers) {
            if (h.success()) {
                Position des = h.get_position();
                if (std::find(destinations.begin(), destinations.end(), des) == destinations.end()) {
                    score++;
                    destinations.push_back(des);
                }
            }
        }
        return score;
    }

  private:
    Map<char> map;
    TargetMoverFactory tmf;
    Navigator navi;

    size_t finished_hikers{0};
    std::vector<TargetMover> hikers{};
    std::vector<TargetMover> paths_finished{};
    void add_new_hikers() {
        std::vector<TargetMover> new_hikers{};
        for (TargetMover &h : hikers) {
            if (!h.is_finished()) {
                path next_positions = navi.get_next_positions(h.get_position());
                if (next_positions.size() == 0) {
                    h.set_finished();
                    finished_hikers++;
                } else {
                    h.set_direction(std::get<1>(next_positions[0]));

                    for (size_t i = 1; i < next_positions.size(); i++) {
                        TargetMover p_new = tmf.get_hiker(h.get_position(), std::get<1>(next_positions[i]));

                        new_hikers.push_back(p_new);
                    }
                }
            }
        }
        for (TargetMover nh : new_hikers) {
            hikers.push_back(nh);
        }
    }
    void move_all_hikers() {
        for (TargetMover &h : hikers) {
            if (!h.is_finished()) {
                h.move();
            }
        }
    }
};

class Landscape {
  public:
    Landscape(const std::vector<std::string> puzzle) : map(puzzle){};
    void go_hiking() {
        trailheads = map.get_all_occurances('0');
        for (const Position &start : trailheads) {
            HikerManager m(start, map, '9');
            while (!m.all_finished()) {
                m.advance();
            }
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{0};
        for (const HikerManager &m : managers) {
            score += m.get_score();
        }
        return score;
    };
    size_t get_rating() {
        size_t rating{0};
        for (const HikerManager &m : managers) {
            rating += m.get_succeeded_hikers();
        }
        return rating;
    };

  private:
    Map<char> map;
    std::vector<Position> trailheads{};
    std::vector<HikerManager> managers{};
};
