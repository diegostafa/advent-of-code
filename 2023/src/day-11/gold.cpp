#include "../../utils/aoc-utils.cpp"

auto
find_empty_rows_cols(const auto& grid)
{
    std::pair<std::vector<int>, std::vector<int>> res;

    for (int i = 0; i < grid.size(); i++)
    {
        bool isEmpty = true;
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '#')
            {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty)
            res.first.push_back(i);
    }

    for (int j = 0; j < grid[0].size(); j++)
    {
        bool isEmpty = true;
        for (int i = 0; i < grid.size(); i++)
        {
            if (grid[i][j] == '#')
            {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty)
            res.second.push_back(j);
    }
    return res;
};

int
main()
{

    auto grid             = aoc_utils::read_file_lines("input/day-11/input.txt");
    auto emptyRowsAndCols = find_empty_rows_cols(grid);
    auto emptyRows        = emptyRowsAndCols.first;
    auto emptyCols        = emptyRowsAndCols.second;
    auto expansionSize    = 1000000 - 1;

    auto tot_pair_distance = [&](const auto& start)
    {
        auto compute_single_distance = [&](const auto& to)
        {
            auto man_distance = [&]()
            { return std::abs(to.first - start.first) + std::abs(to.second - start.second); };

            auto intersectX = [&](const auto& row)
            { return row > std::min(start.first, to.first) && row < std::max(start.first, to.first); };

            auto intersectY = [&](const auto& col)
            { return col > std::min(start.second, to.second) && col < std::max(start.second, to.second); };

            auto xIntersections = std::count_if(emptyRows.begin(), emptyRows.end(), intersectX);
            auto yIntersections = std::count_if(emptyCols.begin(), emptyCols.end(), intersectY);

            return man_distance() + xIntersections * expansionSize + yIntersections * expansionSize;
        };

        int64_t totDistance = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == '#' && start != std::make_pair(i, j))
                    totDistance += compute_single_distance(std::make_pair(i, j));

        return totDistance;
    };

    int64_t tot = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
            if (grid[i][j] == '#')
                tot += tot_pair_distance(std::make_pair(i, j));

    std::cout << tot / 2 << std::endl;
}