defmodule Aoc25.Day2Test do
  use ExUnit.Case, asunc: true

  test "day 2 parse ranges" do
    assert Aoc25Day2.get_ranges("11-22,95-115") == [11..22, 95..115]
  end

  test "day 2 id invalid" do
    assert !Aoc25Day2.is_valid1?(123_123)
    assert !Aoc25Day2.is_valid1?(6464)
    assert !Aoc25Day2.is_valid1?(55)
    assert Aoc25Day2.is_valid1?(101)
  end

  test "day 2 id valid" do
    assert Aoc25Day2.is_valid1?(101)
    assert Aoc25Day2.is_valid1?(9457)
  end

  test "day 2 get factors" do
    assert Aoc25Day2.get_factors(1) == []
    assert Aoc25Day2.get_factors(2) == [2]
    assert Aoc25Day2.get_factors(3) == [3]
    assert Aoc25Day2.get_factors(4) == [2, 4]
    assert Aoc25Day2.get_factors(10) == [2, 5, 10]
    assert Aoc25Day2.get_factors(12) == [2, 3, 4, 6, 12]
    assert Aoc25Day2.get_factors(24) == [2, 3, 4, 6, 8, 12, 24]
  end

  test "day 2 all equal" do
    assert Aoc25Day2.all_equal?([]) == true
    assert Aoc25Day2.all_equal?([1]) == true
    assert Aoc25Day2.all_equal?([1, 1]) == true
    assert Aoc25Day2.all_equal?([1, 2]) == false
  end

  test "day 2 part 1 example" do
    assert Path.join("input", "day2_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> Aoc25Day2.get_invalid_sum(&Aoc25Day2.is_valid1?/1) == 1_227_775_554
  end

  test "day 2 part 2 example" do
    assert Path.join("input", "day2_example.txt")
           |> File.read!()
           |> String.trim_trailing("\n")
           |> Aoc25Day2.get_invalid_sum(&Aoc25Day2.is_valid2?/1) == 4_174_379_265
  end
end
