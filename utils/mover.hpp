#include "utils/map.hpp"
#include <cassert>
#include <cstdlib>
#include <memory>

class Mover {
  public:
    Mover(Direction start_dir) : dir(start_dir){};
    Mover(Direction start_dir, const Position &start_pos) : dir(start_dir), pos_internal(start_pos) {
        history.push_back(PathElement(start_pos, start_dir));
    };
    Mover(Direction start_dir, const Position &start_pos, const path previous_history)
        : dir(start_dir), pos_internal(start_pos) {
        history = previous_history;
    };
    Mover(const Position &start_pos) : pos_internal(start_pos){};
    Position get_next_position() { return get_next_position(pos_internal); };
    Position get_next_position(const Position &current_pos) {
        Position next_Position{};
        switch (dir) {
        case Direction::left:
            next_Position = move_left(current_pos);
            break;
        case Direction::right:
            next_Position = move_right(current_pos);
            break;
        case Direction::top:
            next_Position = move_forward(current_pos);
            break;
        case Direction::bottom:
            next_Position = move_backward(current_pos);
            break;
        }
        return next_Position;
    };
    void rotate() {
        switch (dir) {
        case Direction::left:
            dir = Direction::top;
            break;
        case Direction::right:
            dir = Direction::bottom;
            break;
        case Direction::top:
            dir = Direction::right;
            break;
        case Direction::bottom:
            dir = Direction::left;
            break;
        }
    };
    void move_to_next_position() {
        const Position current_pos(pos_internal);
        pos_internal = get_next_position(current_pos);
        history.push_back(PathElement(pos_internal, dir));
    }
    Position get_position() const { return pos_internal; };
    Direction get_direction() const { return dir; };
    path get_history() const { return history; };
    void set_direction(const Direction &direction) { dir = std::move(direction); };
    void set_direction(char next_direction) { dir = static_cast<Direction>(next_direction); };

  private:
    Direction dir;
    Position pos_internal;
    path history{};
    Position move_forward(const Position &pos) {
        // std::cout << "moving top" << std::endl;
        const Position next_pos{pos[0] - 1, pos[1]};
        return next_pos;
    }
    Position move_backward(const Position &pos) {
        // std::cout << "moving back" << std::endl;
        const Position next_pos{pos[0] + 1, pos[1]};
        return next_pos;
    }
    Position move_left(const Position &pos) {
        // std::cout << "moving left" << std::endl;
        const Position next_pos{pos[0], pos[1] - 1};
        return next_pos;
    }
    Position move_right(const Position &pos) {
        // std::cout << "moving right" << std::endl;
        const Position next_pos{pos[0], pos[1] + 1};
        return next_pos;
    }
};

class TargetMover : public Mover {
  public:
    TargetMover(const Position &start_pos, const Direction &start_dir, const Map<char> &map, char target_element,
                const path &history)
        : Mover(start_dir, start_pos, history), map(map), target_element(target_element){};
    TargetMover(const Position &start_pos, const Direction &start_dir, const Map<char> &map, char target_element)
        : Mover(start_dir, start_pos), map(map), target_element(target_element){};

    std::vector<Position> get_path() const { return path; };
    void set_finished() { finished = true; };
    bool is_finished() const { return finished; };
    bool success() const { return map.get_entry(get_position()) == target_element; };
    void move() {
        if (!finished) {
            move_to_next_position();
            path.push_back(get_position());
        }
        if (success()) {
            set_finished();
        }
    };

  private:
    Map<char> map;
    std::vector<Position> path{};
    bool finished{false};
    char target_element{};
};

class TargetMoverFactory {
  public:
    TargetMoverFactory(const Map<char> &map, char target_element) : map(map), target_element(target_element){};
    TargetMover get_mover(const Position &start_pos, const Direction &start_dir, const path &history) const {
        return TargetMover(start_pos, start_dir, map, target_element, history);
    };
    TargetMover get_mover(const Position &start_pos, const Direction &start_dir) const {
        return TargetMover(start_pos, start_dir, map, target_element);
    };

  private:
    Map<char> map;
    char target_element{};
};

class Navigator {
  public:
    Navigator(const Map<char> &map) : map(map){};
    path get_next_positions(const Position &pos, const Direction &dir) const {
        path neighbour_positions = get_neighbour_positions(pos, dir);
        path allowed_next_positions = get_allowed_next_positions(pos, neighbour_positions);
        return allowed_next_positions;
    };

