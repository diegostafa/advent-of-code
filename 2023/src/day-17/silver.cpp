#include "../../utils/aoc-utils.cpp"
#include <map>
#include <numeric>
#include <unordered_set>

namespace std
{
    template <>
    class hash<std::pair<int, int>>
    {
    public:
        std::size_t
        operator()(const std::pair<int, int>& p) const
        {
            return std::hash<int>()(p.first) + std::hash<int>()(p.second);
        }
    };

    template <>
    class hash<std::tuple<std::pair<int, int>, std::pair<int, int>, int>>
    {
    public:
        std::size_t
        operator()(const std::tuple<std::pair<int, int>, std::pair<int, int>, int>& p) const
        {
            return std::hash<std::pair<int, int>>()(std::get<0>(p)) +
                   std::hash<std::pair<int, int>>()(std::get<1>(p)) +
                   std::hash<int>()(std::get<2>(p));
        }
    };
}

auto INF        = 9999999;
auto grid       = aoc_utils::read_file_lines("src/day-17/input.txt");
auto rows       = grid.size();
auto cols       = grid[0].size();
auto start      = std::pair<int, int>{0, 0};
auto end        = std::pair<int, int>{rows - 1, cols - 1};
auto startValue = grid[start.first][start.second] - '0';
auto endValue   = grid[end.first][end.second] - '0';

const auto directions = std::vector<std::pair<int, int>>{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int
computeMinHeat(auto& memo, auto trail, const auto& pos, const auto& currDir, int stepsLeft)
{
    trail[pos] += 1;
    if (pos == end)
        return 0;

    auto minHeat = INF;
    for (auto&& dir : directions)
    {
        auto newPos = aoc_utils::sum_pair(pos, dir);
        if (!aoc_utils::in_bound(grid, newPos))
            continue;

        if (trail.count(pos) && trail[pos] > 1)
            continue;

        auto steps = dir == currDir ? stepsLeft - 1 : 3;
        if (stepsLeft == 0)
            continue;

        auto posValue = grid[newPos.first][newPos.second] - '0';
        minHeat       = std::min({minHeat, posValue + computeMinHeat(memo, trail, newPos, dir, steps)});
    }

    return minHeat;
}

int
main()
{
    auto memo    = std::unordered_map<std::tuple<std::pair<int, int>, std::pair<int, int>, int>, int>();
    auto dir     = std::pair<int, int>{0, 0};
    auto visited = std::unordered_map<std::pair<int, int>, int>();

    std::cout << computeMinHeat(memo, visited, start, dir, 3) << std::endl;
}