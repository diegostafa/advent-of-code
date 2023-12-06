#include "../../utils/aoc-utils.cpp"

auto split_space = [](const auto& s)
{ return aoc_utils::split_string(s, " "); };

auto to_num = [](const auto& s)
{ return (int64_t)std::stoll((s.c_str())); };

int
main()
{
    auto parse_line = [](const auto& s)
    { return split_space(s) | std::views::drop(1) | std::views::transform(to_num); };

    auto input     = aoc_utils::read_file_lines("input/day-06/input.txt") | std::views::transform(parse_line);
    auto times     = input[0];
    auto distances = input[1];

    auto compute_better_time = [](auto time, auto dist)
    {
        int64_t better_results = 0;
        for (int64_t speed = 0; speed < time; speed++)
            if (speed * (time - speed) > dist)
                better_results++;

        return better_results;
    };

    int64_t sum = 1;
    for (int64_t i = 0; i < times.size(); i++)
        sum *= compute_better_time(times[i], distances[i]);

    std::cout << sum << std::endl;
}