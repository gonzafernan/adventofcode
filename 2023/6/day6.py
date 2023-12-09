"""
Advent of Code // 2023
--- Day 6: Wait For It ---
"""

import re


def read_input(file_path: str) -> list:
    """Read challenge input"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        time_line = input_file.readline()
        dist_line = input_file.readline()

    time_lst = [int(time) for time in re.split(pattern=r" +", string=time_line)[1:]]
    dist_lst = [int(dist) for dist in re.split(pattern=r" +", string=dist_line)[1:]]

    return [(time, dist) for time, dist in zip(time_lst, dist_lst)]


def read_input2(file_path: str) -> tuple[int, int]:
    """Read challenge input"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        time_line = input_file.readline()
        dist_line = input_file.readline()

    time = int(
        "".join([time for time in re.split(pattern=r" +", string=time_line)[1:]])
    )
    dist = int(
        "".join([dist for dist in re.split(pattern=r" +", string=dist_line)[1:]])
    )

    return time, dist


def day6_part1(file_path: str):
    """Day 6 part 1 resolution"""
    record_lst = read_input(file_path=file_path)
    ans = 1
    for time, dist in record_lst:
        win_counter = 0
        for msec in range(time + 1):
            if ((time - msec) * msec) > dist:
                win_counter += 1
        ans *= win_counter
    return ans


def day6_part2(file_path: str):
    """Day 6 part 1 resolution"""
    time, dist = read_input2(file_path=file_path)
    win_counter = 0
    for msec in range(time + 1):
        if ((time - msec) * msec) > dist:
            win_counter += 1
    return win_counter


if __name__ == "__main__":
    ans1 = day6_part1(file_path="2023/6/input.txt")
    ans2 = day6_part2(file_path="2023/6/input.txt")
    print(ans1, ans2)
