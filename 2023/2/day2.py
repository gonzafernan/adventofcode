"""
Advent of Code // 2023
--- Day 2: Cube Conundrum ---
"""

import re

MAX_SET = {"red": 12, "green": 13, "blue": 14}


def read_input(file_path: str):
    """Read day 2 input file"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        input_lst = input_file.readlines()

    return input_lst


def check_max(num: int, color: str) -> bool:
    """Check with maximum set and true if game is possible"""
    return MAX_SET[color] >= num


def day2_part1():
    """Day 2 part 1 resolution"""

    # Read input
    input_lst = read_input("./day2/input.txt")

    ans = 0
    game_id_regex = r"^Game \d+: "
    for index, line in enumerate(input_lst, start=1):
        # Remove game prefix
        line = re.sub(pattern=game_id_regex, repl="", string=line)
        # Remove end of line
        line = line.removesuffix("\n")
        cube_pairs = []
        # Split game sets
        for cube_sets in line.split(sep="; "):
            # Get pairs cube number and color
            for cube_group in cube_sets.split(sep=", "):
                cube_pairs.append(cube_group.split(" "))

        # Check result
        for number, color in cube_pairs:
            if not check_max(int(number), color):
                break
        else:
            ans += index
    print("ANS = ", ans)


def day2_part2():
    """Day 2 part 2 resolution"""

    # Read input
    input_lst = read_input("./day2/input.txt")

    ans = 0

    game_id_regex = r"^Game \d+: "
    for line in input_lst:
        # Remove game prefix
        line = re.sub(pattern=game_id_regex, repl="", string=line)
        # Remove end of line
        line = line.removesuffix("\n")
        min_game_set = {"red": 0, "green": 0, "blue": 0}
        # Split game sets
        for cube_sets in line.split(sep="; "):
            # Get pairs cube number and color
            for cube_group in cube_sets.split(sep=", "):
                number, color = cube_group.split(" ")
                number = int(number)
                if number > min_game_set[color]:
                    min_game_set[color] = number

        # Compute result
        power_set = 1
        for value in min_game_set.values():
            power_set *= value
        ans += power_set

    print("ANS = ", ans)


if __name__ == "__main__":
    day2_part1()
    day2_part2()
