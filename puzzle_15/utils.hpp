#include "utils/mover.hpp"
#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

typedef std::vector<Position> positions;

class Robot : public Mover {
  public:
    Robot(const Position &pos, Map<char> map) : Mover(pos), map(map){};
    void move() {
        map.add_element_at_position(get_position(), '.');
        Position pos = get_next_position();
        if (map.get_entry(pos) == '.') {
            move_to_next_position();
        } else if (map.get_entry(pos) == wall_char) {
        } else {
            Position boxes_end = get_num_boxes_in_sight();
            if (map.get_entry(boxes_end) != wall_char) {
                move_to_next_position();
                move_boxes(boxes_end);
            };
        }
        map.add_element_at_position(get_position(), robot_char);
    };
    Map<char> get_map() const { return map; };

  private:
    Map<char> map;
    char box_char{'O'};
    char wall_char{'#'};
    char robot_char{'@'};
    Position get_num_boxes_in_sight() const {
        Direction dir = get_direction();
        Mover m(dir, get_position());
        m.move_to_next_position();
        char type = map.get_entry(m.get_position());
        while (type == box_char) {
            m.move_to_next_position();
            type = map.get_entry(m.get_position());
        }
        return m.get_position();
    };
    void move_boxes(const Position &end_pos) {
        Direction dir = get_direction();
        Mover m(dir, end_pos);
        m.rotate();
        m.rotate();
        while (m.get_position() != get_position()) {
            map.add_element_at_position(m.get_position(), box_char);
            m.move_to_next_position();
        }
    }
};

class Warehouse {
  public:
    Warehouse(const Map<char> &map) : map(map) { init_robot(); };
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

  private:
    Map<char> map;
    size_t gps_coordinates_sum{0};
    std::unique_ptr<Robot> rob;
    void init_robot() {
        positions start = map.get_all_occurances('@');
        assert(start.size() == 1);
        rob = std::make_unique<Robot>(start[0], map);
    };
    void set_gps_coordinates_sum() {
        positions boxes = map.get_all_occurances('O');
        for (const Position &box : boxes) {
            gps_coordinates_sum += box[0] * 100 + box[1];
        }
    };
};
