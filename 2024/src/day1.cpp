/**
 * Advent of Code 2024
 * Day 1: Historian Hysteria
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <list>
#include <ranges>
#include <regex>
#include <string>

using namespace std;

int day1_part1(list<int> list1, list<int> list2) {
    int sum_distance = 0;
    list1.sort();
    list2.sort();
    for (auto [value1, value2] : views::zip(list1, list2)) {
        sum_distance += abs(value1 - value2);
    }
    return sum_distance;
}
int day1_part2(list<int> list1, list<int> list2) {
    int sum_similarity = 0, value_repetitions;
    for (auto &value1 : list1) {
        value_repetitions = 0;
        for (auto &value2 : list2) {
            if (value1 == value2) {
                value_repetitions++;
            }
        }
        sum_similarity += value1 * value_repetitions;
    }
    return sum_similarity;
}

int day1(string input_file) {
    ifstream input_file_stream;
    string line;
    list<int> list1;
    list<int> list2;
    int input_line_idx, ans;

    regex pattern(R"(^(\d+)\ +(\d+))");
    smatch matches;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    input_line_idx = 0;
    while (getline(input_file_stream, line)) {
        if (!regex_search(line, matches, pattern)) {
            cout << "No match in line " << input_line_idx << ": " << line << endl;
            continue;
        }
        list1.push_back(stoi(matches[1]));
        list2.push_back(stoi(matches[2]));
        input_line_idx++;
    }
    input_file_stream.close();

    ans = day1_part1(list1, list2);
    cout << "Sum of the distances: " << ans << endl;

    ans = day1_part2(list1, list2);
    cout << "Sum of the similarities: " << ans << endl;

    return 0;
}
