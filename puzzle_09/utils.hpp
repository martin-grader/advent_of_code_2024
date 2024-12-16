#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

std::vector<int> compress_disk_content(const std::vector<int> &puzzle) {
    std::vector<int> reordered_disk_map{};
    size_t iter_forw{0};
    size_t iter_back{puzzle.size() - 1};
    while (iter_forw <= iter_back) {
        if (puzzle[iter_forw] != -1) {
            reordered_disk_map.push_back(puzzle[iter_forw]);
            iter_forw++;
        } else {
            while (puzzle[iter_back] == -1) {
                iter_back--;
            }
            reordered_disk_map.push_back(puzzle[iter_back]);
            iter_back--;
            iter_forw++;
        }
    }
    return reordered_disk_map;
}

long int calculate_checksum(const std::vector<int> &map) {
    long int checksum{0};
    for (size_t i = 0; i < map.size(); i++) {
        checksum += i * map[i];
        // std::cout << checksum << std::endl;
        // std::cout << i << std::endl;
    }
    return checksum;
}

std::vector<int> get_disk_content(const std::vector<int> &disk_map) {
    std::vector<int> disk_content{};
    for (size_t i = 0; i < disk_map.size(); i++) {

        if (i % 2 == 0) {
            const int ID = i / 2;
            for (int j = 0; j < disk_map[i]; j++) {
                disk_content.push_back(ID);
            }
        } else {
            for (int j = 0; j < disk_map[i]; j++) {
                disk_content.push_back(-1);
            }
        }
    }
    return disk_content;
}

std::vector<int> convert_map(const std::string &map) {
    std::vector<int> converted_map{};
    for (size_t i = 0; i < map.size(); i++) {
        const std::string a{map[i]};
        const size_t disk_entry = std::stoi(a);
        if (disk_entry >= 0 && disk_entry < 10) {
            converted_map.push_back(disk_entry);
        }
    }
    return converted_map;
}

void print(const std::vector<int> &v) {
    for (int i : v) {
        if (i != -1) {
            std::cout << i;
        } else {
            std::cout << '.';
        }
    }
    std::cout << std::endl;
}

long int get_checksum(const std::string &disk_map) {
    // std::cout << disk_map << std::endl;
    // std::cout << disk_map.size() % 2 << std::endl;
    const std::vector<int> converted_map = convert_map(disk_map);
    // print(converted_map);
    const std::vector<int> disk_content = get_disk_content(converted_map);
    // print(disk_content);
    const std::vector<int> compressed_disk_content = compress_disk_content(disk_content);
    // print(compressed_disk_content);
    long long int checksum = calculate_checksum(compressed_disk_content);
    // std::cout << std::numeric_limits<long int>::max() << std::endl;
    return checksum;
    // return 0;
    //  6323903789307
}
