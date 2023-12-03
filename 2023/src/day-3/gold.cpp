#include "../../utils/aoc-utils.cpp"
#include <ranges>
#include <tuple>

std::pair<int, int>
is_symbol_adjacent(const std::vector<std::string>& grid, int i, int j, int len)
{
    auto check_symbol = [](char c)
    { return !isdigit(c) && c != '.'; };

    if (i > 0)
        for (int x = 0; x < len + 2; x++)
            if (j - 1 + x < grid[i].size() && check_symbol(grid[i - 1][j - 1 + x]))
                return {i - 1, j - 1 + x};

    if (i < grid.size() - 1)
        for (int x = 0; x < len + 2; x++)
            if (j - 1 + x < grid[i].size() && check_symbol(grid[i + 1][j - 1 + x]))
                return {i + 1, j - 1 + x};

    if (j > 0 && check_symbol(grid[i][j - 1]))
        return {i, j - 1};

    if (j + len < grid[i].size() && check_symbol(grid[i][j + len]))
        return {i, j + len};

    return {-1, -1};
}

std::vector<std::pair<int, std::pair<int, int>>>
nums_and_gears(const std::vector<std::string>& grid)
{
    std::vector<std::pair<int, std::pair<int, int>>> numsAndGears;

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

                auto posgear = is_symbol_adjacent(grid, i, j, dig.length());
                if (posgear.first != -1)
                    numsAndGears.push_back({atoi(dig.c_str()), posgear});

                j += dig.length();
            }
            else
                j++;
        }
    }
    return numsAndGears;
}

int
main()
{
    auto grid = aoc_utils::read_file_lines("src/day-3/input.txt");
    auto ngs  = nums_and_gears(grid);

    int64_t sum = 0;

    for (int i = 0; i < ngs.size(); i++)
    {
        int count = 1;
        int twin  = 0;

        for (int j = 0; j < ngs.size(); j++)
        {
            if (i == j)
                continue;

            if (ngs[i].second == ngs[j].second)
            {
                count++;
                twin = ngs[j].first;
            }
        }

        if (count == 2)
            sum += ngs[i].first * twin;
    }

    std::cout << sum / 2 << std::endl;
}