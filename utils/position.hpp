#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

class Position {
  public:
    Position(){};
    Position(size_t row, size_t column) : pos({row, column}){};
    void print() { std::cout << pos[0] << "," << pos[1] << std::endl; };
    size_t operator[](size_t idx) const { return pos[idx]; }
    size_t operator==(const Position &rhs) const { return pos == rhs.pos; }
    size_t operator!=(const Position &rhs) const { return ((pos[0] != rhs.pos[0]) || (pos[1] != rhs.pos[1])); }
    void operator+=(const Position &rhs) {
        pos[0] += rhs.pos[0];
        pos[1] += rhs.pos[1];
    }
    void operator*=(size_t times) {
        pos[0] *= times;
        pos[1] *= times;
    }
    size_t operator<(const Position &rhs) const { return pos < rhs.pos; }
    void set_row(size_t row) { pos[0] = row; };
    void set_column(size_t col) { pos[1] = col; };
    Position get_left_neighbour() const { return Position(pos[0], pos[1] - 1); };
    Position get_top_left_neighbour() const { return Position(pos[0] - 1, pos[1] - 1); };
    Position get_top_neighbour() const { return Position(pos[0] - 1, pos[1]); };
    Position get_top_right_neighbour() const { return Position(pos[0] - 1, pos[1] + 1); };
    Position get_right_neighbour() const { return Position(pos[0], pos[1] + 1); };
    Position get_bottom_right_neighbour() const { return Position(pos[0] + 1, pos[1] + 1); };
    Position get_bottom_neighbour() const { return Position(pos[0] + 1, pos[1]); };
    Position get_bottom_left_neighbour() const { return Position(pos[0] + 1, pos[1] - 1); };

  private:
    std::array<size_t, 2> pos{};
};

enum class Direction { left = '<', top = '^', right = '>', bottom = 'v' };
class PathElement {
  public:
    PathElement(const Position &pos, const Direction &dir) : pos(pos), dir(dir) {}
    Position get_position() const { return pos; };
    Direction get_direction() const { return dir; };

  private:
    Position pos;
    Direction dir;
};

typedef std::vector<PathElement> path;
