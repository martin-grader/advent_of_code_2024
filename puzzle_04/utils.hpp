#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

class MatchesInString {
  public:
    MatchesInString(const std::string &key, const std::string &s) {
        std::string::size_type pos = 0;
        while ((pos = s.find(key, pos)) != std::string::npos) {
            matches++;
            match_mid_positions.push_back(pos + std::floor(key.size() / 2));

            pos += key.length();
        }
    };
    int get_matches() { return matches; };
    std::vector<int> get_match_mid_positions() { return match_mid_positions; };

  private:
    int matches{0};
    std::vector<int> match_mid_positions{};
};

int get_hotizontal_matches(const std::vector<std::string> &puzzle, const std::string &key) {
    int matches{0};
    for (std::string line : puzzle) {
        MatchesInString m(key, line);
        matches += m.get_matches();
    }
    return matches;
}

int get_vertical_matches(const std::vector<std::string> &puzzle, const std::string &key) {
    int matches{0};
    const int index = puzzle[0].size();
    for (int i = 0; i < index; i++) {
        std::string vertical_line{};
        for (std::string line : puzzle) {
            vertical_line.push_back(line[i]);
        }
        MatchesInString m(key, vertical_line);
        matches += m.get_matches();
    }
    return matches;
}

class CrossMatchesInterface {
  public:
    CrossMatchesInterface(const std::vector<std::string> &puzzle, const std::string &key)
        : offset(key.size()), rows(puzzle.size()), columns(puzzle[0].size()), puzzle(puzzle), key(key) {}
    int get_matches() {
        init(puzzle, key);
        return matches;
    };
    std::vector<std::tuple<int, int>> get_match_mid_positions() {
        init(puzzle, key);
        return match_mid_positions;
    };

  protected:
    void init(const std::vector<std::string> &puzzle, const std::string &key) {
        for (int row = get_rows_to_start(); row < get_rows_to_end(); row++) {
            for (int col = 0; col < columns - offset + 1; col++) {
                std::string lrtd_line{};
                for (int k = 0; k < offset; k++) {
                    lrtd_line.push_back(puzzle[get_next_cross_row(row, k)][col + k]);
                }
                MatchesInString m(key, lrtd_line);
                matches += m.get_matches();
                for (int match_mid_position : m.get_match_mid_positions()) {
                    std::tuple<int, int> row_col_mid_pos{get_next_cross_row(row, match_mid_position),
                                                         col + match_mid_position};
                    match_mid_positions.push_back(row_col_mid_pos);
                }
            }
        }
    };
    int matches{0};
    std::vector<std::tuple<int, int>> match_mid_positions{};
    const int offset{};
    const int rows{};
    const int columns{};
    const std::vector<std::string> puzzle{};
    const std::string key{};
    virtual int get_rows_to_start() = 0;
    virtual int get_rows_to_end() = 0;
    virtual int get_next_cross_row(int row, int offset) = 0;
};

class RightLeftCrossMatches : public CrossMatchesInterface {
  public:
    RightLeftCrossMatches(const std::vector<std::string> &puzzle, const std::string &key)
        : CrossMatchesInterface(puzzle, key){};

  protected:
    int get_rows_to_start() override { return offset - 1; };
    int get_rows_to_end() override { return rows; };
    int get_next_cross_row(int row, int offset) override { return row - offset; };
};

class LeftRightCrossMatches : public CrossMatchesInterface {
  public:
    LeftRightCrossMatches(const std::vector<std::string> &puzzle, const std::string &key)
        : CrossMatchesInterface(puzzle, key){};

  protected:
    int get_rows_to_start() override { return 0; };
    int get_rows_to_end() override { return rows - offset + 1; };
    int get_next_cross_row(int row, int offset) override { return row + offset; };
};

int get_results_all_alignements(const std::vector<std::string> &puzzle, std::string key) {
    int matches{0};
    matches += get_hotizontal_matches(puzzle, key);
    matches += get_vertical_matches(puzzle, key);
    RightLeftCrossMatches rlc_m(puzzle, key);
    LeftRightCrossMatches lrc_m(puzzle, key);
    matches += rlc_m.get_matches();
    matches += lrc_m.get_matches();
    return matches;
}

int get_all_occurances(const std::vector<std::string> &puzzle, std::string key) {
    int matches{0};
    matches += get_results_all_alignements(puzzle, key);
    std::reverse(key.begin(), key.end());
    matches += get_results_all_alignements(puzzle, key);
    return matches;
}

int get_n_matching_positions(const std::vector<std::tuple<int, int>> &left,
                             const std::vector<std::tuple<int, int>> &right) {
    int matches{0};
    for (std::tuple<int, int> left_subs : left) {
        auto it = std::find(right.begin(), right.end(), left_subs);
        if (it != right.end()) {
            matches++;
        }
    }
    return matches;
}

int get_star_shaped_occurances(const std::vector<std::string> &puzzle, std::string key) {
    int matches{0};
    RightLeftCrossMatches rlc_m(puzzle, key);
    LeftRightCrossMatches lrc_m(puzzle, key);
    std::reverse(key.begin(), key.end());
    RightLeftCrossMatches rlc_rev_m(puzzle, key);
    LeftRightCrossMatches lrc_rev_m(puzzle, key);
    const std::vector<std::tuple<int, int>> rlc_mid_positions = rlc_m.get_match_mid_positions();
    const std::vector<std::tuple<int, int>> lrc_mid_positions = lrc_m.get_match_mid_positions();
    const std::vector<std::tuple<int, int>> rlc_rev_mid_positions = rlc_rev_m.get_match_mid_positions();
    const std::vector<std::tuple<int, int>> lrc_rev_mid_positions = lrc_rev_m.get_match_mid_positions();
    matches += get_n_matching_positions(rlc_mid_positions, lrc_mid_positions);
    matches += get_n_matching_positions(rlc_mid_positions, lrc_rev_mid_positions);
    matches += get_n_matching_positions(rlc_rev_mid_positions, lrc_rev_mid_positions);
    matches += get_n_matching_positions(rlc_rev_mid_positions, lrc_mid_positions);

    return matches;
}
