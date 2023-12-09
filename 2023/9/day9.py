"""
Advent of Code // 2023
--- Day 9: Mirage Maintenance ---
"""

import numpy as np


def read_input(file_path: str):
    """Read challenge input"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        input_lines = input_file.readlines()
    return [list(map(int, line.removesuffix("\n").split(" "))) for line in input_lines]


def extrapolate_hist(hist: np.ndarray, forward: bool) -> int:
    """Recursion for history extrapolation"""
    if not np.any(hist):  # check for all zeros
        return 0
    prediction = extrapolate_hist(
        hist=np.convolve(hist, [1, -1], mode="valid"), forward=forward
    )
    return hist[-1] + prediction if forward else hist[0] - prediction


def day9_part1(file_path: str):
    """Day 9 part 1 resolution"""
    oasis_read = read_input(file_path=file_path)
    ans = 0
    for reading in oasis_read:
        ans += extrapolate_hist(np.array(reading), forward=True)
    return ans


def day9_part2(file_path: str):
    """Day 9 part 2 resolution"""
    oasis_read = read_input(file_path=file_path)
    ans = 0
    for reading in oasis_read:
        pred = extrapolate_hist(np.array(reading), forward=False)
        ans += pred
    return ans


if __name__ == "__main__":
    ans1 = day9_part1(file_path="2023/9/input.txt")
    ans2 = day9_part2(file_path="2023/9/input.txt")
    print(ans1, ans2)
