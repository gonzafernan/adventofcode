"""
Advent of Code // 2023
--- Day 4: Scratchcards ---
"""

import re


def read_input(file_path: str) -> list[str]:
    """Read Day 4 input file"""
    with open(file=file_path, mode="r", encoding=" utf-8") as input_file:
        input_lines = input_file.readlines()
    return [line.removesuffix("\n") for line in input_lines]


def parse_line(card: str) -> tuple[list[int], list[int]]:
    """Parse single line of input file"""
    card = re.sub(pattern=r"Card \d+: ", repl="", string=card)
    win_nums, my_nums = card.split(sep=" | ")
    win_nums = re.split(pattern=r" +", string=win_nums)
    my_nums = re.split(pattern=r" +", string=my_nums)
    return win_nums, my_nums


def get_matches(win_nums: list, my_nums: list) -> int:
    """Get number of card matches"""
    num_match = 0
    for num in win_nums:
        if num in my_nums:
            num_match += 1
    return num_match


def get_points(win_nums: list, my_nums: list) -> int:
    """Get card points"""
    num_match = 0
    for num in win_nums:
        if num in my_nums:
            num_match += 1
    if num_match == 0:
        return 0
    return 2 ** (num_match - 1)


def day4_part1(input_file: str) -> int:
    """Day4 part 1 resolution"""
    input_lines = read_input(file_path=input_file)
    total = 0
    for card in input_lines:
        win_nums, my_nums = parse_line(card=card)
        points = get_points(win_nums=win_nums, my_nums=my_nums)
        total += points
    return total


def day4_part2(input_file: str) -> int:
    """Day4 part 1 resolution"""
    input_lines = read_input(file_path=input_file)
    card_deck = {}
    for card_num, card in enumerate(input_lines, start=1):
        win_nums, my_nums = parse_line(card=card)
        points = get_matches(win_nums=win_nums, my_nums=my_nums)
        card_copies = list(range(card_num + 1, card_num + points + 1))
        card_deck[card_num] = card_copies

    card_lst = list(card_deck.keys())
    index = 0
    stop = len(card_lst)
    while index < stop:
        card_lst.extend(card_deck[card_lst[index]])
        stop = len(card_lst)
        index += 1
    return len(card_lst)


if __name__ == "__main__":
    ans1 = day4_part1("day4/input.txt")
    ans2 = day4_part2("day4/input.txt")
    print(ans1, ans2)
