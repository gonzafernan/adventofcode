"""
Advent of Code // 2023
--- Day 1: Trebuchet?! ---
"""

import re
from typing import Optional

DIGITS_STR = [
    ("one", "1"),
    ("two", "2"),
    ("three", "3"),
    ("four", "4"),
    ("five", "5"),
    ("six", "6"),
    ("seven", "7"),
    ("eight", "8"),
    ("nine", "9"),
    # ("zero", "0"),
]


def read_input(file_path: str) -> list[str]:
    """Read challenge input"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_txt:
        input_lst = input_txt.readlines()
    return input_lst


def left_search(input_str) -> Optional[str]:
    """Search for first digit"""
    str_len = len(input_str)
    for index in range(str_len):
        test_str = input_str[index:]
        if test_str[0].isdigit():
            return test_str[0]
        for pattern, digit in DIGITS_STR:
            if re.match(pattern=pattern, string=test_str):
                return digit
    return None


def right_search(input_str) -> Optional[str]:
    """Search for first digit"""
    str_len = len(input_str)
    for index in range(-1, -str_len, -1):
        test_str = input_str[:index]
        if test_str[-1].isdigit():
            return test_str[-1]
        for pattern, digit in DIGITS_STR:
            if re.search(pattern=pattern + "$", string=test_str):
                return digit
    return None


def digits_tranlation(input_str: str) -> str:
    """Translate spelled digits to numbers"""
    new_str = input_str
    for spelled, number in DIGITS_STR:
        # new_str = new_str.replace(spelled, number) # It doen't take into consideration the order
        new_str = re.sub(r"^" + spelled, number, new_str)
    return new_str


def day1_part1() -> int:
    """Only digits onsidered"""
    in_lines = read_input("day1/input.txt")
    ans = 0
    for line in in_lines:
        digit_lst = [ch for ch in line if ch.isdigit()]
        ans += int("".join([digit_lst[0], digit_lst[-1]]))
    return ans


def day1_part2() -> int:
    """Spelled digits considered"""
    in_lines = read_input("day1/input.txt")
    ans = 0
    for line in in_lines:
        ans += int("".join([left_search(line), right_search(line)]))
    return ans


if __name__ == "__main__":
    RESULT1 = day1_part1()
    RESULT2 = day1_part2()
    print(RESULT1, RESULT2)
