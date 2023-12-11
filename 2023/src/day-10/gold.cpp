#include "../../utils/aoc-utils.cpp"
#include <deque>
#include <set>
#include <thread>

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

std::set<char> cornerSet = {
    {'S'},
    {'J'},
    {'7'},
    {'F'},
    {'L'},
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

std::pair<int, std::vector<std::vector<bool>>>
maxLoopSizeAndTrail(const auto& grid, const auto& curr, auto visited, int steps)
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
        return {steps, visited};

    visited[curr.first][curr.second] = true;

    std::vector<std::pair<int, int>> nextPos = {
        {curr.first, curr.second + 1},
        {curr.first, curr.second - 1},
        {curr.first + 1, curr.second},
        {curr.first - 1, curr.second},
    };

    int  maxSteps = 0;
    auto maxLoop  = visited;
    for (auto&& next : nextPos)
    {
        if (!illegalPosition(curr, next))
        {
            auto stepsAndLoop = maxLoopSizeAndTrail(grid, next, visited, steps + 1);

            if (stepsAndLoop.first >= maxSteps)
            {
                maxSteps = stepsAndLoop.first;
                maxLoop  = stepsAndLoop.second;
            }
        }
    }

    return {maxSteps, maxLoop};
}

void
flood(auto& trail, const std::pair<int, int>& start)
{
    auto illegalPosition = [&trail](const auto& p)
    {
        return (p.first < 0 || p.first >= trail.size()) ||
               (p.second < 0 || p.second >= trail[0].size()) ||
               (trail[p.first][p.second]);
    };

    if (illegalPosition(start))
        return;

    std::vector<std::pair<int, int>> wave;

    wave.reserve(trail.size() * 2);
    wave.push_back(start);
    int i = 0;

    while (i < wave.size())
    {
        auto curr = wave[i];

        trail[curr.first][curr.second] = true;

        std::vector<std::pair<int, int>> nextPos = {
            {curr.first, curr.second + 1},
            {curr.first, curr.second - 1},
            {curr.first + 1, curr.second},
            {curr.first - 1, curr.second},
        };

        for (auto&& next : nextPos)
            if (!illegalPosition(next) && std::find(wave.begin(), wave.end(), next) == wave.end())
                wave.push_back(next);
        i++;
    }
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

    auto sizeAndTrail = maxLoopSizeAndTrail(grid, start, visited, 0);
    auto trail        = sizeAndTrail.second;

    for (int i = 0; i < trail.size(); i++)
        flood(trail, {i, 0});

    for (int i = 0; i < trail.size(); i++)
        flood(trail, {i, trail[0].size() - 1});

    for (int i = 0; i < trail[0].size(); i++)
        flood(trail, {0, i});

    for (int i = 0; i < trail[0].size(); i++)
        flood(trail, {trail.size() - 1, i});

    int area = 0;
    for (int i = 0; i < trail.size(); i++)
        for (int j = 0; j < trail[i].size(); j++)
            if (!trail[i][j])
                area++;

    std::cout << area << std::endl;
}
