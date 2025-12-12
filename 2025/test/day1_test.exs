defmodule Aoc25.Day1Test do
  use ExUnit.Case, async: true

  test "day 1 parse instruction" do
    assert Aoc25Day1.parse_instruction("R8") == 8
    assert Aoc25Day1.parse_instruction("L19") == -19
  end

  test "day 1 turn dial" do
    assert Aoc25Day1.turn_dial1(5, -10) == 95
    assert Aoc25Day1.turn_dial1(95, 5) == 0
  end

  test "day 1 part 1 example" do
    assert Path.join("input", "day1_example.txt")
           |> File.read!()
           |> String.split("\n", trim: true)
           |> Aoc25Day1.get_password1() == 3
  end

  test "day 1 part 2 example" do
    assert Path.join("input", "day1_example.txt")
           |> File.read!()
           |> String.split("\n", trim: true)
           |> Aoc25Day1.get_password2() == 6
  end
end
