#include "../../utils/aoc-utils.cpp"
#include <numeric>

int64_t
shoelace_area(auto& verts)
{
    auto    prev = std::pair<int64_t, int64_t>{1, 1};
    int64_t area = 0;

    std::reverse(verts.begin(), verts.end());

    for (auto&& curr : verts)
    {
        area += prev.first * curr.second - prev.second * curr.first;
        prev = curr;
    }

    return area / 2;
}

int
main()
{
    auto directions = std::unordered_map<char, std::pair<int, int>>{
        {'0', {0, 1}}, {'1', {1, 0}}, {'2', {0, -1}}, {'3', {-1, 0}}};

    auto parse_line = [](const auto& s)
    {
        auto hex = aoc_utils::split_string(s, "(")[1];
        hex.pop_back();
        auto dir = hex.back();
        hex.pop_back();
        hex.erase(hex.begin());
        auto len = std::stoi(hex, nullptr, 16);

        return std::make_pair(dir, len);
    };

    auto input = aoc_utils::read_file_lines("src/day-18/input.txt") | std::views::transform(parse_line);
    auto start = std::pair<int64_t, int64_t>{0, 0};
    auto verts = std::vector<std::pair<int64_t, int64_t>>();

    verts.push_back(start);
    for (auto&& [dir, len] : input)
    {
        auto [dx, dy] = directions[dir];

        start = std::make_pair(start.first + dx * len, start.second + dy * len);
        verts.push_back(start);
    }

    int64_t perimeter = 0;
    for (auto&& [_, len] : input)
        perimeter += len;

    std::cout << perimeter + shoelace_area(verts) << std::endl;
}