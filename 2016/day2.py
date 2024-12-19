"""
Advent of Code // 2016
-- Day 2: Bathroom Security --
"""

import sys


def parse_input(input_file: str) -> list[str]:
    """Parse input file"""
    parsed_input = []
    with open(file=input_file, mode="r", encoding="utf-8") as input_stream:
        parsed_input = input_stream.readlines()
    return [line.strip("\n") for line in parsed_input]


def get_keypad_part1() -> list[list[str]]:
    """Get keypad for day 2 part 1"""
    return [["1", "2", "3"], ["4", "5", "6"], ["7", "8", "9"]]


def get_keypad_part2() -> list[list[str]]:
    """Get keypad for day 2 part 2"""
    return [
        ["", "", "1", "", ""],
        ["", "2", "3", "4", ""],
        ["5", "6", "7", "8", "9"],
        ["", "A", "B", "C", ""],
        ["", "", "D", "", ""],
    ]


def get_bathroom_code(
    instructions: list[str], keypad: list[list[str]], current_key: list[int]
) -> str:
    """Get the bathroom code from instructions, keypad, and initial key"""
    bathroom_code = []
    for line in instructions:
        for movement in line:
            if (
                movement == "U"
                and current_key[0] > 0
                and keypad[current_key[0] - 1][current_key[1]]
            ):
                current_key[0] -= 1
            if (
                movement == "D"
                and current_key[0] < len(keypad) - 1
                and keypad[current_key[0] + 1][current_key[1]]
            ):
                current_key[0] += 1
            if (
                movement == "L"
                and current_key[1] > 0
                and keypad[current_key[0]][current_key[1] - 1]
            ):
                current_key[1] -= 1
            if (
                movement == "R"
                and current_key[1] < len(keypad[0]) - 1
                and keypad[current_key[0]][current_key[1] + 1]
            ):
                current_key[1] += 1
        bathroom_code.append(keypad[current_key[0]][current_key[1]])
    return "".join(bathroom_code)


def day2_part1(instructions: list[str]) -> str:
    """Get bathroom code for day 2 part 1"""
    return get_bathroom_code(instructions, get_keypad_part1(), [1, 1])


def day2_part2(instructions: list[str]) -> str:
    """Get bathroom code for day 2 part 1"""
    return get_bathroom_code(instructions, get_keypad_part2(), [2, 0])


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please provide input file")
        sys.exit(1)
    input_instructions = parse_input(sys.argv[1])

    print("Part 1: Bathroom code:", day2_part1(instructions=input_instructions))
    print("Part 2: Bathroom code:", day2_part2(instructions=input_instructions))
