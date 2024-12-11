#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

typedef std::array<size_t, 2> position;

class Map {
  public:
    Map(std::vector<std::string> init_map) : rows(init_map.size()), columns(init_map[0].size()), map(init_map){};
    Map(size_t rows, size_t columns) : rows(rows), columns(columns) {
        for (size_t i = 0; i < rows; i++) {
            std::string row(columns, '.');
            map.push_back(row);
        }
    };
    size_t rows{};
    size_t columns{};
    char get_entry(size_t row, size_t column) const { return map[row][column]; };
    char get_entry(const position &pos) const { return map[pos[0]][pos[1]]; };
    void print() {
        for (std::string row : map) {
            std::cout << row << std::endl;
        }
        std::cout << std::endl;
    }
    void add_element_at_position(const position &pos, char element) {
        if (is_inside(pos)) {
            map[pos[0]][pos[1]] = '#';
        }
    }
    int count_occurances(char type) {
        int occurances{0};
        for (std::string row : map) {
            for (char c : row) {
                if (c == type) {
                    occurances++;
                }
            }
        }
        return occurances;
    }
    std::vector<position> get_all_occurances(char type) {
        std::vector<position> occurances{};
        for (size_t row = 0; row < map.size(); row++) {
            for (size_t col = 0; col < map[0].size(); col++) {
                if (get_entry(row, col) == type) {
                    const position pos = {row, col};
                    occurances.push_back(pos);
                }
            }
        }
        return occurances;
    }
    bool is_inside(position pos) {
        const bool inside_rows = pos[0] < rows;
        const bool inside_columns = pos[1] < columns;
        return inside_rows && inside_columns;
    }

  private:
    std::vector<std::string> map{};
};
