#include <string>
#include <vector>

std::vector<std::string> get_puzzle() {
    std::vector<std::string> puzzle{
        "##############################################################################################################"
        "###############################",
        "#...#.................................#...#...#...............#...............#.........#...............#...#."
        "....#.........#.....#........E#",
        "#.###.#.#####.###########.#.#.#####.#.#.#.#.#.#.###.#####.#.###.#########.#.#.#.#.#####.###.#######.#####.#.#."
        "#.#.#######.#.#.#.###.###.###.#",
        "#.........#...#.........#.#.#.........#.#...#.....#.....#.#.....#.........#.#...#.#...#...#.....#...#........."
        "................#.....#...#.#.#",
        "#######.###.#####.###.###.#########.#.#.###############.###.#####.#########.#.###.###.###.#####.#.#.#.########"
        "#.###.#.#.#.###.#######.###.#.#",
        "#.........#.....#...#.#...#.........#...#...#...#.............#...#.#.....#.#...#...#...#.......#...#.....#..."
        "#...#...#.#...#.....#...#...#.#",
        "#.#######.#.###.#.#.###.###.#######.#.#.#.#.#.###.###.#.#####.#.###.#.#.#.#.#.#.###.#.#.#.#######.#.#####.#.#."
        "###.#####.###.###.###.###.#.#.#",
        "#.#...#.#.....#.#.....................#...#...#...#.#.#...#...#.#.....#.#.#...#...#.#.........#...#.....#.#.#."
        "..#.....#.....................#",
        "#.#.#.#.#####.#.#####.#.###.#.#.#.#.#.#.#######.###.#.###.#.#.#.###.###.#####.###.#.#.#.#.#.###.###.###.#.#.##"
        "#.#####.###.#####.#.###.#.#####",
        "#.#.#.#.......#.....#.#.....#.#.#...#...#.........................#...#.........#.#.#.#...#.#.....#.#...#.#..."
        "#.#.....#.#.....#.#.#.......#.#",
        "#.#.#.#######.#####.#.#######.#.###.#.###.#######.#######.#.#.#.#.###.#######.###.#.###.#.###.#####.#.###.#.#."
        "###.#####.#####.###.#######.#.#",
        "#...#.......#.......................#.#...#.....#...#...#.#...#.#.#.......#.......#...#.#.#...#...#.#.....#.#."
        "..#...#.............#...#.#...#",
        "#.###.#####.#########.###.#.#####.#.#.#.#####.#.###.#.#.###.#.###.#########.#.#######.#.#.#.###.#.#.##########"
        "#.###.#.#########.###.#.#.###.#",
        "#...#.....#.#...#.........#.#...#...#...#.....#...#.#.#.....#...#...#.......#.......#.#.#.#.#................."
        "........#.......#.#...#.#...#.#",
        "#####.###.#.#.#.#.###.#####.#.#.###.#####.#########.#.#####.###.#.#.#.#######.#.#.###.#.#.#.#.###.#.###.######"
        "###.#.###.#####.#.#.###.#.#.#.#",
        "#.....#.....#.#.#...#.#.....#.#.#.......#...........#.....#.....#.#.#.#.#.......#.#...#.#...#...#...#...#....."
        "..#.#.....#...#.#.#.#...#.#...#",
        "#.###.#######.#####.#.#.#####.###.#######.###.###########.#####.###.#.#.#.###.###.#.###.#######.#.#.#.###.###."
        "###.#######.###.#.#.#.#########",
        "#.#.......#...#.......#.#...........#.....#.............#.....#.#...#.#.....#.#...#...#.#.#...#.#.#...#.#.#.#."
        "............#...#.#.#.#.......#",
        "#.#.#.###.#.#.#.#######.#.#####.#####.#######.#########.#####.#.#.#.#.#######.#######.#.#.#.#.#.#.###.#.#.#.##"
        "###########.#.#####.#.#.#####.#",
        "#.#.....#.#.#...#...#...#.#...#.#.....#.....#.....#...#.#.....#.#.#.#.....#...#.......#.#.#.#...#.#...#.#....."
        "#.#...#...#.#.......#...#...#.#",
        "#.###.#.#.#####.#.#.#.###.#.#.###.#####.###.###.#.#.#.#.#.#####.#.#######.#.#.#.#######.#.#.#####.#.#.#.#####."
        "#.#.#.###.#.#########.###.#.#.#",
        "#.......#.....#.#.#...#...#.#.#...#...#...#.#.....#.#...#.#...#.#.#.......#.#.#...#...#...#.......#.#.....#..."
        "..#.#...#...#.............#.#.#",
        "#.###.#######.#.#.#########.#.#.###.#.###.#.#.#####.#####.#.#.#.#.#.#######.#.###.#.#.#.#.#######.#.#######.##"
        "###.###.#.#.#.#####.#########.#",
        "#.....#.....#.#.#.........#.#...#...#...#.#...#...#.#.....#.#.#.#.#...#...#.#...#.#.#.#.......#.........#...#."
        "#...#...#.#...#...#.#.....#...#",
        "#####.#.###.#.#.#.#######.#.#####.#.###.#.#####.###.###.###.#.#.#.#.#.#.#.#.###.#.#.#.###.#####.#######.#.###."
        "#.###.###.#.#.#.###.#.###.#.###",
        "#...#.#...#.....#.#.....#.#.#...#.#.#.........#...#.....#.#.#...#.#...#.#...#...#.#.#.....#.......#...#.#.#..."
        "#.#.......#.#.#.....#.#.#.#...#",
        "#.#.#.###.#.###.#.###.###.#.#.#.#.#.#######.#.#.#.#######.#.#####.#.###.#.#######.#.#######.#####.#.###.#.#.##"
        "#.#.###.#####.#######.#.#.#.#.#",
        "#.#.#.#...#.....#...#...#...#.#...#...#...#.#...#...#.....#...#...#.#...#.#...#...#...#.....#...#.#...#.....#."
        "..#...#.......#.......#.#.#.#.#",
        "#.#.#.#.#.#####.###.###.#####.#######.###.#.#####.###.###.###.#.###.#.#.###.#.#.###.###.#####.#.#.###.#######."
        "#####.#######.#.#######.#.#.#.#",
        "#.#.#...#.#.....#.....#.............#...#...#...#.....#.#.......#...#.#.#...#...#...........#.#.#.....#......."
        "#.....#...#...#.#.......#...#.#",
        "#.###.###.#.#########.#.###########.###.#.###.#.###.###.#########.#####.#.#########.#.#######.#.#.#####.######"
        "#.#####.#.#.###.###.#######.#.#",
        "#.....#...#.........#.#...#.......#...#.#.....#...#.......#.....#...#...#.....#...#.#.#.#.....#.#.#..........."
        "#...#.......#.#.#...#.......#.#",
        "#.###.#.###########.#.###.#.#####.#####.#########.#.###.###.###.###.#.###.###.#.#.#.#.#.#.#####.###.#####.#.##"
        "#.#.#.#######.#.#.###.###.#.#.#",
        "#...#...#.....#.....#.#...#.#...#.#...#.....#...#.......#...#.....#...#.....#.#.#.#.#.#.#.#...#.....#.....#.#."
        "..#.....#.....#.......#...#...#",
        "###.#####.#.###.#####.#####.###.#.#.#.#####.#.#.#####.###.###.#####.###.###.#.#.#.###.#.#.###.#######.#####.#."
        "#######.#.#.#.#.#####.#.#.#.###",
        "#.........#.#...#...#.#.....#...#.#.#...#...#.#.#.....#...#...#.....#...#...#...#...#...#...#.......#...#...#."
        "#...#...#.#.#.#.....#.#.#.....#",
        "#.#########.#.#####.#.#.#####.###.#.###.#.#####.#.#####.###.#.#.#####.###.#########.###.###.#####.#####.#.###."
        "#.#.#.#####.#######.#.#.#.#.#.#",
        "#...#.......#.#.....#...#...#.#...#.#.#.#.....#.#.#...#.#.#.#.#...#...#...#...#...#.......#.....#.....#.#...#."
        "#.#.#.....#.#...............#.#",
        "###.#.#######.#.###.#####.#.#.#.###.#.#.###.#.#.#.#.###.#.#.#####.#.###.###.#.#.#.#.###########.#.#.#.#.###.#."
        "#.#.###.#.#.#.#.#.###.#.#.#.#.#",
        "#.....#...#...#.#.....#...#...#.#...#.#...#.#.#.....#...#.#.....#.#.#.......#...#.#.#.#.......#.#.#.#.#.#.#.#."
        "..#.#...#.#...#.#.#.#.#.#.#...#",
        "#.#####.#.#.###.#######.#.#####.#.###.###.###.#.#####.###.#####.#.#.#####.#######.#.#.#.###.#.#.#.#.###.#.#.##"
        "###.#.#.#.#.###.#.#.#.#.#.###.#",
        "#.........#.#...........#.....#...#.....#...#.#.#.....#.......#...#...#.......#...#.#.#.#...#...#.#.......#..."
        "........#.#.#...#.............#",
        "#.#.#####.#.#.###############.#######.#.###.#.#.#.#####.#.###.#######.#.#.###.#.###.#.#.#.#######.###.###.####"
        "#####.###.###.#.#.#.#.#.#.#.#.#",
        "#.#.#...#...#.#.............#.#.......#...#.#.#.#...#...#.#.#.......#.#.#.#.#.#.#.#...#.#.......#...#...#...#."
        "..........#...#.#.#.#...#...#.#",
        "#.#.#.#.#####.#########.###.#.#.###.#.#.#.#.#.#.###.#.###.#.#####.###.#.#.#.#.#.#.###.#.#.###.#.###.#.#####.#."
        "#########.#.###.#.###.#.#.###.#",
        "#.#.#.#.....#.#.......#...#.#...#.#.#.#.#.....#.#...#.#.#.#.....#.#...#.#.#...#.#.......#.#...#.#...#.....#..."
        "#.......#...#...#.......#.#.#.#",
        "#.#.#.#######.#.#####.#####.#####.#.###.#########.###.#.#.###.###.#.###.#.#.###.#.#####.#.#.###.#.#####.###.##"
        "#.#####.###.#######.###.#.#.#.#",
        "#.#.#.......#...#.#...#.......#...#.....#...#.....#.#...#...#.#...#.#...#.#.....#.....#.#.#.#...#.....#...#.#."
        "..#...#.#...#.....#.#.....#.#.#",
        "#.#.#.#####.#####.#.###.#####.###.#######.###.#####.#.#.###.#.#.###.#####.#.#.#######.#.#.#.#########.###.#.#."
        "#####.#.#####.###.#.#.#.#.#.#.#",
        "#.#...#.....#.....#.....#...#...#...#.......#.#.#.....#.....#.....#.....#.#.#...#.....#.#.#.........#.#.#.#..."
        "#.....#.#.....#...#.#...#.....#",
        "#.###.#.#####.###.#######.#.###.#.#.#.#.###.#.#.#.#####.#.#############.#.#.###.#.#####.#.#######.###.#.#.###."
        "#.#.#.#.#.#####.###.###.#####.#",
        "#...#.#...#.....#...#.....#...#.#.#...#.#...#.#.....#...#.#.............#.......#.#.....#...#.....#...#.#....."
        "#.#.#.#.#...#.#.#...#.#.....#.#",
        "###.#.###.#.#######.#.#.#.###.#.#.#####.#.###.#######.###.#.#############.#########.#.#.#.###.#.###.#.#.#.####"
        "#.#.#.#.###.#.#.#.###.#.###.#.#",
        "#...#...#...#.....#.#.#...#.#.....#...#.#...#.#.......#...#.#...#.......#.....#.....#...#.#...#.#...#...#....."
        "#.#.#.#.....#.#...............#",
        "#.###.#.#####.###.#.#.#####.#######.#.#.###.#.#.#.#.#######.#.###.#####.#####.#.###########.#.###.#####.###.#."
        "#.#.#########.#.#####.#.#.#.#.#",
        "#.#...#.#.......#.#.#.#.....#...#...#.#.#...#.#.#...........#.#...#...#...#...#.#.....#.......#...#.......#.#."
        "..#.......#...#...#.#.#...#.#.#",
        "#.#.#.#.#.#######.#.#.###.#.###.#.###.#.#.###.#.###.#.###.#.#.#.###.#.#.###.###.#.#.#.#.#####.#.###.#####.#.##"
        "#####.#.###.#.###.#.#.#.###.#.#",
        "#.....#.#.....#...#...#...#.....#...#.#...#...#...#.#...#...#...#...#.#.#...#...#.#.#...#.....#.#...#...#....."
        "....#.#.#...#.....#.....#...#.#",
        "###.#.#.#.#.#.#.###.###.#####.###.#.#.#####.###.#.#.###.#####.###.###.#.#.#####.#.#.#######.###.#.###.#.#.#.#."
        "###.#.###.#############.#.###.#",
        "#...#.#.#...#.#.#.#.....#.........#.#.#.....#.#.#.#.#.#...#.#...#.#...#.#.#.....#.#.......#.#.#.......#...#.#."
        "..#.#...#.....#.......#...#...#",
        "#.#.#.#.###.###.#.###.#########.###.#.#.#####.#.#.#.#.###.#.###.###.#.#.#.###.###.#.#####.#.#.#.###.#.#####.#."
        "#.#.###.#.###.#.#####.#.###.###",
        "#.#...#.....#...#.....#.............#.....#...#.#.#.#...#.#...#...#.#.#.#.#...#.#.#.......#.#.....#.#.#...#..."
        "#.#.#.#.....#...#...#.#.#.....#",
        "#.#.#.#######.#.#######.#############.###.#.#.#.#.#.###.#.#.#####.#.#.#.#.#.###.#.#.#######.#.#####.#.#.#.####"
        "#.#.#.#####.#######.#.#.#####.#",
        "#.............#.#...#.....#...#.......#.#.#.#...#.#.....#.#.....#.#.#.#.....#.....#.#...#.....#.....#........."
        "#.#.#.....#.........#.#.....#.#",
        "#.###.#######.###.#.#.#####.#.#.#####.#.#.#.#####.#######.#.###.#.#.#.#######.#####.###.#.#####.#######.###.#."
        "#.#.#####.#####.#.###.#.###.#.#",
        "#.#.......#...#...#...#.#...#.....#...#...#.#.....#.....#.#.#.#.......#...#.#...#.#...#...#.....#.#.....#...#."
        "..#...........#.#.#...#...#.#.#",
        "#.#.#####.#.###.#######.#.#######.#.###.#####.#.###.###.#.#.#.#########.#.#.###.#.###.#.###.#####.#.#.###.####"
        "#######.#######.#.#.###.###.#.#",
        "#...#.....#...#.#.......#.#...#...#.#.........#.#...#.#...#.#.#...#...#.#.#...#.....#.#.#...#.....#.#.....#..."
        "....#...#...................#.#",
        "#.###.#########.#.###.###.#.#.#.###.#############.#.#.#####.#.#.#.#.#.#.#.###.#.#.###.#.#.###.#.#.#.###.###.##"
        "###.#.###.###.#####.###.#.###.#",
        "#...#.....#.....#...#.#...#.#.#.....#...#.......#.#.....#.....#.#...#...#.#...#.#...#.#.#.#...#.#.#.#...#...#."
        "..#.#...#.#...#.....#.....#...#",
        "#########.#.#######.#.#.###.#.#####.#.#.#.#####.#.#.###.#.#####.#########.#.###.#.#.#.#.#.#.###.#.#.###.#.###."
        "#.#.#.###.#.###.#####.#.#######",
        "#.........#.......#.#.#.....#.....#.#.#...#...#...#...#.#...#...#.....#...#...#.#.#.....#.#.#...#.#.......#..."
        "#.#...#...#...#.#.......#.....#",
        "#.###############.#.#############.#.#.###.#.#.#####.#.#####.#.###.###.#####.#.#.#.#######.#.#.###.#########.##"
        "#.#####.#####.#.#.#####.#.###.#",
        "#...#.........#...#.............#.#...#...#.#.#.....#.....#.#.#...#.#.....#.#.#.#.......#.#.#...#.#.....#....."
        "#...#...#.#...#.#.#.#...#.#...#",
        "###.#.###.#####.#.#.###.###.###.#.#.#######.#.#####.#####.#.#.#.###.###.#.###.#.#######.#.#.###.#.###.#.#####."
        "###.#.###.#.###.#.#.#.###.#.#.#",
        "#...#.#.#.....#.#.#.#.#.......#.#.#.........#.....#.....#...#.#.....#...#...#.#...#...#...#...#.#.......#...#."
        "..#.#.#.....#...#...#.#...#.#.#",
        "#.#.#.#.#####.#.#.#.#.#######.###.#.#############.#.###.#.###.#.###.#.#####.#.###.###.#######.#.#.#.###.#.#.##"
        "#.#.#.#######.#####.#.#.###.#.#",
        "#.#.#.#.....#...#.#...#...#.#...#...#.#.....#...#.....#.#...#...#...#.....#.....#.....#.......#.#.......#.#..."
        "..#.#.........#.#...#...#...#.#",
        "#.###.#.#########.###.#.#.#.###.#####.#.#.###.#.#######.#.#####.#.#######.#####.#####.###.#####.#.#######.####"
        "###.###########.#.###.#.#.#####",
        "#.....#.......#.....#...#.............#.#.....#.........#.#.....#.......#.#...#...#.#...#.#.....#.#.........#."
        "..#.......#...#...#.#...#.....#",
        "#.###########.#.#.#########.#.#####.###.#######.###.#.#.###.#########.###.#.#.###.#.###.###.#####.#.#######.##"
        "#.#######.#.#.#.###.#########.#",
        "#...........#...#.#.......#.#.........#.#...#.......#.#.#...#.......#.#...#.#.........#.#...#.#...#...#.....#."
        "........#...#.#.#.....#.....#.#",
        "#########.#.#.###.#.#.#####.#.###.###.#.#.###.#.#.#.#.#.#.#####.#.#.###.###############.#.#.#.#.#####.#.#####."
        "#####.#.#####.#.#.###.#####.#.#",
        "#...#.......#...#...#.......#...#...#.....#...#.#...#.#.......#.#.#.....#.............#...#...#...#.#.#...#..."
        "......#.......#...#.#.#.....#.#",
        "#.###.###.###############.#.###.###.#######.###.#.#.#.#######.#.#.###.#.#.###########.#####.#####.#.#.###.#.##"
        "#####.#############.#.#.###.#.#",
        "#...#.#...#.....#...#...#.#...#.#...#.....#.#.#...#.#.........#.#.#.#.#...#...........#.....#.....#.#.#......."
        "#...#.#.............#...#...#.#",
        "#.#.#.#.#.#.###.#.#.#.#.###.#.#.#.###.###.#.#.#####.#############.#.#.#####.#######.###.#.#.#.#####.#.#.######"
        "#.#.###.#######.#####.#####.#.#",
        "#.#.#.#.#...#.#...#...#.....#...#.....#...#.#...#...#.....#.......#.#...........#...#...#.#...#...#...#...#..."
        "..#...#.....#.#.......#.......#",
        "###.#.#.#.###.#####.#######.###########.###.#.###.#######.#.###.###.#####.#.###.###.#.###.#.#.#.#.#####.#.#.##"
        "#####.#####.#.#######.#.#####.#",
        "#...#.#...#.............#...#...#.......#...#.............#...#...#.....#.#...#...#.#...#.#.#...#.......#....."
        "#.....#.#.........#...#.....#.#",
        "#.#.#.###.###.#.#########.###.#.#.#######.###################.###.#.###.#.###.###.#####.#.#############.#.####"
        "#.###.#.#.#######.###.#####.#.#",
        "#.#.#.#...#...#.#...#.....#...#.#.........#.........#...#.....#...#.#.#.#.#.#.#.#.....#.#...#.........#.#...#."
        "..#.....#.#.#...#.......#...#.#",
        "#.###.#.###.###.#.#.#.#####.###.###########.#######.#.#.#.###.#.###.#.#.#.#.#.#.###.###.###.#.#######.#.###.#."
        "###.#####.#.#.#.#####.#.#.#####",
        "#...#.#...#.......#.....#.....#...........#.......#...#...#...#.#.#.#.#...#.#.............#.#.#.#...#.#...#.#."
        "....#...#.#.#.#...............#",
        "###.#.#.#.#.###########.#.###.###########.#######.#########.###.#.#.#.#####.#####.#######.#.#.#.#.#.#.###.###."
        "#####.#.#.#.#.#######.###.###.#",
        "#...#.#.............#.#.#...#...#.....#.#.......#...........#...#.#...#.........#.#...#...#.....#.#...#.#.#..."
        "#.....#.#...#.#...#.#...#...#.#",
        "#.#.#.###.#.#.#.###.#.#.###.#.#.###.#.#.#.#####.#########.###.###.###.#######.#.#.#.#.###########.###.#.#.#.#."
        "#.#####.###.#.#.#.#.#.#.#.###.#",
        "#.#.#...#.#.#.....#.#.#.#...#.#.....#...#.....#...#...#...#...#.#.....#.....#.....#.#...#.........#.#...#.#.#."
        "#.#...#.....#...........#.#...#",
        "#.#####.#.#.#######.#.#.#.###.#########.#####.#####.#.#.###.###.#.#####.###.#######.###.#.#########.###.#.#.##"
        "#.###.###########.#.#.#####.#.#",
        "#.......#.....#.....#.#.#.#.....#.....#.#...#.......#.....#.#...#...#...#.#.#.........#.#...#.#.........#.#..."
        "#...#.......#.....#.......#.#.#",
        "#.###.#####.#.#.#####.#.#.#####.###.#.#.###.###############.#.#####.#.###.#.#.#.#####.#.###.#.#.#.#######.#.#."
        "#.#.#.###.#.#.#####.#.#.#.#.###",
        "#.#...........#.#...#...#.#...#.#...#.#.#.....#...#...#...#.#.....#.#.#...#...#.#...#.#.....#.#.#.#.......#.#."
        "......#...#.#.#.#...#.#...#...#",
        "#.###.#####.###.#.#.#####.#.#.#.#.###.#.#.###.#.#.#.###.#.#.#.###.#.#.#.#.#####.#.#.#.###.#.#.#.#.#.##########"
        "#.###.#.#####.#.#.#.#.#.#.###.#",
        "#...#.....#.....#.#.........#...#.#.....#.#.....#...#...#.#...#.#.#...#.#.#.....#.#.#.............#...#......."
        "#.....#...#...#...#.#...#...#.#",
        "###.#.###.#.#####.#######.#######.#.###.#.#######.###.###.#.#.#.#.#####.#.#.#####.#.###.#######.#.###.#.#####."
        "###.#.###.#.###.###.#######.#.#",
        "#...#.#.#.#.......#.....#...#.....#...#.#...#.....#...#.....#...#...#...#...#...#.#...#...#.....#.#...#.....#."
        "..#.#.....#.#.....#.#.......#.#",
        "#.###.#.#.#.#######.###.#.#.###.#######.###.#.#####.###.#######.#.#.#.#########.#.#.#.###.#.###.###.#######.##"
        "#.#.###.#.#.#.#####.#.#######.#",
        "#.....#.#.#.........#...#.#...#...#...#...#.#...#...#.........#.#.#.#...#.....#...#.#.#.#.#...#...#.....#...#."
        "..#.......#.#.#...#.#.#.......#",
        "#####.#.#.#.#######.#.###.###.#.#.#.#.###.#.#.#.#.#####.#.#.###.#.#####.#.###.#.#.#.#.#.#.###.###.#####.#.#.#."
        "###.#######.#.#.#.#.#.###.#####",
        "#.#...#...#.........#.....#...#.#...#...#...#.#...#...#.#.......#...#...#.#.....#...#.#.....#.#.#.....#.#...#."
        "#...#.......#.#.#.#.#...#.....#",
        "#.#.#.#.###.#########.#####.###.#####.#.#.###.###.#.#.###.#.#######.#.###.#######.#.#.#.#####.#.#####.#.#.#.#."
        "#####.#######.#.#.#.###.#.###.#",
        "#...#...#.#...#.....#.#...#...#.#...#.#.#.#...#.....#...#.#.......#...#.......#.....#...#.....#.....#...#.#.#."
        "....#.#...#...#.#.....#.#.#.#.#",
        "#.###.###.#.#.#.###.###.#.###.###.#.###.#.#.###.#######.#.###.#.#########.###.#.#####.###.#########.#######.##"
        "###.#.#.###.###.###.#.#.#.#.#.#",
        "#...........#...#.#.........#.....#...#.#.#.#...#...#.#.#...#.#.........#...#.#.....#.....#.......#.........#."
        "..#...#.....#.#.....#.#.#...#.#",
        "#.###.#.###.#####.#########.#########.#.#.#.#.###.#.#.#.###.#.###.#####.#.#.#.#####.#######.#####.###.###.####"
        "#.#####.#####.#####.###.#.#.#.#",
        "#.#...#.#.............#...#.#.....#...#...#.#.....#...#.....#.....#.....#.#.#...#...#.......#...#...#.#.#.#..."
        "....#...#.....#...#.....#...#.#",
        "#.#.###.#.#.###########.#.#.###.#.#.#######.#########.###.#.###.###.#####.#.#.#.#.#####.#.###.#####.#.#.#.#.#."
        "#####.###.###.#.#.#.#####.###.#",
        "#.#...#.#.#.#...........#...#.....#.......#.......#...#.#.#.#...#.#...#.....#...#...#...#.#.....#...#...#.#.#."
        "......#...#...#.#.........#.#.#",
        "#.###.#.#.###.#.#############.###.#######.#.###.###.###.#.#.#.###.###.#######.#.###.#.###.#.###.#.#.#####.#.##"
        "#########.#.###.###.#####.#.#.#",
        "#...#.#.#.#...#.#...#.#.......#...#.....#.........#.#...#.#...#.....#.......#.#.#...#.#.....#.#.#.#..........."
        "#.........#.#.#.#...........#.#",
        "###.#.#.#.#.#####.#.#.#.#####.#.###.#########.###.#.###.#.#####.###########.#.#.#.###.#.#####.#.#.#.#########."
        "#.#.#######.#.#.#.#######.###.#",
        "#...#.#.#.#.#.....#.#...#.....#...#.........#...#.......#.#.......#...#.....#.#.#...#.#...#...#...#.#.......#."
        "#.#.......#.#.....#.....#...#.#",
        "#.###.#.#.#.#.#####.###.#.###.###.#####.#######.#.#####.#.###.###.#.#.#.#####.#.###.#.###.#.#.#####.###.#.#.#."
        "###.#####.#.#.#####.###.#.#.#.#",
        "#.#.....#.#.......#...#.#.......#.#...#.....#...#.#...#.#...#.#.#...#.#.......#...#.#...#...#.#.......#.#.#.#."
        "..#.....#.#.#.#...#...#...#.#.#",
        "#.#.#####.#########.#.#########.#.#.#.#.#.#.#.#####.#.#.###.#.#.#####.#.###.#####.#.###.###.#.#.#####.#.#.####"
        "#.#####.#.#.###.#.###.###.#.#.#",
        "#.............#...#.#.#.....#...#...#.#...#.#.#.....#.#...#.#.....#.#.#.....#.#...#...#.#...#.#.#.....#.#....."
        "#...#...#.#.....#.....#.....#.#",
        "#.#.#####.#.###.#.###.#.###.#.#######.#.###.#.###.###.#.###.#####.#.#.#######.#.#####.#.#.#.#.#.###.#.#######."
        "###.#.###.#############.#.###.#",
        "#.#.......#.#...#...#.#...#...#...#...#...#.#.....#.#.#.#...#...#.#.#.#.........#.....#...#.#.#.#...#.#......."
        "..#.#...#.#.......#...#...#...#",
        "#.###.#######.#####.#.###.#####.#.#.#######.#######.#.###.###.#.#.#.#.#.###.#####.###.#.###.#.#.#.###.#.######"
        "###.#####.#.#####.#.#.###.#.#.#",
        "#.....................#...#...#.#...............#.#...#...#...#.#.#.#.#.........#.#...#.#...#.#...#...#......."
        "..#.#.....#.#.......#...#...#.#",
        "###.###.#######.###.#.#.#.#.#.#.#########.#####.#.#.###.###.###.#.#.#.###.#.#####.#.#.###.###.#.###.###.######"
        "#.#.#.#####.#.#######.#######.#",
        "#.#.....#.........#...#.......................#...#.....#.....#.#...#.....#.....#.#.#.....#...#.....#.....#..."
        "#.#...#.....#.....#.........#.#",
        "#.###############.#####.###.#.###.#.#.###.###.#######.#.#.#####.#####.#####.###.#.#.#######.#####.#######.#.##"
        "#.#######.#.#####.#.#.#.#####.#",
        "#.#.............#.......#...#...#...#.#.....#...#...#.#...#...#.....#...#...#.............#.#...#.....#...#.#."
        "........#.#...#...............#",
        "#.#.#.#########.###.#####.#####.###.#.###.#.###.#.#.#.#####.#.#####.###.#.#.#.###.#.#.#.###.#.#.#####.#.###.#."
        "#######.#####.#.###.#.#########",
        "#.#.#.#...#.........#...#.#...#.#...#.....#.#.#.#.#.#.#.....#.......................#.#.#...#.#.......#.#...#."
        "#.............#.#...#.......#.#",
        "#.#.#.#.#.###########.#.#.#.###.#########.#.#.#.#.#.#.#.#############.###.#.#######.###.#.###.#########.#.#.#."
        "#####.#######.###.###.#.###.#.#",
        "#...............#...#.#...#...#.......#...#.#.#.#.#...#.#...........#.#...#.........#...#.#...#...#...#.#.#.#."
        "#...#.#...#...#...#...#...#...#",
        "#.###.#.#.#.###.#.#.#.#######.#######.#.#.#.#.#.#.#####.#.###.#######.#.#####.#######.###.#.###.#.#.#.#.###.#."
        "#.#.###.#.#####.###.#.###.#.#.#",
        "#S..#...#.....#...#.................#...#.....#.........#...#.........#.........................#...#.......#."
        "..#.....#...........#.....#...#",
        "##############################################################################################################"
        "###############################",
    };
    return puzzle;
};
