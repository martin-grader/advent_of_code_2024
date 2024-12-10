#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

std::vector<int> extract_vector_by_typle_index(const std::vector<std::array<int, 2>> &puzzle, int array_idx) {
    std::vector<int> extracted_vector{};
    for (std::array<int, 2> a : puzzle) {
        extracted_vector.push_back(a[array_idx]);
    }
    return extracted_vector;
}

void sort_vector(std::vector<int> &v) { std::sort(v.begin(), v.end()); }

int get_accumulated_distance(const std::vector<int> &left, const std::vector<int> &right) {
    int distance{0};
    for (size_t i = 0; i < left.size(); i++) {
        distance += std::abs(left[i] - right[i]);
    }
    return distance;
}

int similarity_score_two_vectors(const std::vector<int> &left_sorted, const std::vector<int> &right_sorted) {
    int similarity_score{0};
    for (int left : left_sorted) {
        auto first_right_occurance = std::find(right_sorted.begin(), right_sorted.end(), left);
        if (first_right_occurance != right_sorted.end()) {
            auto last_right_occurance = std::find(right_sorted.rbegin(), right_sorted.rend(), left);
            int occurances = static_cast<int>(std::distance(last_right_occurance.base(), first_right_occurance));
            similarity_score += left * std::abs(occurances);
        }
    }
    return similarity_score;
}

int get_similarity_score(const std::vector<std::array<int, 2>> &puzzle) {
    std::vector<int> left_column = extract_vector_by_typle_index(puzzle, 0);
    std::vector<int> right_column = extract_vector_by_typle_index(puzzle, 1);
    sort_vector(left_column);
    sort_vector(right_column);
    int similarity_score = similarity_score_two_vectors(left_column, right_column);
    return similarity_score;
}

int get_distance(const std::vector<std::array<int, 2>> &puzzle) {
    std::vector<int> left_column = extract_vector_by_typle_index(puzzle, 0);
    std::vector<int> right_column = extract_vector_by_typle_index(puzzle, 1);
    sort_vector(left_column);
    sort_vector(right_column);
    int distance = get_accumulated_distance(left_column, right_column);
    return distance;
}
