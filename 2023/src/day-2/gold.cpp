#include "../../utils/aoc-utils.cpp"
#include <unordered_map>

int
tot_min_rgb(const std::vector<std::string>& sets)
{
    std::unordered_map<std::string, int> colorToMin{
        {"red", 0},
        {"green", 0},
        {"blue", 0},
    };

    auto split_set_values = [](auto s)
    { return split_string(s, ", "); };

    auto split_value_color = [](auto s)
    { return split_string(s, " "); };

    for (auto&& setPair : map_vector<std::string, std::vector<std::string>>(sets, split_set_values))
        for (auto&& valAndColor : map_vector<std::string, std::vector<std::string>>(setPair, split_value_color))
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
    auto split_sets = [](auto s)
    { return split_string(split_string(s, ": ")[1], "; "); };

    auto lines       = read_file_lines("src/day-2/input.txt");
    auto linesSets   = map_vector<std::string, std::vector<std::string>>(lines, split_sets);
    auto linesMinRgb = map_vector<std::vector<std::string>, int>(linesSets, tot_min_rgb);
    auto sum         = 0;

    for (auto&& v : linesMinRgb)
        sum += v;

    std::cout << sum << std::endl;
}