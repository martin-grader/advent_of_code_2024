#include "utils/mover.hpp"
#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

typedef std::vector<Position> positions;

struct MapElements {
    char wall{'#'};
    char robot{'@'};
    char box{'O'};
    char box_left{'['};
    char box_right{']'};
    char blank{'.'};
};

class Box : public Mover, public MapElements {
  public:
    Box(const Direction &dir, const Position &pos, char type) : Mover(dir, pos), type(type){};
    bool operator==(const Box &rhs) const { return (get_position() == rhs.get_position() && type == rhs.get_type()); }
    char get_type() const { return type; };
    Box get_neighbour_box() {
        Position pos = get_position();
        Direction dir = get_direction();
        if (type == box_left) {
            return Box(dir, pos.get_right_neighbour(), box_right);
        } else {
            return Box(dir, pos.get_left_neighbour(), box_left);
        }
    };

  private:
    char type;
};

class BoxManager : public MapElements {
  public:
    BoxManager(const Position &robot_pos, const Direction &robot_dir, Map<char> &map)
        : robot_pos(robot_pos), robot_dir(robot_dir), map(map){};
    Map<char> get_map() const { return map; };
    void set_boxes() {
        boxes.clear();
        boxes.push_back(Box(robot_dir, robot_pos, robot));
        bool boxes_remain_ahead{true};
        while (boxes_remain_ahead) {
            boxes_remain_ahead = add_next_boxes();
        };
    };
    bool boxes_are_movable() {
        bool are_movable{true};
        for (Box &b : boxes) {
            Position next_box_pos = b.get_next_position();
            if (map.get_entry(next_box_pos) == wall) {
                are_movable = false;
            }
        }
        return are_movable;
    }
    void move_boxes() {
        for (Box &b : boxes) {
            map.add_element_at_position(b.get_position(), blank);
        }
        for (Box &b : boxes) {
            b.move_to_next_position();
        }
        for (Box &b : boxes) {
            map.add_element_at_position(b.get_position(), b.get_type());
        }
    }

  private:
    Position robot_pos;
    Direction robot_dir;
    Map<char> map;
    std::vector<Box> boxes;
    bool add_next_boxes() {
        bool box_added = false;
        std::vector<Box> new_boxes;
        for (Box &b : boxes) {
            Position next_box_pos = b.get_next_position();
            Direction dir = b.get_direction();
            char next_box_element = map.get_entry(next_box_pos);
            if (next_box_element == box_left || next_box_element == box_right || next_box_element == box) {
                Box next_box(dir, next_box_pos, next_box_element);
                if (std::find(boxes.begin(), boxes.end(), next_box) == boxes.end()) {
                    new_boxes.push_back(next_box);
                    if ((dir == Direction::top || dir == Direction::bottom) && next_box_element != box) {
                        new_boxes.push_back(next_box.get_neighbour_box());
                    }
                    box_added = true;
                }
            }
        }
        for (const Box &b : new_boxes) {
            boxes.push_back(b);
        }
        return box_added;
    }
};

class Robot : public Mover {
  public:
    Robot(const Position &pos, Map<char> map) : Mover(pos), map(map){};
    void move() {
        BoxManager bm(get_position(), get_direction(), map);
        bm.set_boxes();
        if (bm.boxes_are_movable()) {
            bm.move_boxes();
            move_to_next_position();
        }
        map = bm.get_map();
    };
    Map<char> get_map() const { return map; };

  private:
    Map<char> map;
};

class Warehouse : public MapElements {
  public:
    Warehouse(const Map<char> &map) : map(map){};
    void move_robot(const std::string &movements) {
        for (char direction : movements) {
            rob->set_direction(direction);
            rob->move();
        };
        map = rob->get_map();
    };
    size_t get_gps_coordinates_sum() {
        set_gps_coordinates_sum();
        return gps_coordinates_sum;
    };
    void init_robot() {
        positions start = map.get_all_occurances(robot);
        assert(start.size() == 1);
        rob = std::make_unique<Robot>(start[0], map);
    };
    virtual char get_box_char() const { return box; };

  protected:
    Map<char> map;
    size_t gps_coordinates_sum{0};
    std::unique_ptr<Robot> rob;
    void set_gps_coordinates_sum() {
        positions boxes = map.get_all_occurances(get_box_char());
        for (const Position &box : boxes) {
            gps_coordinates_sum += box[0] * 100 + box[1];
        }
    };
};

class WiderWarehouse : public Warehouse {
  public:
    WiderWarehouse(const Map<char> &this_map) : Warehouse(this_map) { extend_warehouse(); };

  private:
    char get_box_char() const override { return '['; };
    void extend_warehouse() {
        Map<char> wider_map(map.rows, map.columns * 2);
        for (size_t row = 0; row < map.rows; row++) {
            for (size_t col = 0; col < map.columns; col++) {
                char element = map.get_entry(row, col);
                size_t wide_col = col * 2;
                if (element == wall) {
                    wider_map.add_element_at_position(row, wide_col, wall);
                    wider_map.add_element_at_position(row, wide_col + 1, wall);

                } else if (element == box) {
                    wider_map.add_element_at_position(row, wide_col, box_left);
                    wider_map.add_element_at_position(row, wide_col + 1, box_right);

                } else if (element == robot) {
                    wider_map.add_element_at_position(row, wide_col, robot);
                }
            }
        }
        map = wider_map;
    };
};
