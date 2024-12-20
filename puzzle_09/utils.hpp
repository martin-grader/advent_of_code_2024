#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

void print(const std::vector<size_t> &v) {
    for (size_t i : v) {
        if (i != std::numeric_limits<size_t>::max()) {
            std::cout << i;
        } else {
            std::cout << '.';
        }
    }
    std::cout << std::endl;
}

std::vector<size_t> compress_disk_content(const std::vector<size_t> &puzzle) {
    std::vector<size_t> reordered_disk_map{};
    size_t iter_forw{0};
    size_t iter_back{puzzle.size() - 1};
    while (iter_forw <= iter_back) {
        if (puzzle[iter_forw] != std::numeric_limits<size_t>::max()) {
            reordered_disk_map.push_back(puzzle[iter_forw]);
            iter_forw++;
        } else {
            while (puzzle[iter_back] == std::numeric_limits<size_t>::max()) {
                iter_back--;
            }
            if (iter_forw < iter_back) {
                reordered_disk_map.push_back(puzzle[iter_back]);
                iter_back--;
                iter_forw++;
            }
        }
    }
    return reordered_disk_map;
}

size_t find_closest_empty_sequence(const std::vector<size_t> disk_map, size_t sequence_size, size_t max_idx) {
    for (size_t j = 1; j <= max_idx; j += 2) {
        if (disk_map[j] >= sequence_size) {
            return j;
        }
    }
    return max_idx;
}

std::vector<size_t> loosely_compress_disk_content(std::vector<size_t> disk, std::vector<size_t> disk_map) {
    std::vector<size_t> original_disk_map(disk_map);
    for (size_t disk_map_idx_candidate = disk_map.size() - 1; disk_map_idx_candidate > 0; disk_map_idx_candidate -= 2) {
        assert(disk_map_idx_candidate % 2 == 0);
        size_t ID = disk_map_idx_candidate / 2;
        size_t insert_size = original_disk_map[disk_map_idx_candidate];
        size_t disk_map_idx_insert = find_closest_empty_sequence(disk_map, insert_size, disk_map_idx_candidate);
        if (disk_map_idx_insert < disk_map_idx_candidate) {
            size_t disk_idx_blank = std::accumulate(disk_map.begin(), disk_map.begin() + disk_map_idx_insert, 0);
            size_t disk_idx_back = std::accumulate(disk_map.begin(), disk_map.begin() + disk_map_idx_candidate, 0);
            disk_map[disk_map_idx_insert] -= insert_size;
            disk_map[disk_map_idx_insert - 1] += insert_size;
            for (size_t k = 0; k < insert_size; k++) {
                disk[disk_idx_blank + k] = ID;
                disk[disk_idx_back + k] = std::numeric_limits<size_t>::max();
            }
        }
    }
    return disk;
}

size_t calculate_checksum(const std::vector<size_t> &map) {
    size_t checksum{0};
    for (size_t i = 0; i < map.size(); i++) {
        if (map[i] != std::numeric_limits<size_t>::max()) {
            checksum += i * map[i];
        }
    }
    return checksum;
}

std::vector<size_t> get_disk_content(const std::vector<size_t> &disk_map) {
    std::vector<size_t> disk_content{};
    for (size_t i = 0; i < disk_map.size(); i++) {

        if (i % 2 == 0) {
            const size_t ID = i / 2;
            for (size_t j = 0; j < disk_map[i]; j++) {
                disk_content.push_back(ID);
            }
        } else {
            for (size_t j = 0; j < disk_map[i]; j++) {
                disk_content.push_back(std::numeric_limits<size_t>::max());
            }
        }
    }
    return disk_content;
}

std::vector<size_t> convert_map(const std::string &map) {
    std::vector<size_t> converted_map{};
    for (size_t i = 0; i < map.size(); i++) {
        const std::string a{map[i]};
        const size_t disk_entry = std::stoi(a);
        assert(disk_entry >= 0);
        assert(disk_entry < 10);
        converted_map.push_back(disk_entry);
    }
    return converted_map;
}

size_t get_checksum(const std::string &disk_map) {
    assert(disk_map.size() % 2 == 1);
    const std::vector<size_t> converted_map = convert_map(disk_map);
    const std::vector<size_t> disk_content = get_disk_content(converted_map);
    const std::vector<size_t> compressed_disk_content = compress_disk_content(disk_content);
    size_t checksum = calculate_checksum(compressed_disk_content);
    return checksum;
}

size_t get_updated_checksum(const std::string &disk_map) {
    assert(disk_map.size() % 2 == 1);
    const std::vector<size_t> converted_map = convert_map(disk_map);
    const std::vector<size_t> disk_content = get_disk_content(converted_map);
    const std::vector<size_t> compressed_disk_content = loosely_compress_disk_content(disk_content, converted_map);
    size_t checksum = calculate_checksum(compressed_disk_content);
    return checksum;
}
