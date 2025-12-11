defmodule Aoc25Day3 do
  def get_bank_max_joltage([_], max_joltage) do
    max_joltage
  end

  def get_bank_max_joltage([v1 | tail], max_joltage) do
    max_current_joltage = Enum.map(tail, fn v2 -> String.to_integer(v1 <> v2) end) |> Enum.max()

    if max_current_joltage > max_joltage do
      get_bank_max_joltage(tail, max_current_joltage)
    else
      get_bank_max_joltage(tail, max_joltage)
    end
  end

  def get_total_output_joltage(banks_set) do
    Enum.map(banks_set, &String.codepoints/1)
    |> Enum.map(fn bank -> get_bank_max_joltage(bank, 0) end)
    |> Enum.sum()
  end
end

Path.join("input", "day3.txt")
|> File.read!()
|> String.trim_trailing("\n")
|> String.split("\n")
|> Aoc25Day3.get_total_output_joltage()
|> IO.puts()
