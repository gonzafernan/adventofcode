defmodule Aoc25.Day4Test do
  use ExUnit.Case, async: true

  test "day 4 part 1 example" do
    assert Path.join("input", "day4_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> String.split("\n")
           |> Aoc25Day4.get_accesible_nodes() == 13
  end

  test "day 4 part 2 example" do
    assert Path.join("input", "day4_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> String.split("\n")
           |> Aoc25Day4.get_cleanable_nodes() == 43
  end
end
