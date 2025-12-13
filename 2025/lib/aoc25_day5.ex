defmodule Aoc25Day5 do
  @moduledoc """
  Provides functions to solve [Advent of Code 2025 Day 5](https://adventofcode.com/2025/day/5).
  """

  @doc """
  Parse the problem `input` to get fresh ranges and available items.
  """
  def parse_database(input) do
    div_index = Enum.find_index(input, fn x -> x == "" end)
    {fresh_ranges_str, [_ | available_items]} = Enum.split(input, div_index)

    fresh_ranges =
      Enum.map(fresh_ranges_str, fn range_str ->
        String.split(range_str, "-") |> Enum.map(&String.to_integer/1)
      end)

    {fresh_ranges, Enum.map(available_items, &String.to_integer/1)}
  end

  @doc """
  Check if an `item` is fresh given the `fresh_ranges`.
  """
  def is_fresh?(item, fresh_ranges) do
    Enum.any?(fresh_ranges, &Enum.member?(&1, item))
  end

  @doc """
  Get number of fresh items given a `database_input`.
  """
  def get_fresh_items(database_input) do
    {fresh_ranges_lst, available_items} = parse_database(database_input)
    fresh_ranges = Enum.map(fresh_ranges_lst, fn [min, max] -> min..max end)
    Enum.filter(available_items, &is_fresh?(&1, fresh_ranges)) |> length()
  end
end
