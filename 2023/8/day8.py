"""
Advent of Code // 2023
--- Day 8: Haunted Wasteland ---
"""

import re
from math import lcm


def read_input(file_path: str) -> tuple[str, dict]:
    """Read challenge input"""

    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        rl_instruct = input_file.readline()
        _ = input_file.readline()
        node_lines = input_file.readlines()

    graph_lut = {}
    for line in node_lines:
        m = re.match(
            pattern=r"([A-Z|\d]{3}) = \(([A-Z|\d]{3}), ([A-Z|\d]{3})\)", string=line
        )
        if m:
            graph_lut.update({m.group(1): (m.group(2), m.group(3))})
        else:
            raise ValueError(f"Invalid input {line}")
    return rl_instruct.removesuffix("\n"), graph_lut


def rl_generator(rl_pattern: str):
    """Infinite sequence of steps RL generation"""
    index = 0
    while True:
        yield rl_pattern[index]
        index += 1
        if index >= len(rl_pattern):
            index = 0


def get_steps_to_z(start: str, graph_lut: dict, rl_instruct: str) -> int:
    """Get amount of steps to end"""
    rl_gen = rl_generator(rl_instruct)
    steps = 0
    node_id = start
    while node_id[-1] != "Z":
        rl = next(rl_gen)
        lut_index = 0 if rl == "L" else 1
        node_id = graph_lut[node_id][lut_index]
        steps += 1
    return steps


def day8_part1(file_path: str) -> int:
    """Day 8 part 1 resolution"""
    rl_instruct, graph_lut = read_input(file_path=file_path)
    rl_gen = rl_generator(rl_instruct)
    node_id = "AAA"
    steps = 0
    while node_id != "ZZZ":
        rl = next(rl_gen)
        lut_index = 0 if rl == "L" else 1
        node_id = graph_lut[node_id][lut_index]
        steps += 1

    return steps


def day8_part2(file_path: str) -> int:
    """Day 8 part 2 resolution"""
    rl_instruct, graph_lut = read_input(file_path=file_path)
    src_nodes = [node for node in graph_lut.keys() if node[-1] == "A"]
    print(src_nodes)
    steps = []
    for src_node in src_nodes:
        steps.append(
            get_steps_to_z(start=src_node, graph_lut=graph_lut, rl_instruct=rl_instruct)
        )
    return lcm(*steps)


if __name__ == "__main__":
    ans1 = day8_part1(file_path="2023/8/input_example2.txt")
    ans2 = day8_part2(file_path="2023/8/input.txt")
    print(ans1, ans2)
