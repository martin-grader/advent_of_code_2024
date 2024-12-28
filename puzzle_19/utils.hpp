#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

class DesignFinder {
  public:
    DesignFinder(const std::vector<std::string> &patterns, const std::string &design)
        : patterns(patterns), design(design) {
        set_match_range();
    }
    bool is_possible() {

        for (const auto &match : match_range) {
            if (std::get<0>(match) == 0) {
                nesting_counter = 0;
                if (match_chain_until_end(match)) {
                    return true;
                }
            }
        }
        return false;
    }

  private:
    std::vector<std::string> patterns;
    std::string design;
    std::vector<std::tuple<size_t, size_t>> match_range{};
    size_t nesting_counter{0};
    void set_match_range() {
        for (const std::string &p : patterns) {
            size_t find_start{0};
            size_t idx_pattern_start = design.find(p, find_start);
            while (idx_pattern_start != design.npos) {
                size_t idx_pattern_end = idx_pattern_start + p.size();
                match_range.push_back({idx_pattern_start, idx_pattern_end});
                find_start = idx_pattern_end;
                idx_pattern_start = design.find(p, find_start);
            }
        }
        std::sort(match_range.begin(), match_range.end());
    }

    bool match_chain_until_end(const std::tuple<size_t, size_t> &match_start) {
        if (nesting_counter > design.size()) {
            return false;
        }
        nesting_counter++;
        if (match_is_end(match_start)) {
            return true;
        }
        const size_t expected_start = std::get<1>(match_start);
        for (const auto &match : match_range) {
            const size_t match_start = std::get<0>(match);
            if (match_start == expected_start) {
                if (match_chain_until_end(match)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool match_is_end(const std::tuple<size_t, size_t> &match) {
        const size_t match_end = std::get<1>(match);
        const bool end_found = match_end == design.size();
        return end_found;
    }
};

class Onsen {
  public:
    Onsen(const std::vector<std::string> &patterns) : patterns(patterns) {}
    size_t get_number_of_possible_designs(const std::vector<std::string> &designs) {
        size_t number_of_possible_designs{0};
        for (const std::string &d : designs) {
            DesignFinder f(patterns, d);
            if (f.is_possible()) {
                number_of_possible_designs++;
            }
        }
        return number_of_possible_designs;
    };

  private:
    std::vector<std::string> patterns;
};
