#include "position.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

template <typename T = char> class Map {
  public:
    Map(std::vector<std::vector<T>> init_map) : rows(init_map.size()), columns(init_map[0].size()), map(init_map) {
        set_unique_map_elements();
    };
    Map(std::vector<std::string> init_map) : rows(init_map.size()), columns(init_map[0].size()) {
        for (size_t row = 0; row < rows; row++) {
            std::vector<T> r{};
            for (size_t col = 0; col < columns; col++) {
                r.push_back(init_map[row][col]);
            }
            map.push_back(r);
        }

        set_unique_map_elements();
    };
    Map(size_t rows, size_t columns) : rows(rows), columns(columns) {
        for (size_t i = 0; i < rows; i++) {
            std::vector<T> row(columns, void_char);
            map.push_back(row);
        }
        set_unique_map_elements();
    };
    Map(T type, std::vector<Position> positions, size_t rows, size_t columns) : rows(rows), columns(columns) {
        for (size_t i = 0; i < rows; i++) {
            std::vector<T> row(columns, void_char);
            map.push_back(row);
        }
        for (const Position &pos : positions) {
            add_element_at_position(pos, type);
        }
        set_unique_map_elements();
    };
    size_t rows{};
    size_t columns{};
    T get_entry(size_t row, size_t column) const { return map[row][column]; };
    T get_entry(const Position &pos) const { return map[pos[0]][pos[1]]; };
    void print() const {
        for (const std::vector<T> &row : map) {
            for (T c : row) {

                std::cout << c;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void add_element_at_position(const Position &pos, T element) {
        if (is_inside(pos)) {
            map[pos[0]][pos[1]] = element;
        }
    }
    void add_element_at_position(size_t row, size_t column, T element) {
        const Position pos = {row, column};
        add_element_at_position(pos, element);
    }
    int count_occurances(T type) const {
        int occurances{0};
        for (std::vector<T> row : map) {
            for (T c : row) {
                if (c == type) {
                    occurances++;
                }
            }
        }
        return occurances;
    }
    std::vector<Position> get_all_occurances(T type) const {
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
    std::vector<Position> get_all_inside_occurances(T type) const {
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
    bool is_inside(Position pos) const {
        const bool inside_rows = pos[0] < rows;
        const bool inside_columns = pos[1] < columns;
        return inside_rows && inside_columns;
    }
    std::vector<T> get_unique_map_elements() {
        set_unique_map_elements();
        return unique_map_elements;
    }

  protected:
    static constexpr T void_char = std::is_same<T, char>::value ? '.' : 0;
    std::vector<std::vector<T>> map{};
    std::vector<T> unique_map_elements{};
    void set_unique_map_elements() {
        for (size_t row = 0; row < map.size(); row++) {
            for (size_t col = 0; col < map[0].size(); col++) {
                const T element = get_entry(row, col);
                if (std::find(unique_map_elements.begin(), unique_map_elements.end(), element) ==
                    unique_map_elements.end()) {
                    unique_map_elements.push_back(element);
                }
            }
        }
    };
};
