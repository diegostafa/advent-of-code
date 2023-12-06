#include "../../utils/aoc-utils.cpp"
#include <math.h>
#include <ranges>

int
main()
{
    auto split_sets = [](const auto& s)
    { return aoc_utils::split_string(aoc_utils::split_string(s, ": ")[1], " | "); };

    auto split_numbers = [](const auto& v)
    {
        auto sx = aoc_utils::split_string(v[0], " ");
        auto dx = aoc_utils::split_string(v[1], " ");

        std::vector<int> vsx;
        std::vector<int> vdx;

        vsx.reserve(sx.size());
        vdx.reserve(dx.size());

        for (auto&& s : sx)
            if (atoi(s.c_str()) != 0)
                vsx.push_back(atoi(s.c_str()));

        for (auto&& d : dx)
            if (atoi(d.c_str()) != 0)
                vdx.push_back(atoi(d.c_str()));

        return std::make_pair(vsx, vdx);
    };

    auto games =
        aoc_utils::read_file_lines("input/day-04/input.txt") |
        std::views::transform(split_sets) |
        std::views::transform(split_numbers);

    std::vector<int> matches(games.size());

    for (int i = 0; i < games.size(); ++i)
        for (auto&& hand_val : games[i].second)
            for (auto&& win_val : games[i].first)
                if (hand_val == win_val)
                    matches[i]++;

    int sum = 0;
    for (auto&& m : matches)
        sum += std::pow(2, m - 1);

    std::cout << sum << std::endl;
}