/**
 * Advent of Code 2024
 * @author Gonzalo G. Fernandez
 */

#include <iostream>

#include "adventofcode2024.hpp"

using namespace std;

#define EXPECTED_ARGS 2

int (*day_table[24])() = {day1, day2, day3, day4};

int main(int argc, char *argv[]) {
    int day_to_execute;
    cout << "Advent of Code 2024!" << endl;
    // args check
    if (argc < EXPECTED_ARGS) {
        cout << "Provide day to execute!" << endl;
        return -1;
    }
    day_to_execute = atoi(argv[1]);
    if (day_to_execute < 1 || day_to_execute > 24) {
        cout << "Invalid Day " << day_to_execute << " provided." << endl;
        return -1;
    }
    return day_table[day_to_execute - 1]();
}
