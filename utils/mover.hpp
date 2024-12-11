#include "utils/map.hpp"

enum class Direction { left, top, right, bottom };

class Mover {
  public:
    Mover(Direction start_dir) : dir(start_dir){};
    Mover(Direction start_dir, const position &start_pos) : dir(start_dir), pos_internal(start_pos){};
    position get_next_position(const position &current_pos) {
        position next_position{};
        switch (dir) {
        case Direction::left:
            next_position = move_left(current_pos);
            break;
        case Direction::right:
            next_position = move_right(current_pos);
            break;
        case Direction::top:
            next_position = move_forward(current_pos);
            break;
        case Direction::bottom:
            next_position = move_backward(current_pos);
            break;
        }
        return next_position;
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
        const position current_pos(pos_internal);
        pos_internal = get_next_position(current_pos);
    }
    position get_position() const { return pos_internal; };
    Direction get_direction() const { return dir; };
    void set_direction(const Direction &direction) { dir = std::move(direction); };

  private:
    Direction dir;
    position pos_internal;
    position move_forward(const position &pos) {
        // std::cout << "moving top" << std::endl;
        const position next_pos{pos[0] - 1, pos[1]};
        return next_pos;
    }
    position move_backward(const position &pos) {
        // std::cout << "moving back" << std::endl;
        const position next_pos{pos[0] + 1, pos[1]};
        return next_pos;
    }
    position move_left(const position &pos) {
        // std::cout << "moving left" << std::endl;
        const position next_pos{pos[0], pos[1] - 1};
        return next_pos;
    }
    position move_right(const position &pos) {
        // std::cout << "moving right" << std::endl;
        const position next_pos{pos[0], pos[1] + 1};
        return next_pos;
    }
};
