#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

typedef std::array<size_t, 2> position;

position get_starting_position(const std::vector<std::string> &puzzle) {
    position starting_position{};
    const char obstacle{'#'};
    const char floor{'.'};
    for (size_t i = 0; i < puzzle.size(); i++) {
        for (size_t j = 0; j < puzzle[i].size(); j++) {
            char c = puzzle[i][j];
            if ((c != obstacle) && (c != floor)) {
                starting_position[0] = i;
                starting_position[1] = j;
                break;
            }
        }
    }
    return starting_position;
}

enum class Direction { left, top, right, bottom };

Direction get_direction(char s) {
    if (s == '^') {
        return Direction::top;
    } else if (s == '>') {
        return Direction::right;
    } else if (s == '<') {
        return Direction::left;
    } else {
        return Direction::bottom;
    }
}

bool is_outside(position pos, const std::vector<std::string> &puzzle) {
    const bool out_left = pos[0] == std::numeric_limits<size_t>::max();
    const bool out_right = pos[0] == puzzle[0].size();
    const bool out_top = pos[1] == std::numeric_limits<size_t>::max();
    const bool out_bottom = pos[1] == puzzle.size();
    return out_left || out_right || out_top || out_bottom;
}
char get_map_content(const position &sp, const std::vector<std::string> &map) {
    char s{};
    if (is_outside(sp, map)) {
        s = '-';
    } else {
        s = map[sp[0]][sp[1]];
    }
    return s;
}

class Mover {
  public:
    Mover(Direction start_dir) : dir(start_dir){};
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

  private:
    Direction dir;
    position move_forward(const position &pos) {
        const position next_pos{pos[0] - 1, pos[1]};
        return next_pos;
    }
    position move_backward(const position &pos) {
        const position next_pos{pos[0] + 1, pos[1]};
        return next_pos;
    }
    position move_left(const position &pos) {
        const position next_pos{pos[0], pos[1] - 1};
        return next_pos;
    }
    position move_right(const position &pos) {
        const position next_pos{pos[0], pos[1] + 1};
        return next_pos;
    }
};

class Guard {
  public:
    Guard(const position &start_point, Direction direction, const std::vector<std::string> &map)
        : pos(start_point), dir(direction), map(map), m(direction) {
        tiles_visited.push_back(pos);
    }
    position get_position() const { return pos; };
    int get_number_tiles_visited() {
        std::vector<position> v(tiles_visited);
        std::sort(v.begin(), v.end());
        int unique_count = std::unique(v.begin(), v.end()) - v.begin();
        return unique_count;
    };
    void move() {
        const position next_position = m.get_next_position(pos);
        const char tile_type = get_map_content(next_position, map);
        if (tile_type == '#') {
            m.rotate();
        } else {
            pos = next_position;
            tiles_visited.push_back(pos);
        }
    };

  private:
    position pos;
    Direction dir;
    const std::vector<std::string> map;
    Mover m;
    std::vector<position> tiles_visited;
};

bool moving_guard_not_withing_limits(Guard &g, const std::vector<std::string> &puzzle, size_t max_movements) {
    size_t movements{0};
    while (!is_outside(g.get_position(), puzzle) && (movements < max_movements)) {
        g.move();
        movements++;
    }
    return movements == max_movements;
}

Guard setup_guard(const std::vector<std::string> &puzzle) {
    const position start_point = get_starting_position(puzzle);
    const char start_type = get_map_content(start_point, puzzle);
    Direction dir = get_direction(start_type);
    Guard g(start_point, dir, puzzle);
    return g;
}

int get_points_visited(const std::vector<std::string> &puzzle) {
    Guard g = setup_guard(puzzle);
    const size_t max_movements = puzzle.size() * puzzle[0].size();
    moving_guard_not_withing_limits(g, puzzle, max_movements);
    const int positions_visited = g.get_number_tiles_visited() - 1;
    return positions_visited;
}

int get_possible_obstructions(const std::vector<std::string> &puzzle) {
    int possible_obstructions{0};
    const size_t max_movements = puzzle.size() * puzzle[0].size() * 2;
    for (size_t i = 0; i < puzzle.size(); i++) {
        for (size_t j = 0; j < puzzle[0].size(); j++) {
            std::vector<std::string> new_puzzle(puzzle);
            new_puzzle[i][j] = '#';
            Guard g = setup_guard(new_puzzle);
            const bool max_movements_reached = moving_guard_not_withing_limits(g, new_puzzle, max_movements);
            if (max_movements_reached) {
                possible_obstructions++;
            }
        }
    }
    return possible_obstructions;
}
