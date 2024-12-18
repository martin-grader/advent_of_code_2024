#include "utils/map.hpp"
// #include "utils/position.hpp"
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

typedef std::vector<Position> positions;

class Neighbourhood {
  public:
    Neighbourhood(const Map<char> &map, char type) : map(map), type(type){};
    std::vector<positions> get_neighbourhoods() {
        set_neighbourhood();
        return neighbourhoods;
    };

  private:
    Map<char> map;
    char type;
    std::vector<positions> neighbourhoods{};
    void set_neighbourhood() {
        positions p = map.get_all_occurances(type);
        while (p.size() > 0) {
            positions neighbourhood{p[0]};
            set_neighbours(p[0], p, neighbourhood);
            for (const Position &neighbour : neighbourhood) {
                p.erase(std::find(p.begin(), p.end(), neighbour));
            }
            neighbourhoods.push_back(neighbourhood);
        }
    };
    positions get_neighbours(positions area, Position pos) {
        positions neighbours{};
        positions possible_neighbours = get_possible_neighbours(pos);
        for (const Position &possible_neighbour : possible_neighbours) {
            if (std::find(area.begin(), area.end(), possible_neighbour) != area.end()) {
                neighbours.push_back(possible_neighbour);
            }
        }
        return neighbours;
    }
    virtual positions get_possible_neighbours(const Position &pos) {
        positions possible_neighbours{};
        possible_neighbours.push_back(pos.get_left_neighbour());
        possible_neighbours.push_back(pos.get_top_neighbour());
        possible_neighbours.push_back(pos.get_right_neighbour());
        possible_neighbours.push_back(pos.get_bottom_neighbour());
        return possible_neighbours;
    }
    void set_neighbours(Position pos, positions area, positions &neighbourhood) {
        positions neighbours = get_neighbours(area, pos);
        for (const Position &neighbour : neighbours) {
            if (std::find(neighbourhood.begin(), neighbourhood.end(), neighbour) == neighbourhood.end()) {
                neighbourhood.push_back(neighbour);
                set_neighbours(neighbour, area, neighbourhood);
            }
        }
    }
};

class VerticalNeighbourhood : public Neighbourhood {
  public:
    VerticalNeighbourhood(const Map<char> &map, char type) : Neighbourhood(map, type){};

  private:
    positions get_possible_neighbours(const Position &pos) override {
        positions possible_neighbours{};
        possible_neighbours.push_back(pos.get_top_neighbour());
        possible_neighbours.push_back(pos.get_bottom_neighbour());
        return possible_neighbours;
    };
};

class HorizontalNeighbourhood : public Neighbourhood {
  public:
    HorizontalNeighbourhood(const Map<char> &map, char type) : Neighbourhood(map, type){};

  private:
    positions get_possible_neighbours(const Position &pos) override {
        positions possible_neighbours{};
        possible_neighbours.push_back(pos.get_left_neighbour());
        possible_neighbours.push_back(pos.get_right_neighbour());
        return possible_neighbours;
    };
};

class Region : public Map<char> {
  public:
    Region(char type, positions p, size_t rows, size_t columns) : Map(type, p, rows, columns), plant(type){};
    size_t get_area() const { return count_occurances(plant); };
    size_t get_internal_cross_points() const {
        size_t cross_points{0};
        for (const Position &pos : get_all_inside_occurances(plant)) {
            if (is_cross_point(pos)) {
                cross_points++;
            }
        }
        return cross_points;
    };

  private:
    char plant;
    bool is_cross_point(const Position &pos) const {
        bool option_1 = is_cross_point_option_1(pos);
        bool option_2 = is_cross_point_option_2(pos);
        return option_1 || option_2;
    };
    bool is_cross_point_option_1(const Position &pos) const {
        bool cond_1 = get_entry(pos.get_right_neighbour()) == void_char;
        bool cond_2 = get_entry(pos.get_bottom_neighbour()) == void_char;
        bool cond_3 = get_entry(pos.get_bottom_right_neighbour()) == plant;
        return cond_1 && cond_2 && cond_3;
    }
    bool is_cross_point_option_2(const Position &pos) const {
        bool cond_1 = get_entry(pos.get_right_neighbour()) == void_char;
        bool cond_2 = get_entry(pos.get_top_neighbour()) == void_char;
        bool cond_3 = get_entry(pos.get_top_right_neighbour()) == plant;
        return cond_1 && cond_2 && cond_3;
    }
};

