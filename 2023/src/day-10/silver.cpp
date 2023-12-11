#include "../../utils/aoc-utils.cpp"

std::pair<int, int> start;

const std::pair<int, int> goUp    = {-1, 0};
const std::pair<int, int> goDown  = {1, 0};
const std::pair<int, int> goLeft  = {0, -1};
const std::pair<int, int> goRight = {0, 1};

std::unordered_map<char, std::vector<std::pair<int, int>>> linkMap = {
    {'S', {goUp, goDown, goLeft, goRight}},
    {'J', {goLeft, goUp}},
    {'|', {goUp, goDown}},
    {'-', {goLeft, goRight}},
    {'7', {goLeft, goDown}},
    {'L', {goUp, goRight}},
    {'F', {goDown, goRight}},
    {'.', {}},
};

bool
isLinked(const auto& grid, const auto& currPos, const auto& nextPos)
{
    auto cCurr = grid[currPos.first][currPos.second];
    auto cNext = grid[nextPos.first][nextPos.second];
    auto dx    = nextPos.first - currPos.first;
    auto dy    = nextPos.second - currPos.second;
    auto links = linkMap[cCurr];
    return std::find(links.begin(), links.end(), std::make_pair(dx, dy)) != links.end();
}

int
maxLoopSize(const auto& grid, const auto& curr, auto visited, int steps)
{
    auto compute_distance = [](const auto& p)
    { return std::abs(p.first - start.first) + std::abs(p.second - start.second); };

    auto illegalPosition = [&grid, &visited](const auto& curr, const auto& p)
    {
        return (p.first < 0 || p.first >= grid.size()) ||
               (p.second < 0 || p.second >= grid[0].size()) ||
               (grid[p.first][p.second] == '.') ||
               (!isLinked(grid, curr, p));
    };

    if (visited[curr.first][curr.second])
        return steps;

    visited[curr.first][curr.second] = true;

    std::vector<std::pair<int, int>> nextPos = {
        {curr.first, curr.second + 1},
        {curr.first, curr.second - 1},
        {curr.first + 1, curr.second},
        {curr.first - 1, curr.second},
    };

    int maxSteps = 0;
    for (auto&& next : nextPos)
        if (!illegalPosition(curr, next))
            maxSteps = std::max(maxSteps, maxLoopSize(grid, next, visited, steps + 1));

    return maxSteps;
}

int
main()
{
    auto grid = aoc_utils::read_file_lines("input/day-10/input.txt");

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'S')
                start = {i, j};

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size()));
    std::cout << maxLoopSize(grid, start, visited, 0) / 2 << std::endl;
}
