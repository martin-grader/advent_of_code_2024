#include <array>
#include <cstddef>

class Position {
  public:
    Position(){};
    Position(size_t row, size_t column) : pos({row, column}){};
    size_t operator[](size_t idx) const { return pos[idx]; }
    size_t operator==(const Position &rhs) const { return pos == rhs.pos; }
    size_t operator<(const Position &rhs) const { return pos < rhs.pos; }
    void set_row(size_t row) { pos[0] = row; };
    void set_column(size_t col) { pos[1] = col; };

  private:
    std::array<size_t, 2> pos{};
};
