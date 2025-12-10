defmodule Aoc25Day2 do
  def get_ranges(input_stream) do
    String.split(input_stream, ",", trim: true)
    |> Enum.map(fn x ->
      [a, b] = String.split(x, "-", trim: true)
      String.to_integer(a)..String.to_integer(b)
    end)
  end

  def is_valid1?(id) do
    id_str = Integer.to_string(id)
    {id1, id2} = String.split_at(id_str, div(String.length(id_str), 2))
    id1 != id2
  end

  def get_factors(number) do
    case number do
      1 -> []
      x when div(x, 2) < 2 -> [x]
      _ -> Enum.filter(2..div(number, 2), fn x -> rem(number, x) == 0 end) ++ [number]
    end
  end

  def all_equal?([]), do: true
  def all_equal?([_]), do: true
  def all_equal?([a, a | rest]), do: all_equal?([a | rest])
  def all_equal?([_, _ | _]), do: false

  def is_valid2?(id) do
    id_str = Integer.to_string(id)

    valid =
      for chunk_size <-
            Enum.map(get_factors(String.length(id_str)), fn x -> div(String.length(id_str), x) end) do
        String.codepoints(id_str)
        |> Enum.chunk_every(chunk_size)
        |> Enum.map(&Enum.join/1)
      end
      |> Enum.map(&all_equal?/1)
      |> Enum.any?()

    !valid
  end

  def get_invalids(range, is_valid) do
    Enum.filter(range, fn x -> !is_valid.(x) end)
  end

  def get_invalid_sum(input, is_valid) do
    Aoc25Day2.get_ranges(input)
    |> Enum.flat_map(&get_invalids(&1, is_valid))
    |> Enum.sum()
  end
end

Path.join("input", "day2.txt")
|> File.read!()
|> String.trim_trailing("\n")
|> Aoc25Day2.get_invalid_sum(&Aoc25Day2.is_valid1?/1)
|> IO.puts()

Path.join("input", "day2.txt")
|> File.read!()
|> String.trim_trailing("\n")
|> Aoc25Day2.get_invalid_sum(&Aoc25Day2.is_valid2?/1)
|> IO.puts()
