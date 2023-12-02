#include "../../utils/aoc-utils.cpp"
#include <ranges>
#include <unordered_map>

int
tot_min_rgb(const std::vector<std::string>& sets)
{
    std::unordered_map<std::string, int> colorToMin{
        {"red", 0},
        {"green", 0},
        {"blue", 0},
    };

    auto split_set_values = [](const auto& s)
    { return aoc_utils::split_string(s, ", "); };

    auto split_value_color = [](const auto& s)
    { return aoc_utils::split_string(s, " "); };

    for (auto&& setPair : std::views::transform(sets, split_set_values))
        for (auto&& valAndColor : std::views::transform(setPair, split_value_color))
        {
            auto  val    = atoi(valAndColor[0].c_str());
            auto& minVal = colorToMin[valAndColor[1]];

            if (val > minVal)
                minVal = val;
        }

    return colorToMin["red"] * colorToMin["green"] * colorToMin["blue"];
}

int
main()
{
    auto split_sets = [](const auto& s)
    { return aoc_utils::split_string(aoc_utils::split_string(s, ": ")[1], "; "); };

    auto linesMinRgb =
        aoc_utils::read_file_lines("src/day-2/input.txt") |
        std::views::transform(split_sets) |
        std::views::transform(tot_min_rgb);

    auto sum = 0;
    for (auto&& v : linesMinRgb)
        sum += v;

    std::cout << sum << std::endl;
}