#include "../../utils/aoc-utils.cpp"

int
main()
{
    auto grid = aoc_utils::read_file_lines("src/day-14/input.txt");

    auto slide = [](auto& grid)
    {
        auto slide_north = [](auto& grid, int row, int col)
        {
            int finalPos = row;
            for (int i = row - 1; i >= 0; i--)
                if (grid[i][col] == '.')
                    finalPos--;
                else
                    break;

            grid[row][col]      = '.';
            grid[finalPos][col] = 'O';
        };

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    slide_north(grid, i, j);
    };

    auto compute_load = [](const auto& grid)
    {
        int load = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    load += grid.size() - i;
        return load;
    };

    slide(grid);
    std::cout << compute_load(grid) << std::endl;
}