  protected:
    Map<char> map;
    std::vector<Direction> neighbour_directions{Direction::left, Direction::top, Direction::right, Direction::bottom};
    path get_neighbour_positions(const Position &pos, const Direction &dir) const {
        path neighbour_positions{};
        for (Direction neighbour_direction : neighbour_directions) {
            Mover m(neighbour_direction);
            Position neighbour_position = m.get_next_position(pos);
            PathElement p(neighbour_position, neighbour_direction);
            neighbour_positions.push_back(p);
        }
        return neighbour_positions;
    }
    path get_allowed_next_positions(const Position &pos, const path &neighbour_positions) const {
        path allowed_next_positions{};
        for (const PathElement &p : neighbour_positions) {
            if (is_possible_position(pos, p.get_position())) {
                allowed_next_positions.push_back(p);
            }
        }
        return allowed_next_positions;
    }
    virtual bool is_possible_position(const Position &pos, const Position &next_pos) const = 0;
};

class TargetMoverManager {

  public:
    TargetMoverManager(const Position &start_position, const Map<char> &map, char target_element,
                       std::shared_ptr<Navigator> navi)
        : map(map), tmf(map, target_element), navi(std::move(navi)) {
        TargetMover first_mover = tmf.get_mover(start_position, Direction::left);
        active_movers.push_back(first_mover);
        add_new_movers(true);
    }
    void advance() {
        move_all_movers();
        retire_succeded_movers();
        check_for_finished_movers();
        remove_finished_movers();
        add_new_movers(false);
    }
    bool all_finished() const { return active_movers.empty(); };
    size_t get_number_of_succeeded_movers() const { return succeeded_movers.size(); }
    std::vector<TargetMover> get_succeeded_movers() const { return succeeded_movers; }

  protected:
    Map<char> map;
    TargetMoverFactory tmf;
    std::shared_ptr<Navigator> navi;

    std::vector<TargetMover> active_movers{};
    std::vector<TargetMover> succeeded_movers{};
    virtual void add_new_movers(bool allow_opposite_direction = false) {
        // std::cout << "active movers on adding = " << active_movers.size() << std::endl;
        std::vector<TargetMover> new_movers{};
        for (TargetMover &h : active_movers) {
            path next_positions = navi->get_next_positions(h.get_position(), h.get_direction());
            assert(next_positions.size() > 0);
            Direction this_direction = h.get_direction();
            h.set_direction(next_positions[0].get_direction());

            for (size_t i = 1; i < next_positions.size(); i++) {
                Direction next_direction = next_positions[i].get_direction();
                if (!is_opposite_direction(this_direction, next_direction) || allow_opposite_direction) {
                    TargetMover p_new = tmf.get_mover(h.get_position(), next_direction, h.get_history());

                    new_movers.push_back(p_new);
                }
            }
        }
        for (TargetMover nh : new_movers) {
            active_movers.push_back(nh);
        }
    }
    virtual void check_for_finished_movers() {
        for (TargetMover &h : active_movers) {
            path next_positions = navi->get_next_positions(h.get_position(), h.get_direction());
            if (next_positions.size() == 0) {
                h.set_finished();
            }
        }
    }
    void move_all_movers() {
        for (TargetMover &h : active_movers) {
            h.move();
        }
    }
    void remove_finished_movers() {
        active_movers.erase(std::remove_if(active_movers.begin(), active_movers.end(),
                                           [](const TargetMover &h) { return h.is_finished(); }),
                            active_movers.end());
        // std::cout << "active movers = " << active_movers.size() << std::endl;
    }
    void retire_succeded_movers() {
        std::copy_if(active_movers.begin(), active_movers.end(), std::back_inserter(succeeded_movers),
                     [](const TargetMover &h) { return h.success(); });
    }
    bool is_opposite_direction(const Direction &lhs, const Direction &rhs) const {
        if (lhs == Direction::left) {
            return rhs == Direction::right;
        } else if (lhs == Direction::top) {
            return rhs == Direction::bottom;
        } else if (lhs == Direction::right) {
            return rhs == Direction::left;
        } else
            return rhs == Direction::top;
    }
};
