#include "../../utils/aoc-utils.cpp"
#include <ranges>
#include <unordered_map>

const std::unordered_map<std::string, int> colorsToMax{
    {"red", 12},
    {"green", 13},
    {"blue", 14},
};

bool
is_valid_set(const std::vector<std::string>& sets)
{
    auto split_set_values = [](const auto& s)
    { return aoc_utils::split_string(s, ", "); };

    auto split_value_color = [](const auto& s)
    { return aoc_utils::split_string(s, " "); };

    for (auto&& setPair : std::views::transform(sets, split_set_values))
        for (auto&& valAndColor : std::views::transform(setPair, split_value_color))
            if (atoi(valAndColor[0].c_str()) > colorsToMax.at(valAndColor[1]))
                return false;

    return true;
}

int
main()
{
    auto split_sets = [](const auto& s)
    { return aoc_utils::split_string(aoc_utils::split_string(s, ": ")[1], "; "); };

    auto validSets =
        aoc_utils::read_file_lines("src/day-02/input.txt") |
        std::views::transform(split_sets) |
        std::views::transform(is_valid_set);

    auto sum = 0;
    for (int i = 0; i < validSets.size(); i++)
        if (validSets[i])
            sum += i + 1;

    std::cout << sum << std::endl;
}