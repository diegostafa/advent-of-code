#include "../../utils/aoc-utils.cpp"
#include <ranges>

bool
is_symbol_adjacent(const std::vector<std::string>& grid, int i, int j, int len)
{
    auto check_symbol = [](char c)
    { return !isdigit(c) && c != '.'; };

    if (i > 0)
        for (int x = 0; x < len + 2; x++)
            if (j - 1 + x < grid[i].size() && check_symbol(grid[i - 1][j - 1 + x]))
                return true;

    if (i < grid.size() - 1)
        for (int x = 0; x < len + 2; x++)
            if (j - 1 + x < grid[i].size() && check_symbol(grid[i + 1][j - 1 + x]))
                return true;

    if (j > 0 && check_symbol(grid[i][j - 1]))
        return true;

    if (j + len < grid[i].size() && check_symbol(grid[i][j + len]))
        return true;

    return false;
}

int
adjacent_sum(const std::vector<std::string>& grid)
{
    int sum = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        int j = 0;
        while (j < grid[i].size())
        {
            if (isdigit(grid[i][j]))
            {
                std::string dig;
                for (int k = 0; k < 4; k++)
                {
                    if (j + k >= grid[i].size())
                        break;

                    auto nc = grid[i][j + k];
                    if (isdigit(nc))
                        dig.push_back(nc);
                    else
                        break;
                }

                if (is_symbol_adjacent(grid, i, j, dig.length()))
                    sum += atoi(dig.c_str());

                j += dig.length();
            }
            else
                j++;
        }
    }
    return sum;
}

int
main()
{
    auto grid = aoc_utils::read_file_lines("input/day-03/input.txt");
    std::cout << adjacent_sum(grid) << std::endl;
}