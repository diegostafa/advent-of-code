#include "../../utils/aoc-utils.cpp"
#include <thread>
#include <unordered_map>

namespace std
{
    template <>
    class hash<std::vector<std::string>>
    {
    public:
        std::size_t
        operator()(const std::vector<std::string>& vec) const
        {
            std::size_t hash = 0;
            for (const auto& str : vec)
            {
                hash = (hash * 127 + std::hash<std::string>()(str)) % std::numeric_limits<std::size_t>::max();
            }
            return hash;
        }
    };
}

int
main()
{
    auto grid = aoc_utils::read_file_lines("src/day-14/input.txt");

    auto slide_cycle = [](auto& grid)
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

        auto slide_south = [](auto& grid, int row, int col)
        {
            int finalPos = row;
            for (int i = row + 1; i < grid.size(); i++)
                if (grid[i][col] == '.')
                    finalPos++;
                else
                    break;

            grid[row][col]      = '.';
            grid[finalPos][col] = 'O';
        };

        auto slide_east = [](auto& grid, int row, int col)
        {
            int finalPos = col;
            for (int i = col + 1; i < grid[0].size(); i++)
                if (grid[row][i] == '.')
                    finalPos++;
                else
                    break;

            grid[row][col]      = '.';
            grid[row][finalPos] = 'O';
        };

        auto slide_west = [](auto& grid, int row, int col)
        {
            int finalPos = col;
            for (int i = col - 1; i >= 0; i--)
                if (grid[row][i] == '.')
                    finalPos--;
                else
                    break;

            grid[row][col]      = '.';
            grid[row][finalPos] = 'O';
        };

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    slide_north(grid, i, j);

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    slide_west(grid, i, j);

        for (int i = grid.size() - 1; i >= 0; i--)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    slide_south(grid, i, j);

        for (int i = 0; i < grid.size(); i++)
            for (int j = grid.size() - 1; j >= 0; j--)
                if (grid[i][j] == 'O')
                    slide_east(grid, i, j);
    };

    auto compute_load = [](const auto& grid)
    {
        auto load = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 'O')
                    load += grid.size() - i;
        return load;
    };

    auto slid      = std::unordered_map<std::vector<std::string>, int>();
    auto totCycles = 1000000000;

    for (int i = 0; i < totCycles; i++)
    {
        slid[grid] = i;
        slide_cycle(grid);

        if (slid.count(grid))
        {
            totCycles = (totCycles - i) % (i - slid[grid]);
            for (int j = 0; j < totCycles; j++)
                slide_cycle(grid);
            break;
        }
    }

    std::cout << compute_load(grid) << std::endl;
}