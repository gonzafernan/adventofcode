defmodule Aoc25.Day5Test do
  use ExUnit.Case, async: true

  test "day 5 part 1 example" do
    assert Path.join("input", "day5_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> String.split("\n")
           |> Aoc25Day5.get_fresh_items() == 3
  end
end
