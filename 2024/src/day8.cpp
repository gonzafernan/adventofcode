/**
 * Advent of Code 2024
 * Day 8: Resonant Collinearity
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <vector>

using namespace std;

typedef pair<int, int> position_t;
typedef unordered_map<char, vector<position_t>> antenna_map_t;

void add_antenna(antenna_map_t &antenna_map, char frequency, position_t position) {
    antenna_map[frequency].push_back(position);
}

vector<position_t> get_antennas_antinodes_part1(position_t antenna1, position_t antenna2, int max_reach_x,
                                                int max_reach_y) {
    position_t antenna_left, antenna_right;
    vector<position_t> antinodes;
    antenna_left = (antenna1.first < antenna2.first) ? antenna1 : antenna2;
    antenna_right = (antenna1.first < antenna2.first) ? antenna2 : antenna1;
    int x1 = antenna_left.first;
    int x2 = antenna_right.first;
    int y1 = antenna_left.second;
    int y2 = antenna_right.second;
    position_t antinode1 = position_t(x1 - (x2 - x1), y1 - (y2 - y1));
    position_t antinode2 = position_t(x2 + (x2 - x1), y2 + (y2 - y1));
    if (antinode1.first >= 0 && antinode1.first < max_reach_x && antinode1.second >= 0 &&
        antinode1.second < max_reach_y) {
        antinodes.push_back(antinode1);
    }
    if (antinode2.first >= 0 && antinode2.first < max_reach_x && antinode2.second >= 0 &&
        antinode2.second < max_reach_y) {
        antinodes.push_back(antinode2);
    }
    return antinodes;
}

vector<position_t> get_antennas_antinodes_part2(position_t antenna1, position_t antenna2, int max_reach_x,
                                                int max_reach_y) {
    position_t antenna_left, antenna_right, antinode1, antinode2;
    vector<position_t> antinodes = {antenna1, antenna2};
    antenna_left = (antenna1.first < antenna2.first) ? antenna1 : antenna2;
    antenna_right = (antenna1.first < antenna2.first) ? antenna2 : antenna1;
    int x1 = antenna_left.first;
    int x2 = antenna_right.first;
    int y1 = antenna_left.second;
    int y2 = antenna_right.second;
    bool in_reach = true;
    int antinone_order = 1;
    while (in_reach) {
        antinode1 = position_t(x1 - antinone_order * (x2 - x1), y1 - antinone_order * (y2 - y1));
        if (antinode1.first >= 0 && antinode1.first < max_reach_x && antinode1.second >= 0 &&
            antinode1.second < max_reach_y) {
            antinodes.push_back(antinode1);
            antinone_order++;
        } else {
            in_reach = false;
        }
    }
    in_reach = true;
    antinone_order = 1;
    while (in_reach) {
        antinode2 = position_t(x2 + antinone_order * (x2 - x1), y2 + antinone_order * (y2 - y1));
        if (antinode2.first >= 0 && antinode2.first < max_reach_x && antinode2.second >= 0 &&
            antinode2.second < max_reach_y) {
            antinodes.push_back(antinode2);
            antinone_order++;
        } else {
            in_reach = false;
        }
    }
    return antinodes;
}

vector<position_t> get_all_antinodes(const antenna_map_t &antennas, int max_reach_x, int max_reach_y,
                                     bool with_resonance) {
    vector<position_t> antinodes;
    char frequency;
    vector<position_t> antennas_position;
    vector<position_t> antenna_antinodes;

    for (const auto &pair : antennas) {
        frequency = pair.first;
        antennas_position = pair.second;
        if (antennas_position.size() <= 1) {
            continue;
        }
        for (int i = 0; i < antennas_position.size() - 1; i++) {
            for (int j = i + 1; j < antennas_position.size(); j++) {
                if (!with_resonance) {
                    antenna_antinodes = get_antennas_antinodes_part1(antennas_position[i], antennas_position[j],
                                                                     max_reach_x, max_reach_y);
                } else {
                    antenna_antinodes = get_antennas_antinodes_part2(antennas_position[i], antennas_position[j],
                                                                     max_reach_x, max_reach_y);
                }
                antinodes.insert(antinodes.end(), antenna_antinodes.begin(), antenna_antinodes.end());
            }
        }
    }

    return antinodes;
}

vector<vector<char>> fill_grid(const antenna_map_t &antennas, const vector<vector<char>> &grid, bool with_resonance) {
    vector<vector<char>> new_grid = grid;
    vector<position_t> antinodes = get_all_antinodes(antennas, new_grid[0].size(), new_grid.size(), with_resonance);
    for (const auto &position : antinodes) {
        new_grid[position.second][position.first] = '#';
    }
    return new_grid;
}

int count_unique_antinodes(const vector<vector<char>> &grid) {
    int unique_antinodes = 0;
    for (const auto &row : grid) {
        for (const auto &value : row) {
            if (value == '#') {
                unique_antinodes++;
            }
        }
    }
    return unique_antinodes;
}

int day8(string input_file) {
    ifstream input_file_stream;
    string line;
    int row_idx, col_idx;
    vector<vector<char>> grid;
    antenna_map_t antennas;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    row_idx = 0;
    while (getline(input_file_stream, line)) {
        cout << line << endl;
        grid.emplace_back();
        for (auto [col_idx, value] : views::enumerate(line)) {
            grid[row_idx].push_back(value);
            if (value != '.') {
                add_antenna(antennas, value, position_t(col_idx, row_idx));
            }
        }
        row_idx++;
    }

    input_file_stream.close();

    int antinodes1 = count_unique_antinodes(fill_grid(antennas, grid, false));
    int antinodes2 = count_unique_antinodes(fill_grid(antennas, grid, true));
    cout << "Part 1: Number of unique locations that contain antinodes: " << antinodes1 << endl;
    cout << "Part 2: Number of unique locations that contain antinodes: " << antinodes2 << endl;

    return 0;
}
