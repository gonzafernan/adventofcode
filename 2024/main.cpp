/**
 * Advent of Code 2024
 * @author Gonzalo G. Fernandez
 */

#include <iostream>

#include "adventofcode2024.hpp"

using namespace std;

#define EXPECTED_ARGS 3

int (*day_table[24])(string) = {day1,    day2,  day3,    day4,    nullptr, day6,    nullptr, nullptr,
                                nullptr, day10, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

int main(int argc, char *argv[]) {
    int day_to_execute;
    string input_file;
    cout << "Advent of Code 2024!" << endl;
    // args check
    if (argc < EXPECTED_ARGS) {
        cout << "Provide day to execute and input file!" << endl;
        return -1;
    }
    day_to_execute = atoi(argv[1]);
    input_file = string(argv[2]);
    if (day_to_execute < 1 || day_to_execute > 24) {
        cout << "Invalid Day " << day_to_execute << " provided." << endl;
        return -1;
    }
    return day_table[day_to_execute - 1](input_file);
}
