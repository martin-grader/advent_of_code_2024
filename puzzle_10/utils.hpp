#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

class Navigator {
  public:
    Navigator(const Map &map, const position &pos) : map(map), pos(pos) {
        elevation = map.get_entry(pos);
        set_neighbour_positions();
        set_allowed_next_positions();
    };
    std::vector<std::tuple<position, Direction>> get_next_positions() { return allowed_next_positions; };

  private:
    Map map;
    position pos;
    char elevation;
    std::vector<Direction> neighbour_directions{Direction::left, Direction::top, Direction::right, Direction::bottom};
    std::vector<std::tuple<position, Direction>> neighbour_positions;
    std::vector<std::tuple<position, Direction>> allowed_next_positions;
    void set_neighbour_positions() {
        for (Direction neighbour_direction : neighbour_directions) {
            Mover m(neighbour_direction);
            position neighbour_position = m.get_next_position(pos);
            neighbour_positions.push_back({neighbour_position, neighbour_direction});
        }
    }
    void set_allowed_next_positions() {
        for (auto [pos, d] : neighbour_positions) {
            if (is_possible_position(pos)) {
                allowed_next_positions.push_back({pos, d});
            }
        }
    }
    bool is_possible_position(const position &pos) {
        bool is_possible{false};
        if (map.is_inside(pos)) {
            const char next_elevation = map.get_entry(pos);
            const bool height_difference_ok = next_elevation == elevation + 1;
            is_possible = height_difference_ok;
        }
        return is_possible;
    }
};

class Hiker : public Mover {
  public:
    Hiker(const position &start_pos, const Direction &start_dir, const Map &map)
        : Mover(start_dir, start_pos), map(map){};

    std::vector<position> get_path() const { return path; };
    void set_finished() { finished = true; };
    bool is_finished() const { return finished; };
    bool success() const { return map.get_entry(get_position()) == '9'; };
    void move() {
        if (!finished) {
            move_to_next_position();
            path.push_back(get_position());
        }
    };

  private:
    Map map;
    std::vector<position> path{};
    bool finished{false};
};

class HikerManager {

  public:
    HikerManager(const position &start_position, const Map &map) : map(map) {
        Hiker first_hiker(start_position, Direction::left, map);
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
        for (const Hiker &h : hikers) {
            if (h.success()) {
                succeeded++;
            }
        }
        return succeeded;
    }
    size_t get_score() const {
        size_t score{0};
        std::vector<position> destinations;
        for (const Hiker &h : hikers) {
            if (h.success()) {
                position des = h.get_position();
                if (std::find(destinations.begin(), destinations.end(), des) == destinations.end()) {
                    score++;
                    destinations.push_back(des);
                }
            }
        }
        return score;
    }

  private:
    Map map;
    size_t finished_hikers{0};
    std::vector<Hiker> hikers{};
    std::vector<Hiker> paths_finished{};
    void add_new_hikers() {
        std::vector<Hiker> new_hikers{};
        for (Hiker &h : hikers) {
            if (!h.is_finished()) {
                Navigator navi(map, h.get_position());
                std::vector<std::tuple<position, Direction>> next_positions = navi.get_next_positions();
                if (next_positions.size() == 0) {
                    h.set_finished();
                    finished_hikers++;
                } else {
                    h.set_direction(std::get<1>(next_positions[0]));

                    for (size_t i = 1; i < next_positions.size(); i++) {
                        Hiker p_new(h.get_position(), std::get<1>(next_positions[i]), map);

                        new_hikers.push_back(p_new);
                    }
                }
            }
        }
        for (Hiker nh : new_hikers) {
            hikers.push_back(nh);
        }
    }
    void move_all_hikers() {
        for (Hiker &h : hikers) {
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
        for (const position &start : trailheads) {
            HikerManager m(start, map);
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
    Map map;
    std::vector<position> trailheads{};
    std::vector<HikerManager> managers{};
};
