#include "../../utils/aoc-utils.cpp"
#include <ranges>

int
main()
{
    auto split_sets = [](const auto& s)
    { return aoc_utils::split_string(aoc_utils::split_string(s, ": ")[1], " | "); };

    auto split_numbers = [](const auto& v)
    {
        auto sx  = aoc_utils::split_string(v[0], " ");
        auto dx  = aoc_utils::split_string(v[1], " ");
        auto vsx = std::vector<int>();
        auto vdx = std::vector<int>();

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

    auto games = aoc_utils::read_file_lines("src/day-04/input.txt") |
                 std::views::transform(split_sets) |
                 std::views::transform(split_numbers);

    auto matches = std::vector<int>(games.size());
    auto copies  = std::vector<int>(games.size(), 1);

    for (int i = 0; i < games.size(); ++i)
        for (auto&& hand_val : games[i].second)
            for (auto&& win_val : games[i].first)
                if (hand_val == win_val)
                    matches[i]++;

    for (int i = 0; i < matches.size(); ++i)
        for (int j = 1; j <= matches[i]; ++j)
            copies[i + j] += copies[i];

    int sum = 0;
    for (auto&& c : copies)
        sum += c;

    std::cout << sum << std::endl;
}