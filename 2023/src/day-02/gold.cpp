#include "../../utils/aoc-utils.cpp"
#include <numeric>
#include <ranges>
#include <unordered_map>

int
tot_min_rgb(const std::vector<std::string>& sets)
{
    auto colorToMin = std::unordered_map<std::string, int>{
        {"red", 0},
        {"green", 0},
        {"blue", 0},
    };

    auto split_set_values = [](const auto& s)
    { return aoc_utils::split_string(s, ", "); };

    auto split_value_color = [](const auto& s)
    {
        auto split = aoc_utils::split_string(s, " ");
        return std::make_pair(atoi(split[0].c_str()), split[1]);
    };

    for (auto&& setPair : std::views::transform(sets, split_set_values))
        for (auto&& [value, color] : std::views::transform(setPair, split_value_color))
            colorToMin[color] = std::max({colorToMin[color], value});

    return colorToMin["red"] * colorToMin["green"] * colorToMin["blue"];
}

int
main()
{
    auto split_sets = [](const auto& s)
    { return aoc_utils::split_string(aoc_utils::split_string(s, ": ")[1], "; "); };

    auto linesMinRgb =
        aoc_utils::read_file_lines("src/day-02/input.txt") |
        std::views::transform(split_sets) |
        std::views::transform(tot_min_rgb);

    std::cout << std::accumulate(linesMinRgb.begin(), linesMinRgb.end(), 0) << std::endl;
}