#include "../../utils/aoc-utils.cpp"
#include <unordered_map>

const std::unordered_map<std::string, int> colorsToMax{
    {"red", 12},
    {"green", 13},
    {"blue", 14},
};

bool
is_valid_set(const std::vector<std::string>& sets)
{
    auto split_set_values = [](auto s)
    { return split_string(s, ", "); };

    auto split_value_color = [](auto s)
    { return split_string(s, " "); };

    for (auto&& setPair : map_vector<std::string, std::vector<std::string>>(sets, split_set_values))
        for (auto&& valAndColor : map_vector<std::string, std::vector<std::string>>(setPair, split_value_color))
            if (atoi(valAndColor[0].c_str()) > colorsToMax.at(valAndColor[1]))
                return false;

    return true;
}

int
main()
{
    auto split_sets = [](auto s)
    { return split_string(split_string(s, ": ")[1], "; "); };

    auto lines     = read_file_lines("src/day-2/input.txt");
    auto linesSets = map_vector<std::string, std::vector<std::string>>(lines, split_sets);
    auto validSets = map_vector<std::vector<std::string>, bool>(linesSets, is_valid_set);
    auto sum       = 0;

    for (int i = 0; i < validSets.size(); i++)
        if (validSets[i])
            sum += i + 1;

    std::cout << sum << std::endl;
}