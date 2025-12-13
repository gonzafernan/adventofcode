defmodule Aoc25Day1 do
  @moduledoc """
  Provides functions to solve [Advent of Code 2025 Day 1](https://adventofcode.com/2025/day/1).
  """

  def parse_instruction(<<direction, value::binary>>) do
    case direction do
      ?L ->
        -String.to_integer(value)

      ?R ->
        String.to_integer(value)
    end
  end

  def get_clicks(delta_to_turn, dial_position) do
    div(abs(delta_to_turn), 100) +
      if(
        dial_position != 0 and
          (dial_position + rem(delta_to_turn, 100) <= 0 or
             dial_position + rem(delta_to_turn, 100) >= 100),
        do: 1,
        else: 0
      )
  end

  def turn_dial1(delta_to_turn, dial_position) do
    Integer.mod(dial_position + delta_to_turn, 100)
  end

  def turn_dial2(delta_to_turn, dial_position) do
    {Integer.mod(dial_position + delta_to_turn, 100), get_clicks(delta_to_turn, dial_position)}
  end

  def get_password1(instructions) do
    Enum.map(instructions, &Aoc25Day1.parse_instruction/1)
    |> Stream.scan(50, &Aoc25Day1.turn_dial1/2)
    |> Enum.count(&(&1 == 0))
  end

  def get_password2(instructions) do
    Enum.map(instructions, &Aoc25Day1.parse_instruction/1)
    |> Stream.scan({50, 0}, fn new_delta, {dial_position, _} ->
      Aoc25Day1.turn_dial2(new_delta, dial_position)
    end)
    |> Enum.reduce(0, fn {_, clicks}, acc ->
      acc + clicks
    end)
  end
end
