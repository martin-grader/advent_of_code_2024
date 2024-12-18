#include <gtest/gtest.h>

#include "puzzle_15/utils.hpp"

TEST(WarehouseTest, test_gps_coordinates_sum_small) {
    std::vector<std::string> map = {
        "########", "#..O.O.#", "##@.O..#", "#...O..#", "#.#.O..#", "#...O..#", "#......#", "########",
    };
    std::string movements = "<^^>>>vv<v>>v<<";
    Warehouse w(map);
    w.init_robot();
    w.move_robot(movements);
    EXPECT_EQ(w.get_gps_coordinates_sum(), 2028);
}
TEST(WarehouseTest, test_gps_coordinates_sum_small_wide_warehouse) {
    std::vector<std::string> map = {
        "#######", "#...#.#", "#.....#", "#..OO@#", "#..O..#", "#.....#", "#######",
    };
    std::string movements = "<vv<<^^<<^^";
    WiderWarehouse ww(map);
    ww.init_robot();
    ww.move_robot(movements);
    EXPECT_EQ(ww.get_gps_coordinates_sum(), 105 + 207 + 306);
}

TEST(WarehouseTest, test_gps_coordinates_sum_large) {
    std::vector<std::string> map = {
        "##########", "#..O..O.O#", "#......O.#", "#.OO..O.O#", "#..O@..O.#",
        "#O#..O...#", "#O..O..O.#", "#.OO.O.OO#", "#....O...#", "##########",
    };
    std::string movements =
        "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^"
        "v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<<<v<^>>^^^"
        "^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>"
        ">v<v<v>vvv>^<><<>^><^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^>^>>^v>vv>^<<^v<>><<"
        "><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^"
        ">^^<>^>v<>^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>v^^>>><<^^<>>^v^<v^vv<>v^<<>^<"
        "^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^";
    Warehouse w(map);
    w.init_robot();
    w.move_robot(movements);
    EXPECT_EQ(w.get_gps_coordinates_sum(), 10092);

    WiderWarehouse ww(map);
    ww.init_robot();
    ww.move_robot(movements);
    EXPECT_EQ(ww.get_gps_coordinates_sum(), 9021);
}
