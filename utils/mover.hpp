#include "utils/map.hpp"

enum class Direction { left, top, right, bottom };

class Mover {
  public:
    Mover(Direction start_dir) : dir(start_dir){};
    Mover(Direction start_dir, const Position &start_pos) : dir(start_dir), pos_internal(start_pos){};
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
    }
    Position get_position() const { return pos_internal; };
    Direction get_direction() const { return dir; };
    void set_direction(const Direction &direction) { dir = std::move(direction); };

  private:
    Direction dir;
    Position pos_internal;
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
