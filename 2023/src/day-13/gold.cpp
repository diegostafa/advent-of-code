#include "../../utils/aoc-utils.cpp"
#include <algorithm>

auto
count_left_sym(const auto& grid)
{
    auto compute_row_pivot = [](const auto& grid)
    {
        auto fuzzy_equal_row = [&grid](int i, int j)
        {
            int diff = 0;
            for (int k = 0; k < grid[0].size() && diff < 2; k++)
                if (grid[i][k] != grid[j][k])
                    diff++;
            return diff == 1 ? true : false;
        };

        auto check_refl_row = [&grid, &fuzzy_equal_row](auto pivot)
        {
            auto dist = std::min(pivot, int(grid.size() - (pivot + 2)));
            for (int i = 0; i <= dist; i++)
                if (grid[pivot - i] != grid[pivot + 1 + i])
                    return false;
            return true;
        };

        auto pivot = -1;
        auto size  = grid.size();
        for (int i = 0; i < size && pivot == -1; i++)
            for (int j = 0; j < size && pivot == -1; j++)
                if (i != j && (grid[i] == grid[j] || fuzzy_equal_row(i, j)))
                {
                    pivot = (i + j) / 2;
                    if (!check_refl_row(pivot))
                        pivot = -1;
                }

        return pivot;
    };

    auto compute_col_pivot = [](const auto& grid)
    {
        auto fuzzy_equal_col = [&grid](int i, int j)
        {
            int diff = 0;
            for (int k = 0; k < grid.size() && diff < 2; k++)
                if (grid[k][i] != grid[k][j])
                    diff++;
            return diff == 1 ? true : false;
        };

        auto equal_col = [&grid](int i, int j)
        {
            for (int k = 0; k < grid.size(); k++)
                if (grid[k][i] != grid[k][j])
                    return false;
            return true;
        };

        auto check_refl_col = [&grid, &equal_col, &fuzzy_equal_col](auto pivot)
        {
            auto dist = std::min(pivot, int(grid[0].size() - (pivot + 2)));
            for (int i = 0; i <= dist; i++)
            {
                if (!equal_col(pivot - i, pivot + 1 + i))
                    return false;
            }
            return true;
        };

        auto pivot = -1;
        auto size  = grid[0].size();
        for (int i = 0; i < size && pivot == -1; i++)
            for (int j = 0; j < size && pivot == -1; j++)
                if (i != j && (equal_col(i, j) || fuzzy_equal_col(i, j)))
                {
                    pivot = (i + j) / 2;
                    if (!check_refl_col(pivot))
                        pivot = -1;
                }

        return pivot;
    };

    auto rowPivot = compute_row_pivot(grid);
    if (rowPivot != -1)
        return (rowPivot + 1) * 100;

    auto colPivot = compute_col_pivot(grid);
    if (colPivot != -1)
        return colPivot + 1;

    throw std::runtime_error("missing col pivot " + grid[0]);
}

int
main()
{
    auto input = aoc_utils::split_string(aoc_utils::read_file("src/day-13/input.txt"), "\n\n") |
                 std::views::transform(aoc_utils::split_line);

    int64_t sum = 0;
    for (auto&& grid : input)
        sum += count_left_sym(grid);

    std::cout << sum << std::endl;
}