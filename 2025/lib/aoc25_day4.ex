defmodule GridNode do
  @enforce_keys [:position]
  defstruct position: {-1, -1}, adjacents: []
end

defmodule Aoc25Day4 do
  def is_adjacent?(node_a, node_b) do
    {%GridNode{position: {x1, y1}, adjacents: _}, %GridNode{position: {x2, y2}, adjacents: _}} =
      {node_a, node_b}

    case {abs(x1 - x2), abs(y1 - y2)} do
      {0, 1} -> true
      {1, 0} -> true
      {1, 1} -> true
      _ -> false
    end
  end

  def is_accesible?(node) do
    %GridNode{position: _, adjacents: adjacents} = node
    length(adjacents) < 4
  end

  def get_adjacents(node, grid) do
    Enum.filter(grid, fn other_node -> is_adjacent?(node, other_node) end)
  end

  def load_grid(input_diagram) do
    Enum.with_index(input_diagram)
    |> Enum.map(fn {row, row_index} ->
      String.codepoints(row)
      |> Enum.with_index()
      |> Enum.map(fn {value, col_index} -> {col_index, row_index, value} end)
    end)
    |> List.flatten()
    |> Enum.filter(fn {_, _, value} -> value == "@" end)
    |> Enum.map(fn {col_index, row_index, _} -> %GridNode{position: {col_index, row_index}} end)
  end

  def get_nodes(input_diagram) do
    grid = load_grid(input_diagram)
    Enum.map(grid, fn node -> struct!(node, adjacents: get_adjacents(node, grid)) end)
  end

  def get_accesible_nodes(input_diagram) do
    length(get_nodes(input_diagram) |> Enum.filter(&is_accesible?/1))
  end

  def remove_accesible_nodes(nodes, total_cleaned_nodes) do
    {accesible_nodes, restricted_nodes} = Enum.split_with(nodes, &is_accesible?/1)

    case accesible_nodes do
      [] ->
        total_cleaned_nodes

      _ ->
        Enum.map(restricted_nodes, fn node ->
          struct!(node, adjacents: get_adjacents(node, restricted_nodes))
        end)
        |> remove_accesible_nodes(total_cleaned_nodes + length(accesible_nodes))
    end
  end

  def get_cleanable_nodes(input_diagram) do
    get_nodes(input_diagram) |> remove_accesible_nodes(0)
  end
end
