#include "../../utils/aoc-utils.cpp"

int
main()
{
    auto parse_line = [](const auto& s)
    { return aoc_utils::split_space(s) | std::views::drop(1) | std::views::transform(aoc_utils::to_int64); };

    auto input     = aoc_utils::read_file_lines("src/day-06/input.txt") | std::views::transform(parse_line);
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

    std::cout << compute_better_time(times[0], distances[0]) << std::endl;
}