#include "../../utils/aoc-utils.cpp"
#include <queue>

void
flood(std::vector<std::vector<bool>>& trail, const std::pair<int, int>& start)
{
    if (!aoc_utils::in_bound(trail, start) || trail[start.first][start.second])
        return;

    const auto directions = std::vector<std::pair<int, int>>{
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

    std::queue<std::pair<int, int>> wave;
    wave.push(start);

    while (!wave.empty())
    {
        auto curr = wave.front();
        wave.pop();

        for (const auto& dir : directions)
        {
            auto nextPos = std::pair<int, int>{curr.first + dir.first, curr.second + dir.second};
            if (!aoc_utils::in_bound(trail, nextPos) || trail[nextPos.first][nextPos.second])
                continue;

            trail[nextPos.first][nextPos.second] = true;
            wave.push(nextPos);
        }
    }
}

int
main()
{
    std::unordered_map<char, std::pair<int, int>> directions = {
        {'R', {0, 1}},
        {'L', {0, -1}},
        {'D', {1, 0}},
        {'U', {-1, 0}},
    };

    auto get_max_sz = [](const auto& input)
    {
        auto w = 0;
        auto h = 0;

        for (auto&& [d, len, c] : input)
        {
            if (d == 'D')
                h += len;
            else if (d == 'R')
                w += len;
        }
        return std::make_pair(w, h);
    };

    auto parse_line = [](const auto& s)
    {
        auto values = aoc_utils::split_space(s);
        return std::make_tuple(values[0][0], atoi(values[1].c_str()), values[2]);
    };

    auto dig = [&directions](auto& grid, const auto& start, char d, int len)
    {
        auto dir = directions.at(d);
        for (int i = 0; i < len; i++)
            grid[start.first + dir.first * i][start.second + dir.second * i] = true;

        return std::make_pair(start.first + dir.first * len, start.second + dir.second * len);
    };

    auto input  = aoc_utils::read_file_lines("src/day-18/input.txt") | std::views::transform(parse_line);
    auto [w, h] = get_max_sz(input);
    auto grid   = std::vector<std::vector<bool>>(h * 1.5, std::vector<bool>(w * 1.5));
    auto start  = std::pair<int, int>{h, w};

    for (auto&& [dir, len, _] : input)
        start = dig(grid, start, dir, len);

    for (int i = 0; i < grid.size(); i++)
        flood(grid, {i, 0});

    for (int i = 0; i < grid.size(); i++)
        flood(grid, {i, grid[0].size() - 1});

    for (int i = 0; i < grid[0].size(); i++)
        flood(grid, {0, i});

    for (int i = 0; i < grid[0].size(); i++)
        flood(grid, {grid.size() - 1, i});

    int tsize = 0;
    for (auto&& [d, l, c] : input)
        tsize += l;

    int fsize = 0;
    for (auto&& row : grid)
        for (auto&& cell : row)
            if (!cell)
                fsize++;

    std::cout << tsize + fsize << std::endl;
}