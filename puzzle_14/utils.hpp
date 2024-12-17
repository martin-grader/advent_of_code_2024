#include "utils/mover.hpp"
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

typedef std::vector<Position> positions;

class Robot {
  public:
    Robot(){};
    Robot(const Position &pos, const Map<char> &map, int v_rows, int v_columns)
        : pos(pos), map_size_rows(map.rows), map_size_columns(map.columns), vel_rows(v_rows), vel_columns(v_columns){};
    void move(size_t ticks) {
        for (size_t i = 0; i < ticks; i++) {
            move();
        }
    };
    Position get_pos() const { return pos; };

  private:
    Position pos;
    int map_size_rows;
    int map_size_columns;
    int vel_rows;
    int vel_columns;
    void move() {
        move_rows();
        move_columns();
    };
    void move_rows() {
        int next_row = static_cast<int>(pos[0]) + vel_rows;
        if (next_row < 0) {
            size_t row = static_cast<size_t>(map_size_rows + next_row);
            pos.set_row(row);
        } else if (next_row >= map_size_rows) {
            size_t row = static_cast<size_t>(next_row - map_size_rows);
            pos.set_row(row);
        } else {
            size_t row = static_cast<size_t>(next_row);
            pos.set_row(row);
        }
    };
    void move_columns() {
        int next_col = static_cast<int>(pos[1]) + vel_columns;
        if (next_col < 0) {
            size_t col = static_cast<size_t>(map_size_columns + next_col);
            pos.set_column(col);
        } else if (next_col >= map_size_columns) {
            size_t col = static_cast<size_t>(next_col - map_size_columns);
            pos.set_column(col);
        } else {
            size_t col = static_cast<size_t>(next_col);
            pos.set_column(col);
        }
    };
};

class RobotFactory {
  public:
    RobotFactory(const Map<char> &map) : map(map){};
    void parse(const std::string raw_robot) {

        size_t start_row = get_start_row(raw_robot);
        size_t start_column = get_start_column(raw_robot);
        int vel_row = get_vel_row(raw_robot);
        int vel_column = get_vel_column(raw_robot);
        Position pos(start_row, start_column);
        r = Robot(pos, map, vel_row, vel_column);
    };
    Robot get_robot() const { return r; };

  private:
    Map<char> map;
    Robot r;
    size_t get_start_column(const std::string &s) {
        auto idx1 = s.find("p=") + 2;
        auto idx2 = s.find(",");
        std::string dx = s.substr(idx1, idx2 - idx1);
        return std::stoi(dx);
    };
    size_t get_start_row(const std::string &s) {
        auto idx1 = s.find(",") + 1;
        auto idx2 = s.find(" ");
        std::string dx = s.substr(idx1, idx2 - idx1);
        return std::stoi(dx);
    };
    int get_vel_column(const std::string &s) {
        auto idx1 = s.find("v=") + 2;
        auto idx2 = s.find(",", idx1);
        std::string dx = s.substr(idx1, idx2 - idx1);
        return std::stoi(dx);
    };
    int get_vel_row(const std::string &s) {
        auto idx1 = s.rfind(",") + 1;
        std::string dx = s.substr(idx1);
        return std::stoi(dx);
    };
};

class TickMap : public Map<size_t> {
  public:
    TickMap(size_t rows, size_t columns) : Map(rows, columns), christmas_tree(rows, columns) { set_christmas_tree(); };
    void tick(const Position &pos) {
        size_t element = get_entry(pos);
        if (element == void_char) {
            add_element_at_position(pos, 1);
        } else {
            add_element_at_position(pos, element + 1);
        }
    };
    size_t count_ticks() {
        size_t ticks{0};
        for (size_t element : get_unique_map_elements()) {
            ticks += element * count_occurances(element);
        }
        return ticks;
    };
    bool is_christams_tree() {
        size_t r_value = calc_r_value();
        return r_value > 300;
    };

  private:
    Map<size_t> christmas_tree;
    void set_christmas_tree() {
        size_t box_size{christmas_tree.rows / 4};
        for (size_t i = box_size; i < christmas_tree.rows - box_size; i++) {
            for (size_t j = box_size; j < christmas_tree.columns - box_size; j++) {
                christmas_tree.add_element_at_position(i, j, 1);
            }
        }
        // christmas_tree.print();
    };
    size_t calc_r_value() {
        size_t r_value{0};
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                if ((get_entry(i, j) != christmas_tree.void_char) &&
                    (christmas_tree.get_entry(i, j) != christmas_tree.void_char)) {
                    r_value++;
                }
            }
        }
        return r_value;
    };
};

class Headquarter {
  public:
    Headquarter(const std::vector<std::string> raw_robots, size_t rows, size_t columns)
        : map(rows, columns), map_tl(rows, columns), map_tr(rows, columns), map_bl(rows, columns),
          map_br(rows, columns) {
        set_robots(raw_robots);
        assert(rows % 2 == 1);
        assert(columns % 2 == 1);
    };
    void calc_safety_factor(size_t ticks = 0) {
        for (Robot &r : robots) {
            r.move(ticks);
            const Position r_pos = r.get_pos();
            if (r_pos[0] < (map.rows - 1) / 2 && r_pos[1] < (map.columns - 1) / 2) {
                map_tl.tick(r_pos);
            } else if (r_pos[0] < (map.rows - 1) / 2 && r_pos[1] > (map.columns - 1) / 2) {
                map_tr.tick(r_pos);
            } else if (r_pos[0] > (map.rows - 1) / 2 && r_pos[1] < (map.columns - 1) / 2) {
                map_bl.tick(r_pos);
            } else if (r_pos[0] > (map.rows - 1) / 2 && r_pos[1] > (map.columns - 1) / 2) {
                map_br.tick(r_pos);
            }
        }
        safety_factor = map_tl.count_ticks() * map_tr.count_ticks() * map_bl.count_ticks() * map_br.count_ticks();
    };
    size_t get_safety_factor() const { return safety_factor; };
    size_t get_christms_tree_iterations() {
        size_t counter{0};
        bool christmas_tree_finished{false};
        while (!christmas_tree_finished) {
            counter++;
            TickMap this_map(map.rows, map.columns);
            for (Robot &r : robots) {
                r.move(1);
                const Position r_pos = r.get_pos();
                this_map.tick(r_pos);
            }
            christmas_tree_finished = this_map.is_christams_tree();
            if (christmas_tree_finished) {
                // this_map.print();
            }
        }
        return counter;
    };

  private:
    size_t safety_factor{0};
    std::vector<Robot> robots;
    Map<char> map;
    TickMap map_tl;
    TickMap map_tr;
    TickMap map_bl;
    TickMap map_br;
    void set_robots(const std::vector<std::string> &raw_robots) {
        RobotFactory p(map);
        for (const std::string &raw_robot : raw_robots) {
            p.parse(raw_robot);
            robots.push_back(p.get_robot());
        }
    };
};
