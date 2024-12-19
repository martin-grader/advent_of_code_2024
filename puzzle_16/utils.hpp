#include "utils/mover.hpp"
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <memory>
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

class RaindeerNavigator : public Navigator {
  public:
    RaindeerNavigator(const Map<char> &map) : Navigator(map){};

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
class RaindeerManager : public TargetMoverManager {

  public:
    RaindeerManager(const Position &start_position, const Map<char> &map, char target_element,
                    std::shared_ptr<Navigator> navi)
        : TargetMoverManager(start_position, map, target_element, navi){};

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
    void print_succeeded() {
        std::cout << "---------------------\n";
        for (TargetMover &h : succeeded_movers) {
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
    std::vector<std::tuple<PathElement, size_t>> scored_histories{};
    void update_history() {
        for (TargetMover &h : active_movers) {
            path history = h.get_history();
            size_t path_score = scorer.calc_path_score(history);
            scored_histories.push_back({history.back(), path_score});
        }
    }
    virtual void check_for_finished_movers() override {
        update_history();
        for (TargetMover &h : active_movers) {
            path next_positions = navi->get_next_positions(h.get_position(), h.get_direction());
            if (next_positions.size() == 0) {
                h.set_finished();
            }
            PathElement p = h.get_history().back();
            path history = h.get_history();
            size_t h_path_score = scorer.calc_path_score(history);
            auto idx = std::find_if(scored_histories.begin(), scored_histories.end(),
                                    [&](const std::tuple<PathElement, size_t> &h) {
                                        return (std::get<0>(h) == p) && (std::get<1>(h) < h_path_score);
                                    });
            if (idx != scored_histories.end()) {
                h.set_finished();
            }
        }
    }
};

class Maze {
  public:
    Maze(const std::vector<std::string> puzzle) : map(puzzle){};
    void go_raindeers() {
        trailheads = map.get_all_occurances('S');
        for (const Position &start : trailheads) {
            std::shared_ptr<Navigator> navi = std::make_shared<RaindeerNavigator>(map);
            RaindeerManager m(start, map, 'E', navi);
            size_t counter{0};
            while (!m.all_finished()) {
                m.advance();
                counter++;
                std::cout << counter << std::endl;
                // m.print();
            }
            // m.print_succeeded();
            managers.push_back(m);
        }
    }
    size_t get_score() {
        size_t score{std::numeric_limits<size_t>::max()};
        for (const TargetMoverManager &m : managers) {
            for (const TargetMover &r : m.get_succeeded_movers()) {
                const size_t this_score = scorer.calc_path_score(r.get_history());
                std::cout << this_score << std::endl;
                const size_t new_score = std::min(this_score, score);
                score = new_score;
            }
        }
        return score;
    };

  private:
    Map<char> map;
    Scorer scorer{};
    std::vector<Position> trailheads{};
    std::vector<TargetMoverManager> managers{};
};
