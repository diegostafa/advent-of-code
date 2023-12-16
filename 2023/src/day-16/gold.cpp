#include "../../utils/aoc-utils.cpp"
#include <set>

std::pair<int, int>
sum_pair(const auto& p1, const auto& p2)
{
    return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

int
trail_size(const auto& trail)
{
    int sum = 0;
    for (auto&& row : trail)
        for (auto&& cell : row)
            if (cell == '#')
                sum++;
    return sum;
}

std::vector<std::pair<int, int>>
compute_refl(char mirror, const auto& dir)
{
    auto [row, col] = dir;

    if (mirror == '.' ||
        mirror == '|' && col == 0 ||
        mirror == '-' && row == 0)
        return {dir};

    if (mirror == '/')
        return {{col * -1, row * -1}};

    if (mirror == '\\')
        return {{col, row}};

    if (mirror == '|' && row == 0)
        return {{-1, 0}, {1, 0}};

    if (mirror == '-' && col == 0)
        return {{0, -1}, {0, 1}};

    return {dir};
}

void
simulate_beam(auto& visited, const auto& grid, auto& trail, const auto& pos, const auto& dir)
{
    if (!aoc_utils::in_bound(grid, pos) || visited.contains({pos, dir}))
        return;

    visited.insert({pos, dir});
    trail[pos.first][pos.second] = '#';

    for (auto&& newDir : compute_refl(grid[pos.first][pos.second], dir))
        simulate_beam(visited, grid, trail, sum_pair(pos, newDir), newDir);
}

int
max_beam_size(const auto& grid)
{
    auto fire_beam = [&grid](const std::pair<int, int>& pos, const std::pair<int, int>& dir)
    {
        auto trail   = grid;
        auto visited = std::set<std::pair<std::pair<int, int>, std::pair<int, int>>>();
        simulate_beam(visited, grid, trail, pos, dir);
        return trail_size(trail);
    };

    auto maxSize = 0;
    auto rows    = grid.size();
    auto cols    = grid[0].size();

    for (int i = 0; i < rows; i++)
        maxSize = std::max({maxSize, fire_beam({i, 0}, {0, 1})});

    for (int i = 0; i < cols; i++)
        maxSize = std::max({maxSize, fire_beam({0, i}, {1, 0})});

    for (int i = 0; i < rows; i++)
        maxSize = std::max({maxSize, fire_beam({i, cols - 1}, {0, -1})});

    for (int i = 0; i < cols; i++)
        maxSize = std::max({maxSize, fire_beam({rows - 1, i}, {-1, 0})});

    return maxSize;
}

int
main()
{
    auto grid = aoc_utils::read_file_lines("src/day-16/input.txt");
    std::cout << max_beam_size(grid) << std::endl;
}