class HorizontalFence : public Map<char> {
  public:
    HorizontalFence(const Region &region) : Map(region.rows + 1, region.columns + 1), region(region) {
        set_horizontal_fences();
    };
    size_t get_perimeter() const {
        size_t perimeter{0};
        perimeter += count_occurances(fence);
        return perimeter;
    }
    size_t count_sides() const {
        HorizontalNeighbourhood n(map, fence);
        size_t sides = n.get_neighbourhoods().size();
        return sides;
    }

  private:
    Region region;
    char fence = '-';
    void set_horizontal_fences() {
        for (size_t col = 0; col < region.columns; col++) {
            char last_char = void_char;
            for (size_t row = 0; row < region.rows; row++) {
                const char c = region.get_entry(row, col);
                if (c != last_char) {
                    add_element_at_position(row, col, fence);
                    last_char = c;
                }
            }
            if (last_char != void_char) {
                add_element_at_position(region.rows, col, fence);
            }
        }
    }
};
class VerticalFence : public Map<char> {
  public:
    VerticalFence(const Region &region) : Map(region.rows + 1, region.columns + 1), region(region) {
        set_vertical_fences();
    };
    size_t get_perimeter() const {
        size_t perimeter{0};
        perimeter += count_occurances(fence);
        return perimeter;
    }
    size_t count_sides() const {
        VerticalNeighbourhood n(map, fence);
        size_t sides = n.get_neighbourhoods().size();
        return sides;
    }

  private:
    Region region;
    char fence = '|';
    void set_vertical_fences() {
        for (size_t row = 0; row < region.rows; row++) {
            char last_char = void_char;
            for (size_t col = 0; col < region.columns; col++) {
                const char c = region.get_entry(row, col);
                if (c != last_char) {
                    add_element_at_position(row, col, fence);
                    last_char = c;
                }
            }
            if (last_char != void_char) {
                add_element_at_position(row, region.columns, fence);
            }
        }
    }
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
            for (const auto &[m, fh, fv] : maps) {
                fence_costs += m.get_area() * (fh.get_perimeter() + fv.get_perimeter());
            }
        }
        return fence_costs;
    };
    size_t get_fence_bulk_discount_costs() {
        size_t fence_costs{0};
        for (const auto &[plant, maps] : regions) {
            for (const auto &[m, fh, fv] : maps) {
                fence_costs += m.get_area() * (fh.count_sides() + fv.count_sides() + m.get_internal_cross_points() * 2);
            }
        }
        return fence_costs;
    };
    void print() {
        for (const auto &[plant, maps] : regions) {
            for (const auto &[m, fh, fv] : maps) {
                m.print();
                fh.print();
                fv.print();
            }
        }
    }

  private:
    Map<char> map;
    size_t garden_rows;
    size_t garden_columns;
    std::map<char, std::vector<std::tuple<Region, HorizontalFence, VerticalFence>>> regions;
    void set_regions() {
        std::vector<char> plants = map.get_unique_map_elements();
        std::map<char, positions> plants_positions{};
        for (char plant : plants) {
            plants_positions[plant] = map.get_all_occurances(plant);
        }

        std::map<char, std::vector<positions>> plants_area_positions{};
        for (auto &[plant_type, p] : plants_positions) {
            Neighbourhood n(map, plant_type);
            plants_area_positions[plant_type] = n.get_neighbourhoods();
        }

        for (const auto &[plant_type, plant_areas] : plants_area_positions) {
            for (const positions &area : plant_areas) {
                Region m(plant_type, area, garden_rows, garden_columns);
                HorizontalFence fh(m);
                VerticalFence fv(m);
                regions[plant_type].push_back({m, fh, fv});
            }
        }
    };
};
