#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
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
    char get_entry(size_t row, size_t column) { return map[row][column]; };
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
    bool is_inside(position pos) {
        const bool inside_rows = pos[0] < rows;
        const bool inside_columns = pos[1] < columns;
        return inside_rows && inside_columns;
    }

  private:
    std::vector<std::string> map{};
};

class Antenna {
  public:
    Antenna(const position &pos, char type) : pos(pos), type(type) {
        x = static_cast<int>(pos[0]);
        y = static_cast<int>(pos[1]);
    }
    position pos{};
    int x{};
    int y{};
    void print() { std::cout << " Antenna " << type << " (" << x << "," << y << ")" << std::endl; };

  private:
    char type{};
};

enum class AntinodeType { tdlr, tdrl };

class Antinode {
  public:
    Antinode(const Antenna &a, const Antenna &b) : first(a), second(b) {
        set_type();
        set_distance();
    };
    std::vector<position> get_positions() {
        set_positions();
        return positions;
    };
    position get_position(size_t i) {
        set_positions();
        return positions[i];
    }
    void print_first() {
        std::cout << " Antinode first " << " (" << get_position(0)[0] << "," << get_position(0)[1] << ")" << std::endl;
    };
    void print_second() {
        std::cout << " Antinode second " << " (" << get_position(1)[0] << "," << get_position(1)[1] << ")" << std::endl;
    };

  protected:
    Antenna first;
    Antenna second;
    AntinodeType type;
    position distance{};
    std::vector<position> positions{};
    void set_type() {
        if (((first.x > second.x) && (first.y > second.y)) || ((first.x < second.x) && (first.y < second.y))) {
            type = AntinodeType::tdlr;
        } else {
            type = AntinodeType::tdrl;
        }
    }

    void set_distance() {
        int dx = std::abs(first.x - second.x);
        int dy = std::abs(first.y - second.y);
        distance = {static_cast<size_t>(dx), static_cast<size_t>(dy)};
    }

    virtual void set_positions() {
        size_t x_min = std::min(first.x, second.x) - distance[0];
        size_t y_min = std::min(first.y, second.y) - distance[1];
        size_t x_max = std::max(first.x, second.x) + distance[0];
        size_t y_max = std::max(first.y, second.y) + distance[1];
        if (type == AntinodeType::tdlr) {
            positions = {{x_min, y_min}, {x_max, y_max}};
        } else {
            positions = {{x_min, y_max}, {x_max, y_min}};
        }
    };
};

class AdvancedAntinode : public Antinode {
  public:
    AdvancedAntinode(const Antenna &a, const Antenna &b, const Map &map) : Antinode(a, b), map(map){};

  private:
    Map map;
    void set_positions() override {
        positions.push_back(first.pos);
        positions.push_back(second.pos);
        int multiplier = std::max(map.rows, map.columns);
        for (int i = 1; i <= multiplier; i++) {
            set_position_multiple(i);
        }
    };
    void set_position_multiple(int multiplier) {
        size_t x_min = std::min(first.x, second.x) - multiplier * distance[0];
        size_t y_min = std::min(first.y, second.y) - multiplier * distance[1];
        size_t x_max = std::max(first.x, second.x) + multiplier * distance[0];
        size_t y_max = std::max(first.y, second.y) + multiplier * distance[1];
        position pos1{};
        position pos2{};
        if (type == AntinodeType::tdlr) {
            pos1 = {x_min, y_min};
            pos2 = {x_max, y_max};
        } else {
            pos1 = {x_min, y_max};
            pos2 = {x_max, y_min};
        }
        if (map.is_inside(pos1)) {
            positions.push_back(pos1);
        }
        if (map.is_inside(pos2)) {
            positions.push_back(pos2);
        }
    }
};

typedef std::map<char, std::vector<Antenna>> grouped_antennas;
typedef std::map<char, std::vector<Antinode>> grouped_antinodes;
typedef std::map<char, std::vector<AdvancedAntinode>> grouped_advanced_antinodes;

grouped_antennas get_antennas_on_map(Map &map) {
    grouped_antennas antennas{};
    const char floor{'.'};
    for (size_t row = 0; row < map.rows; row++) {
        for (size_t column = 0; column < map.columns; column++) {
            const char entry = map.get_entry(row, column);
            if (entry != floor) {
                position pos{row, column};
                Antenna a(pos, entry);
                antennas[entry].push_back(a);
            }
        }
    }
    return antennas;
}

grouped_antinodes get_all_antinodes(const grouped_antennas &antennas_all_types) {
    grouped_antinodes antinodes;
    for (auto [type, antennas_this_type] : antennas_all_types) {
        std::vector antennas(antennas_this_type);
        while (antennas.size() > 1) {
            for (size_t i = 1; i < antennas.size(); i++) {
                Antinode a(antennas[0], antennas[i]);
                antinodes[type].push_back(a);
            }
            antennas.erase(antennas.begin());
        }
    }
    return antinodes;
}

grouped_advanced_antinodes get_all_advanced_antinodes(const grouped_antennas &antennas_all_types, const Map &map) {
    grouped_advanced_antinodes antinodes;
    for (auto [type, antennas_this_type] : antennas_all_types) {
        std::vector antennas(antennas_this_type);
        while (antennas.size() > 1) {
            for (size_t i = 1; i < antennas.size(); i++) {
                AdvancedAntinode a(antennas[0], antennas[i], map);
                antinodes[type].push_back(a);
            }
            antennas.erase(antennas.begin());
        }
    }
    return antinodes;
}

template <typename T> Map get_antinodes_map(const T &all_antinodes, const std::vector<std::string> map) {
    Map antinodes_map(map.size(), map[0].size());
    for (auto [type, antinodes] : all_antinodes) {
        for (auto a : antinodes) {
            for (position pos : a.get_positions()) {
                antinodes_map.add_element_at_position(pos, '#');
            }
        }
    }
    return antinodes_map;
}

int get_antinodes(const std::vector<std::string> &puzzle) {
    Map antenna_map(puzzle);
    grouped_antennas antennas = get_antennas_on_map(antenna_map);
    grouped_antinodes antinodes = get_all_antinodes(antennas);
    Map antinode_map = get_antinodes_map(antinodes, puzzle);
    const int antinodes_count = antinode_map.count_occurances('#');

    return antinodes_count;
}

int get_advanced_antinodes(const std::vector<std::string> &puzzle) {
    Map antenna_map(puzzle);
    grouped_antennas antennas = get_antennas_on_map(antenna_map);
    grouped_advanced_antinodes advanced_antinodes = get_all_advanced_antinodes(antennas, antenna_map);
    Map antinode_map = get_antinodes_map(advanced_antinodes, puzzle);
    const int antinodes = antinode_map.count_occurances('#');

    return antinodes;
}
