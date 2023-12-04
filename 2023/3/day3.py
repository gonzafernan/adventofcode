"""
Advent of Code // 2023
--- Day 3: Gear Ratios ---
"""


class SchematicReference:
    """Schematics element reference"""

    def __init__(self, ref_id: int, grid_pos: list[tuple[int, int]]):
        self._id = ref_id
        self._grid_pos = grid_pos

    def get_id(self) -> int:
        """Get schematic reference ID"""
        return self._id

    def is_valid_reference(self, symbol: tuple[int, int]) -> bool:
        """Check for valid reference to symbol"""
        sym_row, sym_col = symbol
        for row_index, col_index in self._grid_pos:
            # check row
            if not sym_row in (row_index - 1, row_index, row_index + 1):
                continue
            # check col
            if not sym_col in (col_index - 1, col_index, col_index + 1):
                continue
            return True
        return False


def read_input(file_path: str) -> list[str]:
    """Read day 3 input file"""
    with open(file=file_path, mode="r", encoding="utf-8") as input_file:
        input_lst = input_file.readlines()
    return [line.removesuffix("\n") for line in input_lst]


def parse_input(
    input_lines: list[str],
) -> tuple[list[SchematicReference], tuple[int, int]]:
    """Parse engine schematic"""

    schm_refs = []  # list of schematis references
    elem_pos = []  # list of positions of elements
    for row_index, line in enumerate(input_lines):
        number_flag = False
        number_buffer = []
        position_buffer = []

        for col_index, symbol in enumerate(line):
            # craft number to save it
            if symbol.isnumeric():
                number_flag = True
                number_buffer.append(symbol)
                position_buffer.append((row_index, col_index))
                continue

            # add element references
            if number_flag:
                schm_refs.append(
                    SchematicReference(
                        ref_id=int("".join(number_buffer)), grid_pos=position_buffer
                    )
                )
                number_buffer = []
                position_buffer = []
                number_flag = False  # reset number flag

            if "." != symbol:  # valid symbol, add position
                elem_pos.append((row_index, col_index))

        # add element references
        if number_flag:
            schm_refs.append(
                SchematicReference(
                    ref_id=int("".join(number_buffer)), grid_pos=position_buffer
                )
            )

    return schm_refs, elem_pos


def day3_part1(file_path: str):
    """Day 3 part 1 resolution"""

    input_lines = read_input(file_path=file_path)

    ans = 0
    schm_refs, elem_pos = parse_input(input_lines=input_lines)
    valid_ref = []
    invalid_ref = []
    for schm_ref in schm_refs:
        for symbol in elem_pos:
            if schm_ref.is_valid_reference(symbol):
                ans += schm_ref.get_id()
                valid_ref.append(schm_ref)
                break
        else:
            invalid_ref.append(schm_ref)

    print("PART:", [schm_ref.get_id() for schm_ref in schm_refs])
    print("VALID:", [element.get_id() for element in valid_ref])
    print("INVALID:", [element.get_id() for element in invalid_ref])
    print(ans)
    return ans


def day3_part2(file_path: str):
    """Day 3 part 2 resolution"""

    input_lines = read_input(file_path=file_path)

    ans = 0
    schm_refs, elem_pos = parse_input(input_lines=input_lines)
    for symbol in elem_pos:
        gearbox = 0
        gear_ratio = 1
        for schm_ref in schm_refs:
            if schm_ref.is_valid_reference(symbol):
                gearbox += 1
                gear_ratio *= schm_ref.get_id()
        if gearbox == 2:
            ans += gear_ratio

    print("PART:", [schm_ref.get_id() for schm_ref in schm_refs])
    print(ans)
    return ans


if __name__ == "__main__":
    # day3_part1(file_path="./day3/input.txt")
    day3_part2(file_path="./day3/input.txt")
