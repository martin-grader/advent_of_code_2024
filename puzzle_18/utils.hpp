#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <vector>

class Scorer {
  public:
    Scorer(){};
    size_t calc_path_score(const path &history) { return history.size() - 1; }
};

class YourNavigator : public Navigator {
  public:
    YourNavigator(const Map<char> &map) : Navigator(map){};

  private:
    bool is_possible_position(const Position &pos, const Position &next_pos) const override {
        bool is_possible{false};
        if (map.is_inside(next_pos)) {
            const char next_element = map.get_entry(next_pos);
            is_possible = next_element != '#';
        }
        return is_possible;
    }
};
class YourManager : public TargetMoverManager {

  public:
    YourManager(const Position &start_position, const Map<char> &map, char target_element,
                std::shared_ptr<Navigator> navi)
        : TargetMoverManager(start_position, map, target_element, navi), left_direction_scores(map.rows, map.columns),
          top_direction_scores(map.rows, map.columns), right_direction_scores(map.rows, map.columns),
          bottom_direction_scores(map.rows, map.columns){};

    void print() {
        std::cout << "---------------------\n";
        for (TargetMover &h : active_movers) {
            path history = h.get_history();
            Map h_map(map);
            for (const PathElement &p : history) {
                h_map.add_element_at_position(p.get_position(), static_cast<char>(p.get_direction()));
            }
            h_map.print();
        }
    };
    void print_succeeded() const {
        std::cout << "---------------------\n";
        for (const TargetMover &h : succeeded_movers) {
            path history = h.get_history();
            Map h_map(map);
            for (const PathElement &p : history) {
                h_map.add_element_at_position(p.get_position(), static_cast<char>(p.get_direction()));
            }
            h_map.print();
        }
    };

  protected:
    Scorer scorer{};
    Map<size_t> left_direction_scores;
    Map<size_t> top_direction_scores;
    Map<size_t> right_direction_scores;
    Map<size_t> bottom_direction_scores;
    std::vector<std::tuple<PathElement, size_t>> scored_histories{};
    void check_for_finished_movers() override {
        for (TargetMover &h : active_movers) {
            // std::cout << active_movers.size() << std::endl;
            path next_positions = navi->get_next_positions(h.get_position(), h.get_direction());
            if (next_positions.size() == 0) {
                h.set_finished();
            }
            PathElement p = h.get_history().back();
            path history = h.get_history();
            size_t h_path_score = scorer.calc_path_score(history);
            if (score_too_high(p, h_path_score)) {
                h.set_finished();
            }
        }
    }
    bool score_too_high(const PathElement &p, size_t score) {
        Position pos = p.get_position();
        Direction dir = p.get_direction();
        if (dir == Direction::left) {
            return check_score_this_map(pos, left_direction_scores, score);
        } else if (dir == Direction::top) {
            return check_score_this_map(pos, top_direction_scores, score);
        } else if (dir == Direction::right) {
            return check_score_this_map(pos, right_direction_scores, score);
        } else {
            return check_score_this_map(pos, bottom_direction_scores, score);
        }
    }
    bool check_score_this_map(const Position &p, Map<size_t> &map, size_t score) {
        size_t map_score = map.get_entry(p);
        bool score_not_ok{true};
        if ((map_score == 0) || (map_score > score)) {
            map.add_element_at_position(p, score);
            score_not_ok = false;
        }
        return score_not_ok;
    }
};

class Maze {
  public:
    Maze(size_t rows, size_t columns, const std::vector<std::vector<size_t>> bytes, size_t time_passed)
        : map(rows, columns), time_passed(time_passed), bytes(bytes) {
        for (size_t i = 0; i < time_passed; i++) {
            map.add_element_at_position(bytes[i][1], bytes[i][0], '#');
            map.add_element_at_position(0, 0, 'S');
            map.add_element_at_position(rows - 1, columns - 1, 'E');
        }
    };
    void go() {
        trailheads = map.get_all_occurances('S');
        for (const Position &start : trailheads) {
            std::shared_ptr<Navigator> navi = std::make_shared<YourNavigator>(map);
            YourManager m(start, map, 'E', navi);
            while (!m.all_finished()) {
                m.advance();
            }
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{std::numeric_limits<size_t>::max()};
        for (const YourManager &m : managers) {
            for (const TargetMover &r : m.get_succeeded_movers()) {
                const size_t this_score = scorer.calc_path_score(r.get_history());
                score = std::min(this_score, score);
            }
        }
        return score;
    };
    Position find_blocking_tile() {
        bool moover_finished_with_succes = {true};
        size_t element_to_add = time_passed - 1;
        while (moover_finished_with_succes && (element_to_add < bytes.size())) {
            element_to_add++;
            map.add_element_at_position(bytes[element_to_add][1], bytes[element_to_add][0], '#');
            managers.clear();
            go();
            for (const YourManager &m : managers) {
                if (m.get_number_of_succeeded_movers() == 0)
                    moover_finished_with_succes = false;
            }
        }

        Position blocking_element(bytes[element_to_add][1], bytes[element_to_add][0]);
        return blocking_element;
    }

  private:
    Map<char> map;
    size_t time_passed;
    std::vector<std::vector<size_t>> bytes{};
    Scorer scorer{};
    std::vector<Position> trailheads{};
    std::vector<YourManager> managers{};
};
