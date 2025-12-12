defmodule Aoc25.Day3Test do
  use ExUnit.Case, async: true

  test "day 3 part 1 example" do
    assert Path.join("input", "day3_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> String.split("\n")
           |> Aoc25Day3.get_total_output_joltage() == 357
  end
end
