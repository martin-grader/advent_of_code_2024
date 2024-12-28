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
    size_t calc_path_score(const path &history) {
        size_t score{0};
        for (size_t i = 1; i < history.size(); i++) {
            const Direction dir = history[i].get_direction();
            const Direction prev_dir = history[i - 1].get_direction();
            if (dir == prev_dir) {
                score += 1;
            } else {
                score += 1001;
            }
        }
        return score;
    }
};

class RaindeerNavigator : public Navigator<char> {
  public:
    RaindeerNavigator(const std::shared_ptr<Map<char>> map) : Navigator(map){};

  private:
    bool is_possible_position(const Position &pos, const Position &next_pos) const override {
        bool is_possible{false};
        if (map->is_inside(next_pos)) {
            const char next_element = map->get_entry(next_pos);
            is_possible = next_element != '#';
        }
        return is_possible;
    }
};
class RaindeerManager : public TargetMoverManager<char> {

  public:
    RaindeerManager(const Position &start_position, const std::shared_ptr<Map<>> map, char target_element,
                    std::shared_ptr<Navigator<char>> navi)
        : TargetMoverManager(start_position, map, target_element, navi), left_direction_scores(map->rows, map->columns),
          top_direction_scores(map->rows, map->columns), right_direction_scores(map->rows, map->columns),
          bottom_direction_scores(map->rows, map->columns){};

    void print() {
        std::cout << "---------------------\n";
        for (TargetMover<char> &h : active_movers) {
            path history = h.get_history();
            std::shared_ptr<Map<char>> h_map = std::make_shared<Map<char>>(*map);
            for (const PathElement &p : history) {
                h_map->add_element_at_position(p.get_position(), static_cast<char>(p.get_direction()));
            }
            h_map->print();
        }
    };
    void print_succeeded() const {
        std::cout << "---------------------\n";
        for (const TargetMover<> &h : succeeded_movers) {
            path history = h.get_history();
            std::shared_ptr<Map<char>> h_map = std::make_shared<Map<char>>(*map);
            for (const PathElement &p : history) {
                h_map->add_element_at_position(p.get_position(), static_cast<char>(p.get_direction()));
            }
            h_map->print();
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
        for (TargetMover<> &h : active_movers) {
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
        if ((map_score == 0) || (map_score >= score)) {
            map.add_element_at_position(p, score);
            score_not_ok = false;
        }
        return score_not_ok;
    }
};

class Maze {
  public:
    Maze(const std::vector<std::string> puzzle) : map(std::make_shared<Map<char>>(puzzle)){};
    void go_raindeers() {
        trailheads = map->get_all_occurances('S');
        for (const Position &start : trailheads) {
            std::shared_ptr<Navigator<>> navi = std::make_shared<RaindeerNavigator>(map);
            RaindeerManager m(start, map, 'E', navi);
            while (!m.all_finished()) {
                m.advance();
            }
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{std::numeric_limits<size_t>::max()};
        for (const RaindeerManager &m : managers) {
            for (const TargetMover<> &r : m.get_succeeded_movers()) {
                const size_t this_score = scorer.calc_path_score(r.get_history());
                score = std::min(this_score, score);
            }
        }
        return score;
    };
    size_t get_best_tiles() {
        std::set<Position> best_tiles{};
        const size_t best_score = get_score();
        for (const RaindeerManager &m : managers) {
            for (const TargetMover<> &r : m.get_succeeded_movers()) {
                const size_t this_score = scorer.calc_path_score(r.get_history());
                if (this_score == best_score) {
                    std::vector<PathElement> this_path = r.get_history();
                    for (const PathElement p : this_path) {
                        best_tiles.insert(p.get_position());
                    }
                }
            }
        }

        return best_tiles.size();
    }

  private:
    std::shared_ptr<Map<char>> map;
    Scorer scorer{};
    std::vector<Position> trailheads{};
    std::vector<RaindeerManager> managers{};
};
