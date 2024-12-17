#include <iostream>
#include <string>
#include <vector>

#include "puzzle_15/puzzle.hpp"
#include "puzzle_15/utils.hpp"

int main() {
    const std::vector<std::string> map = get_map();
    const std::string movements = get_movements();

    Warehouse w(map);
    w.move_robot(movements);
    std::cout << "sum of GPS coordinates = " << w.get_gps_coordinates_sum() << std::endl;
    return 0;
}
