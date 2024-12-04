/**
 * Advent of Code 2024
 * Day 3: Mull It Over
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

#define OP_MULT_IDX 1
#define OP_MULT_VALUE1_IDX 2
#define OP_MULT_VALUE2_IDX 3
#define OP_DO_IDX 4
#define OP_DONT_IDX 5

int day3_part1(const string &memory_corrupted) {
  regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  auto matches_begin = sregex_iterator(memory_corrupted.begin(),
                                       memory_corrupted.end(), pattern);
  auto matches_end = sregex_iterator();
  int ans = 0;
  for (auto match_it = matches_begin; match_it != matches_end; match_it++) {
    smatch match_mult_op = *match_it;
    ans += stoi(match_mult_op[1]) * stoi(match_mult_op[2]);
  }
  return ans;
}

int day3_part2(const string &memory_corrupted) {
  regex pattern(R"((mul\((\d{1,3}),(\d{1,3})\))|(do\(\))|(don't\(\)))");
  auto matches_begin = sregex_iterator(memory_corrupted.begin(),
                                       memory_corrupted.end(), pattern);
  auto matches_end = sregex_iterator();
  bool is_mult_enable = true;
  int ans = 0;
  for (auto match_it = matches_begin; match_it != matches_end; match_it++) {
    smatch match_op = *match_it;
    if (match_op[OP_DO_IDX] != "") {
      is_mult_enable = true;
    } else if (match_op[OP_DONT_IDX] != "") {
      is_mult_enable = false;
    } else if (match_op[OP_MULT_IDX] != "" && is_mult_enable) {
      ans += stoi(match_op[OP_MULT_VALUE1_IDX]) *
             stoi(match_op[OP_MULT_VALUE2_IDX]);
    }
  }
  return ans;
}

int day3(void) {
  ifstream input_file;
  string line, memory_corrupted;
  // input_file.open("day3-input-example.txt");
  // input_file.open("day3-input-example2.txt");
  input_file.open("day3-input.txt");
  if (!input_file.is_open()) {
    cout << "Couldn't open input file" << endl;
    return -1;
  }
  while (getline(input_file, line)) {
    memory_corrupted += line;
  }
  cout << "Part 1 sum: " << day3_part1(memory_corrupted) << endl;
  cout << "Part 2 sum: " << day3_part2(memory_corrupted) << endl;
  return 0;
}
