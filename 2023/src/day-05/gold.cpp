#include "../../utils/aoc-utils.cpp"
#include <algorithm>
#include <math.h>
#include <ranges>

auto split_space = [](const auto& s)
{ return aoc_utils::split_string(s, " "); };

auto split_line = [](const auto& s)
{ return aoc_utils::split_string(s, "\n"); };

auto to_num = [](const auto& s)
{ return (int64_t)std::stoll((s.c_str())); };

auto parse_line = [](const auto& l)
{ return split_space(l) | std::views::transform(to_num); };

auto parse_block = [](const auto& s)
{ return split_line(s) | std::views::drop(1) | std::views::transform(parse_line); };

auto
map_range_to_vec(const auto& maps)
{
    std::vector<std::vector<std::vector<int64_t>>> res;
    for (auto&& map : maps)
    {
        std::vector<std::vector<int64_t>> vmap;
        for (auto&& row : map)
        {
            std::vector<int64_t> vline;
            for (auto&& val : row)
                vline.push_back(val);

            vmap.push_back(vline);
        }
        res.push_back(vmap);
    }
    return res;
}

int
main()
{
    auto input = aoc_utils::split_string(aoc_utils::read_file("input/day-05/input.txt"), "\n\n");
    auto seeds = parse_line(split_line(input[0])[1]);
    auto maps  = map_range_to_vec(input | std::views::drop(1) | std::views::transform(parse_block));

    auto get_final_dest = [&maps](auto& seed)
    {
        auto get_next_dest = [](auto& pos, auto& map)
        {
            for (auto&& row : map)
            {
                auto dest   = row[0];
                auto source = row[1];
                auto range  = row[2];

                if (pos >= source && pos <= source + range - 1)
                    return dest + abs(pos - source);
            }
            return pos;
        };

        int64_t currPos = seed;
        for (auto&& map : maps)
            currPos = get_next_dest(currPos, map);

        return currPos;
    };

    int64_t min = 9999999999999;
    for (int64_t i = 0; i < seeds.size(); ++i)
    {
        auto seedStart = seeds[i];
        auto seedEnd   = seedStart + seeds[++i];

        for (int64_t j = seedStart; j < seedEnd; j = ++j)
            min = std::min(min, get_final_dest(j));
    }

    std::cout << min << std::endl;
}