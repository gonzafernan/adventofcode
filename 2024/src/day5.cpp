/**
 * Advent of Code 2024
 * Day 5: Print Queue
 * @author Gonzalo G. Fernandez
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

vector<vector<int>> order_pairs;

bool update_pages_sort(int a, int b) {
    for (const auto &order_pair : order_pairs) {
        if (a == order_pair[1] && b == order_pair[0]) {
            return false;
        }
    }
    return true;
}

bool update_is_sorted(const vector<int> &update) {
    return is_sorted(update.begin(), update.end(), update_pages_sort);
}

// sort inplace
void update_sort(vector<int> &update) {
    sort(update.begin(), update.end(), update_pages_sort);
}

int day5(string input_file) {
    ifstream input_file_stream;
    string line;
    vector<vector<int>> updates_to_check;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    int order_pair_idx = 0;
    while (getline(input_file_stream, line)) {
        if (line == "") {
            break;
        }
        auto split_view = line | views::split('|');
        order_pairs.emplace_back();
        for (const auto &value : split_view) {
            order_pairs[order_pair_idx].push_back(stoi(string(value.begin(), value.end())));
        }
        order_pair_idx++;
    }
    int update_idx = 0;
    while (getline(input_file_stream, line)) {
        auto split_view = line | views::split(',');
        updates_to_check.emplace_back();
        for (const auto &value : split_view) {
            updates_to_check[update_idx].push_back(stoi(string(value.begin(), value.end())));
        }
        update_idx++;
    }
    input_file_stream.close();

    int sum_correct_middle_page = 0;
    int sum_incorrect_middle_page = 0;
    for (auto &update : updates_to_check) {
        if (update_is_sorted(update)) {
            sum_correct_middle_page += update[update.size() / 2];
        } else {
            update_sort(update);
            sum_incorrect_middle_page += update[update.size() / 2];
        }
    }

    cout << "Part 1: Sum middle page of valid updates: " << sum_correct_middle_page << endl;
    cout << "Part 1: Sum middle page of corrected updates: " << sum_incorrect_middle_page << endl;

    return 0;
}
