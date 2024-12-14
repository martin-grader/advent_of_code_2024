#include "utils/mover.hpp"
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Region : public Map {
  public:
    Region(char type, std::vector<position> positions, size_t rows, size_t columns)
        : Map(type, positions, rows, columns), plant(type){};
    size_t get_area() const { return count_occurances(plant); };
    size_t get_perimeter() const {
        size_t perimeter{0};

        for (const std::string &row : map) {
            char last_char = void_char;
            for (char c : row) {
                if (c != last_char) {
                    perimeter += 1;
                }
                last_char = c;
            }
            if (last_char != void_char) {
                perimeter++;
            }
        }
        for (size_t column = 0; column < columns; column++) {
            char last_char = void_char;
            for (size_t row = 0; row < rows; row++) {
                char c = map[row][column];
                if (c != last_char) {
                    perimeter += 1;
                }
                last_char = c;
            }
            if (last_char != void_char) {
                perimeter++;
            }
        }
        return perimeter;
    };

  private:
    char plant;
};

class Garden {
  public:
    Garden(std::vector<std::string> puzzle) : map(puzzle) {
        garden_rows = map.rows;
        garden_columns = map.columns;
        set_regions();
    };
    size_t get_fence_costs() {
        size_t fence_costs{0};
        for (const auto &[plant, maps] : regions) {
            for (const Region &m : maps) {
                fence_costs += m.get_area() * m.get_perimeter();
            }
        }
        return fence_costs;
    };
    void print() {
        for (const auto &[plant, maps] : regions) {
            for (const Map &m : maps) {
                if (plant == 'E')
                    m.print();
            }
        }
    }

  private:
    Map map;
    size_t garden_rows;
    size_t garden_columns;
    std::map<char, std::vector<Region>> regions;
    void set_regions() {
        std::vector<char> plants = map.get_unique_map_elements();
        std::map<char, std::vector<position>> plants_positions{};
        for (char plant : plants) {
            plants_positions[plant] = map.get_all_occurances(plant);
        }

        std::map<char, std::vector<std::vector<position>>> plants_area_positions{};
        for (auto &[plant_type, positions] : plants_positions) {
            while (positions.size() > 0) {
                std::vector<position> neighbourhood{positions[0]};
                set_neighbours(positions[0], positions, neighbourhood);
                for (const position &neighbour : neighbourhood) {
                    positions.erase(std::find(positions.begin(), positions.end(), neighbour));
                }
                plants_area_positions[plant_type].push_back({neighbourhood});
            }
        }

        for (const auto &[plant_type, plant_areas] : plants_area_positions) {
            for (const std::vector<position> &area : plant_areas) {
                Region m(plant_type, area, garden_rows, garden_columns);
                regions[plant_type].push_back(m);
            }
        }
    };
    std::vector<position> get_neighbours(std::vector<position> area, position pos) {
        std::vector<position> neighbours{};
        std::vector<position> possible_neighbours = get_possible_neighbours(pos);
        for (const position &possible_neighbour : possible_neighbours) {
            if (std::find(area.begin(), area.end(), possible_neighbour) != area.end()) {
                neighbours.push_back(possible_neighbour);
            }
        }
        return neighbours;
    }
    std::vector<position> get_possible_neighbours(const position &pos) {
        std::vector<position> possible_neighbours{};
        possible_neighbours.push_back({pos[0] - 1, pos[1]});
        possible_neighbours.push_back({pos[0] + 1, pos[1]});
        possible_neighbours.push_back({pos[0], pos[1] + 1});
        possible_neighbours.push_back({pos[0], pos[1] - 1});
        return possible_neighbours;
    }
    void set_neighbours(position pos, std::vector<position> area, std::vector<position> &neighbourhood) {
        std::vector<position> neighbours = get_neighbours(area, pos);
        for (const position &neighbour : neighbours) {
            if (std::find(neighbourhood.begin(), neighbourhood.end(), neighbour) == neighbourhood.end()) {
                neighbourhood.push_back(neighbour);
                set_neighbours(neighbour, area, neighbourhood);
            }
        }
    }
};
