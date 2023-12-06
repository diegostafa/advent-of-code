#include "../../utils/aoc-utils.cpp"
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

int
main()
{
    auto input = aoc_utils::split_string(aoc_utils::read_file("input/day-05/input.txt"), "\n\n");
    auto seeds = parse_line(split_line(input[0])[1]);
    auto maps  = input | std::views::drop(1) | std::views::transform(parse_block);

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

    std::vector<int64_t> finalDest;
    finalDest.reserve(seeds.size());

    for (auto&& s : seeds)
        finalDest.push_back(get_final_dest(s));

    std::cout << *std::min_element(finalDest.begin(), finalDest.end()) << std::endl;
}