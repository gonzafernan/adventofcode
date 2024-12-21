/**
 * Advent of Code 2024
 * Day 2: Red-Nosed Reports
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

#define MAX_VALUE_DIFF 3
#define PROBLEM_DAMPENER_CORRECTIONS 1

bool is_report_safe(vector<int> report) {
    int value_diff;
    bool unsafe_condition;
    int values_trend = report[1] - report[0];
    for (int i = 1; i < report.size(); i++) {
        value_diff = report[i] - report[i - 1];

        unsafe_condition = (values_trend > 0 && value_diff < 0 || value_diff > MAX_VALUE_DIFF) ||
                           (values_trend < 0 && value_diff > 0 || value_diff < -MAX_VALUE_DIFF) || (value_diff == 0);
        if (!unsafe_condition) {
            continue;
        }
        return false;
    }
    return true;
}

int day2_part1(const vector<vector<int>> &unusual_data) {
    int safe_reports = 0;
    for (const auto &report : unusual_data) {
        if (is_report_safe(report)) {
            safe_reports++;
        }
    }
    return safe_reports;
}

int day2_part2(const vector<vector<int>> &unusual_data) {
    int safe_reports = 0;
    for (const auto &report : unusual_data) {
        if (is_report_safe(report)) {
            safe_reports++;
            continue;
        }
        // problem dampener
        for (int i = 0; i < report.size(); i++) {
            vector<int> damp_report = report;
            damp_report.erase(damp_report.begin() + i);
            if (is_report_safe(damp_report)) {
                safe_reports++;
                break;
            }
        }
    }
    return safe_reports;
}

int day2(string input_file) {
    ifstream input_file_stream;
    string line;
    int input_line_idx;
    vector<vector<int>> unusual_data;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }
    input_line_idx = 0;
    while (getline(input_file_stream, line)) {
        auto split_view = views::split(line, ' ');
        vector<int> report;
        for (const auto value : split_view) {
            report.push_back(stoi(string(value.begin(), value.end())));
        }
        unusual_data.push_back(report);
        input_line_idx++;
    }
    input_file_stream.close();

    cout << "Number of safe reports: " << day2_part1(unusual_data) << endl;
    cout << "Number of safe reports: " << day2_part2(unusual_data) << endl;

    return 0;
}
