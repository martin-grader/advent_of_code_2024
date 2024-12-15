#include "position.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Map {
  public:
    Map(std::vector<std::string> init_map) : rows(init_map.size()), columns(init_map[0].size()), map(init_map) {
        set_unique_map_elements();
    };
    Map(size_t rows, size_t columns) : rows(rows), columns(columns) {
        for (size_t i = 0; i < rows; i++) {
            std::string row(columns, void_char);
            map.push_back(row);
        }
        set_unique_map_elements();
    };
    Map(char type, std::vector<Position> positions, size_t rows, size_t columns) : rows(rows), columns(columns) {
        for (size_t i = 0; i < rows; i++) {
            std::string row(columns, void_char);
            map.push_back(row);
        }
        for (const Position &pos : positions) {
            add_element_at_position(pos, type);
        }
        set_unique_map_elements();
    };
    size_t rows{};
    size_t columns{};
    char get_entry(size_t row, size_t column) const { return map[row][column]; };
    char get_entry(const Position &pos) const { return map[pos[0]][pos[1]]; };
    void print() const {
        for (std::string row : map) {
            std::cout << row << std::endl;
        }
        std::cout << std::endl;
    }
    void add_element_at_position(const Position &pos, char element) {
        if (is_inside(pos)) {
            map[pos[0]][pos[1]] = element;
        }
    }
    void add_element_at_position(size_t row, size_t column, char element) {
        const Position pos = {row, column};
        add_element_at_position(pos, element);
    }
    int count_occurances(char type) const {
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
    std::vector<Position> get_all_occurances(char type) const {
        std::vector<Position> occurances{};
        for (size_t row = 0; row < map.size(); row++) {
            for (size_t col = 0; col < map[0].size(); col++) {
                if (get_entry(row, col) == type) {
                    occurances.push_back(Position(row, col));
                }
            }
        }
        return occurances;
    }
    std::vector<Position> get_all_inside_occurances(char type) const {
        std::vector<Position> occurances{};
        for (size_t row = 1; row < map.size() - 1; row++) {
            for (size_t col = 1; col < map[0].size() - 1; col++) {
                if (get_entry(row, col) == type) {
                    occurances.push_back(Position(row, col));
                }
            }
        }
        return occurances;
    }
    bool is_inside(Position pos) {
        const bool inside_rows = pos[0] < rows;
        const bool inside_columns = pos[1] < columns;
        return inside_rows && inside_columns;
    }
    std::vector<char> get_unique_map_elements() const { return unique_map_elements; }

  protected:
    char void_char{'.'};
    std::vector<std::string> map{};
    std::vector<char> unique_map_elements{};
    void set_unique_map_elements() {
        for (size_t row = 0; row < map.size(); row++) {
            for (size_t col = 0; col < map[0].size(); col++) {
                const char element = get_entry(row, col);
                if (std::find(unique_map_elements.begin(), unique_map_elements.end(), element) ==
                    unique_map_elements.end()) {
                    unique_map_elements.push_back(element);
                }
            }
        }
    };
};
